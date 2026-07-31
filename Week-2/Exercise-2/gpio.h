#ifndef __GPIO_H__
#define __GPIO_H__
#include <stdint.h>

#define SET_BIT(reg, pos) ((reg) |= (1U << (pos)))
#define CLEAR_BIT(reg, pos) ((reg) &= ~(1U << (pos)))
#define TOGGLE_BIT(reg, pos) (((reg)) ^= (1U << (pos)))
#define READ_BIT(reg, pos) (((reg) & (1U << (pos))) >> (pos))

#define SET_BITS_MASK(reg, pos, mask) ((reg) |= ((mask) << (pos)))
#define CLEAR_BITS_MASK(reg, pos, mask) ((reg) &= ~((mask) << (pos)))
#define TOGGLE_BITS_MASK(reg, pos, mask) ((reg) ^= ((mask) << (pos)))
#define READ_BITS_MASK(reg, pos, mask) (((reg) & ((mask) << (pos))) >> (pos))

#define EXEC_OK 0x7F7F7F7F
#define EXEC_ERR 0x5F5F5F5F

typedef struct {
  volatile uint32_t MODER;
  volatile uint32_t OTYPER;
  volatile uint32_t OSPEEDR;
  volatile uint32_t PUPDR;
  const volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t LCKR;
  volatile uint32_t AFRL;
  volatile uint32_t AFRH;
} GPIO_Typedef;

#define T_GPIO_BASE (0x40020000UL)
#define T_GPIOA ((GPIO_Typedef *)T_GPIO_BASE)
#define T_GPIOC ((GPIO_Typedef *)(T_GPIO_BASE + 0x0800UL))
#define T_GPIOG ((GPIO_Typedef *)(T_GPIO_BASE + 0x1800UL))

typedef struct {
  uint8_t mode;
  uint8_t otype;
  uint8_t speed;
  uint8_t pullup;
  uint32_t AF_L;
  uint32_t AF_H;
  uint16_t pins;
} GPIO_Config_t;

uint32_t GPIO_Pin_Write(GPIO_Typedef *GPIOx, uint32_t pin_number,
                        uint32_t pin_state);
uint32_t GPIO_Pin_Read(GPIO_Typedef *igpi, uint32_t pin_number);
uint32_t GPIO_Set_Config(GPIO_Typedef *GPIOx, GPIO_Config_t *conf);
uint32_t GPIO_Get_Config(GPIO_Typedef *GPIOx, GPIO_Config_t *conf,
                         uint8_t pin_number);
#endif // __GPIO_H__
