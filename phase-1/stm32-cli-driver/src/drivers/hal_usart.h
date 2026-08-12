#ifndef HAL_USART_H
#define HAL_USART_H

#include <stdbool.h>
#include <stdint.h>
#include <stm32f429xx.h>

// UART interrupt flags
#define UART_INTERRUPT_NO_IT (0U)
#define UART_INTERRUPT_PEIE (1U << 0)
#define UART_INTERRUPT_TXEIE (1U << 1)
#define UART_INTERRUPT_TCIE (1U << 2)
#define UART_INTERRUPT_RXNEIE (1U << 3)
#define UART_INTERRUPT_IDLEIE (1U << 4)
#define UART_INTERRUPT_CTSIE (1U << 5)
#define UART_INTERRUPT_EIE (1U << 6)
#define UART_INTERRUPT_LBDIE (1U << 7)
// UART Status Flags
#define UART_FLAG_CTS (1U << 9)
#define UART_FLAG_LBD (1U << 8)
#define UART_FLAG_TXE (1U << 7)
#define UART_FLAG_TC (1U << 6)
#define UART_FLAG_RXNE (1U << 5)
#define UART_FLAG_IDLE (1U << 4)
#define UART_FLAG_ORE (1U << 3)
#define UART_FLAG_NF (1U << 2)
#define UART_FLAG_FE (1U << 1)
#define UART_FLAG_PE (1U << 0)

typedef enum {
  UART_STOPBITS_1 = 0,
  UART_STOPBITS_0_5 = 1,
  UART_STOPBITS_2 = 2,
  UART_STOPBITS_1_5 = 3
} UART_StopBits_t;

typedef enum {
  UART_PARITY_NONE = 0,
  UART_PARITY_EVEN = 1,
  UART_PARITY_ODD = 2,
} UART_Parity_t;

typedef enum {
  UART_WORDLENGTH_8B = 0,
  UART_WORDLENGTH_9B = 1
} UART_WordLength_t;

typedef enum {
  UART_OVERSAMPLING_8 = 0,
  UART_OVERSAMPLING_16 = 1
} UART_Oversampling_t;

typedef enum {
  UART_HWCONTROL_NONE = 0,
  UART_HWCONTROL_RTS = 1,
  UART_HWCONTROL_CTS = 2,
  UART_HWCONTROL_RTS_CTS = 3
} UART_FlowControl_t;

typedef enum {
  UART_MODE_TX = 0,
  UART_MODE_RX = 1,
  UART_MODE_TX_RX = 2
} UART_Mode_t;

static inline void HAL_USART_Enable(USART_TypeDef *usart) {
  usart->CR1 |= USART_CR1_UE;
}

static inline void HAL_USART_Disable(USART_TypeDef *usart) {
  usart->CR1 &= ~(USART_CR1_UE);
}

static inline void HAL_USART_SetWordLength(USART_TypeDef *usart,
                                           UART_WordLength_t wordlength) {
  switch (wordlength) {
  case UART_WORDLENGTH_8B:
    usart->CR1 &= ~(USART_CR1_M);
    break;
  case UART_WORDLENGTH_9B:
    usart->CR1 |= USART_CR1_M;
    break;
  }
}

static inline void HAL_USART_SetStopBits(USART_TypeDef *usart,
                                         UART_StopBits_t stop) {

  switch (stop) {
  case UART_STOPBITS_1:
    usart->CR2 = (usart->CR2 & ~USART_CR2_STOP) | (0U << USART_CR2_STOP_Pos);
    break;
  case UART_STOPBITS_0_5:
    usart->CR2 = (usart->CR2 & ~USART_CR2_STOP) | (1U << USART_CR2_STOP_Pos);
    break;
  case UART_STOPBITS_2:
    usart->CR2 = (usart->CR2 & ~USART_CR2_STOP) | (2U << USART_CR2_STOP_Pos);
    break;
  case UART_STOPBITS_1_5:
    usart->CR2 = (usart->CR2 & ~USART_CR2_STOP) | (3U << USART_CR2_STOP_Pos);
    break;
  }
}

static inline void HAL_USART_SetBaudRate(USART_TypeDef *usart, uint32_t pclk,
                                         uint32_t baud) {
  uint8_t over8 = 0U;
  uint16_t uartdiv = pclk / baud;

  over8 = (usart->CR1 & USART_CR1_OVER8) >> USART_CR1_OVER8_Pos;
  if (over8 == 1) {
    usart->BRR = (((uartdiv / 8) << USART_BRR_DIV_Mantissa_Pos) |
                  ((uartdiv % 8) << USART_BRR_DIV_Fraction_Pos)) &
                 0xFFF7;
  } else {
    usart->BRR = (((uartdiv / 16) << USART_BRR_DIV_Mantissa_Pos) |
                  ((uartdiv % 16) << USART_BRR_DIV_Fraction_Pos));
  }
}

static inline void HAL_USART_SetParity(USART_TypeDef *usart,
                                       UART_Parity_t parity) {

  switch (parity) {
  case UART_PARITY_NONE:
    usart->CR1 &= ~USART_CR1_PCE;
    break;
  case UART_PARITY_EVEN:
    usart->CR1 |= USART_CR1_PCE;
    usart->CR1 &= ~USART_CR1_PS;
    break;
  case UART_PARITY_ODD:
    usart->CR1 |= USART_CR1_PCE;
    usart->CR1 |= USART_CR1_PS;
    break;
  }
}

static inline void HAL_USART_EnableIT(USART_TypeDef *usart, uint8_t flag) {
  if (flag & UART_INTERRUPT_PEIE) {
    usart->CR1 |= USART_CR1_PEIE;
  }
  if (flag & UART_INTERRUPT_TXEIE) {
    usart->CR1 |= USART_CR1_TXEIE;
  }
  if (flag & UART_INTERRUPT_TCIE) {
    usart->CR1 |= USART_CR1_TCIE;
  }
  if (flag & UART_INTERRUPT_RXNEIE) {
    usart->CR1 |= USART_CR1_RXNEIE;
  }
  if (flag & UART_INTERRUPT_IDLEIE) {
    usart->CR1 |= USART_CR1_IDLEIE;
  }
  if (flag & UART_INTERRUPT_CTSIE) {
    usart->CR3 |= USART_CR3_CTSIE;
  }
  if (flag & UART_INTERRUPT_EIE) {
    usart->CR3 |= USART_CR3_EIE;
  }
  if (flag & UART_INTERRUPT_LBDIE) {
    usart->CR2 |= USART_CR2_LBDIE;
  }
}

static inline void HAL_USART_DisableIT(USART_TypeDef *usart, uint8_t flag) {
  if (flag & UART_INTERRUPT_PEIE) {
    usart->CR1 &= ~USART_CR1_PEIE;
  }
  if (flag & UART_INTERRUPT_TXEIE) {
    usart->CR1 &= ~USART_CR1_TXEIE;
  }
  if (flag & UART_INTERRUPT_TCIE) {
    usart->CR1 &= ~USART_CR1_TCIE;
  }
  if (flag & UART_INTERRUPT_RXNEIE) {
    usart->CR1 &= ~USART_CR1_RXNEIE;
  }
  if (flag & UART_INTERRUPT_IDLEIE) {
    usart->CR1 &= ~USART_CR1_IDLEIE;
  }
  if (flag & UART_INTERRUPT_CTSIE) {
    usart->CR3 &= ~USART_CR3_CTSIE;
  }
  if (flag & UART_INTERRUPT_EIE) {
    usart->CR3 &= ~USART_CR3_EIE;
  }
  if (flag & UART_INTERRUPT_LBDIE) {
    usart->CR2 &= ~USART_CR2_LBDIE;
  }
}

static inline bool HAL_USART_FlagIsSet(USART_TypeDef *usart, uint32_t flag) {
  return (usart->SR & flag) != 0;
}

static inline void HAL_USART_WriteByte(USART_TypeDef *usart, uint8_t byte) {
  usart->DR = byte;
}

static inline uint8_t HAL_USART_ReadByte(USART_TypeDef *usart) {
  return (usart->DR & 0xFF);
}

static inline void HAL_USART_SetMode(USART_TypeDef *usart, UART_Mode_t mode) {
  switch (mode) {
  case UART_MODE_TX:
    usart->CR1 |= USART_CR1_TE;
    usart->CR1 &= ~USART_CR1_RE;
    break;
  case UART_MODE_RX:
    usart->CR1 |= USART_CR1_RE;
    usart->CR1 &= ~USART_CR1_TE;
    break;
  case UART_MODE_TX_RX:
    usart->CR1 |= USART_CR1_TE;
    usart->CR1 |= USART_CR1_RE;
    break;
  }
}

static inline void HAL_USART_SetOversampling(USART_TypeDef *usart,
                                             UART_Oversampling_t oversampling) {
  switch (oversampling) {
  case UART_OVERSAMPLING_8:
    usart->CR1 |= USART_CR1_OVER8;
    break;
  case UART_OVERSAMPLING_16:
    usart->CR1 &= ~USART_CR1_OVER8;
    break;
  }
}

static inline void HAL_USART_SetFlowControl(USART_TypeDef *usart,
                                            UART_FlowControl_t flowcontrol) {
  switch (flowcontrol) {
  case UART_HWCONTROL_NONE:
    usart->CR3 &= ~USART_CR3_RTSE;
    usart->CR3 &= ~USART_CR3_CTSE;
    break;
  case UART_HWCONTROL_RTS:
    usart->CR3 |= USART_CR3_RTSE;
    usart->CR3 &= ~USART_CR3_CTSE;
    break;
  case UART_HWCONTROL_CTS:
    usart->CR3 |= USART_CR3_CTSE;
    usart->CR3 &= ~USART_CR3_RTSE;
    break;
  case UART_HWCONTROL_RTS_CTS:
    usart->CR3 |= USART_CR3_RTSE;
    usart->CR3 |= USART_CR3_CTSE;
    break;
  }
}

#endif // !HAL_USART_H
