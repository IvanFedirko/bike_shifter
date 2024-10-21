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

#include "lsm6ds3.h"

#define led_red 2
#define led_green 3
#define sw_interrupt 11

void input_pin_handle(nrf_drv_gpiote_pin_t pin, nrf_gpiote_polarity_t action) {
}

int main(void) {

  APP_ERROR_CHECK(NRF_LOG_INIT(NULL));
  NRF_LOG_DEFAULT_BACKENDS_INIT();

  NRF_LOG_INFO("APP is running.");

  nrf_gpio_cfg_output(led_red);
  nrf_gpio_cfg_output(led_green);

  //-------------------------------------------------------------
  ret_code_t err_code; //hold error value

  err_code = nrf_drv_gpiote_init();
  APP_ERROR_CHECK(err_code);

  nrf_gpio_pin_set(led_red); //turn off

  nrf_gpio_pin_clear(led_green); //turn on
  nrf_delay_ms(1000);
  nrf_gpio_pin_set(led_green); //turn off

  nrf_drv_gpiote_in_config_t in_config = GPIOTE_CONFIG_IN_SENSE_LOTOHI(false);
  nrf_gpio_cfg_sense_input(sw_interrupt, NRF_GPIO_PIN_PULLDOWN, NRF_GPIO_PIN_SENSE_HIGH);

  err_code = nrf_drv_gpiote_in_init(sw_interrupt, &in_config, input_pin_handle);
  APP_ERROR_CHECK(err_code);

  nrf_drv_gpiote_in_event_enable(sw_interrupt, true);
  //--------------------------------------------------

  static int16_t angle;

  NRF_LOG_INFO("I2C LSM6DS3 project started.");
  NRF_LOG_FLUSH();

  twi_master_init(); // initialize the twi
  nrf_delay_ms(10);  // give some delay

  while (lsm6ds3_check_address_answer() == false) // wait until LSM6DS3 sensor is successfully initialized
  {
    NRF_LOG_INFO("LSM6DS3 initialization failed!!!"); // if it failed to initialize then print a message
    NRF_LOG_FLUSH();
    nrf_delay_ms(1000);
  }

  (void)lsm6ds3_setup();

  NRF_LOG_INFO("DEEP SLEEP.");
  NRF_LOG_FLUSH();

  //deep sleep magic
  __SEV();
  __WFE();
  NRF_POWER->SYSTEMOFF = 1;
  //end deep sleep magic

  while (true) {

    nrf_delay_ms(1000);
    NRF_LOG_INFO("...");
    NRF_LOG_FLUSH();
  }
}