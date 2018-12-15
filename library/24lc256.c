//*****************************************************************************
//
//  API for the 24lc256.
//  File:     24lc256.c
//  Version:  1.0v
//  Author:   Ronald Rodriguez Ruiz.
//  Date:     April 10, 2016.
//  ---------------------------------------------------------------------------
//  Specifications:
//  Runs on 8-bit AVR Microcontrollers (ATmega series).
//
//*****************************************************************************

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "24lc256.h"
#include "spi.h"
#include "bitwiseop.h"

//*****************************************************************************
//
//  Prototypes for the private functions.
//
//*****************************************************************************

static void EEPROM_write_enable(void);
static uint8_t EEPROM_read_status(void);
static void EEPROM_send_address(uint16_t address);

//*****************************************************************************
//
//  Functions for the API.
//
//*****************************************************************************
//*****************************************************************************
//
//! @brief Initialize the 24lc256 EEPROM.
//!
//! This function initializes the GPIO for the 24lc256.
//!
//! @return None.
//
//*****************************************************************************
void
EEPROM_init(void)
{
  _set_bit(HOLD_DDR, EEPROM_HOLD);
  _set_bit(HOLD_PORT, EEPROM_HOLD);

  //
  //  Deselect (SS from SPI)
  //
  SLAVE_DESELECT;
  delay(10);
}

//*****************************************************************************
//
//! @brief Write a data byte.
//!
//! This function writes a data byte in a specific memory location.
//!
//! @param[in] address Memory location for the writing operation.
//! @param[in] data    Byte to be written on the EEPROM.
//!
//! @return None.
//
//*****************************************************************************
void
EEPROM_write_byte(uint16_t address, uint8_t data)
{
  //
  //  Enable writing operations.
  //
  EEPROM_write_enable();
  SLAVE_SELECT;
  delay(10);
  spi_transfer(EEPROM_WRITE);

  //
  //  Send the address.
  //
  EEPROM_send_address(address);
  spi_transfer(data);
  SLAVE_DESELECT;
  delay(10);

  //
  //  Wait until writing has finished.
  //
  while(_read_bit(EEPROM_read_status(), EEPROM_WRITE_IN_PROGRESS))
  ;
}

//*****************************************************************************
//
//! @brief Read a data byte.
//!
//! This function reads a data byte in a specific memory location.
//!
//! @param[in] address Memory location for the reading operation.
//!
//! @return response Data byte read from the memeory location.
//
//*****************************************************************************
uint8_t
EEPROM_read_byte(uint16_t address)
{
  SLAVE_SELECT;
  delay(10);
  spi_transfer(EEPROM_READ);
  EEPROM_send_address(address);

  uint8_t response = spi_transfer(0);
  SLAVE_DESELECT;
  delay(10);

  return response;
}

//*****************************************************************************
//
//! @brief Enable writing.
//!
//! This function enables the writing operation on the 24lc256 EEPROM.
//!
//! @return None.
//
//*****************************************************************************
static void
EEPROM_write_enable(void)
{
  SLAVE_SELECT;
  delay(10);
  spi_transfer(EEPROM_WREN);
  SLAVE_DESELECT;
  delay(10);
}

//*****************************************************************************
//
//! @brief Read status register.
//!
//! This function read the status register of the 24lc256 EEPROM and return
//! the response.
//!
//! @return status Response from the status register.
//
//*****************************************************************************
static uint8_t
EEPROM_read_status(void)
{
  SLAVE_SELECT;
  delay(10);
  spi_transfer(EEPROM_RDSR);

  //
  //  Clock out eight bits.
  //
  uint8_t status = spi_transfer(0);
  SLAVE_DESELECT;
  delay(10);

  return status;
}

//*****************************************************************************
//
//! @brief Send address.
//!
//! This function splits a 16-bit address into 2 bytes and sends both to the
//! 24lc256 EEPROM over SPI trasnfer.
//!
//! @return None.
//
//*****************************************************************************
static void
EEPROM_send_address(uint16_t address)
{
  //
  //  Most significant byte.
  //
  spi_transfer((uint8_t) (address >> 8));

  //
  //  Least significant byte.
  //
  spi_transfer((uint8_t) address);
}
