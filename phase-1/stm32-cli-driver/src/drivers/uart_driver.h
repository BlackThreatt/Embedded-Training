/**
 ******************************************************************************
 * @file           : uart_driver.h
 * @brief          : Header file for uart_driver.c
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
#ifndef UART_DRIVER_H
#define UART_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "uart_hal.h"
#include <stdbool.h>
#include <stddef.h>

/* Exported types ------------------------------------------------------------*/

/**
 * @brief UART driver configuration structure passed to UART_DRV_Init().
 */
typedef struct {
  uint32_t baudrate;                /*!< Desired baud rate in bits per second */
  UART_WordLength_t word_length;    /*!< UART_WORDLEN_8B / 9B */
  UART_Parity_t parity;             /*!< UART_PARITY_NONE / ODD / EVEN */
  UART_StopBits_t stop_bits;        /*!< UART_STOPBITS_1 / 2 */
  UART_Oversampling_t oversampling; /*!< UART_OVERSAMPLING_8 / 16 */
  UART_Mode_t mode;                 /*!< UART_MODE_TX / RX / TX_RX */
  uint8_t it_flags; /*!< UART_FLAG_PEIE / TXEIE / TCIE / RXNEIE / IDLEIE /
                          CTSIE / EIE / LBDIE */
} USART_Config_t;

/* Exported constants --------------------------------------------------------*/

/* Exported macros -----------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

/**
 * @brief  Initializes a USART peripheral and its RX/TX ring buffers.
 * @param[in]  conf  Pointer to a USART_Config_t configuration structure.
 * @retval None
 */
void UART_DRV_Init(USART_Config_t *conf);

/**
 * @brief  Transmits a single byte over the given USART peripheral.
 * @param[in] conf  Pointer to a USART_Config_t configuration structure.
 * @param[in] byte  Poiner to bytes to transmit.
 * @param[in] len   Length of byte array to transmit.
 * @retval None
 */
void UART_DRV_Transmit(USART_Config_t *conf, const uint8_t *byte, size_t len);

/**
 * @brief  Receives a single byte from the given USART peripheral.
 * @param[in] conf  Pointer to a USART_Config_t configuration structure.
 * @param[out] data Pointer to where received data will be saved.
 * @param[in] len   Length of data to be read.
 * @retval None
 */
void UART_DRV_Receive(USART_Config_t *conf, uint8_t *data, size_t len);

/**
 * @brief  Defines Interrupt Service Routine
 * @retval None
 */
void USART1_IRQHandler(void);

#ifdef __cplusplus
}
#endif

#endif /* UART_DRIVER_H */
