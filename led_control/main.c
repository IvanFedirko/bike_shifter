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
#define led_green 3
#define led_blue 28

int main(void) {
  APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
  NRF_LOG_DEFAULT_BACKENDS_INIT();


  nrf_gpio_cfg_output(led_red);
  nrf_gpio_cfg_output(led_green);
  nrf_gpio_cfg_output(led_blue);

  nrf_gpio_pin_set(led_red);
  nrf_gpio_pin_set(led_green);
  nrf_gpio_pin_set(led_blue);

  while (true) {

    NRF_LOG_INFO("Programm cycle.");
    NRF_LOG_FLUSH();
    nrf_gpio_pin_toggle(led_red);

    nrf_gpio_pin_clear(led_green);
    nrf_gpio_pin_clear(led_blue);
    nrf_delay_ms(100);
    nrf_gpio_pin_set(led_green);
    nrf_gpio_pin_clear(led_blue);

    nrf_delay_ms(100);
  }
}
