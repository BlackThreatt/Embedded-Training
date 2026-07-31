#ifndef __UART_H__
#define __UART_H__

#include <stdint.h>

#define T_UART1_BASE 0x40011000UL
#define T_UART6_BASE 0x40011400UL

typedef struct {
  volatile uint32_t SR;
  volatile uint32_t DR;
  volatile uint32_t BRR;
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t CR3;
  volatile uint32_t GTPR;
} UART_Typedef;

#define T_USART1 ((UART_Typedef *)T_UART1_BASE)
#define T_USART6 ((UART_Typedef *)T_UART6_BASE)

void UART_Init(UART_Typedef *UARTx);
void UART_Transmit(UART_Typedef *UARTx, uint8_t byte);
uint8_t UART_Receive(UART_Typedef *UARTx);
#endif /* ifndef __UART_H__ */
