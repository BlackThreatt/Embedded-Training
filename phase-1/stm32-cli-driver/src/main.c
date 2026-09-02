#include "common/logger.h"
#include "drivers/uart_driver.h"
#include "logger.h"
#include <stdint.h>
#include <stm32f4xx.h>

USART_Config_t uartConf;

int main(void) {
  error_t err;
  // Initialize USART1
  uartConf.baudrate = 115200;
  uartConf.mode = UART_MODE_TX_RX;
  uartConf.parity = UART_PARITY_NONE;
  uartConf.stop_bits = UART_STOPBITS_1;
  uartConf.oversampling = UART_OVERSAMPLING_16;
  uartConf.word_length = UART_WORDLENGTH_8B;
  uartConf.it_flags = UART_INTERRUPT_RXNEIE;

  err = UART_DRV_Init(&uartConf);
  if (err != ERR_OK) {
    return err;
  }

  // uint8_t buf[3] = {65, 66, 67};
  // api_uart_write(buf, 3);
  LOG_DEBUG("LOG_DEBUG TEST");
  LOG_INFO("LOG_INFO TEST");
  LOG_ERROR("LOG_ERROR TEST");
  // uint8_t recv[3];
  // api_uart_read(recv, 3);
  while (1) {
  }
}
