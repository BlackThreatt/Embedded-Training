/**
 ******************************************************************************
 * @file           : gpio_hal.h
 * @brief          : Header file for gpio_hal.c
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

#ifndef GPIO_HAL_H
#define GPIO_HAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "error.h"
#include "stm32f429xx.h"
#include <stdint.h>

/* Exported types ------------------------------------------------------------*/

typedef enum {
  PIN_STATE_RESET = 0,
  PIN_STATE_SET = !PIN_STATE_RESET
} GPIO_PinState;

typedef enum {
  PIN_MODE_INPUT = 0U,
  PIN_MODE_OUTPUT = 1U,
  PIN_MODE_AF = 2U,
  PIN_MODE_ANALOG = 3U
} GPIO_PinMode;

typedef enum {
  PIN_LOW_SPEED = 0U,
  PIN_MEDIUM_SPEED = 1U,
  PIN_HIGH_SPEED = 2U,
  PIN_VERY_HIGH_SPEED = 3U
} GPIO_PinSpeed;

typedef enum {
  PIN_PULL_NO_PP = 0U,
  PIN_PULL_PULL_UP = 1U,
  PIN_PULL_PULL_DOWN = 2U
} GPIO_PinPull;

typedef enum { PIN_OTYPE_PP = 0U, PIN_OTYPE_OPENDRAIN = 1U } GPIO_PinOType;

/* Exported constants --------------------------------------------------------*/

#define GPIO_PIN_0 ((uint16_t)0x0001)
#define GPIO_PIN_1 ((uint16_t)0x0002)
#define GPIO_PIN_2 ((uint16_t)0x0004)
#define GPIO_PIN_3 ((uint16_t)0x0008)
#define GPIO_PIN_4 ((uint16_t)0x0010)
#define GPIO_PIN_5 ((uint16_t)0x0020)
#define GPIO_PIN_6 ((uint16_t)0x0040)
#define GPIO_PIN_7 ((uint16_t)0x0080)
#define GPIO_PIN_8 ((uint16_t)0x0100)
#define GPIO_PIN_9 ((uint16_t)0x0200)
#define GPIO_PIN_10 ((uint16_t)0x0400)
#define GPIO_PIN_11 ((uint16_t)0x0800)
#define GPIO_PIN_12 ((uint16_t)0x1000)
#define GPIO_PIN_13 ((uint16_t)0x2000)
#define GPIO_PIN_14 ((uint16_t)0x4000)
#define GPIO_PIN_15 ((uint16_t)0x8000)
#define GPIO_PIN_All ((uint16_t)0xFFFF)

#define GPIO_AF0 ((uint8_t)0x00)
#define GPIO_AF1 ((uint8_t)0x01)
#define GPIO_AF2 ((uint8_t)0x02)
#define GPIO_AF3 ((uint8_t)0x03)
#define GPIO_AF4 ((uint8_t)0x04)
#define GPIO_AF5 ((uint8_t)0x05)
#define GPIO_AF6 ((uint8_t)0x06)
#define GPIO_AF7 ((uint8_t)0x07)
#define GPIO_AF8 ((uint8_t)0x08)
#define GPIO_AF9 ((uint8_t)0x09)
#define GPIO_AF10 ((uint8_t)0x0A)
#define GPIO_AF11 ((uint8_t)0x0B)
#define GPIO_AF12 ((uint8_t)0x0C)
#define GPIO_AF13 ((uint8_t)0x0D)
#define GPIO_AF14 ((uint8_t)0x0E)
#define GPIO_AF15 ((uint8_t)0x0F)

/* Exported macros
 * ------------------------------------------------------------*/

#if defined(__GNUC__) || defined(__clang__)
#define ERR_CHECK __attribute__((warn_unused_result))
#else
#define ERR_CHECK
#endif

/* Exported functions prototypes
 * ----------------------------------------------*/

/**
 * @brief  Sets or clears a single GPIO output pin.
 * @param  GPIOx      Pointer to the GPIO port register block.
 * @param  pin_number Pin number (0-15).
 * @param  pin_state  Desired pin state (0 = reset, non-zero = set).
 * @retval ERR_OK on success, ERR_NULL_PTR if GPIOx is NULL,
 *         ERR_INVALID_PARAM if pin_number is out of range.
 */
ERR_CHECK error_t HAL_GPIO_PinWrite(GPIO_TypeDef *GPIOx, uint16_t pin_number,
                                    GPIO_PinState pin_state);

/**
 * @brief  Reads the current input state of a single GPIO pin.
 * @param  GPIOx      Pointer to the GPIO port register block.
 * @param  pin_number Pin number (0-15).
 * @param  out_state  Pointer to where the pin state will be written.
 * @retval ERR_OK on success, ERR_NULL_PTR if GPIOx or out_state is NULL,
 *         ERR_INVALID_PARAM if pin_number is out of range.
 */
ERR_CHECK error_t HAL_GPIO_PinRead(GPIO_TypeDef *GPIOx, uint16_t pin_number,
                                   GPIO_PinState *out_state);

/**
 * @brief  Toggles the current output state of a single GPIO pin.
 * @param  GPIOx      Pointer to the GPIO port register block.
 * @param  pin_number Pin number (0-15).
 * @retval ERR_OK on success, ERR_NULL_PTR if GPIOx is NULL,
 *         ERR_INVALID_PARAM if pin_number is out of range.
 */
ERR_CHECK error_t HAL_GPIO_PinToggle(GPIO_TypeDef *GPIOx, uint16_t pin_number);

/**
 * @brief  Configures the mode (input, output, alternate function, analog)
 *         of a single GPIO pin.
 * @param  GPIOx      Pointer to the GPIO port register block.
 * @param  pin_number Pin number (0-15).
 * @param  mode       Desired pin mode.
 * @retval ERR_OK on success, ERR_NULL_PTR if GPIOx is NULL,
 *         ERR_INVALID_PARAM if pin_number or mode is out of range.
 */
ERR_CHECK error_t HAL_GPIO_SetMode(GPIO_TypeDef *GPIOx, uint16_t pin_number,
                                   GPIO_PinMode mode);

/**
 * @brief  Configures the output type (push-pull or open-drain) of a
 *         single GPIO pin.
 * @param  GPIOx       Pointer to the GPIO port register block.
 * @param  pin_number  Pin number (0-15).
 * @param  outputType  Desired output type.
 * @retval ERR_OK on success, ERR_NULL_PTR if GPIOx is NULL,
 *         ERR_INVALID_PARAM if pin_number or outputType is out of range.
 */
ERR_CHECK error_t HAL_GPIO_SetOutputType(GPIO_TypeDef *GPIOx,
                                         uint16_t pin_number,
                                         GPIO_PinOType outputType);

/**
 * @brief  Configures the output speed of a single GPIO pin.
 * @param  GPIOx      Pointer to the GPIO port register block.
 * @param  pin_number Pin number (0-15).
 * @param  speed      Desired output speed setting.
 * @retval ERR_OK on success, ERR_NULL_PTR if GPIOx is NULL,
 *         ERR_INVALID_PARAM if pin_number or speed is out of range.
 */
ERR_CHECK error_t HAL_GPIO_SetSpeed(GPIO_TypeDef *GPIOx, uint16_t pin_number,
                                    GPIO_PinSpeed speed);

/**
 * @brief  Configures the pull-up/pull-down state of a single GPIO pin.
 * @param  GPIOx      Pointer to the GPIO port register block.
 * @param  pin_number Pin number (0-15).
 * @param  pull       Desired pull configuration (none, pull-up, pull-down).
 * @retval ERR_OK on success, ERR_NULL_PTR if GPIOx is NULL,
 *         ERR_INVALID_PARAM if pin_number or pull is out of range.
 */
ERR_CHECK error_t HAL_GPIO_SetPull(GPIO_TypeDef *GPIOx, uint16_t pin_number,
                                   GPIO_PinPull pull);

/**
 * @brief  Selects the alternate function for a pin.
 * @param  GPIOx      Pointer to the GPIO port register block.
 * @param  pin_number Pin number (0-15).
 * @param  af         Alternate function selector (0-15).
 * @retval ERR_OK on success, ERR_NULL_PTR if GPIOx is NULL,
 *         ERR_INVALID_PARAM if pin_number or af is out of range.
 */
ERR_CHECK error_t HAL_GPIO_SetAF(GPIO_TypeDef *GPIOx, uint16_t pin_number,
                                 uint8_t af);

/**
 * @brief  Reads the configured mode of a single GPIO pin.
 * @param  GPIOx      Pointer to the GPIO port register block.
 * @param  pin_number Pin number (0-15).
 * @param  out_mode   Pointer to where the mode will be written.
 * @retval ERR_OK on success, ERR_NULL_PTR if GPIOx or out_mode is NULL,
 *         ERR_INVALID_PARAM if pin_number is out of range.
 */
ERR_CHECK error_t HAL_GPIO_GetMode(GPIO_TypeDef *GPIOx, uint16_t pin_number,
                                   GPIO_PinMode *out_mode);

/**
 * @brief  Reads the configured output type of a single GPIO pin.
 * @param  GPIOx       Pointer to the GPIO port register block.
 * @param  pin_number  Pin number (0-15).
 * @param  out_otype   Pointer to where the output type will be written.
 * @retval ERR_OK on success, ERR_NULL_PTR if GPIOx or out_otype is NULL,
 *         ERR_INVALID_PARAM if pin_number is out of range.
 */
ERR_CHECK error_t HAL_GPIO_GetOutputType(GPIO_TypeDef *GPIOx,
                                         uint16_t pin_number,
                                         GPIO_PinOType *out_otype);

/**
 * @brief  Reads the configured output speed of a single GPIO pin.
 * @param  GPIOx      Pointer to the GPIO port register block.
 * @param  pin_number Pin number (0-15).
 * @param  out_speed  Pointer to where the speed will be written.
 * @retval ERR_OK on success, ERR_NULL_PTR if GPIOx or out_speed is NULL,
 *         ERR_INVALID_PARAM if pin_number is out of range.
 */
ERR_CHECK error_t HAL_GPIO_GetSpeed(GPIO_TypeDef *GPIOx, uint16_t pin_number,
                                    GPIO_PinSpeed *out_speed);

/**
 * @brief  Reads the configured pull-up/pull-down state of a single GPIO pin.
 * @param  GPIOx      Pointer to the GPIO port register block.
 * @param  pin_number Pin number (0-15).
 * @param  out_pull   Pointer to where the pull configuration will be written.
 * @retval ERR_OK on success, ERR_NULL_PTR if GPIOx or out_pull is NULL,
 *         ERR_INVALID_PARAM if pin_number is out of range.
 */
ERR_CHECK error_t HAL_GPIO_GetPull(GPIO_TypeDef *GPIOx, uint16_t pin_number,
                                   GPIO_PinPull *out_pull);

/**
 * @brief  Reads the alternate function selected for a pin.
 * @param  GPIOx      Pointer to the GPIO port register block.
 * @param  pin_number Pin number (0-15).
 * @param  out_af     Pointer to where the alternate function will be
 *                     written.
 * @retval ERR_OK on success, ERR_NULL_PTR if GPIOx or out_af is NULL,
 *         ERR_INVALID_PARAM if pin_number is out of range.
 */
ERR_CHECK error_t HAL_GPIO_GetAF(GPIO_TypeDef *GPIOx, uint16_t pin_number,
                                 uint8_t *out_af);

#ifdef __cplusplus
}
#endif

#endif /* GPIO_HAL_H */
