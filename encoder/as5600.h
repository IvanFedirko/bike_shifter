#ifndef AS5000_H__
#define AS5000_H__
#include "nrf_delay.h"

//I2C Pins Settings, you change them to any other pins
#define TWI_SCL_M           5         //I2C SCL Pin
#define TWI_SDA_M           4         //I2C SDA Pin


#define AS5600_ADDRESS_LEN  1         //AS5600
#define AS5600_ADDRESS     0x36U  //AS5600 Device Address



void twi_master_init(void); // initialize the twi communication
bool as5600_check_address_answer(void);    // Check the as5600

/**
  @brief Function for writing a AS5600 register contents over TWI.
  @param[in]  register_address Register address to start writing to
  @param[in] value Value to write to register
  @retval true Register write succeeded
  @retval false Register write failed
*/
bool as5600_register_write(uint8_t register_address, const uint8_t value);

/**
  @brief Function for reading AS5600 register contents over TWI.
  Reads one or more consecutive registers.
  @param[in]  register_address Register address to start reading from
  @param[in]  number_of_bytes Number of bytes to read
  @param[out] destination Pointer to a data buffer where read data will be stored
  @retval true Register read succeeded
  @retval false Register read failed
*/
bool as5600_register_read(uint8_t register_address, uint8_t *destination, uint8_t number_of_bytes);

/**
  @brief Function for reading and verifying AS5600 product ID.
  @retval true Product ID is what was expected
  @retval false Product ID was not what was expected
*/
bool as5600_verify_product_id(void);

bool AS5600_ReadAngle( int16_t *angle);

#endif