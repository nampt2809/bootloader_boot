//--thanhcm3--12--06--23--


#include "header_files.h"

///1.===========================================================================
uint8_t init_rs485(UART_Type *base,IRQn_Type interrupt, uint32_t baudrate){
  uint8_t err = NO_ERR;
  //UART_Deinit(base);
  uart_config_t config;
  
  /*
  * config.baudRate_Bps = 115200U;
  * config.parityMode = kUART_ParityDisabled;
  * config.stopBitCount = kUART_OneStopBit;
  * config.txFifoWatermark = 0;
  * config.rxFifoWatermark = 1;
  * config.enableTx = false;
  * config.enableRx = false;
  */
  UART_GetDefaultConfig(&config);
  
  config.baudRate_Bps = baudrate;
  config.enableTx     = true;
  config.enableRx     = true;
  
  UART_Init(base, &config, UART_CLK_FREQ);
  
  /* Enable RX interrupt. */
  UART_EnableInterrupts(base, kUART_RxDataRegFullInterruptEnable | kUART_RxOverrunInterruptEnable);
  EnableIRQ(interrupt);
  
  
  return err;
}



