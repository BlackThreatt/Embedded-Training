/**
 ******************************************************************************
 * @file           : uart_hal.c
 * @brief          : Register-level access layer for the STM32F429 USART
 * peripheral
 * @author         : Mohamed Ali BESSAIDI
 * @date           : 1 Sept 2026
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 MOHAMED ALI BESSAIDI.
 * All rights reserved.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "uart_hal.h"
#include "stm32f429xx.h"
#include <stddef.h>
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes
 * ------------------------------------------------*/

/* Exported functions
 * ----------------------------------------------------------*/

error_t HAL_UART_Enable(void) {
  USART1->CR1 |= USART_CR1_UE;
  return ERR_OK;
}

error_t HAL_UART_Disable(void) {
  USART1->CR1 &= ~(USART_CR1_UE);
  return ERR_OK;
}

error_t HAL_UART_SetWordLength(UART_WordLength wordlength) {
  switch (wordlength) {
  case UART_WORDLENGTH_8B:
    USART1->CR1 &= ~(USART_CR1_M);
    return ERR_OK;
  case UART_WORDLENGTH_9B:
    USART1->CR1 |= USART_CR1_M;
    return ERR_OK;
  default:
    return ERR_INVALID_PARAM;
  }
}

error_t HAL_UART_SetStopBits(UART_StopBits stop) {
  switch (stop) {
  case UART_STOPBITS_1:
    USART1->CR2 = (USART1->CR2 & ~USART_CR2_STOP) | (0U << USART_CR2_STOP_Pos);
    return ERR_OK;
  case UART_STOPBITS_0_5:
    USART1->CR2 = (USART1->CR2 & ~USART_CR2_STOP) | (1U << USART_CR2_STOP_Pos);
    return ERR_OK;
  case UART_STOPBITS_2:
    USART1->CR2 = (USART1->CR2 & ~USART_CR2_STOP) | (2U << USART_CR2_STOP_Pos);
    return ERR_OK;
  case UART_STOPBITS_1_5:
    USART1->CR2 = (USART1->CR2 & ~USART_CR2_STOP) | (3U << USART_CR2_STOP_Pos);
    return ERR_OK;
  default:
    return ERR_INVALID_PARAM;
  }
}

error_t HAL_UART_SetBaudRate(uint32_t pclk, uint32_t baud) {
  uint8_t over8 = 0U;
  uint16_t uartdiv;

  if (baud == 0U) {
    return ERR_INVALID_PARAM;
  }
  uartdiv = pclk / baud;

  over8 = (USART1->CR1 & USART_CR1_OVER8) >> USART_CR1_OVER8_Pos;
  if (over8 == 1) {
    USART1->BRR = (((uartdiv / 8) << USART_BRR_DIV_Mantissa_Pos) |
                   ((uartdiv % 8) << USART_BRR_DIV_Fraction_Pos)) &
                  0xFFF7;
  } else {
    USART1->BRR = (((uartdiv / 16) << USART_BRR_DIV_Mantissa_Pos) |
                   ((uartdiv % 16) << USART_BRR_DIV_Fraction_Pos));
  }
  return ERR_OK;
}

error_t HAL_UART_SetParity(UART_Parity parity) {
  switch (parity) {
  case UART_PARITY_NONE:
    USART1->CR1 &= ~USART_CR1_PCE;
    return ERR_OK;
  case UART_PARITY_EVEN:
    USART1->CR1 |= USART_CR1_PCE;
    USART1->CR1 &= ~USART_CR1_PS;
    return ERR_OK;
  case UART_PARITY_ODD:
    USART1->CR1 |= USART_CR1_PCE;
    USART1->CR1 |= USART_CR1_PS;
    return ERR_OK;
  default:
    return ERR_INVALID_PARAM;
  }
}

error_t HAL_UART_EnableIT(uint8_t flag) {
  if (flag & UART_INTERRUPT_PEIE) {
    USART1->CR1 |= USART_CR1_PEIE;
  }
  if (flag & UART_INTERRUPT_TXEIE) {
    USART1->CR1 |= USART_CR1_TXEIE;
  }
  if (flag & UART_INTERRUPT_TCIE) {
    USART1->CR1 |= USART_CR1_TCIE;
  }
  if (flag & UART_INTERRUPT_RXNEIE) {
    USART1->CR1 |= USART_CR1_RXNEIE;
  }
  if (flag & UART_INTERRUPT_IDLEIE) {
    USART1->CR1 |= USART_CR1_IDLEIE;
  }
  if (flag & UART_INTERRUPT_CTSIE) {
    USART1->CR3 |= USART_CR3_CTSIE;
  }
  if (flag & UART_INTERRUPT_EIE) {
    USART1->CR3 |= USART_CR3_EIE;
  }
  if (flag & UART_INTERRUPT_LBDIE) {
    USART1->CR2 |= USART_CR2_LBDIE;
  }
  return ERR_OK;
}

error_t HAL_UART_DisableIT(uint8_t flag) {
  if (flag & UART_INTERRUPT_PEIE) {
    USART1->CR1 &= ~USART_CR1_PEIE;
  }
  if (flag & UART_INTERRUPT_TXEIE) {
    USART1->CR1 &= ~USART_CR1_TXEIE;
  }
  if (flag & UART_INTERRUPT_TCIE) {
    USART1->CR1 &= ~USART_CR1_TCIE;
  }
  if (flag & UART_INTERRUPT_RXNEIE) {
    USART1->CR1 &= ~USART_CR1_RXNEIE;
  }
  if (flag & UART_INTERRUPT_IDLEIE) {
    USART1->CR1 &= ~USART_CR1_IDLEIE;
  }
  if (flag & UART_INTERRUPT_CTSIE) {
    USART1->CR3 &= ~USART_CR3_CTSIE;
  }
  if (flag & UART_INTERRUPT_EIE) {
    USART1->CR3 &= ~USART_CR3_EIE;
  }
  if (flag & UART_INTERRUPT_LBDIE) {
    USART1->CR2 &= ~USART_CR2_LBDIE;
  }
  return ERR_OK;
}

error_t HAL_UART_FlagIsSet(uint32_t flag, bool *out_is_set) {
  if (out_is_set == NULL) {
    return ERR_NULL_PTR;
  }
  *out_is_set = (USART1->SR & flag) != 0;
  return ERR_OK;
}

error_t HAL_UART_WriteByte(uint8_t byte) {
  USART1->DR = byte;
  return ERR_OK;
}

error_t HAL_UART_ReadByte(uint8_t *out_byte) {
  if (out_byte == NULL) {
    return ERR_NULL_PTR;
  }
  *out_byte = (USART1->DR & 0xFF);
  return ERR_OK;
}

error_t HAL_UART_SetMode(UART_Mode mode) {
  switch (mode) {
  case UART_MODE_TX:
    USART1->CR1 |= USART_CR1_TE;
    USART1->CR1 &= ~USART_CR1_RE;
    return ERR_OK;
  case UART_MODE_RX:
    USART1->CR1 |= USART_CR1_RE;
    USART1->CR1 &= ~USART_CR1_TE;
    return ERR_OK;
  case UART_MODE_TX_RX:
    USART1->CR1 |= USART_CR1_TE;
    USART1->CR1 |= USART_CR1_RE;
    return ERR_OK;
  default:
    return ERR_INVALID_PARAM;
  }
}

error_t HAL_UART_SetOversampling(UART_Oversampling oversampling) {
  switch (oversampling) {
  case UART_OVERSAMPLING_8:
    USART1->CR1 |= USART_CR1_OVER8;
    return ERR_OK;
  case UART_OVERSAMPLING_16:
    USART1->CR1 &= ~USART_CR1_OVER8;
    return ERR_OK;
  default:
    return ERR_INVALID_PARAM;
  }
}

error_t HAL_UART_IsTxReady(bool *out_ready) {
  if (out_ready == NULL) {
    return ERR_NULL_PTR;
  }
  *out_ready = !!(USART1->SR & USART_SR_TXE);
  return ERR_OK;
}

error_t HAL_UART_IsRxReady(bool *out_ready) {
  if (out_ready == NULL) {
    return ERR_NULL_PTR;
  }
  *out_ready = !!(USART1->SR & USART_SR_RXNE);
  return ERR_OK;
}

error_t HAL_UART_EnableRxIRQ(void) {
  USART1->CR1 |= USART_CR1_RXNEIE;
  return ERR_OK;
}

error_t HAL_UART_DisableRxIRQ(void) {
  USART1->CR1 &= ~USART_CR1_RXNEIE;
  return ERR_OK;
}

error_t HAL_UART_EnableTxIRQ(void) {
  USART1->CR1 |= USART_CR1_TXEIE;
  return ERR_OK;
}

error_t HAL_UART_DisableTxIRQ(void) {
  USART1->CR1 &= ~USART_CR1_TXEIE;
  return ERR_OK;
}

/* Private functions
 * -------------------------------------------------------------*/
