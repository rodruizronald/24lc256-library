//*****************************************************************************
//
//  API for the SPI Interface.
//  File:     spi.c
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
#include "spi.h"
#include "bitwiseop.h"

//*****************************************************************************
//
//  Functions for the API.
//
//*****************************************************************************
//*****************************************************************************
//
//! @brief Initialize the SPI.
//!
//! This function initializes the GPIO pins for the SPI interface and configues
//! the clock rate.
//!
//! @return None.
//
//*****************************************************************************
void
SPI_init(void)
{
  //
  //  SPI Interface.
  //  MOSI: Output.
  //  MISO: Input (Pull-Up).
  //  SCK: Output.
  //  SS: Output.
  //
  _set_three_bits(SPI_DDR, SPI_MOSI, SPI_SCK, SPI_SS);
  _set_bit(SPI_PORT, SPI_MISO);

  //
  //  SPI Register Control.
  //  SPE: SPI Enable.
  //  MSTR: Master Select.
  //  SPR0: Set clock rate fosc/16 (1 Mbps).
  //
   _set_three_bits(SPCR, SPR0, MSTR, SPE);
}

//*****************************************************************************
//
//! @brief Transfer a data byte over SPI.
//!
//! This function puts a data byte in the SPDR port and loops until it has
//! been transmitted.
//!
//! @param[in] data Byte to be transferred over SPI.
//!
//! @return None.
//
//*****************************************************************************
uint8_t
SPI_transfer(uint8_t data)
{
  //
  //  Start transmission.
  //
  SPDR = data;

  //
  //  Wait for transmission complete.
  //
  while (!(SPSR & (1<<SPIF)))
  ;

  //
  //  SPDR now contains the received byte.
  //
  return SPDR;
}
