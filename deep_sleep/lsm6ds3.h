#ifndef AS5000_H__
#define AS5000_H__
#include "nrf_delay.h"

//I2C Pins Settings, you change them to any other pins
#define TWI_SCL_M           27         //I2C SCL Pin
#define TWI_SDA_M           7         //I2C SDA Pin


#define LSM6DS3_ADDRESS_LEN  1         //LSM6DS3
#define LSM6DS3_ADDRESS     0x6AU  //LSM6DS3 Device Address



void twi_master_init(void); // initialize the twi communication
bool lsm6ds3_check_address_answer(void);    // Check the lsm6ds3

/**
  @brief Function for writing a LSM6DS3 register contents over TWI.
  @param[in]  register_address Register address to start writing to
  @param[in] value Value to write to register
  @retval true Register write succeeded
  @retval false Register write failed
*/
bool lsm6ds3_register_write(uint8_t register_address, const uint8_t value);

/**
  @brief Function for reading LSM6DS3 register contents over TWI.
  Reads one or more consecutive registers.
  @param[in]  register_address Register address to start reading from
  @param[in]  number_of_bytes Number of bytes to read
  @param[out] destination Pointer to a data buffer where read data will be stored
  @retval true Register read succeeded
  @retval false Register read failed
*/
bool lsm6ds3_register_read(uint8_t register_address, uint8_t *destination, uint8_t number_of_bytes);

/**
  @brief Function for reading and verifying LSM6DS3 product ID.
  @retval true Product ID is what was expected
  @retval false Product ID was not what was expected
*/
bool lsm6ds3_verify_product_id(void);

bool lsm6ds3_setup();

#endif