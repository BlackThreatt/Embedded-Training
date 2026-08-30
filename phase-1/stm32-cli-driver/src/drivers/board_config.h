/**
 ******************************************************************************
 * @file           : board_config.h
 * @brief          : Board peripherals mapping
 * @author         : Mohamed Ali BESSAIDI
 * @date           : 30 Aug 2026
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 MOHAMED ALI BESSAIDI.
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#include "gpio_driver.h"

#define DEBUG_UART_TX_PORT GPIOA
#define DEBUG_UART_TX_PIN 9U
#define DEBUG_UART_RX_PORT GPIOA
#define DEBUG_UART_RX_PIN 10U
#define DEBUG_UART_AF 7U /* AF7 = USART1 on PA9/PA10 */

#endif
