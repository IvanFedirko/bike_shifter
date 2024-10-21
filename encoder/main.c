#include "app_error.h"
#include "app_util_platform.h"
#include "boards.h"
#include "nrf_drv_twi.h"
#include <stdio.h>

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

#include "as5600.h"

#define led_red 2
#define led_green 3
#define sw 40

int main(void) {

  static int16_t angle;

  APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
  NRF_LOG_DEFAULT_BACKENDS_INIT();

  nrf_gpio_cfg_output(led_red);
  nrf_gpio_cfg_output(led_green);
  nrf_gpio_cfg_output(sw);

  nrf_gpio_pin_set(led_red);   //turn off
  nrf_gpio_pin_set(led_green); //turn off
  nrf_gpio_pin_set(sw);        //turn on

  NRF_LOG_INFO("I2C Encoder project started.");
  NRF_LOG_FLUSH();

  twi_master_init();  // initialize the twi
  nrf_delay_ms(1000); // give some delay

  while (as5600_check_address_answer() == false) // wait until AS5600 sensor is successfully initialized
  {
    NRF_LOG_INFO("Encoder initialization failed!!!"); // if it failed to initialize then print a message
    NRF_LOG_FLUSH();
    nrf_delay_ms(1000);
  }

  while (true) {
    nrf_gpio_pin_toggle(led_green);
    if (AS5600_ReadAngle(&angle)) {
      NRF_LOG_INFO("Angle Value: x = %d", angle);
    } else {
      NRF_LOG_INFO("Problem to read value..");
    }

    NRF_LOG_FLUSH();

    nrf_delay_ms(1000);
  }

  NRF_LOG_INFO("AS5600 device was found.");
  NRF_LOG_FLUSH();
  nrf_gpio_pin_toggle(led_green);
}

/** @} */