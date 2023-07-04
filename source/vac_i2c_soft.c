//--thanhcm3--12--06--23--

//ST_TIME_FORMAT rtc_BQ32000;
#include "header_files.h"

ST_TIME_FORMAT rtc_DS3231;
///0.===========================================================================
static void i2c_sda_pin(gpio_port_num_t base, uint32_t pin,uint8_t pin_in_out );
static void i2c_scl_pin_output(gpio_port_num_t base, uint32_t pin);
static void i2c_sda_pin_on(gpio_port_num_t base, uint32_t pin);
static void i2c_sda_pin_off(gpio_port_num_t base, uint32_t pin);
static void i2c_scl_pin_on(gpio_port_num_t base, uint32_t pin);
static void i2c_scl_pin_off(gpio_port_num_t base, uint32_t pin);
static uint32_t i2c_sda_pin_read(gpio_port_num_t base, uint32_t pin);
static void i2c_delay_us(uint32_t us);
///1.i2c_sda_pin================================================================
static void i2c_sda_pin(gpio_port_num_t base, uint32_t pin,uint8_t pin_in_out ){ 
  // SDA input.
  if(pin_in_out == PIN_INPUT)
  {
    gpio_pin_config_t i2c_config = {
      .pinDirection = kGPIO_DigitalInput,
      .outputLogic = 0U,
    };
    
    GPIO_PinInit(base,pin,&i2c_config);
  }
  // SDA output.
  else if(pin_in_out == PIN_OUTPUT)
  {
    gpio_pin_config_t i2c_config = {
      .pinDirection = kGPIO_DigitalOutput,
      .outputLogic = 0U,
    };
    GPIO_PinInit(base,pin,&i2c_config);
  }
}

static void i2c_scl_pin_output(gpio_port_num_t base, uint32_t pin){ 
  // SCL output.
  gpio_pin_config_t i2c_config = {
    .pinDirection = kGPIO_DigitalOutput,
    .outputLogic = 0U,
  };
  GPIO_PinInit(base,pin,&i2c_config);
}

static void i2c_sda_pin_on(gpio_port_num_t base, uint32_t pin){
  GPIO_PinWrite(base, pin, 1);
}

static void i2c_sda_pin_off(gpio_port_num_t base, uint32_t pin){
  GPIO_PinWrite(base, pin, 0);
}

static void i2c_scl_pin_on(gpio_port_num_t base, uint32_t pin){
  GPIO_PinWrite(base, pin, 1);
}

static void i2c_scl_pin_off(gpio_port_num_t base, uint32_t pin){
  GPIO_PinWrite(base, pin, 0);
}

static uint32_t i2c_sda_pin_read(gpio_port_num_t base, uint32_t pin){
  return GPIO_PinRead(base,pin); 
}


///2.i2c_delay_us===============================================================
static void i2c_delay_us(uint32_t us){
  
  volatile uint32_t i = 0;
    for (i = 0; i < us; ++i)
    {
        __NOP(); /* delay */
    } 
}

///3.Convert binary to BCD======================================================
uint8_t dec2bcd(uint8_t val){			
  return ((val/0xA*0x10)+(val%0xA));
}

///4.Convert BCD to binary======================================================
uint8_t bcd2dec(uint8_t val){
  return ((val/0x10*0xA)+(val%0x10));
}

///5.i2c_init===================================================================
void i2c_init(gpio_port_num_t base_sda, uint32_t pin_sda,gpio_port_num_t base_scl, uint32_t pin_scl,uint32_t ms){
  
  i2c_sda_pin(base_sda, pin_sda, PIN_OUTPUT);
  i2c_scl_pin_output(base_scl,pin_scl);
  i2c_sda_pin_on(base_sda, pin_sda);
  i2c_delay_us(ms);
  i2c_scl_pin_on(base_scl,pin_scl);
}
///6.i2c_start==================================================================
void i2c_start(gpio_port_num_t base_sda, uint32_t pin_sda,gpio_port_num_t base_scl, uint32_t pin_scl,uint32_t ms){
  
  i2c_sda_pin(base_sda, pin_sda, PIN_OUTPUT);
  i2c_delay_us(ms);
  
  i2c_sda_pin_on(base_sda, pin_sda);
  i2c_delay_us(ms);
  i2c_scl_pin_on(base_scl,pin_scl);
  i2c_delay_us(ms);
  
  i2c_sda_pin_off(base_sda, pin_sda);
  i2c_delay_us(ms);
  i2c_scl_pin_off(base_scl,pin_scl);
  i2c_delay_us(ms);
}
///7.i2c_stop===================================================================
void i2c_stop(gpio_port_num_t base_sda, uint32_t pin_sda,gpio_port_num_t base_scl, uint32_t pin_scl,uint32_t ms){
  i2c_sda_pin(base_sda, pin_sda, PIN_OUTPUT);
  i2c_delay_us(ms);
  
  i2c_sda_pin_off(base_sda, pin_sda);
  i2c_delay_us(ms);
  i2c_scl_pin_on(base_scl,pin_scl);
  i2c_delay_us(ms);
  i2c_sda_pin_on(base_sda, pin_sda);
  i2c_delay_us(ms);
}
///8.i2c_write==================================================================
void i2c_write(gpio_port_num_t base_sda, uint32_t pin_sda,gpio_port_num_t base_scl, uint32_t pin_scl,uint32_t ms,uint8_t data){
  uint8_t i;
  
  i2c_sda_pin(base_sda, pin_sda, PIN_OUTPUT);
  i2c_delay_us(ms);
  
  for(i = 0;i<8;i++){
    if((data & 0x80)==0)i2c_sda_pin_off(base_sda, pin_sda);
    else i2c_sda_pin_on(base_sda, pin_sda);
    i2c_scl_pin_on(base_scl,pin_scl);
    i2c_delay_us(ms);
    i2c_scl_pin_off(base_scl,pin_scl);
    data<<=1;
    i2c_delay_us(ms);
  }
  // ACK -- SDA off while extra clock pulse 
  i2c_sda_pin_off(base_sda, pin_sda);
  i2c_scl_pin_on(base_scl,pin_scl);
  i2c_delay_us(ms);
  i2c_scl_pin_off(base_scl,pin_scl);
  i2c_delay_us(ms);
}

///9.i2c_read===================================================================
uint8_t i2c_read(gpio_port_num_t base_sda, uint32_t pin_sda,gpio_port_num_t base_scl, uint32_t pin_scl,uint32_t ms,uint8_t ack_bit){
  uint8_t i;
  uint8_t data=0;
  i2c_sda_pin(base_sda, pin_sda, PIN_OUTPUT);
  i2c_delay_us(ms);
  i2c_sda_pin_on(base_sda, pin_sda);
  i2c_sda_pin(base_sda, pin_sda, PIN_INPUT);
  i2c_delay_us(ms);
  for (i=0;i<8;i++)
  {
    i2c_scl_pin_on(base_scl,pin_scl);;
    i2c_delay_us(ms);
    data<<= 1;
    if(i2c_sda_pin_read(base_sda, pin_sda)==0)
      data  = (data | 0);
    else
      data  = (data | 1);
    i2c_scl_pin_off(base_scl,pin_scl);
    i2c_delay_us(ms);
  }
  i2c_sda_pin(base_sda, pin_sda, PIN_OUTPUT);
  if (ack_bit == 1)
    i2c_sda_pin_off(base_sda, pin_sda); // Send ACK
  else
    i2c_sda_pin_on(base_sda, pin_sda); // Send ACK;  // Send NO ACK
  i2c_scl_pin_on(base_scl,pin_scl);
  i2c_delay_us(ms);
  i2c_scl_pin_off(base_scl,pin_scl);
  i2c_delay_us(ms);
  return data;
}

///10.Read RTC==================================================================

uint8_t read_rtc(gpio_port_num_t base_sda, uint32_t pin_sda,gpio_port_num_t base_scl, uint32_t pin_scl,uint32_t ms,uint8_t addr){
  unsigned char data;
  
  i2c_start(base_sda,pin_sda,base_scl,pin_scl,ms);
  i2c_write(base_sda,pin_sda,base_scl,pin_scl,ms,ADDR_I2C_RTC_WRITE);
  i2c_write(base_sda,pin_sda,base_scl,pin_scl,ms,addr);
  
  i2c_start(base_sda,pin_sda,base_scl,pin_scl,ms);
  i2c_write(base_sda,pin_sda,base_scl,pin_scl,ms,ADDR_I2C_RTC_READ);
  data = i2c_read(base_sda,pin_sda,base_scl,pin_scl,ms,NO_ACK);
  
  i2c_stop(base_sda,pin_sda,base_scl,pin_scl,ms);
  return (data);
}

///11.Write RTC=================================================================
void write_rtc(gpio_port_num_t base_sda, uint32_t pin_sda,gpio_port_num_t base_scl, uint32_t pin_scl,uint32_t ms,uint8_t addr,uint8_t data){
  
  i2c_start(base_sda,pin_sda,base_scl,pin_scl,ms);
  i2c_write(base_sda,pin_sda,base_scl,pin_scl,ms,ADDR_I2C_RTC_WRITE);
  i2c_write(base_sda,pin_sda,base_scl,pin_scl,ms,addr);
  i2c_write(base_sda,pin_sda,base_scl,pin_scl,ms,data);
  i2c_stop(base_sda,pin_sda,base_scl,pin_scl,ms);
}

///12.set_time_rtc==============================================================
void set_time_rtc(gpio_port_num_t base_sda, uint32_t pin_sda,gpio_port_num_t base_scl, uint32_t pin_scl,uint32_t ms,ST_TIME_FORMAT time_rtc){
  write_rtc(base_sda, pin_sda,base_scl, pin_scl,ms,0,dec2bcd(time_rtc.sec)&0x7f);
  write_rtc(base_sda, pin_sda,base_scl, pin_scl,ms,1,dec2bcd(time_rtc.min)&0x7f);
  write_rtc(base_sda, pin_sda,base_scl, pin_scl,ms,2,dec2bcd(time_rtc.hour)&0x3f);
  write_rtc(base_sda, pin_sda,base_scl, pin_scl,ms,3,dec2bcd(time_rtc.day));
  write_rtc(base_sda, pin_sda,base_scl, pin_scl,ms,4,dec2bcd(time_rtc.date));
  write_rtc(base_sda, pin_sda,base_scl, pin_scl,ms,5,dec2bcd(time_rtc.month));
  write_rtc(base_sda, pin_sda,base_scl, pin_scl,ms,6,dec2bcd(time_rtc.year));
}

///13.get_time_rtc==============================================================
ST_TIME_FORMAT get_time_rtc(gpio_port_num_t base_sda, uint32_t pin_sda,gpio_port_num_t base_scl, uint32_t pin_scl,uint32_t ms){
  ST_TIME_FORMAT time_rtc;
  
  time_rtc.sec          =read_rtc(base_sda, pin_sda,base_scl, pin_scl,ms, 0);     // read second
  time_rtc.min          =read_rtc(base_sda, pin_sda,base_scl, pin_scl,ms, 1);     // read minute
  time_rtc.hour         =read_rtc(base_sda, pin_sda,base_scl, pin_scl,ms, 2);     // read hour
  time_rtc.day          =read_rtc(base_sda, pin_sda,base_scl, pin_scl,ms, 3);     // read day
  time_rtc.date         =read_rtc(base_sda, pin_sda,base_scl, pin_scl,ms, 4);     // read date
  time_rtc.month        =read_rtc(base_sda, pin_sda,base_scl, pin_scl,ms, 5);     // read month
  time_rtc.year         =read_rtc(base_sda, pin_sda,base_scl, pin_scl,ms, 6);     // read year
  
  time_rtc.sec   	= bcd2dec(time_rtc.sec&0x7f);
  time_rtc.min 	        = bcd2dec(time_rtc.min&0x7f);
  time_rtc.hour 	= bcd2dec(time_rtc.hour&0x3f);
  time_rtc.day 	        = bcd2dec(time_rtc.day&0x07);
  time_rtc.date 	= bcd2dec(time_rtc.date&0x3f);
  time_rtc.month 	= bcd2dec(time_rtc.month&0x1f);
  time_rtc.year 	= bcd2dec(time_rtc.year);
  
  return time_rtc;
}
///14.rtc_enable_charge========================================================= 
static void rtc_enable_charge(gpio_port_num_t base_sda, uint32_t pin_sda,gpio_port_num_t base_scl, uint32_t pin_scl,uint32_t ms){
  write_rtc(base_sda,pin_sda,base_scl,pin_scl,ms,0x08,0x20); //TCH2 control
  write_rtc(base_sda,pin_sda,base_scl,pin_scl,ms,0x09,0x45); //TCHE+TCFE
}
///15.init_rtc==================================================================
void init_rtc(gpio_port_num_t base_sda, uint32_t pin_sda,gpio_port_num_t base_scl, uint32_t pin_scl,uint32_t ms){
  i2c_init(base_sda,pin_sda,base_scl,pin_scl,ms);
  rtc_enable_charge(base_sda,pin_sda,base_scl,pin_scl,ms);
}