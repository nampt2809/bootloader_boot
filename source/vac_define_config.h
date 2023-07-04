//--thanhcm3--12--06--23--

#ifndef _VAC_DEFINE_CONFIG_H
#define _VAC_DEFINE_CONFIG_H
//include-----------------------------------------------------------------------
//define------------------------------------------------------------------------
//function----------------------------------------------------------------------
///0. DEVICE INFO===============================================================
#define  DEVICE_INFO                     "VAC-5G"
#define  VERSION_SW                      "V1.01.01"
#define  VERSION_HW                      "V1.01"

#define  ERR                             0
#define  NO_ERR                          1                         

///1. RS485 CONFIG==============================================================
#define DIR_485_ON                           GPIO_PinWrite(BOARD_RS485_DIR_RS485_GPIO_PORT,BOARD_RS485_DIR_RS485_PIN,1);       
#define DIR_485_OFF                          GPIO_PinWrite(BOARD_RS485_DIR_RS485_GPIO_PORT,BOARD_RS485_DIR_RS485_PIN,0);

#define USER_UART2                           UART2
#define UART_CLK_FREQ                        CLOCK_GetFreq(kCLOCK_BusClk)
#define USER_UART2_IRQn                      UART2_IRQn
#define USER_UART2_IRQHandler                UART2_IRQHandler

///2. RTC HUMI CONFIG================================================================
#define MS                                   20U
#define RTC_SCL_PORT                         BOARD_I2C_I2C_SCL_RTC_GPIO_PORT
#define RTC_SCL_PIN                          BOARD_I2C_I2C_SCL_RTC_PIN
#define RTC_SDA_PORT                         BOARD_I2C_I2C_SDA_RTC_GPIO_PORT
#define RTC_SDA_PIN                          BOARD_I2C_I2C_SDA_RTC_PIN

///3. FLASH CONFIG==============================================================
#define USER_SPI1_MASTER                      SPI1
#define USER_SPI1_MASTER_CLK_FREQ             CLOCK_GetFreq(kCLOCK_BusClk)

#define USER_FLASH_SPI1_CS_LOW                GPIO_PinWrite(BOARD_FLASH_SPI_SPI1_CS_GPIO_PORT,BOARD_FLASH_SPI_SPI1_CS_PIN,0);
#define USER_FLASH_SPI1_CS_HIGH               GPIO_PinWrite(BOARD_FLASH_SPI_SPI1_CS_GPIO_PORT,BOARD_FLASH_SPI_SPI1_CS_PIN,1);

#define USER_SPI1_HOLD_ON                     GPIO_PinWrite(BOARD_FLASH_SPI_SPI1_HOLD_GPIO_PORT,BOARD_FLASH_SPI_SPI1_HOLD_PIN,1);
#define USER_SPI1_HOLD_OFF                    GPIO_PinWrite(BOARD_FLASH_SPI_SPI1_HOLD_GPIO_PORT,BOARD_FLASH_SPI_SPI1_HOLD_PIN,0);

#define USER_SPI1_WP_ON                       GPIO_PinWrite(BOARD_FLASH_SPI_SPI1_WP_GPIO_PORT,BOARD_FLASH_SPI_SPI1_WP_PIN,1);
#define USER_SPI1_WP_OFF                      GPIO_PinWrite(BOARD_FLASH_SPI_SPI1_WP_GPIO_PORT,BOARD_FLASH_SPI_SPI1_WP_PIN,0);






///4. TIMER CONFIG==============================================================
/* The Flextimer instance/channel used for board */
#define USER_FTM2_BASEADDR                   FTM2
/* Get source clock for FTM driver */
#define FTM_SOURCE_CLOCK                     (CLOCK_GetFreq(kCLOCK_TimerClk))
/* Set counter period to 50ms */
#define TIMER_PERIOD_MS                      (50U)
/* Interrupt number and interrupt handler for the FTM instance used */
#define USER_FTM2_IRQ_NUM                    FTM2_IRQn
#define USER_FTM2_HANDLER                    FTM2_IRQHandler

///5. LED CONFIG================================================================
#define RUN_LED_TOGGLE                       GPIO_PortToggle(BOARD_RUN_LED_GPIO_PORT, 1u << BOARD_RUN_LED_PIN);
#define SYS_NORMAL_LED_TOGGLE                GPIO_PortToggle(BOARD_SYS_NORMAL_GPIO_PORT, 1u << BOARD_SYS_NORMAL_PIN);
#define SYS_ALARM_LED_ON                     GPIO_PinWrite(BOARD_SYS_ALARM_LED_GPIO_PORT,BOARD_SYS_ALARM_LED_PIN,1);
#define SYS_ALARM_LED_OFF                    GPIO_PinWrite(BOARD_SYS_ALARM_LED_GPIO_PORT,BOARD_SYS_ALARM_LED_PIN,0);
#define SYS_FAULT_LED_ON                     GPIO_PinWrite(BOARD_SYS_FAULT_LED_GPIO_PORT,BOARD_SYS_FAULT_LED_PIN,1);  
#define SYS_FAULT_LED_OFF                    GPIO_PinWrite(BOARD_SYS_FAULT_LED_GPIO_PORT,BOARD_SYS_FAULT_LED_PIN,0);

///6. ROLE CONFIG===============================================================

///7. ADC CONFIG================================================================


//code here


#endif /* _VAC_DEFINE_CONFIG_H */