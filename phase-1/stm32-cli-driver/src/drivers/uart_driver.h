#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#include "hal_usart.h"
#include <stdbool.h>

typedef struct {
  uint32_t baudrate;
  UART_WordLength_t word_length;    // UART_WORDLEN_8B / 9B
  UART_Parity_t parity;             // UART_PARITY_NONE / ODD / EVEN
  UART_StopBits_t stop_bits;        // UART_STOPBITS_1 / 2
  UART_FlowControl_t flow_control;  // UART_FLOWCTRL_NONE / RTS / CTS / RTS_CTS
  UART_Oversampling_t oversampling; // UART_OVERSAMPLING_8 /16
  UART_Mode_t mode;                 // UART_MODE_TX / RX / TX_RX
  uint8_t it_flags; // UART_FLAG_PEIE / TXEIE / TCIE / RXNEIE / IDLEIE / CTSIE
                    // / EIE / LBDIE
} USART_Config_t;

void UART_Init(USART_TypeDef *UARTx, USART_Config_t *conf);
void UART_Transmit(USART_TypeDef *UARTx, uint8_t byte);
uint8_t UART_Receive(USART_TypeDef *UARTx);
void UART_EnableIT(USART_TypeDef *UARTx, uint8_t it);
void UART_DisableIT(USART_TypeDef *UARTx, uint8_t it);
bool UART_GetFlagStatus(USART_TypeDef *usart, uint32_t flag);
#endif /*  UART_DRIVER_H */
