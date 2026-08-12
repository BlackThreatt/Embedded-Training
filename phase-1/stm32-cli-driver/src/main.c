#include "common/RingBuffer.h"
#include "drivers/gpio.h"
#include "drivers/uart_driver.h"
#include "stm32f4xx.h"
#include <stdint.h>

uint8_t uart_write(USART_TypeDef *UARTx, RingBuffer_t *rb, uint8_t *data,
                   uint32_t len);
uint8_t uart_read(USART_TypeDef *UARTx, RingBuffer_t *rb);

GPIO_Config_t gpioConf;
USART_Config_t uartConf;
RingBuffer_t uartRxRb;
RingBuffer_t uartTxRb;

int main(void) {
  // Enable GPIOA clock
  RCC->AHB1ENR |= (1U << 0);
  // Enable USART1 Clock
  RCC->APB2ENR |= (1U << 4);

  gpioConf.pins = (1U << 9) | (1U << 10);
  // Set mode to Alternate Function
  gpioConf.mode = 2U;
  // Set AF_H to AF7;
  gpioConf.AF_H = 7U;
  GPIO_Set_Config(T_GPIOA, &gpioConf);

  // Initialize USART1
  uartConf.baudrate = 115200;
  uartConf.flow_control = UART_HWCONTROL_NONE;
  uartConf.mode = UART_MODE_TX_RX;
  uartConf.parity = UART_PARITY_NONE;
  uartConf.stop_bits = UART_STOPBITS_1;
  uartConf.oversampling = UART_OVERSAMPLING_16;
  uartConf.word_length = UART_WORDLENGTH_8B;
  uartConf.it_flags = UART_INTERRUPT_RXNEIE;

  UART_Init(USART1, &uartConf);

  // Set interrupt priority and enable it
  NVIC_SetPriority(USART1_IRQn, 5);
  NVIC_EnableIRQ(USART1_IRQn);

  uint8_t buf[3] = {65, 66, 67};
  uart_write(USART1, &uartTxRb, buf, 3);

  while (1) {
  }
}

uint8_t uart_write(USART_TypeDef *UARTx, RingBuffer_t *rb, uint8_t *data,
                   uint32_t len) {
  for (uint32_t iter = 0; iter < len; iter++) {
    if (RingBuf_IsFull(rb)) {
      UART_EnableIT(UARTx, UART_INTERRUPT_TXEIE);
      return 0;
    } else {
      RingBuf_Push(rb, data[iter]);
      UART_EnableIT(UARTx, UART_INTERRUPT_TXEIE);
    }
  }
  return 1;
}

uint8_t uart_read(USART_TypeDef *UARTx, RingBuffer_t *rb) {
  uint8_t byte;
  RingBuf_Pop(rb, &byte);
  return byte;
}

void USART1_IRQHandler() {
  // check TXE bit status
  uint8_t byte = 0;

  if (UART_GetFlagStatus(USART1, UART_FLAG_TXE) == 1) {

    if (RingBuf_Pop(&uartTxRb, &byte)) {
      UART_Transmit(USART1, byte);
    } else {
      // Clear TXE bit
      UART_DisableIT(USART1, UART_INTERRUPT_TXEIE);
    }
  }
  // Check RXNE bit status
  if (UART_GetFlagStatus(USART1, UART_FLAG_RXNE) == 1) {
    byte = UART_Receive(USART1);
    if (RingBuf_Push(&uartRxRb, byte) == 0) {
      uint8_t oldData;
      RingBuf_Pop(&uartRxRb, &oldData);
      RingBuf_Push(&uartRxRb, byte);
    }
  }
}
