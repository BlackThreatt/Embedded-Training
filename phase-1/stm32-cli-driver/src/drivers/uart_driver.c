/**
 ******************************************************************************
 * @file           : uart_driver.c
 * @brief          : Driver layer for USART peripherals, built on top of
 * uart_hal
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
#include "uart_driver.h"
#include "RingBuffer.h"
#include "board_config.h"
#include "gpio_driver.h"
#include <stddef.h>

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static RingBuffer_t uartRxRb;
static RingBuffer_t uartTxRb;

static GPIO_Pin_t uartTxPin = {.port = DEBUG_UART_TX_PORT,
                               .pin = DEBUG_UART_TX_PIN};
static GPIO_Pin_t uartRxPin = {.port = DEBUG_UART_RX_PORT,
                               .pin = DEBUG_UART_RX_PIN};

/* Private function prototypes
 * ------------------------------------------------*/

/* Exported functions
 * ----------------------------------------------------------*/

error_t UART_DRV_Init(USART_Config_t *conf) {
  error_t err;

  if (conf == NULL) {
    return ERR_NULL_PTR;
  }

  err = RingBuf_Init(&uartRxRb);
  if (err != ERR_OK) {
    return err;
  }
  err = RingBuf_Init(&uartTxRb);
  if (err != ERR_OK) {
    return err;
  }

  // Initialize USART1 GPIOA Clock Config
  RCC->AHB1ENR |= (1U << 0);
  // Enable USART1 Clock
  RCC->APB2ENR |= (1U << 4);

  GPIO_Config_t uartPinConf = {
      .mode = PIN_MODE_AF,
      .otype = PIN_OTYPE_PP,
      .speed = PIN_HIGH_SPEED,
      .pullup = PIN_PULL_NO_PP,
      .af = DEBUG_UART_AF,
  };

  err = GPIO_DRV_Init(&uartTxPin, &uartPinConf);
  if (err != ERR_OK) {
    return err;
  }

  err = GPIO_DRV_Init(&uartRxPin, &uartPinConf);
  if (err != ERR_OK) {
    return err;
  }

  err = HAL_UART_SetWordLength(conf->word_length);
  if (err != ERR_OK) {
    return err;
  }

  err = HAL_UART_SetParity(conf->parity);
  if (err != ERR_OK) {
    return err;
  }

  err = HAL_UART_SetStopBits(conf->stop_bits);
  if (err != ERR_OK) {
    return err;
  }

  err = HAL_UART_SetOversampling(conf->oversampling);
  if (err != ERR_OK) {
    return err;
  }

  // INFO: value is temporary until RCC module is developed
  uint32_t pclk = 16000000UL;
  err = HAL_UART_SetBaudRate(pclk, conf->baudrate);
  if (err != ERR_OK) {
    return err;
  }

  err = HAL_UART_SetMode(conf->mode);
  if (err != ERR_OK) {
    return err;
  }

  if (conf->it_flags != UART_INTERRUPT_NO_IT) {
    NVIC_EnableIRQ(USART1_IRQn);
    err = HAL_UART_EnableIT(conf->it_flags);
    if (err != ERR_OK) {
      return err;
    }
  }

  return HAL_UART_Enable();
}

error_t UART_DRV_Transmit(const uint8_t *byte, size_t len) {
  error_t status = ERR_OK;
  error_t err;
  bool full = false;
  bool pushed = false;

  if (byte == NULL) {
    return ERR_NULL_PTR;
  }

  for (size_t iter = 0; iter < len; iter++) {
    err = RingBuf_IsFull(&uartTxRb, &full);
    if (err != ERR_OK) {
      return err;
    }
    if (full) {
      status = ERR_BUFFER_FULL;
      continue;
    }
    err = RingBuf_Push(&uartTxRb, byte[iter], &pushed);
    if (err != ERR_OK) {
      return err;
    }
    err = HAL_UART_EnableTxIRQ();
    (void)err;
  }
  return status;
}

error_t UART_DRV_Receive(uint8_t *data, size_t len) {
  error_t status = ERR_OK;
  error_t err;
  bool empty = false;
  bool popped = false;

  if (data == NULL) {
    return ERR_NULL_PTR;
  }

  for (size_t iter = 0; iter < len; iter++) {
    err = RingBuf_IsEmpty(&uartRxRb, &empty);
    if (err != ERR_OK) {
      return err;
    }
    if (empty) {
      return ERR_BUFFER_EMPTY;
    }
    err = RingBuf_Pop(&uartRxRb, &data[iter], &popped);
    if (err != ERR_OK) {
      return err;
    }
  }
  return status;
}

void USART1_IRQHandler(void) {
  error_t err;
  uint8_t byte;
  bool ready = false;
  bool popped = false;
  bool pushed = false;
  /* NOTE: There's no error propagation in ISR, Errors are voided to clean
   * terminal output*/
  err = HAL_UART_IsTxReady(&ready);
  if (ready) {
    err = RingBuf_Pop(&uartTxRb, &byte, &popped);
    if (popped) {
      err = HAL_UART_WriteByte(byte);
    } else {
      err = HAL_UART_DisableTxIRQ();
    }
  }

  err = HAL_UART_IsRxReady(&ready);
  if (ready) {
    err = HAL_UART_ReadByte(&byte);
    err = RingBuf_Push(&uartRxRb, byte, &pushed);
    if (!pushed) {
      uint8_t oldData;
      err = RingBuf_Pop(&uartRxRb, &oldData, &popped);
      err = RingBuf_Push(&uartRxRb, byte, &pushed);
    }
  }
  (void)err;
}

/* Private functions
 * -------------------------------------------------------------*/
