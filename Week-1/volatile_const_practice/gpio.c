#include "gpio.h"

uint32_t GPIO_Pin_Write(GPIO_Handle_t *hgpio, uint32_t pin_number,
                        uint32_t pin_state) {
  uint32_t tmpReg = 0U;

  if (!(hgpio->is_initialized) || (pin_number > 15)) {
    return EXEC_ERR;
  }

  tmpReg = hgpio->regs->ODR;
  if (pin_state == 1U) {
    tmpReg |= (1U << pin_number);
  } else {
    tmpReg &= ~(1U << pin_number);
  }
  hgpio->regs->ODR = tmpReg;
  return EXEC_OK;
}

uint32_t GPIO_Pin_Read(GPIO_Handle_t *hgpio, uint32_t pin_number) {
  uint32_t tmpReg = 0U;

  if (!(hgpio->is_initialized) || (pin_number > 15)) {
    return EXEC_ERR;
  }

  uint32_t mask = (1U << pin_number);
  tmpReg = hgpio->regs->IDR;
  tmpReg &= mask;

  return (tmpReg >> pin_number);
}

uint32_t GPIO_Set_Config(GPIO_Handle_t *hgpio, GPIO_Config_t *conf) {

  uint32_t tmpReg = 0U;
  uint32_t mask = 0U;

  if (conf == (void *)0) {
    return EXEC_ERR;
  }

  for (uint8_t iter = 0; iter < 16; iter++) {

    if (conf->pins & (1U << iter)) {
      // set mode
      mask = (3U << (iter * 2));
      tmpReg = hgpio->regs->MODER;
      tmpReg &= ~mask;
      tmpReg |= (conf->mode << (iter * 2)) & mask;
      hgpio->regs->MODER = tmpReg;

      // set otype
      tmpReg = hgpio->regs->OTYPER;
      tmpReg &= ~(1U << iter);

      if (conf->otype == 1U) {
        tmpReg |= (1U << iter);
      }
      hgpio->regs->OTYPER = tmpReg;

      // set speed
      mask = (3U << (iter * 2));
      tmpReg = hgpio->regs->OSPEEDR;
      tmpReg &= ~mask;
      tmpReg |= (conf->speed << (iter * 2)) & mask;
      hgpio->regs->OSPEEDR = tmpReg;

      // set pullup
      mask = (3U << (iter * 2));
      tmpReg = hgpio->regs->PUPDR;
      tmpReg &= ~mask;
      tmpReg |= (conf->pullup << (iter * 2)) & mask;
      hgpio->regs->PUPDR = tmpReg;

      // set AFRL
      if (iter < 8) {

        mask = (15U << (iter * 4));
        tmpReg = hgpio->regs->AFRL;
        tmpReg &= ~mask;
        tmpReg |= (conf->AF_L << (iter * 4)) & mask;
        hgpio->regs->AFRL = tmpReg;
      } else {
        // set AFRH
        mask = (15U << ((iter - 8) * 4));
        tmpReg = hgpio->regs->AFRH;
        tmpReg &= ~mask;
        tmpReg |= (conf->AF_H << ((iter - 8) * 4)) & mask;
        hgpio->regs->AFRH = tmpReg;
      }
    }
  }
  hgpio->is_initialized = 1;
  return EXEC_OK;
}

uint32_t GPIO_Get_Config(GPIO_Handle_t *hgpio, GPIO_Config_t *conf,
                         uint8_t pin_number) {
  uint32_t tmpReg = 0U;
  uint32_t mask = 0U;
  if (!(hgpio->is_initialized) || (pin_number > 15) || (conf == (void *)0)) {
    return EXEC_ERR;
  }
  // get mode
  mask = (3U << (pin_number * 2));
  tmpReg = hgpio->regs->MODER;
  tmpReg &= mask;
  conf->mode = tmpReg >> (pin_number * 2);

  // get otype
  mask = (1U << pin_number);
  tmpReg = hgpio->regs->OTYPER;
  tmpReg &= mask;
  conf->otype = tmpReg >> pin_number;

  // get speed
  mask = (3U << (pin_number * 2));
  tmpReg = hgpio->regs->OSPEEDR;
  tmpReg &= mask;
  conf->speed = tmpReg >> (pin_number * 2);

  // get pullup
  mask = (3U << (pin_number * 2));
  tmpReg = hgpio->regs->PUPDR;
  tmpReg &= mask;
  conf->pullup = tmpReg >> (pin_number * 2);

  // get AFRL
  if (pin_number < 8) {

    mask = (15U << (pin_number * 4));
    tmpReg = hgpio->regs->AFRL;
    tmpReg &= mask;
    conf->AF_L = tmpReg >> (pin_number * 4);
  } else {

    // get AFRH
    mask = (3U << ((pin_number - 8) * 4));
    tmpReg = hgpio->regs->AFRH;
    tmpReg &= mask;
    conf->AF_H = tmpReg >> ((pin_number - 8) * 4);
  }
  return EXEC_OK;
}
