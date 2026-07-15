#include <stdint.h>

#define UART1_BASE 0x40011000UL

#define USART1_SR (*(volatile uint32_t *)UART1_BASE)
#define USART1_DR (*(volatile uint32_t *)(UART1_BASE + 0x4))
#define USART1_BRR (*(volatile uint32_t *)(UART1_BASE + 0x8))
#define USART1_CR1 (*(volatile uint32_t *)(UART1_BASE + 0xc))
#define USART1_CR2 (*(volatile uint32_t *)(UART1_BASE + 0x10))
#define USART1_CR3 (*(volatile uint32_t *)(UART1_BASE + 0x14))
#define USART1_GTPR (*(volatile uint32_t *)(UART1_BASE + 0x18))

void uart_init_ptr(void) {
  USART1_CR1 |= (1U << 13);
  USART1_BRR = 0x0683;
  USART1_CR1 |= (1U << 3);
}

void uart_send_ptr(uint8_t byte) {
  while (!(USART1_SR & (1U << 7))) {
  }
  USART1_DR = byte;
}
