#include "drivers/uart_driver.h"
#include "error.h"
#include <stdint.h>
#include <stm32f4xx.h>

void api_uart_write(uint8_t *data, uint32_t len);
void api_uart_read(uint8_t *data, uint32_t len);

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

  uint8_t buf[3] = {65, 66, 67};
  api_uart_write(buf, 3);
  // uint8_t recv[3];
  // api_uart_read(recv, 3);
  while (1) {
  }
}

void api_uart_write(uint8_t *data, uint32_t len) {
  UART_DRV_Transmit(data, 3);
  // TODO: add status return
}
void api_uart_read(uint8_t *data, uint32_t len) {
  UART_DRV_Receive(data, len);
  // TODO: add status return
}
