
#include "lsm6ds3.h"
#include "nrf_drv_twi.h"
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

//Initializing TWI0 instance
#define TWI_INSTANCE_ID 0


// A flag to indicate the transfer state
static volatile bool m_xfer_done = false;

// Create a Handle for the twi communication
static const nrf_drv_twi_t m_twi = NRF_DRV_TWI_INSTANCE(TWI_INSTANCE_ID);

//Event Handler
void twi_handler(nrf_drv_twi_evt_t const *p_event, void *p_context) {
  //Check the event to see what type of event occurred
  switch (p_event->type) {
  //If data transmission or receiving is finished
  case NRF_DRV_TWI_EVT_DONE:
    m_xfer_done = true; //Set the flag
    break;

  default:
    // do nothing
    break;
  }
}

//Initialize the TWI as Master device
void twi_master_init(void) {
  ret_code_t err_code;

  // Configure the settings for twi communication
  const nrf_drv_twi_config_t twi_config = {
      .scl = TWI_SCL_M,                            //SCL Pin
      .sda = TWI_SDA_M,                            //SDA Pin
      .frequency = NRF_DRV_TWI_FREQ_100K,          //Communication Speed
      .interrupt_priority = APP_IRQ_PRIORITY_HIGH, //Interrupt Priority(Note: if using Bluetooth then select priority carefully)
      .clear_bus_init = false                      //automatically clear bus
  };

  //A function to initialize the twi communication
  err_code = nrf_drv_twi_init(&m_twi, &twi_config, twi_handler, NULL);
  APP_ERROR_CHECK(err_code);

  //Enable the TWI Communication
  nrf_drv_twi_enable(&m_twi);
}

/*
   A function to write a Single Byte to LSM6DS3's internal Register
*/
bool lsm6ds3_register_write(uint8_t register_address, uint8_t value) {
  ret_code_t err_code;
  uint8_t tx_buf[LSM6DS3_ADDRESS_LEN + 1];

  //Write the register address and data into transmit buffer
  tx_buf[0] = register_address;
  tx_buf[1] = value;

  //Set the flag to false to show the transmission is not yet completed
  m_xfer_done = false;

  //Transmit the data over TWI Bus
  err_code = nrf_drv_twi_tx(&m_twi, LSM6DS3_ADDRESS, tx_buf, LSM6DS3_ADDRESS_LEN + 1, false);

  //Wait until the transmission of the data is finished
  while (m_xfer_done == false) {
  }

  // if there is no error then return true else return false
  if (NRF_SUCCESS != err_code) {
    return false;
  }

  return true;
}

/*
  A Function to read data from the LSM6DS3
*/
bool lsm6ds3_register_read(uint8_t register_address, uint8_t *destination, uint8_t number_of_bytes) {
  ret_code_t err_code;

  //Set the flag to false to show the receiving is not yet completed
  m_xfer_done = false;

  // Send the Register address where we want to write the data
  err_code = nrf_drv_twi_tx(&m_twi, LSM6DS3_ADDRESS, &register_address, 1, true);

  //Wait for the transmission to get completed
  while (m_xfer_done == false) {
  }

  // If transmission was not successful, exit the function with false as return value
  if (NRF_SUCCESS != err_code) {
    return false;
  }

  //set the flag again so that we can read data from the LSM6DS3's internal register
  m_xfer_done = false;

  // Receive the data from the LSM6DS3
  err_code = nrf_drv_twi_rx(&m_twi, LSM6DS3_ADDRESS, destination, number_of_bytes);

  //wait until the transmission is completed
  while (m_xfer_done == false) {
  }

  // if data was successfully read, return true else return false
  if (NRF_SUCCESS != err_code) {
    return false;
  }

  return true;
}

/*
  Function to initialize the lsm6ds3
*/
bool lsm6ds3_check_address_answer(void) {
  ret_code_t err_code;
  uint8_t sample_data;
  int counter = 0;

  err_code = nrf_drv_twi_rx(&m_twi, LSM6DS3_ADDRESS, &sample_data, sizeof(sample_data));

    while (m_xfer_done == false) {
    if (counter > 50)
    {
          return false;
    }

    nrf_delay_ms(10);
    counter++;
  }

  if (err_code == NRF_SUCCESS) {
    return true;
  }

  return false;
}


bool lsm6ds3_setup() {

    (void)lsm6ds3_register_write(0x10, 0x0); // CTRL1_XL (10h) Linear acceleration sensor control register: prw down
    (void)lsm6ds3_register_write(0x11, 0x0); // CTRL2_G (11h) Angular rate sensor control register 2 (r/w): prw down
    (void)lsm6ds3_register_write(0x13, 0x0); // CTRL4_C (13h) Control register 4 (r/w).

    nrf_delay_ms(4);

    (void)lsm6ds3_register_write(0X5C, 0x00); // WAKE_UP_DUR (5Ch) -  No duration
    (void)lsm6ds3_register_write(0X5B, 0x02); // WAKE_UP_THS (5Bh) - Single and double-tap function threshold register
    (void)lsm6ds3_register_write(0X58, 0x80); // TAP_CFG (58h) Enable interrupts and apply slope filter; latch mode disabled

    (void)lsm6ds3_register_write(0X10, 0x70); // Turn on the accelerometer
                           // ODR_XL = 833 Hz, FS_XL = ±2 g
    nrf_delay_ms(4);
    // Delay time per application note
    (void)lsm6ds3_register_write(0X10, 0xB0); // ODR_XL = 1.6 Hz
    (void)lsm6ds3_register_write(0X15, 0x10); // CTRL6_C (15h) - High-performance operating mode disabled for accelerometer
    (void)lsm6ds3_register_write(0X5E, 0x20); // MD1_CFG (5Eh) - Functions routing on INT1 register  Wake-up interrupt driven to INT1 pin
    (void)nrf_delay_ms(4);

  return true;
}