#include "common/RingBuffer.h"
#include "drivers/gpio.h"
#include "drivers/uart.h"
#include "stm32f4xx.h"
#include <stdint.h>

uint8_t uart_write(UART_Typedef *UARTx, RingBuffer_t *rb, uint8_t *data,
                   uint32_t len);
uint8_t uart_read(UART_Typedef *UARTx, RingBuffer_t *rb);

GPIO_Config_t gpioConf;
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
  UART_Init(T_USART1);
  
  // Set interrupt priority and enable it
  NVIC_SetPriority(USART1_IRQn, 5);
  NVIC_EnableIRQ(USART1_IRQn);
  
  uint8_t buf[3] = {65, 66, 67};
  uart_write(T_USART1, &uartTxRb, buf, 3);
  
  while (1) {
  }
}

uint8_t uart_write(UART_Typedef *UARTx, RingBuffer_t *rb, uint8_t *data,
                   uint32_t len) {
  for (uint32_t iter = 0; iter < len; iter++) {
    if (is_rb_full(rb)) {
      // Enable TXE interrupt
      UARTx->CR1 |= (1U << 7);
      return 0;
    } else {
      rb_push(rb, data[iter]);
      UARTx->CR1 |= (1U << 7);
    }
  }
  return 1;
}

uint8_t uart_read(UART_Typedef *UARTx, RingBuffer_t *rb) {
  uint8_t byte;
  rb_pop(rb, &byte);
  return byte;
}

void USART1_IRQHandler() {
  // check TXE bit status
  uint8_t byte = 0;
  if (T_USART1->SR & (1U << 7)) {
    if (rb_pop(&uartTxRb, &byte)) {
      UART_Transmit(T_USART1, byte);
    } else {
      // Clear TXE bit
      T_USART1->CR1 &= ~(1U << 7);
    }
  }
  // Check RXNE bit status
  if (T_USART1->SR & (1U << 5)) {
    byte = UART_Receive(T_USART1);
    if (!rb_push(&uartRxRb, byte)) {
      uint8_t oldData;
      rb_pop(&uartRxRb, &oldData);
      rb_push(&uartRxRb, byte);
    }
  }
}
