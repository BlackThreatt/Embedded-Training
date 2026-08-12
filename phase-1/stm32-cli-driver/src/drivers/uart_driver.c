#include "uart_driver.h"

void UART_Init(USART_TypeDef *UARTx, USART_Config_t *conf) {

  HAL_USART_SetWordLength(UARTx, conf->word_length);
  HAL_USART_SetParity(UARTx, conf->parity);
  HAL_USART_SetStopBits(UARTx, conf->stop_bits);
  HAL_USART_SetOversampling(UARTx, conf->oversampling);

  // INFO: value is temporary until RCC module is developed
  uint32_t pclk = 16000000UL;
  HAL_USART_SetBaudRate(UARTx, pclk, conf->baudrate);
  HAL_USART_SetMode(UARTx, conf->mode);
  HAL_USART_SetFlowControl(UARTx, conf->flow_control);

  if (conf->it_flags != UART_INTERRUPT_NO_IT) {
    HAL_USART_EnableIT(UARTx, conf->it_flags);
  }
  // Enable USART
  HAL_USART_Enable(UARTx);
}

void UART_Transmit(USART_TypeDef *UARTx, uint8_t byte) {
  HAL_USART_WriteByte(UARTx, byte);
}
uint8_t UART_Receive(USART_TypeDef *UARTx) { return HAL_USART_ReadByte(UARTx); }

void UART_EnableIT(USART_TypeDef *UARTx, uint8_t it) {
  HAL_USART_EnableIT(UARTx, it);
}

void UART_DisableIT(USART_TypeDef *UARTx, uint8_t it) {
  HAL_USART_DisableIT(UARTx, it);
}

bool UART_GetFlagStatus(USART_TypeDef *usart, uint32_t flag) {
  return HAL_USART_FlagIsSet(usart, flag);
}
