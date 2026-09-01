/**
 ******************************************************************************
 * @file           : uart_hal.h
 * @brief          : Header file for uart_hal.c
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

#ifndef UART_HAL_H
#define UART_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "../common/error.h"
#include <stdbool.h>
#include <stdint.h>

/* Exported types ------------------------------------------------------------*/

typedef enum {
  UART_STOPBITS_1 = 0,
  UART_STOPBITS_0_5 = 1,
  UART_STOPBITS_2 = 2,
  UART_STOPBITS_1_5 = 3
} UART_StopBits;

typedef enum {
  UART_PARITY_NONE = 0,
  UART_PARITY_EVEN = 1,
  UART_PARITY_ODD = 2,
} UART_Parity;

typedef enum { UART_WORDLENGTH_8B = 0, UART_WORDLENGTH_9B = 1 } UART_WordLength;

typedef enum {
  UART_OVERSAMPLING_8 = 0,
  UART_OVERSAMPLING_16 = 1
} UART_Oversampling;

typedef enum {
  UART_MODE_TX = 0,
  UART_MODE_RX = 1,
  UART_MODE_TX_RX = 2
} UART_Mode;

/* Exported constants --------------------------------------------------------*/

#define UART_INTERRUPT_NO_IT (0U)
#define UART_INTERRUPT_PEIE (1U << 0)
#define UART_INTERRUPT_TXEIE (1U << 1)
#define UART_INTERRUPT_TCIE (1U << 2)
#define UART_INTERRUPT_RXNEIE (1U << 3)
#define UART_INTERRUPT_IDLEIE (1U << 4)
#define UART_INTERRUPT_CTSIE (1U << 5)
#define UART_INTERRUPT_EIE (1U << 6)
#define UART_INTERRUPT_LBDIE (1U << 7)

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

/* Exported macros
 * ------------------------------------------------------------*/

#if defined(__GNUC__) || defined(__clang__)
#define ERR_CHECK __attribute__((warn_unused_result))
#else
#define ERR_CHECK
#endif

/* Exported functions prototypes
 * ----------------------------------------------*/
/**
 * @brief  Enables the USART peripheral.
 * @retval ERR_OK.
 */
ERR_CHECK error_t HAL_UART_Enable(void);

/**
 * @brief  Disables the USART peripheral.
 * @retval ERR_OK.
 */
ERR_CHECK error_t HAL_UART_Disable(void);

/**
 * @brief  Configures the USART word length.
 * @param  wordlength Word length setting (8 or 9 bits).
 * @retval ERR_OK on success, ERR_INVALID_PARAM if wordlength is out of range.
 */
ERR_CHECK error_t HAL_UART_SetWordLength(UART_WordLength wordlength);

/**
 * @brief  Configures the USART stop bits.
 * @param  stop Stop bits setting.
 * @retval ERR_OK on success, ERR_INVALID_PARAM if stop is out of range.
 */
ERR_CHECK error_t HAL_UART_SetStopBits(UART_StopBits stop);

/**
 * @brief  Configures the USART baud rate.
 * @param  pclk Peripheral clock frequency in Hz.
 * @param  baud Desired baud rate in bits per second.
 * @retval ERR_OK on success, ERR_INVALID_PARAM if baud is zero.
 */
ERR_CHECK error_t HAL_UART_SetBaudRate(uint32_t pclk, uint32_t baud);

/**
 * @brief  Configures the USART parity mode.
 * @param  parity Parity setting.
 * @retval ERR_OK on success, ERR_INVALID_PARAM if parity is out of range.
 */
ERR_CHECK error_t HAL_UART_SetParity(UART_Parity parity);

/**
 * @brief  Enables one or more USART interrupt sources.
 * @param  flag Bitmask of UART_INTERRUPT_x flags to enable.
 * @retval ERR_OK.
 */
ERR_CHECK error_t HAL_UART_EnableIT(uint8_t flag);

/**
 * @brief  Disables one or more USART interrupt sources.
 * @param  flag Bitmask of UART_INTERRUPT_x flags to disable.
 * @retval ERR_OK.
 */
ERR_CHECK error_t HAL_UART_DisableIT(uint8_t flag);

/**
 * @brief  Checks whether a given USART status flag is set.
 * @param  flag       UART_FLAG_x status flag to check.
 * @param  out_is_set Pointer to where the result will be written.
 * @retval ERR_OK on success, ERR_NULL_PTR if out_is_set is NULL.
 */
ERR_CHECK error_t HAL_UART_FlagIsSet(uint32_t flag, bool *out_is_set);

/**
 * @brief  Writes a single byte to the USART data register for transmission.
 * @param  byte Byte to transmit.
 * @retval ERR_OK.
 */
ERR_CHECK error_t HAL_UART_WriteByte(uint8_t byte);

/**
 * @brief  Reads a single byte from the USART data register.
 * @param  out_byte Pointer to where the received byte will be written.
 * @retval ERR_OK on success, ERR_NULL_PTR if out_byte is NULL.
 */
ERR_CHECK error_t HAL_UART_ReadByte(uint8_t *out_byte);

/**
 * @brief  Configures the USART transfer direction (TX, RX, or both).
 * @param  mode Direction mode setting.
 * @retval ERR_OK on success, ERR_INVALID_PARAM if mode is out of range.
 */
ERR_CHECK error_t HAL_UART_SetMode(UART_Mode mode);

/**
 * @brief  Configures the USART oversampling rate.
 * @param  oversampling Oversampling setting (8x or 16x).
 * @retval ERR_OK on success, ERR_INVALID_PARAM if oversampling is out of
 *         range.
 */
ERR_CHECK error_t HAL_UART_SetOversampling(UART_Oversampling oversampling);

/**
 * @brief  Checks whether TXE flag is set.
 * @param  out_ready Pointer to where the result will be written.
 * @retval ERR_OK on success, ERR_NULL_PTR if out_ready is NULL.
 */
ERR_CHECK error_t HAL_UART_IsTxReady(bool *out_ready);

/**
 * @brief  Checks whether RXNE flag is set.
 * @param  out_ready Pointer to where the result will be written.
 * @retval ERR_OK on success, ERR_NULL_PTR if out_ready is NULL.
 */
ERR_CHECK error_t HAL_UART_IsRxReady(bool *out_ready);

/**
 * @brief  Enables the RXNE interrupt.
 * @retval ERR_OK.
 */
ERR_CHECK error_t HAL_UART_EnableRxIRQ(void);

/**
 * @brief  Disables the RXNE interrupt.
 * @retval ERR_OK.
 */
ERR_CHECK error_t HAL_UART_DisableRxIRQ(void);

/**
 * @brief  Enables the TXE interrupt.
 * @retval ERR_OK.
 */
ERR_CHECK error_t HAL_UART_EnableTxIRQ(void);

/**
 * @brief  Disables the TXE interrupt.
 * @retval ERR_OK.
 */
ERR_CHECK error_t HAL_UART_DisableTxIRQ(void);

#ifdef __cplusplus
}
#endif

#endif /* UART_HAL_H */
