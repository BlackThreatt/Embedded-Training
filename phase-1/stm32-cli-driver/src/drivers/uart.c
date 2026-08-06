#include "uart.h"
#include <stdint.h>

void UART_Init(UART_Typedef *UARTx) {
  // Enable USART
  UARTx->CR1 |= (1U << 13);
  // Set word length to 8B
  UARTx->CR1 &= ~(1U << 12);
  // Set STOP bits to 1
  UARTx->CR2 &= ~(3U << 12);
  /* Configure Baudrate
   * USARTDIV = Fck / (16 * Baud Rate)
   *          = 16MHz / (16 * 115200)
   *          = 16000000 / 1843200 = 8.6805
   * Mantissa = 0x8
   * Fraction = 0.6805 * 16 = 10.88 = 11 => 0xB
   * BRR = 0x8B
   */
  UARTx->BRR = 0x008B;
  // Enable RXNEIE interrupt
  UARTx->CR1 |= (1U << 5);
  // Enable transmitter TE
  UARTx->CR1 |= (1U << 3);
  // Enable reciever RE
  UARTx->CR1 |= (1U << 2);
}

void UART_Transmit(UART_Typedef *UARTx, uint8_t byte) { UARTx->DR = byte; }
uint8_t UART_Receive(UART_Typedef *UARTx) { return (UARTx->DR & 0xFF); }
