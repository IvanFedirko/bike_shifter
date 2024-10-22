#include "app_error.h"
#include "app_util_platform.h"
#include "boards.h"
#include "nrf.h"
#include "nrf_delay.h"
#include "nrf_drv_ppi.h"
#include "nrf_drv_saadc.h"
#include "nrf_drv_timer.h"
#include "nrf_pwr_mgmt.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "nrf_log.h"
#include "nrf_log_ctrl.h"
#include "nrf_log_default_backends.h"

void saadc_callback_handler(nrf_drv_saadc_evt_t const *p_event) {

}

void saadc_init(void) {
  ret_code_t err_code;
  nrf_saadc_channel_config_t channel_0_config = NRFX_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN6);
  nrf_saadc_channel_config_t channel_1_config = NRFX_SAADC_DEFAULT_CHANNEL_CONFIG_SE(NRF_SAADC_INPUT_AIN7);
 
  
  err_code = nrf_drv_saadc_init(NULL, saadc_callback_handler);
  APP_ERROR_CHECK(err_code);

  err_code = nrfx_saadc_channel_init(0, &channel_0_config);
  APP_ERROR_CHECK(err_code);

  err_code = nrfx_saadc_channel_init(1, &channel_1_config);
  APP_ERROR_CHECK(err_code);
}


void log_init(void) {
  uint32_t err_code = NRF_LOG_INIT(NULL);
  APP_ERROR_CHECK(err_code);
  NRF_LOG_DEFAULT_BACKENDS_INIT();
}


int main(void) {
  log_init();
  saadc_init();
  nrf_saadc_value_t adc_val_current;

   nrf_saadc_value_t adc_val_voltage;
  NRF_LOG_INFO("Application Started!!!");

  // Inifinite loop
  while (1) {
    nrfx_saadc_sample_convert(0, &adc_val_current);

    nrfx_saadc_sample_convert(1, &adc_val_voltage);

    NRF_LOG_INFO("Sample value Read: %d", adc_val_current);
    NRF_LOG_INFO("Current: " NRF_LOG_FLOAT_MARKER "\r\n", NRF_LOG_FLOAT((adc_val_current * 3.6 / 1024)/0.02));

    NRF_LOG_INFO("Sample value Read: %d", adc_val_voltage);
    NRF_LOG_INFO("Volts: " NRF_LOG_FLOAT_MARKER "\r\n", NRF_LOG_FLOAT((adc_val_voltage * 3.6 / 1024)*3.0));

    nrf_delay_ms(500);
    NRF_LOG_FLUSH();
  }
}