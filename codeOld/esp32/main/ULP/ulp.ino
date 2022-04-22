//Dont really know that i  need
#include <stdio.h>
#include <math.h>
#include "esp_sleep.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/rtc_io_reg.h"
#include "soc/sens_reg.h"
#include "soc/soc.h"
#include "driver/rtc_io.h"
#include "esp32/ulp.h"
#include "sdkconfig.h"
#include "ulp_main.h"
#include "ulptool.h"

#define SDAPin
#define SCLPin

// need this for some reason
extern const uint8_t ulp_main_bin_start[] asm("_binary_ulp_main_bin_start");
extern const uint8_t ulp_main_bin_end[]   asm("_binary_ulp_main_bin_end");

//dont know where "gpio_num_t" komes from
const gpio_num_t sdaPiPin = SDAPin;
const gpio_num_t sdaPiPin = SCLPin;

static void init_ulp_program()
{
    esp_err_t err = ulptool_load_binary(0, ulp_main_bin_start,
        (ulp_main_bin_end - ulp_main_bin_start) / sizeof(uint32_t));
    ESP_ERROR_CHECK(err);
    rtc_gpio_init(sclPin); //not sure if enumeration is correct
    rtc_gpio_set_direction(sclPin, RTC_GPIO_MODE_INPUT_ONLY);
    rtc_gpio_init(sdaPin);
    rtc_gpio_set_direction(sdaPin, RTC_GPIO_MODE_INPUT_ONLY);
}

static void start_ulp_program()
{
  /* Start the program */
  esp_err_t err = ulp_run((&ulp_entry - RTC_SLOW_MEM) / sizeof(uint32_t));
  ESP_ERROR_CHECK(err);
}