//dont know what includes do
#include "soc/rtc_cntl_reg.h"
#include "soc/rtc_io_reg.h"
#include "soc/soc_ulp.h"
#include "stack.s"

//something good i hope
.bss
i2c_started:
  .long 0
i2c_didInit:
  .long 0


.text
.global i2c_start_cond
.global i2c_stop_cond
.global i2c_write_bit
.global i2c_read_bit
.global i2c_write_byte
.global i2c_read_byte

//macros for i2c communication
.macro I2C_delay
  wait 50   // if number equ 10 then clock gap is minimal 4.7us
.endm

.macro read_SCL 
  READ_RTC_REG(RTC_GPIO_IN_REG, RTC_GPIO_IN_NEXT_S + 9, 1) 
.endm

.macro read_SDA 
  READ_RTC_REG(RTC_GPIO_IN_REG, RTC_GPIO_IN_NEXT_S + 8, 1) 
.endm

.macro set_SCL 
  WRITE_RTC_REG(RTC_GPIO_ENABLE_W1TC_REG, RTC_GPIO_ENABLE_W1TC_S + 9, 1, 1)
.endm

.macro clear_SCL 
  WRITE_RTC_REG(RTC_GPIO_ENABLE_W1TS_REG, RTC_GPIO_ENABLE_W1TS_S + 9, 1, 1)
.endm

.macro set_SDA 
  WRITE_RTC_REG(RTC_GPIO_ENABLE_W1TC_REG, RTC_GPIO_ENABLE_W1TC_S + 8, 1, 1)
.endm

.macro clear_SDA 
  WRITE_RTC_REG(RTC_GPIO_ENABLE_W1TS_REG, RTC_GPIO_ENABLE_W1TS_S + 8, 1, 1)
.endm