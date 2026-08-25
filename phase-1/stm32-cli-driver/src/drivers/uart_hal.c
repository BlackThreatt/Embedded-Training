/**
 ******************************************************************************
 * @file           : uart_hal.c
 * @brief          : Register-level access layer for the STM32F429 USART
 * peripheral
 * @author         : Mohamed Ali BESSAIDI
 * @date           : 22 Aug 2026
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
/* Private typedef
 * ------------------------------------------------------------*/

/* Private define
 * --------------------------------------------------------------*/

/* Private macro
 * ----------------------------------------------------------------*/

/* Private variables
 * --------------------------------------------------------------*/

/* Private function prototypes
 * ----------------------------------------------------*/

/* Exported functions
 * --------------------------------------------------------------*/

/**
 * @brief  Enables the USART peripheral.
 * @param  usart Pointer to the USART peripheral register block.
 * @retval None
 */
void HAL_UART_Enable() { USART1->CR1 |= USART_CR1_UE; }

/**
 * @brief  Disables the USART peripheral.
 * @param  usart Pointer to the USART peripheral register block.
 * @retval None
 */
void HAL_UART_Disable() { USART1->CR1 &= ~(USART_CR1_UE); }

/**
 * @brief  Configures the USART word length.
 * @param  usart      Pointer to the USART peripheral register block.
 * @param  wordlength Word length setting (8 or 9 bits).
 * @retval None
 */
void HAL_UART_SetWordLength(UART_WordLength wordlength) {
  switch (wordlength) {
  case UART_WORDLENGTH_8B:
    USART1->CR1 &= ~(USART_CR1_M);
    break;
  case UART_WORDLENGTH_9B:
    USART1->CR1 |= USART_CR1_M;
    break;
  }
}

/**
 * @brief  Configures the USART stop bits.
 * @param  usart Pointer to the USART peripheral register block.
 * @param  stop  Stop bits setting.
 * @retval None
 */
void HAL_UART_SetStopBits(UART_StopBits stop) {

  switch (stop) {
  case UART_STOPBITS_1:
    USART1->CR2 = (USART1->CR2 & ~USART_CR2_STOP) | (0U << USART_CR2_STOP_Pos);
    break;
  case UART_STOPBITS_0_5:
    USART1->CR2 = (USART1->CR2 & ~USART_CR2_STOP) | (1U << USART_CR2_STOP_Pos);
    break;
  case UART_STOPBITS_2:
    USART1->CR2 = (USART1->CR2 & ~USART_CR2_STOP) | (2U << USART_CR2_STOP_Pos);
    break;
  case UART_STOPBITS_1_5:
    USART1->CR2 = (USART1->CR2 & ~USART_CR2_STOP) | (3U << USART_CR2_STOP_Pos);
    break;
  }
}

/**
 * @brief  Configures the USART baud rate.
 * @param  usart Pointer to the USART peripheral register block.
 * @param  pclk  Peripheral clock frequency in Hz.
 * @param  baud  Desired baud rate in bits per second.
 * @retval None
 */
void HAL_UART_SetBaudRate(uint32_t pclk, uint32_t baud) {
  uint8_t over8 = 0U;
  uint16_t uartdiv = pclk / baud;

  over8 = (USART1->CR1 & USART_CR1_OVER8) >> USART_CR1_OVER8_Pos;
  if (over8 == 1) {
    USART1->BRR = (((uartdiv / 8) << USART_BRR_DIV_Mantissa_Pos) |
                   ((uartdiv % 8) << USART_BRR_DIV_Fraction_Pos)) &
                  0xFFF7;
  } else {
    USART1->BRR = (((uartdiv / 16) << USART_BRR_DIV_Mantissa_Pos) |
                   ((uartdiv % 16) << USART_BRR_DIV_Fraction_Pos));
  }
}

/**
 * @brief  Configures the USART parity mode.
 * @param  usart  Pointer to the USART peripheral register block.
 * @param  parity Parity setting.
 * @retval None
 */
void HAL_UART_SetParity(UART_Parity parity) {

  switch (parity) {
  case UART_PARITY_NONE:
    USART1->CR1 &= ~USART_CR1_PCE;
    break;
  case UART_PARITY_EVEN:
    USART1->CR1 |= USART_CR1_PCE;
    USART1->CR1 &= ~USART_CR1_PS;
    break;
  case UART_PARITY_ODD:
    USART1->CR1 |= USART_CR1_PCE;
    USART1->CR1 |= USART_CR1_PS;
    break;
  }
}

/**
 * @brief  Enables one or more USART interrupt sources.
 * @param  usart Pointer to the USART peripheral register block.
 * @param  flag  Bitmask of UART_INTERRUPT_x flags to enable.
 * @retval None
 */
void HAL_UART_EnableIT(uint8_t flag) {
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
}

/**
 * @brief  Disables one or more USART interrupt sources.
 * @param  usart Pointer to the USART peripheral register block.
 * @param  flag  Bitmask of UART_INTERRUPT_x flags to disable.
 * @retval None
 */
void HAL_UART_DisableIT(uint8_t flag) {
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
}

/**
 * @brief  Checks whether a given USART status flag is set.
 * @param  usart Pointer to the USART peripheral register block.
 * @param  flag  UART_FLAG_x status flag to check.
 * @retval true if the flag is set, false otherwise.
 */
bool HAL_UART_FlagIsSet(uint32_t flag) { return (USART1->SR & flag) != 0; }

/**
 * @brief  Writes a single byte to the USART data register for transmission.
 * @param  usart Pointer to the USART peripheral register block.
 * @param  byte  Byte to transmit.
 * @retval None
 */
void HAL_UART_WriteByte(uint8_t byte) { USART1->DR = byte; }

/**
 * @brief  Reads a single byte from the USART data register.
 * @param  usart Pointer to the USART peripheral register block.
 * @retval Byte received from the data register.
 */
uint8_t HAL_UART_ReadByte() { return (USART1->DR & 0xFF); }

/**
 * @brief  Configures the USART transfer direction (TX, RX, or both).
 * @param  usart Pointer to the USART peripheral register block.
 * @param  mode  Direction mode setting.
 * @retval None
 */
void HAL_UART_SetMode(UART_Mode mode) {
  switch (mode) {
  case UART_MODE_TX:
    USART1->CR1 |= USART_CR1_TE;
    USART1->CR1 &= ~USART_CR1_RE;
    break;
  case UART_MODE_RX:
    USART1->CR1 |= USART_CR1_RE;
    USART1->CR1 &= ~USART_CR1_TE;
    break;
  case UART_MODE_TX_RX:
    USART1->CR1 |= USART_CR1_TE;
    USART1->CR1 |= USART_CR1_RE;
    break;
  }
}

/**
 * @brief  Configures the USART oversampling rate.
 * @param  usart        Pointer to the USART peripheral register block.
 * @param  oversampling Oversampling setting (8x or 16x).
 * @retval None
 */
void HAL_UART_SetOversampling(UART_Oversampling oversampling) {
  switch (oversampling) {
  case UART_OVERSAMPLING_8:
    USART1->CR1 |= USART_CR1_OVER8;
    break;
  case UART_OVERSAMPLING_16:
    USART1->CR1 &= ~USART_CR1_OVER8;
    break;
  }
}

/**
 * @brief  Checks whether TXE flag is set.
 * @param  usart Pointer to the USART peripheral register block.
 * @retval true if the flag is set, false otherwise.
 */
bool HAL_UART_IsTxReady() { return !!(USART1->SR & USART_SR_TXE); }

/**
 * @brief  Checks whether RXNE flag is set.
 * @param  usart Pointer to the USART peripheral register block.
 * @retval true if the flag is set, false otherwise.
 */
bool HAL_UART_IsRxReady() { return !!(USART1->SR & USART_SR_RXNE); }

/**
 * @brief Enable The RXNE interrupt.
 * @param usart Pointer to the USART peripheral register block.
 * @retval None
 */
void HAL_UART_EnableRxIRQ() { USART1->CR1 |= USART_CR1_RXNEIE; }

/**
 * @brief Disable The RXNE interrupt.
 * @param usart Pointer to the USART peripheral register block.
 * @retval None
 */

void HAL_UART_DisableRxIRQ() { USART1->CR1 &= ~USART_CR1_RXNEIE; }

/**
 * @brief Enable The TXE interrupt.
 * @param usart Pointer to the USART peripheral register block.
 * @retval None
 */
void HAL_UART_EnableTxIRQ() { USART1->CR1 |= USART_CR1_TXEIE; }

/**
 * @brief Enable The TXE interrupt.
 * @param usart Pointer to the USART peripheral register block.
 * @retval None
 */
void HAL_UART_DisableTxIRQ() { USART1->CR1 &= ~USART_CR1_TXEIE; }

/* Private functions
 * -----------------------------------------------------------------*/
