/**
 ******************************************************************************
 * @file           : gpio_hal.c
 * @brief          : Register-level access layer for the STM32F429 GPIO
 * peripheral
 * @author         : Mohamed Ali BESSAIDI
 * @date           : 25 Aug 2026
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

/**
 * @brief  Sets or clears a single GPIO output pin.
 * @param  GPIOx      Pointer to the GPIO port register block.
 * @param  pin_number Pin number (0-15).
 * @param  pin_state  Desired pin state (0 = reset, non-zero = set).
 * @retval None
 */
void HAL_GPIO_PinWrite(GPIO_TypeDef *GPIOx, uint16_t pin_number,
                       GPIO_PinState pin_state) {
  if (pin_state == PIN_STATE_SET) {
    GPIOx->BSRR = pin_number;
  } else {
    GPIOx->BSRR |= (uint32_t)pin_number << 16U;
  }
}

/**
 * @brief  Reads the current input state of a single GPIO pin.
 * @param  GPIOx      Pointer to the GPIO port register block.
 * @param  pin_number Pin number (0-15).
 * @retval Current state of the pin (set or reset).
 */
GPIO_PinState HAL_GPIO_PinRead(GPIO_TypeDef *GPIOx, uint16_t pin_number) {
  return !!(GPIOx->IDR & (1U << pin_number));
}

/**
 * @brief  Toggles the current output state of a single GPIO pin.
 * @param  GPIOx      Pointer to the GPIO port register block.
 * @param  pin_number Pin number (0-15).
 * @retval None
 */
void HAL_GPIO_PinToggle(GPIO_TypeDef *GPIOx, uint16_t pin_number) {
  GPIOx->ODR ^= (1U << pin_number);
}

/**
 * @brief  Configures the mode (input, output, alternate function, analog)
 *         of a single GPIO pin.
 * @param  GPIOx      Pointer to the GPIO port register block.
 * @param  pin_number Pin number (0-15).
 * @param  mode       Desired pin mode.
 * @retval None
 */
void HAL_GPIO_SetMode(GPIO_TypeDef *GPIOx, uint16_t pin_number,
                      GPIO_PinMode mode) {
  GPIOx->MODER &= ~(3U << (pin_number * 2));
  GPIOx->MODER |= (mode << (pin_number * 2));
}

/**
 * @brief  Configures the output type (push-pull or open-drain) of a
 *         single GPIO pin.
 * @param  GPIOx       Pointer to the GPIO port register block.
 * @param  pin_number  Pin number (0-15).
 * @param  outputType  Desired output type.
 * @retval None
 */
void HAL_GPIO_SetOutputType(GPIO_TypeDef *GPIOx, uint16_t pin_number,
                            GPIO_PinOType outputType) {
  GPIOx->OTYPER &= ~(1U << pin_number);
  GPIOx->OTYPER |= (outputType << pin_number);
}

/**
 * @brief  Configures the output speed of a single GPIO pin.
 * @param  GPIOx      Pointer to the GPIO port register block.
 * @param  pin_number Pin number (0-15).
 * @param  speed      Desired output speed setting.
 * @retval None
 */
void HAL_GPIO_SetSpeed(GPIO_TypeDef *GPIOx, uint16_t pin_number,
                       uint32_t speed) {
  GPIOx->OSPEEDR &= ~(3U << (pin_number * 2));
  GPIOx->OSPEEDR |= (speed << (pin_number * 2));
}

/**
 * @brief  Configures the pull-up/pull-down state of a single GPIO pin.
 * @param  GPIOx      Pointer to the GPIO port register block.
 * @param  pin_number Pin number (0-15).
 * @param  pull       Desired pull configuration (none, pull-up, pull-down).
 * @retval None
 */
void HAL_GPIO_SetPull(GPIO_TypeDef *GPIOx, uint16_t pin_number,
                      GPIO_PinPull pull) {
  GPIOx->PUPDR &= ~(3U << (pin_number * 2));
  GPIOx->PUPDR |= (pull << (pin_number * 2));
}

/**
 * @brief  Selects the alternate function for a pin.
 * @param  GPIOx      Pointer to the GPIO port register block.
 * @param  pin_number Pin number (0-15).
 * @param  af        Alternate function selector.
 * @retval None
 */
void HAL_GPIO_SetAF(GPIO_TypeDef *GPIOx, uint16_t pin_number, uint8_t af) {
  if (pin_number < 8) {
    GPIOx->AFR[0] &= ~(15U << (pin_number * 4));
    GPIOx->AFR[0] |= (af << (pin_number * 4));
  } else {
    GPIOx->AFR[1] &= ~(15U << ((pin_number - 8) * 4));
    GPIOx->AFR[1] |= (af << ((pin_number - 8) * 4));
  }
}

/**
 * @brief  Reads the configured mode of a single GPIO pin.
 * @param  GPIOx      Pointer to the GPIO port register block.
 * @param  pin_number Pin number (0-15).
 * @retval Currently configured mode value.
 */
GPIO_PinMode HAL_GPIO_GetMode(GPIO_TypeDef *GPIOx, uint16_t pin_number) {
  return ((GPIOx->MODER & (3U << (pin_number * 2))) >> (pin_number * 2));
}

/**
 * @brief  Reads the configured output type of a single GPIO pin.
 * @param  GPIOx      Pointer to the GPIO port register block.
 * @param  pin_number Pin number (0-15).
 * @retval Currently configured output type value.
 */
GPIO_PinOType HAL_GPIO_GetOutputType(GPIO_TypeDef *GPIOx, uint16_t pin_number) {
  return ((GPIOx->OTYPER & (1U << pin_number)) >> pin_number);
}

/**
 * @brief  Reads the configured output speed of a single GPIO pin.
 * @param  GPIOx      Pointer to the GPIO port register block.
 * @param  pin_number Pin number (0-15).
 * @retval Currently configured speed value.
 */
GPIO_PinSpeed HAL_GPIO_GetSpeed(GPIO_TypeDef *GPIOx, uint16_t pin_number) {
  return ((GPIOx->OSPEEDR & (3U << (pin_number * 2))) >> (pin_number * 2));
}

/**
 * @brief  Reads the configured pull-up/pull-down state of a single GPIO pin.
 * @param  GPIOx      Pointer to the GPIO port register block.
 * @param  pin_number Pin number (0-15).
 * @retval Currently configured pull value.
 */
GPIO_PinPull HAL_GPIO_GetPull(GPIO_TypeDef *GPIOx, uint16_t pin_number) {
  return ((GPIOx->PUPDR & (3U << (pin_number * 2))) >> (pin_number * 2));
}

/**
 * @brief  Reads the alternate function selected for a pin.
 * @param  GPIOx      Pointer to the GPIO port register block.
 * @param  pin_number Pin number (0-15).
 * @retval Currently configured alternate function selector.
 */
uint8_t HAL_GPIO_GetAF(GPIO_TypeDef *GPIOx, uint16_t pin_number) {
  if (pin_number < 8) {
    return (GPIOx->AFR[0] & (15U << (pin_number * 4)) >> pin_number * 4);
  }
  return (GPIOx->AFR[1] &
          (15U << ((pin_number - 8) * 4)) >> (pin_number - 8) * 4);
}

/* Private functions
 * -----------------------------------------------------------------*/
