#include <stdint.h>

#define UART1_BASE 0x40011000UL

typedef struct {
  volatile uint32_t SR;
  volatile uint32_t DR;
  volatile uint32_t BRR;
  volatile uint32_t CR1;
  volatile uint32_t CR2;
  volatile uint32_t CR3;
  volatile uint32_t GTPR;
} USART_TypeDef;

#define USART1 ((USART_TypeDef *)UART1_BASE)

void uart_init_struct(void) {
  USART1->CR1 |= (1U << 13); // UE: USART enable
  USART1->BRR = 0x0683;      // 115200 @ 8MHz
  USART1->CR1 |= (1U << 3);  // TE: transmitter enable
}

void uart_send_struct(uint8_t byte) {
  while (!(USART1->SR & (1U << 7))) {
  } // wait TXE
  USART1->DR = byte;
}
