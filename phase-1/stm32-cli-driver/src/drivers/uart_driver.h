/**
 ******************************************************************************
 * @file           : uart_driver.h
 * @brief          : Header file for uart_driver.c
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
#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "error.h"
#include "uart_hal.h"
#include <stdbool.h>
#include <stddef.h>

/* Exported types ------------------------------------------------------------*/

typedef struct {
  uint32_t baudrate;
  UART_WordLength word_length;
  UART_Parity parity;
  UART_StopBits stop_bits;
  UART_Oversampling oversampling;
  UART_Mode mode;
  uint8_t it_flags;
} USART_Config_t;

/* Exported constants --------------------------------------------------------*/

/* Exported macros
 * ------------------------------------------------------------*/

#if defined(__GNUC__) || defined(__clang__)
#define ERR_CHECK __attribute__((warn_unused_result))
#else
#define ERR_CHECK
#endif

/* Exported functions prototypes
 * -----------------------------------------------*/

/**
 * @brief  Initializes a USART peripheral and its RX/TX ring buffers.
 * @param[in]  conf Pointer to a USART_Config_t configuration structure.
 * @retval ERR_OK on success, ERR_NULL_PTR if conf is NULL, or the first
 *         GPIO/HAL error encountered.
 */
ERR_CHECK error_t UART_DRV_Init(USART_Config_t *conf);

/**
 * @brief  Queues bytes for transmission over the debug USART.
 * @param[in] byte Pointer to bytes to transmit.
 * @param[in] len  Length of byte array to transmit.
 * @retval ERR_OK if all bytes were queued, ERR_NULL_PTR if byte is NULL,
 *         ERR_BUFFER_FULL if one or more bytes could not be queued.
 */
ERR_CHECK error_t UART_DRV_Transmit(const uint8_t *byte, size_t len);

/**
 * @brief  Reads bytes already received on the debug USART.
 * @param[out] data Pointer to where received data will be saved.
 * @param[in]  len  Length of data to be read.
 * @retval ERR_OK if all bytes were read, ERR_NULL_PTR if data is NULL,
 *         ERR_BUFFER_EMPTY if fewer than len bytes were available.
 */
ERR_CHECK error_t UART_DRV_Receive(uint8_t *data, size_t len);

/**
 * @brief  Defines Interrupt Service Routine
 * @retval None
 */
void USART1_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* UART_DRIVER_H */
