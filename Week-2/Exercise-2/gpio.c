#include "gpio.h"

#define SET_BIT(reg, pos) ((reg) |= (1U << (pos)))
#define CLEAR_BIT(reg, pos) ((reg) &= ~(1U << (pos)))
#define TOGGLE_BIT(reg, pos) (((reg)) ^= (1U << (pos)))
#define READ_BIT(reg, pos) (((reg) & (1U << (pos))) >> (pos))

#define SET_BITS_MASK(reg, pos, mask) ((reg) |= ((mask) << (pos)))
#define CLEAR_BITS_MASK(reg, pos, mask) ((reg) &= ~((mask) << (pos)))
#define TOGGLE_BITS_MASK(reg, pos, mask) ((reg) ^= ((mask) << (pos)))
#define READ_BITS_MASK(reg, pos, mask) (((reg) & ((mask) << (pos))) >> (pos))

uint32_t GPIO_Pin_Write(GPIO_Typedef *GPIOx, uint32_t pin_number,
                        uint32_t pin_state) {
  uint32_t tmpReg = 0U;

  if (pin_number > 15) {
    return EXEC_ERR;
  }

  tmpReg = GPIOx->ODR;
  if (pin_state == 1U) {
    SET_BIT(tmpReg, pin_number);
  } else {
    CLEAR_BIT(tmpReg, pin_number);
  }
  GPIOx->ODR = tmpReg;
  return EXEC_OK;
}

uint32_t GPIO_Pin_Read(GPIO_Typedef *GPIOx, uint32_t pin_number) {
  uint32_t tmpReg = 0U;

  if (pin_number > 15) {
    return EXEC_ERR;
  }

  tmpReg = GPIOx->IDR;
  return READ_BIT(tmpReg, pin_number);
}

uint32_t GPIO_Set_Config(GPIO_Typedef *GPIOx, GPIO_Config_t *conf) {

  uint32_t tmpReg = 0U;
  uint32_t mask = 0U;

  if (conf == (void *)0) {
    return EXEC_ERR;
  }

  for (uint8_t iter = 0; iter < 16; iter++) {

    if (conf->pins & (1U << iter)) {
      // set mode
      tmpReg = GPIOx->MODER;
      CLEAR_BITS_MASK(tmpReg, iter * 2, 3U);
      SET_BITS_MASK(tmpReg, iter * 2, conf->mode);

      GPIOx->MODER = tmpReg;

      // set otype
      tmpReg = GPIOx->OTYPER;
      CLEAR_BIT(tmpReg, iter);
      if (conf->otype == 1U) {
        SET_BIT(tmpReg, iter);
      }
      GPIOx->OTYPER = tmpReg;

      // set speed
      tmpReg = GPIOx->OSPEEDR;
      CLEAR_BITS_MASK(tmpReg, 3U, iter * 2);
      SET_BITS_MASK(tmpReg, conf->speed, iter * 2);
      GPIOx->OSPEEDR = tmpReg;

      // set pullup
      tmpReg = GPIOx->PUPDR;
      CLEAR_BITS_MASK(tmpReg, 3U, iter * 2);
      SET_BITS_MASK(tmpReg, conf->pullup, iter * 2);
      GPIOx->PUPDR = tmpReg;

      // set AFRL
      if (iter < 8) {
        tmpReg = GPIOx->AFRL;
        CLEAR_BITS_MASK(tmpReg, iter * 4, 15U);
        SET_BITS_MASK(tmpReg, conf->AF_L, iter * 4);
        GPIOx->AFRL = tmpReg;
      } else {
        // set AFRH
        tmpReg = GPIOx->AFRH;
        CLEAR_BITS_MASK(tmpReg, (iter - 8) * 4, 15U);
        SET_BITS_MASK(tmpReg, conf->AF_H, (iter - 8) * 4);
        GPIOx->AFRH = tmpReg;
      }
    }
  }
  return EXEC_OK;
}

uint32_t GPIO_Get_Config(GPIO_Typedef *GPIOx, GPIO_Config_t *conf,
                         uint8_t pin_number) {
  uint32_t tmpReg = 0U;
  uint32_t mask = 0U;
  if ((pin_number > 15) || (conf == (void *)0)) {
    return EXEC_ERR;
  }
  // get mode
  tmpReg = GPIOx->MODER;
  tmpReg = READ_BITS_MASK(tmpReg, pin_number * 2, 3U);
  conf->mode = tmpReg;

  // get otype
  tmpReg = GPIOx->OTYPER;
  tmpReg = READ_BIT(tmpReg, pin_number);
  conf->otype = tmpReg;

  // get speed
  tmpReg = GPIOx->OSPEEDR;
  tmpReg = READ_BITS_MASK(tmpReg, pin_number * 2, 3U);
  conf->speed = tmpReg;

  // get pullup
  tmpReg = GPIOx->PUPDR;
  tmpReg = READ_BITS_MASK(tmpReg, pin_number * 2, 3U);
  conf->pullup = tmpReg;

  // get AFRL
  if (pin_number < 8) {

    tmpReg = GPIOx->AFRL;
    tmpReg = READ_BITS_MASK(tmpReg, pin_number * 4, 15U);
    conf->AF_L = tmpReg;
  } else {

    // get AFRH
    tmpReg = GPIOx->AFRH;
    tmpReg = READ_BITS_MASK(tmpReg, (pin_number - 8) * 4, 15U);
    conf->AF_H = tmpReg;
  }
  return EXEC_OK;
}
