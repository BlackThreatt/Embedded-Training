# stm32-cli-driver

Portfolio Project #1: a UART driver for the STM32F429 built from scratch
in three explicit layers, with interrupt-driven, ring-buffer-backed
transmit/receive, a project-wide `error_t` error-handling convention,
and a small logging module built on top of it.

## Architecture

The driver is split into three main layers with a optional logger module. 
Only the HAL layer touches peripheral registers directly; everything above
it talks in terms of named types, config structs, and `error_t` return codes.

```
 ┌────────────────────────────────────────────────────────────────┐
 │                        Application                             │
 │                         (main.c)                               │
 │                                                                │
 │   CLI system, To be implemented                                │
 └────────────────────────────────┬───────────────────────────────┘
                                  │
                                  ▼
  ----------------------------------------------------------------
 |                        Logger Module                           |
 |                    (logger.c)                                  |
 |                                                                |
 |   LOG_DEBUG/LOG_INFO/LOG_ERROR                                 |
  ----------------------------------------------------------------
                                  │
                                  ▼
 ┌───────────────────────────────────────────────────────────────┐
 │                       Driver layer                            │
 │            (uart_driver.c/.h, gpio_driver.c/.h)               │
 │                                                               │
 │  UART_DRV_Init / Transmit / Receive / USART1_IRQHandler       │
 │  GPIO_DRV_Init / Write / Read / Toggle                        │
 │                                                               │
 │  - owns USART_Config_t / GPIO_Config_t (policy, not registers)│
 │  - owns TX/RX ring buffers (RingBuffer.c/.h)                  │
 │  - board_config.h: named port/pin/AF constants, no raw values │
 │    scattered through driver logic                             │
 │  - every function returns error_t, propagated from HAL,       │
 │    never swallowed                                            │
 └───────────────────────────────┬───────────────────────────────┘
                                 │  calls into
                                 ▼
 ┌───────────────────────────────────────────────────────────────┐
 │                         HAL layer                             │
 │              (uart_hal.c/.h, gpio_hal.c/.h)                   │
 │                                                               │
 │  HAL_UART_SetWordLength / SetParity / SetStopBits / ...       │
 │  HAL_GPIO_SetMode / SetOutputType / SetSpeed / ...            │
 │                                                               │
 │  - the ONLY files that read/write USARTx->CRx, GPIOx->MODER,  │
 │    etc.                                                       │
 │  - one function per register field, no combined "configure    │
 │    everything at once" calls                                  │
 │  - validates arguments (NULL, range, enum) and returns        │
 │    error_t instead of silently accepting bad input            │
 └───────────────────────────────┬───────────────────────────────┘
                                 │  reads/writes
                                 ▼
 ┌───────────────────────────────────────────────────────────────┐
 │                  STM32F429 peripheral registers               │
 │                 (USART1, GPIOA — via CMSIS)                   │
 └───────────────────────────────────────────────────────────────┘
```

### Why three layers

- **HAL** is the only place register addresses and bit positions
  appear. Porting to a different STM32 family means rewriting HAL
  function bodies, not the driver or application code that calls
  them.
- **Driver** owns *policy*: what a full UART configuration looks like,
  how RX/TX buffering works, what happens on a full ring buffer. It
  never reads or writes a register itself.
- **Application** (logging, `main.c`) only ever calls driver-layer
  functions and never sees `USART_TypeDef`/`GPIO_TypeDef` at all.

## Modules

| File(s)                          | Layer       | Responsibility                                      |
|-----------------------------------|-------------|------------------------------------------------------|
| `uart_hal.c` / `uart_hal.h`        | HAL         | USART1 register access: word length, parity, stop bits, baud rate, oversampling, mode, interrupt enable/disable, TX/RX ready checks |
| `gpio_hal.c` / `gpio_hal.h`        | HAL         | GPIO register access: mode, output type, speed, pull, alternate function, pin read/write/toggle |
| `uart_driver.c` / `uart_driver.h`  | Driver      | `USART_Config_t`, `UART_DRV_Init/Transmit/Receive`, TX/RX ring buffers, `USART1_IRQHandler` |
| `gpio_driver.c` / `gpio_driver.h`  | Driver      | `GPIO_Pin_t`, `GPIO_Config_t`, `GPIO_DRV_Init/Write/Read/Toggle` |
| `board_config.h`                   | Driver      | Named board-wiring constants (debug UART TX/RX port, pin, alternate function) |
| `RingBuffer.c` / `RingBuffer.h`     | Driver support | Fixed-size power-of-two ring buffer used for TX/RX buffering |
| `error.h`                           | Shared      | `error_t` enum shared by every HAL and driver function |
| `logger.c` / `logger.h`             | Application | `LOG_DEBUG`/`LOG_INFO`/`LOG_ERROR` macros built on the UART driver, compiled away when `RELEASE` is defined |
| `main.c`                            | Application | Example init/write/read exercising the driver |

## Error handling

Every HAL and driver function returns `error_t`:

```c
typedef enum {
  ERR_OK            = 0,
  ERR_NULL_PTR      = -1,
  ERR_INVALID_PARAM = -2,
  ERR_TIMEOUT       = -3,
  ERR_BUSY          = -4,
  ERR_BUFFER_FULL   = -5,
  ERR_BUFFER_EMPTY  = -6,
  ERR_NOT_INIT      = -7,
  ERR_HW_FAULT      = -8,
} error_t;
```

Rules followed throughout the driver:

- `ERR_OK` (0) means success; anything else is a failure.
- Every function that can fail returns `error_t`; values that used to
  come back as a plain return type (`GPIO_PinState`, `uint8_t`, `bool`)
  are now written through an `out_*` pointer parameter instead.
- A caller never ignores a returned `error_t`. Every HAL/driver
  declaration is marked `__attribute__((warn_unused_result))` on
  GCC/Clang so an ignored result is a compile-time warning.
- Errors are propagated up unmodified; the driver layer forwards the
  first failure from HAL rather than swallowing or reinterpreting it.
  The application layer is where a failure is finally acted on (retry,
  halt, log).

## Data flow: interrupt-driven TX/RX

Both transmit and receive are non-blocking from the caller's point of
view:

- `UART_DRV_Transmit` pushes bytes into a TX ring buffer and enables
  the TXE interrupt; it returns as soon as the bytes are queued (or
  `ERR_BUFFER_FULL` for whichever bytes did not fit).
- `USART1_IRQHandler` drains the TX ring buffer into the data register
  while TXE is set, and disables the TX interrupt once the buffer is
  empty.
- Received bytes are pushed into an RX ring buffer from the same ISR
  while RXNE is set.
- `UART_DRV_Receive` pulls already-received bytes out of the RX ring
  buffer; it returns `ERR_BUFFER_EMPTY` if fewer bytes are available
  than requested.

## Status

This is the first portfolio milestone: a complete, three-layer,
interrupt-driven UART driver for a single debug USART instance, with
a consistent error-handling convention applied across HAL, driver, and
a logging module built on top. GPIO exists as a supporting driver for
the UART's TX/RX alternate-function pins.

Not yet implemented / known limitations:
- Single USART instance only (hardcoded to USART1); not
  multi-instance.
- No RCC/clock configuration module yet; peripheral clock frequency is
  a hardcoded constant pending a dedicated clock driver.
- No timeout handling on blocking-style waits.
