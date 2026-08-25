/**
 ******************************************************************************
 * @file           : uart_driver.c
 * @brief          : Driver layer for USART peripherals, built on top of
 * uart_hal
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
#include "uart_driver.h"
#include "../common/RingBuffer.h"
#include "gpio.h"
#include "uart_hal.h"
#include <stddef.h>
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static RingBuffer_t
    uartRxRb; /*!< RX ring buffer for the active USART instance */
static RingBuffer_t
    uartTxRb; /*!< TX ring buffer for the active USART instance */

GPIO_Config_t uartGpioConf;
/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/**
 * @brief  Initializes a USART peripheral and its RX/TX ring buffers.
 * @param[in]  conf  Pointer to a USART_Config_t configuration structure.
 * @retval None
 */
void UART_DRV_Init(USART_Config_t *conf) {

  RingBuf_Init(&uartRxRb);
  RingBuf_Init(&uartTxRb);

  // Initialize USART1 GPIOA Clock Config
  RCC->AHB1ENR |= (1U << 0);
  // Enable USART1 Clock
  RCC->APB2ENR |= (1U << 4);

  // Initialize UART gpio
  uartGpioConf.pins = (1U << 9) | (1U << 10);
  // Set mode to Alternate Function
  uartGpioConf.mode = 2U;
  // Set AF_H to AF7;
  uartGpioConf.AF_H = 7U;

  GPIO_Set_Config(T_GPIOA, &uartGpioConf);

  HAL_UART_SetWordLength(conf->word_length);
  HAL_UART_SetParity(conf->parity);
  HAL_UART_SetStopBits(conf->stop_bits);
  HAL_UART_SetOversampling(conf->oversampling);

  // INFO: value is temporary until RCC module is developed
  uint32_t pclk = 16000000UL;
  HAL_UART_SetBaudRate(pclk, conf->baudrate);
  HAL_UART_SetMode(conf->mode);

  if (conf->it_flags != UART_INTERRUPT_NO_IT) {
    NVIC_EnableIRQ(USART1_IRQn);

    HAL_UART_EnableIT(conf->it_flags);
  }
  // Enable USART
  HAL_UART_Enable();
}

/**
 * @brief  Transmits a single byte over the given USART peripheral.
 * @param[in] conf  Pointer to a USART_Config_t configuration structure.
 * @param[in] byte  Byte to transmit.
 * @param[in] len   Length of byte array to transmit
 * @retval None
 */
void UART_DRV_Transmit(USART_Config_t *conf, const uint8_t *byte, size_t len) {
  for (uint32_t iter = 0; iter < len; iter++) {
    if (!RingBuf_IsFull(&uartTxRb)) {
      RingBuf_Push(&uartTxRb, byte[iter]);
      HAL_UART_EnableTxIRQ();
    }
    // TODO: Return error status if fulll
  }
}

/**
 * @brief  Receives a single byte from the given USART peripheral.
 * @param[in] conf  Pointer to a USART_Config_t configuration structure.
 * @param[out] data Pointer to where received data will be saved.
 * @param[in] len   Length of data to be read.
 * @retval None
 */
void UART_DRV_Receive(USART_Config_t *conf, uint8_t *data, size_t len) {

  for (size_t iter = 0; iter < len; iter++) {
    if (!RingBuf_IsEmpty(&uartRxRb)) {
      RingBuf_Pop(&uartRxRb, &data[iter]);
    }
    // TODO: Treat Timeout use case when rx is empty
    // TODO: Add status return
  }
}

/**
 * @brief  Defines Interrupt Service Routine
 * @retval None
 */
void USART1_IRQHandler(void) {
  uint8_t byte;
  if (HAL_UART_IsTxReady()) {
    if (RingBuf_Pop(&uartTxRb, &byte)) {
      HAL_UART_WriteByte(byte);
    } else {
      HAL_UART_DisableTxIRQ();
    }
  }

  // Check RXNE bit status
  if (HAL_UART_IsRxReady()) {
    byte = HAL_UART_ReadByte();
    if (RingBuf_Push(&uartRxRb, byte) == 0) {
      uint8_t oldData;
      RingBuf_Pop(&uartRxRb, &oldData);
      RingBuf_Push(&uartRxRb, byte);
    }
  }
}

/* Private functions --------------------------------------------------------*/

