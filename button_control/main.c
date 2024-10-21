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
#define button 29

int main(void) {
  APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
  NRF_LOG_DEFAULT_BACKENDS_INIT();

  nrf_gpio_cfg_input(button, NRF_GPIO_PIN_PULLDOWN);
  nrf_gpio_cfg_output(led_red);
  nrf_gpio_pin_clear(led_red);
  nrf_delay_ms(1000);
  nrf_gpio_pin_clear(led_red);
  nrf_gpio_pin_set(led_red);
  while (true) {

    if (nrf_gpio_pin_read(button) == 1) {
      nrf_gpio_pin_clear(led_red);
      NRF_LOG_WARNING("Button pressed..");
      while (nrf_gpio_pin_read(button) == 1)
        ;
      NRF_LOG_WARNING("Button released..");
      nrf_gpio_pin_set(led_red);
    }
    nrf_delay_ms(100);
  }
}