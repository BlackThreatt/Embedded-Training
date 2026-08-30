/**
 ******************************************************************************
 * @file           : gpio_driver.c
 * @brief          : Driver layer for GPIOx peripherals, built on top of
 * gpio_hal
 * @author         : Mohamed Ali BESSAIDI
 * @date           : 26 Aug 2026
 *******************************************************************************
 * @attention
 *
 * Copyright (c) 2026 MOHAMED ALI BESSAIDI.
 * All rights reserved.
 *
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "gpio_driver.h"
#include "gpio_hal.h"
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

/**
 * @brief  Configures a GPIO pin according to the given configuration
 *         (mode, output type, speed, pull, alternate function).
 * @param  pins Pointer to the GPIO pin/port identity to configure.
 * @param  conf Pointer to a GPIO_Config_t describing the desired
 *              mode, output type, speed, pull, and alternate function.
 * @retval None
 */
void GPIO_DRV_Init(GPIO_Pin_t *io, GPIO_Config_t *conf) {
  HAL_GPIO_SetMode(io->port, io->pin, conf->mode);
  HAL_GPIO_SetOutputType(io->port, io->pin, conf->otype);
  HAL_GPIO_SetSpeed(io->port, io->pin, conf->speed);
  HAL_GPIO_SetPull(io->port, io->pin, conf->pullup);
  HAL_GPIO_SetAF(io->port, io->pin, conf->af);
}

/**
 * @brief  Sets or clears the output state of a single GPIO pin.
 * @param  pin   Pointer to the GPIO pin identity to write to.
 * @param  state Desired pin state (0 = reset, non-zero = set).
 * @retval None
 */
void GPIO_DRV_Write(GPIO_Pin_t *io, GPIO_PinState state) {
  HAL_GPIO_PinWrite(io->port, io->pin, state);
}

/**
 * @brief  Reads the current input state of a single GPIO pin.
 * @param  pin Pointer to the GPIO pin identity to read.
 * @retval Current state of the pin (set or reset).
 */
GPIO_PinState GPIO_DRV_Read(GPIO_Pin_t *io) {
  return HAL_GPIO_PinRead(io->port, io->pin);
}

/**
 * @brief  Toggles the current output state of a single GPIO pin.
 * @param  pin Pointer to the GPIO pin identity to toggle.
 * @retval None
 */
void GPIO_DRV_Toggle(GPIO_Pin_t *io) { HAL_GPIO_PinToggle(io->port, io->pin); }
/* Exported functions
 * --------------------------------------------------------------*/

/* Private functions
 * -----------------------------------------------------------------*/
