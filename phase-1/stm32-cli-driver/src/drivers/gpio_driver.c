/**
 ******************************************************************************
 * @file           : gpio_driver.c
 * @brief          : Driver layer for GPIOx peripherals, built on top of
 * gpio_hal
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
#include "gpio_driver.h"
#include <stddef.h>
/* Private typedef
 * -------------------------------------------------------------*/

/* Private define
 * ---------------------------------------------------------------*/

/* Private macro
 * ------------------------------------------------------------------*/

/* Private variables
 * --------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Exported functions
 * ---------------------------------------------------------*/

error_t GPIO_DRV_Init(GPIO_Pin_t *io, GPIO_Config_t *conf) {
  error_t err;

  if (io == NULL || conf == NULL) {
    return ERR_NULL_PTR;
  }

  err = HAL_GPIO_SetMode(io->port, io->pin, conf->mode);
  if (err != ERR_OK) {
    return err;
  }

  err = HAL_GPIO_SetOutputType(io->port, io->pin, conf->otype);
  if (err != ERR_OK) {
    return err;
  }

  err = HAL_GPIO_SetSpeed(io->port, io->pin, conf->speed);
  if (err != ERR_OK) {
    return err;
  }

  err = HAL_GPIO_SetPull(io->port, io->pin, conf->pullup);
  if (err != ERR_OK) {
    return err;
  }

  return HAL_GPIO_SetAF(io->port, io->pin, conf->af);
}

error_t GPIO_DRV_Write(GPIO_Pin_t *io, GPIO_PinState state) {
  if (io == NULL) {
    return ERR_NULL_PTR;
  }
  return HAL_GPIO_PinWrite(io->port, io->pin, state);
}

error_t GPIO_DRV_Read(GPIO_Pin_t *io, GPIO_PinState *out_state) {
  if (io == NULL || out_state == NULL) {
    return ERR_NULL_PTR;
  }
  return HAL_GPIO_PinRead(io->port, io->pin, out_state);
}

error_t GPIO_DRV_Toggle(GPIO_Pin_t *io) {
  if (io == NULL) {
    return ERR_NULL_PTR;
  }
  return HAL_GPIO_PinToggle(io->port, io->pin);
}

/* Private functions
 * -----------------------------------------------------------*/
