/**
 ******************************************************************************
 * @file           : uart_hal.h
 * @brief          : Header file for uart_hal.c
 * @author         : Mohamed Ali BESSAIDI
 * @date           : 22 Aug 2026
 ******************************************************************************
 * @attention
 *
 * Copyright (c); 2026 MOHAMED ALI BESSAIDI.
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
#include "stm32f429xx.h"
#include <stdbool.h>
#include <stdint.h>

/* Exported types ------------------------------------------------------------*/

/**
 * @brief UART stop bit configuration options.
 */
typedef enum {
  UART_STOPBITS_1 = 0,
  UART_STOPBITS_0_5 = 1,
  UART_STOPBITS_2 = 2,
  UART_STOPBITS_1_5 = 3
} UART_StopBits_t;

/**
 * @brief UART parity configuration options.
 */
typedef enum {
  UART_PARITY_NONE = 0,
  UART_PARITY_EVEN = 1,
  UART_PARITY_ODD = 2,
} UART_Parity_t;

/**
 * @brief UART word length configuration options.
 */
typedef enum {
  UART_WORDLENGTH_8B = 0,
  UART_WORDLENGTH_9B = 1
} UART_WordLength_t;

/**
 * @brief UART oversampling configuration options.
 */
typedef enum {
  UART_OVERSAMPLING_8 = 0,
  UART_OVERSAMPLING_16 = 1
} UART_Oversampling_t;

/**
 * @brief UART hardware flow control configuration options.
 */
typedef enum {
  UART_HWCONTROL_NONE = 0,
  UART_HWCONTROL_RTS = 1,
  UART_HWCONTROL_CTS = 2,
  UART_HWCONTROL_RTS_CTS = 3
} UART_FlowControl_t;

/**
 * @brief UART direction mode configuration options.
 */
typedef enum {
  UART_MODE_TX = 0,
  UART_MODE_RX = 1,
  UART_MODE_TX_RX = 2
} UART_Mode_t;

/* Exported constants --------------------------------------------------------*/

/**
 * @defgroup UART_Interrupt_Flags UART Interrupt Flags
 * @{
 */
#define UART_INTERRUPT_NO_IT (0U)     /*!< No interrupt enabled */
#define UART_INTERRUPT_PEIE (1U << 0) /*!< Parity error interrupt enable */
#define UART_INTERRUPT_TXEIE                                                   \
  (1U << 1) /*!< TX data register empty interrupt enable */
#define UART_INTERRUPT_TCIE                                                    \
  (1U << 2) /*!< Transmission complete interrupt enable */
#define UART_INTERRUPT_RXNEIE                                                  \
  (1U << 3) /*!< RX data register not empty interrupt enable */
#define UART_INTERRUPT_IDLEIE                                                  \
  (1U << 4) /*!< Idle line detected interrupt enable */
#define UART_INTERRUPT_CTSIE (1U << 5) /*!< CTS interrupt enable */
#define UART_INTERRUPT_EIE (1U << 6)   /*!< Error interrupt enable */
#define UART_INTERRUPT_LBDIE                                                   \
  (1U << 7) /*!< LIN break detection interrupt enable */
/**
 * @}
 */

/**
 * @defgroup UART_Status_Flags UART Status Flags
 * @{
 */
#define UART_FLAG_CTS (1U << 9)  /*!< CTS flag */
#define UART_FLAG_LBD (1U << 8)  /*!< LIN break detection flag */
#define UART_FLAG_TXE (1U << 7)  /*!< TX data register empty flag */
#define UART_FLAG_TC (1U << 6)   /*!< Transmission complete flag */
#define UART_FLAG_RXNE (1U << 5) /*!< RX data register not empty flag */
#define UART_FLAG_IDLE (1U << 4) /*!< Idle line detected flag */
#define UART_FLAG_ORE (1U << 3)  /*!< Overrun error flag */
#define UART_FLAG_NF (1U << 2)   /*!< Noise detected flag */
#define UART_FLAG_FE (1U << 1)   /*!< Framing error flag */
#define UART_FLAG_PE (1U << 0)   /*!< Parity error flag */
/**
 * @}
 */

/* Exported macros
 * ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/

/**
 * @brief  Enables the USART peripheral.
 * @param  usart Pointer to the USART peripheral register block.
 * @retval None
 */
void HAL_UART_Enable();

/**
 * @brief  Disables the USART peripheral.
 * @param  usart Pointer to the USART peripheral register block.
 * @retval None
 */
void HAL_UART_Disable();

/**
 * @brief  Configures the USART word length.
 * @param  usart      Pointer to the USART peripheral register block.
 * @param  wordlength Word length setting (8 or 9 bits).
 * @retval None
 */
void HAL_UART_SetWordLength(UART_WordLength_t wordlength);
/**
 * @brief  Configures the USART stop bits.
 * @param  usart Pointer to the USART peripheral register block.
 * @param  stop  Stop bits setting.
 * @retval None
 */
void HAL_UART_SetStopBits(UART_StopBits_t stop);
/**
 * @brief  Configures the USART baud rate.
 * @param  usart Pointer to the USART peripheral register block.
 * @param  pclk  Peripheral clock frequency in Hz.
 * @param  baud  Desired baud rate in bits per second.
 * @retval None
 */
void HAL_UART_SetBaudRate(uint32_t pclk, uint32_t baud);

/**
 * @brief  Configures the USART parity mode.
 * @param  usart  Pointer to the USART peripheral register block.
 * @param  parity Parity setting.
 * @retval None
 */
void HAL_UART_SetParity(UART_Parity_t parity);

/**
 * @brief  Enables one or more USART interrupt sources.
 * @param  usart Pointer to the USART peripheral register block.
 * @param  flag  Bitmask of UART_INTERRUPT_x flags to enable.
 * @retval None
 */
void HAL_UART_EnableIT(uint8_t flag);
/**
 * @brief  Disables one or more USART interrupt sources.
 * @param  usart Pointer to the USART peripheral register block.
 * @param  flag  Bitmask of UART_INTERRUPT_x flags to disable.
 * @retval None
 */
void HAL_UART_DisableIT(uint8_t flag);
/**
 * @brief  Checks whether a given USART status flag is set.
 * @param  usart Pointer to the USART peripheral register block.
 * @param  flag  UART_FLAG_x status flag to check.
 * @retval true if the flag is set, false otherwise.
 */
bool HAL_UART_FlagIsSet(uint32_t flag);
/**
 * @brief  Writes a single byte to the USART data register for transmission.
 * @param  usart Pointer to the USART peripheral register block.
 * @param  byte  Byte to transmit.
 * @retval None
 */
void HAL_UART_WriteByte(uint8_t byte);
/**
 * @brief  Reads a single byte from the USART data register.
 * @param  usart Pointer to the USART peripheral register block.
 * @retval Byte received from the data register.
 */
uint8_t HAL_UART_ReadByte();
/**
 * @brief  Configures the USART transfer direction (TX, RX, or both).
 * @param  usart Pointer to the USART peripheral register block.
 * @param  mode  Direction mode setting.
 * @retval None
 */
void HAL_UART_SetMode(UART_Mode_t mode);
/**
 * @brief  Configures the USART oversampling rate.
 * @param  usart        Pointer to the USART peripheral register block.
 * @param  oversampling Oversampling setting (8x or 16x).
 * @retval None
 */
void HAL_UART_SetOversampling(UART_Oversampling_t oversampling);
/**
 * @brief  Checks whether TXE flag is set.
 * @param  usart Pointer to the USART peripheral register block.
 * @retval true if the flag is set, false otherwise.
 */
bool HAL_UART_IsTxReady();

/**
 * @brief  Checks whether RXNE flag is set.
 * @param  usart Pointer to the USART peripheral register block.
 * @retval true if the flag is set, false otherwise.
 */
bool HAL_UART_IsRxReady();

/**
 * @brief Enable The RXNE interrupt.
 * @param usart Pointer to the USART peripheral register block.
 * @retval None
 */
void HAL_UART_EnableRxIRQ();

/**
 * @brief Disable The RXNE interrupt.
 * @param usart Pointer to the USART peripheral register block.
 * @retval None
 */

void HAL_UART_DisableRxIRQ();

/**
 * @brief Enable The TXE interrupt.
 * @param usart Pointer to the USART peripheral register block.
 * @retval None
 */
void HAL_UART_EnableTxIRQ();

/**
 * @brief Enable The TXE interrupt.
 * @param usart Pointer to the USART peripheral register block.
 * @retval None
 */
void HAL_UART_DisableTxIRQ();

#ifdef __cplusplus
}
#endif

#endif /* UART_HAL_H */
