//--thanhcm3--12--06--23--

#ifndef _VAC_I2C_SOFT_H
#define _VAC_I2C_SOFT_H
//include-----------------------------------------------------------------------
//define------------------------------------------------------------------------
#define PIN_INPUT                                0U
#define PIN_OUTPUT                               1U

#define ACK			                 1U
#define NO_ACK		                         0U

#define ADDR_I2C_RTC_READ	                 0xD1
#define ADDR_I2C_RTC_WRITE	                 0xD0


typedef struct TimeStruct{
    int8_t      sec;   // read second
    int8_t      min;   // read minute
    int8_t      hour;  // read hour
    int8_t      day;   // read day
    int8_t      date;  // read date
    int8_t      month; // read month
    int8_t      year;  // read year
} ST_TIME_FORMAT;

extern ST_TIME_FORMAT rtc_DS3231;
//function----------------------------------------------------------------------
uint8_t dec2bcd(uint8_t val);
uint8_t bcd2dec(uint8_t val);
void i2c_init(gpio_port_num_t base_sda, uint32_t pin_sda,gpio_port_num_t base_scl, uint32_t pin_scl,uint32_t ms);
void i2c_start(gpio_port_num_t base_sda, uint32_t pin_sda,gpio_port_num_t base_scl, uint32_t pin_scl,uint32_t ms);
void i2c_stop(gpio_port_num_t base_sda, uint32_t pin_sda,gpio_port_num_t base_scl, uint32_t pin_scl,uint32_t ms);
void i2c_write(gpio_port_num_t base_sda, uint32_t pin_sda,gpio_port_num_t base_scl, uint32_t pin_scl,uint32_t ms,uint8_t data);
uint8_t i2c_read(gpio_port_num_t base_sda, uint32_t pin_sda,gpio_port_num_t base_scl, uint32_t pin_scl,uint32_t ms,uint8_t ack_bit);
uint8_t read_rtc(gpio_port_num_t base_sda, uint32_t pin_sda,gpio_port_num_t base_scl, uint32_t pin_scl,uint32_t ms,uint8_t addr);
void write_rtc(gpio_port_num_t base_sda, uint32_t pin_sda,gpio_port_num_t base_scl, uint32_t pin_scl,uint32_t ms,uint8_t addr,uint8_t data);
void init_rtc(gpio_port_num_t base_sda, uint32_t pin_sda,gpio_port_num_t base_scl, uint32_t pin_scl,uint32_t ms);
ST_TIME_FORMAT get_time_rtc(gpio_port_num_t base_sda, uint32_t pin_sda,gpio_port_num_t base_scl, uint32_t pin_scl,uint32_t ms);
void set_time_rtc(gpio_port_num_t base_sda, uint32_t pin_sda,gpio_port_num_t base_scl, uint32_t pin_scl,uint32_t ms,ST_TIME_FORMAT time_rtc);
//code here


#endif /* _VAC_I2C_SOFT_H */