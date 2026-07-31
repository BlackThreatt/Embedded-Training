#ifndef __GPIO_H__
#define __GPIO_H__
#include <stdint.h>
#include <sys/types.h>

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

#define GPIO_Base (0x40020000UL)
#define GPIOA ((GPIO_Typedef *)GPIO_Base)

typedef struct {
  GPIO_Typedef *regs;
  uint8_t is_initialized;
} GPIO_Handle_t;

typedef struct {
  uint8_t mode;
  uint8_t otype;
  uint8_t speed;
  uint8_t pullup;
  uint32_t AF_L;
  uint32_t AF_H;
  uint16_t pins;
} GPIO_Config_t;

uint32_t GPIO_Pin_Write(GPIO_Handle_t *hgpio, uint32_t pin_number,
                        uint32_t pin_state);
uint32_t GPIO_Pin_Read(GPIO_Handle_t *hgpio, uint32_t pin_number);
uint32_t GPIO_Set_Config(GPIO_Handle_t *hgpio, GPIO_Config_t *conf);
uint32_t GPIO_Get_Config(GPIO_Handle_t *hgpio, GPIO_Config_t *conf,
                         uint8_t pin_number);
#endif // __GPIO_H__
