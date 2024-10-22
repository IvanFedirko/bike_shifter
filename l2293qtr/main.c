#include "app_error.h"
#include "app_util_platform.h"
#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_drv_gpiote.h"
#include "nrf_drv_twi.h"
#include "nrf_gpio.h"
#include <stdio.h>

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#define led_red 2
#define pwr 40
#define en_1 43

#define in_1 44 //FWD
#define in_2 45 //REV
#define in_3 46 //Stop Signal

int main(void) {
  APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
  NRF_LOG_DEFAULT_BACKENDS_INIT();

  nrf_gpio_cfg_output(led_red);
  nrf_gpio_pin_clear(led_red); //turn off led_red

  nrf_gpio_cfg_output(pwr);
  nrf_gpio_pin_set(pwr);

  //-------------------------------
  nrf_gpio_cfg_output(en_1);
  nrf_gpio_pin_set(en_1);

  nrf_gpio_cfg_output(in_1);
  nrf_gpio_pin_clear(in_1);

  nrf_gpio_cfg_output(in_2);
  nrf_gpio_pin_clear(in_2);

  nrf_gpio_cfg_output(in_3);
  nrf_gpio_pin_clear(in_3);
  //-------------------------------

  nrf_delay_ms(1000);
  nrf_gpio_pin_set(led_red);

  while (true) {

    nrf_gpio_pin_toggle(led_red);

    nrf_gpio_pin_clear(in_1);
    nrf_gpio_pin_clear(in_2);
    nrf_gpio_pin_clear(in_3);

    //turn on FWD
    nrf_gpio_pin_set(in_1);

    nrf_delay_ms(1000);

    //turn on REV
    nrf_gpio_pin_clear(in_1);
    nrf_gpio_pin_set(in_2);

    nrf_delay_ms(1000);

    //turn on STOP
    nrf_gpio_pin_set(in_3);

    nrf_delay_ms(1000);
  }
}