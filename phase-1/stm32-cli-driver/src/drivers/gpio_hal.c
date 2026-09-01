/**
 ******************************************************************************
 * @file           : gpio_hal.c
 * @brief          : Register-level access layer for the STM32F429 GPIO
 * peripheral
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
#include "gpio_hal.h"
#include <stddef.h>
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

/* Exported functions
 * --------------------------------------------------------------*/

error_t HAL_GPIO_PinWrite(GPIO_TypeDef *GPIOx, uint16_t pin_number,
                          GPIO_PinState pin_state) {
  if (GPIOx == NULL) {
    return ERR_NULL_PTR;
  }
  if (pin_number > 15U) {
    return ERR_INVALID_PARAM;
  }

  if (pin_state == PIN_STATE_SET) {
    GPIOx->BSRR = (uint32_t)(1U << pin_number);
  } else {
    GPIOx->BSRR = (uint32_t)(1U << pin_number) << 16U;
  }
  return ERR_OK;
}

error_t HAL_GPIO_PinRead(GPIO_TypeDef *GPIOx, uint16_t pin_number,
                         GPIO_PinState *out_state) {
  if (GPIOx == NULL || out_state == NULL) {
    return ERR_NULL_PTR;
  }
  if (pin_number > 15U) {
    return ERR_INVALID_PARAM;
  }

  *out_state = !!(GPIOx->IDR & (1U << pin_number));
  return ERR_OK;
}

error_t HAL_GPIO_PinToggle(GPIO_TypeDef *GPIOx, uint16_t pin_number) {
  if (GPIOx == NULL) {
    return ERR_NULL_PTR;
  }
  if (pin_number > 15U) {
    return ERR_INVALID_PARAM;
  }

  GPIOx->ODR ^= (1U << pin_number);
  return ERR_OK;
}

error_t HAL_GPIO_SetMode(GPIO_TypeDef *GPIOx, uint16_t pin_number,
                         GPIO_PinMode mode) {
  if (GPIOx == NULL) {
    return ERR_NULL_PTR;
  }
  if (pin_number > 15U) {
    return ERR_INVALID_PARAM;
  }
  switch (mode) {
  case PIN_MODE_INPUT:
  case PIN_MODE_OUTPUT:
  case PIN_MODE_AF:
  case PIN_MODE_ANALOG:
    break;
  default:
    return ERR_INVALID_PARAM;
  }

  GPIOx->MODER &= ~(3U << (pin_number * 2U));
  GPIOx->MODER |= ((uint32_t)mode << (pin_number * 2U));
  return ERR_OK;
}

error_t HAL_GPIO_SetOutputType(GPIO_TypeDef *GPIOx, uint16_t pin_number,
                               GPIO_PinOType outputType) {
  if (GPIOx == NULL) {
    return ERR_NULL_PTR;
  }
  if (pin_number > 15U) {
    return ERR_INVALID_PARAM;
  }
  switch (outputType) {
  case PIN_OTYPE_PP:
  case PIN_OTYPE_OPENDRAIN:
    break;
  default:
    return ERR_INVALID_PARAM;
  }

  GPIOx->OTYPER &= ~(1U << pin_number);
  GPIOx->OTYPER |= ((uint32_t)outputType << pin_number);
  return ERR_OK;
}

error_t HAL_GPIO_SetSpeed(GPIO_TypeDef *GPIOx, uint16_t pin_number,
                          GPIO_PinSpeed speed) {
  if (GPIOx == NULL) {
    return ERR_NULL_PTR;
  }
  if (pin_number > 15U) {
    return ERR_INVALID_PARAM;
  }
  switch (speed) {
  case PIN_LOW_SPEED:
  case PIN_MEDIUM_SPEED:
  case PIN_HIGH_SPEED:
  case PIN_VERY_HIGH_SPEED:
    break;
  default:
    return ERR_INVALID_PARAM;
  }

  GPIOx->OSPEEDR &= ~(3U << (pin_number * 2U));
  GPIOx->OSPEEDR |= ((uint32_t)speed << (pin_number * 2U));
  return ERR_OK;
}

error_t HAL_GPIO_SetPull(GPIO_TypeDef *GPIOx, uint16_t pin_number,
                         GPIO_PinPull pull) {
  if (GPIOx == NULL) {
    return ERR_NULL_PTR;
  }
  if (pin_number > 15U) {
    return ERR_INVALID_PARAM;
  }
  switch (pull) {
  case PIN_PULL_NO_PP:
  case PIN_PULL_PULL_UP:
  case PIN_PULL_PULL_DOWN:
    break;
  default:
    return ERR_INVALID_PARAM;
  }

  GPIOx->PUPDR &= ~(3U << (pin_number * 2U));
  GPIOx->PUPDR |= ((uint32_t)pull << (pin_number * 2U));
  return ERR_OK;
}

error_t HAL_GPIO_SetAF(GPIO_TypeDef *GPIOx, uint16_t pin_number, uint8_t af) {
  if (GPIOx == NULL) {
    return ERR_NULL_PTR;
  }
  if ((pin_number > 15U) || (af > 15U)) {
    return ERR_INVALID_PARAM;
  }

  if (pin_number < 8U) {
    GPIOx->AFR[0] &= ~(15U << (pin_number * 4U));
    GPIOx->AFR[0] |= ((uint32_t)af << (pin_number * 4U));
  } else {
    GPIOx->AFR[1] &= ~(15U << ((pin_number - 8U) * 4U));
    GPIOx->AFR[1] |= ((uint32_t)af << ((pin_number - 8U) * 4U));
  }
  return ERR_OK;
}

error_t HAL_GPIO_GetMode(GPIO_TypeDef *GPIOx, uint16_t pin_number,
                         GPIO_PinMode *out_mode) {
  if (GPIOx == NULL || out_mode == NULL) {
    return ERR_NULL_PTR;
  }
  if (pin_number > 15U) {
    return ERR_INVALID_PARAM;
  }

  *out_mode = (GPIO_PinMode)((GPIOx->MODER & (3U << (pin_number * 2U))) >>
                             (pin_number * 2U));
  return ERR_OK;
}

error_t HAL_GPIO_GetOutputType(GPIO_TypeDef *GPIOx, uint16_t pin_number,
                               GPIO_PinOType *out_otype) {
  if (GPIOx == NULL || out_otype == NULL) {
    return ERR_NULL_PTR;
  }
  if (pin_number > 15U) {
    return ERR_INVALID_PARAM;
  }

  *out_otype =
      (GPIO_PinOType)((GPIOx->OTYPER & (1U << pin_number)) >> pin_number);
  return ERR_OK;
}

error_t HAL_GPIO_GetSpeed(GPIO_TypeDef *GPIOx, uint16_t pin_number,
                          GPIO_PinSpeed *out_speed) {
  if (GPIOx == NULL || out_speed == NULL) {
    return ERR_NULL_PTR;
  }
  if (pin_number > 15U) {
    return ERR_INVALID_PARAM;
  }

  *out_speed = (GPIO_PinSpeed)((GPIOx->OSPEEDR & (3U << (pin_number * 2U))) >>
                               (pin_number * 2U));
  return ERR_OK;
}

error_t HAL_GPIO_GetPull(GPIO_TypeDef *GPIOx, uint16_t pin_number,
                         GPIO_PinPull *out_pull) {
  if (GPIOx == NULL || out_pull == NULL) {
    return ERR_NULL_PTR;
  }
  if (pin_number > 15U) {
    return ERR_INVALID_PARAM;
  }

  *out_pull = (GPIO_PinPull)((GPIOx->PUPDR & (3U << (pin_number * 2U))) >>
                             (pin_number * 2U));
  return ERR_OK;
}

error_t HAL_GPIO_GetAF(GPIO_TypeDef *GPIOx, uint16_t pin_number,
                       uint8_t *out_af) {
  if (GPIOx == NULL || out_af == NULL) {
    return ERR_NULL_PTR;
  }
  if (pin_number > 15U) {
    return ERR_INVALID_PARAM;
  }

  if (pin_number < 8U) {
    *out_af = (uint8_t)((GPIOx->AFR[0] & (15U << (pin_number * 4U))) >>
                        (pin_number * 4U));
  } else {
    *out_af = (uint8_t)((GPIOx->AFR[1] & (15U << ((pin_number - 8U) * 4U))) >>
                        ((pin_number - 8U) * 4U));
  }
  return ERR_OK;
}

/* Private functions
 * -----------------------------------------------------------------*/
