/**
 ******************************************************************************
 * @file           : logger.c
 * @brief          : UART based logging module for STM32F429xx
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
#include "logger.h"
#include "error.h"
#include "stdint.h"
#include "uart_driver.h"
/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes
 * ------------------------------------------------*/

/* Exported functions
 * ----------------------------------------------------------*/
error_t Logger_Init(void) {
  USART_Config_t conf = {
      .baudrate = 115200,
      .word_length = UART_WORDLENGTH_8B,
      .parity = UART_PARITY_NONE,
      .stop_bits = UART_STOPBITS_1,
      .oversampling = UART_OVERSAMPLING_16,
      .mode = UART_MODE_TX_RX,
      .it_flags = UART_INTERRUPT_RXNEIE,
  };
  return UART_DRV_Init(&conf);
}

error_t Logger_PrintString(const char *str) {
  error_t err;
  if (str == NULL) {
    return ERR_NULL_PTR;
  }
  while (*str != '\0') {
    err = UART_DRV_Transmit((const uint8_t *)str, 1);
    if (err != ERR_OK && err != ERR_BUFFER_FULL) {
      return err;
    }
    str++;
  }
  return ERR_OK;
}
/* Private functions
 * -------------------------------------------------------------*/
