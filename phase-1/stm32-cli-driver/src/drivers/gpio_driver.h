/**
 ******************************************************************************
 * @file           : gpio_driver.h
 * @brief          : Header file for gpio_driver.c
 * @author         : Mohamed Ali BESSAIDI
 * @date           : 26 Aug 2026
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 MOHAMED ALI BESSAIDI.
 * All rights reserved.
 *
 ******************************************************************************
 */

#ifndef __GPIO_DRIVER_H
#define __GPIO_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gpio_hal.h"
#include <stdint.h>

/* Exported types ------------------------------------------------------------*/
/**
 * @brief GPIO driver configuration structure passed to GPIO_DRV_Init().
 */
typedef struct {
  GPIO_PinMode mode;
  GPIO_PinOType otype;
  GPIO_PinSpeed speed;
  GPIO_PinPull pullup;
  uint8_t af;
} GPIO_Config_t;

typedef struct {
  GPIO_TypeDef *port;
  uint16_t pin;
} GPIO_Pin_t;
/* Exported constants --------------------------------------------------------*/

/* Exported macros
 * ------------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
/**
 * @brief  Configures a GPIO pin according to the given configuration
 *         (mode, output type, speed, pull, alternate function).
 * @param  io Pointer to the GPIO pin/port identity to configure.
 * @param  conf Pointer to a GPIO_Config_t describing the desired
 *              mode, output type, speed, pull, and alternate function.
 * @retval None
 */
void GPIO_DRV_Init(GPIO_Pin_t *io, GPIO_Config_t *conf);

/**
 * @brief  Sets or clears the output state of a single GPIO pin.
 * @param  io   Pointer to the GPIO pin identity to write to.
 * @param  state Desired pin state (0 = reset, non-zero = set).
 * @retval None
 */
void GPIO_DRV_Write(GPIO_Pin_t *io, GPIO_PinState state);

/**
 * @brief  Reads the current input state of a single GPIO pin.
 * @param  io Pointer to the GPIO pin identity to read.
 * @retval Current state of the pin (set or reset).
 */
GPIO_PinState GPIO_DRV_Read(GPIO_Pin_t *io);

/**
 * @brief  Toggles the current output state of a single GPIO pin.
 * @param  io Pointer to the GPIO pin identity to toggle.
 * @retval None
 */
void GPIO_DRV_Toggle(GPIO_Pin_t *io);
#ifdef __cplusplus
}
#endif

#endif /* __GPIO_DRIVER_H */
