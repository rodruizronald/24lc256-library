//*****************************************************************************
//
//  Prototypes for the 24lc256.
//  File:     24lc256.h
//  Version:  1.0v
//  Author:   Ronald Rodriguez Ruiz.
//  Date:     April 10, 2016.
//  ---------------------------------------------------------------------------
//  Specifications:
//  Runs on 8-bit AVR Microcontrollers (ATmega series).
//
//*****************************************************************************

#ifndef __24LC256_H__
#define __24LC256_H__

//*****************************************************************************
//
//  The following are defines for the hardware interface with the 24lc256.
//
//*****************************************************************************

#define EEPROM_HOLD                     PD6
#define HOLD_PORT                       PORTD
#define HOLD_DDR                        DDRD

#define SLAVE_SELECT                    _clear_bit(SPI_PORT, SPI_SS);
#define SLAVE_DESELECT                  _set_bit(SPI_PORT, SPI_SS);

//*****************************************************************************
//
//  The following are defines for 24lc256 Instruction Set.
//
//*****************************************************************************

//
//  EEPROM Instruction Set.
//
#define EEPROM_READ                     0x03
#define EEPROM_WRITE                    0x02
#define EEPROM_WRDI                     0x04
#define EEPROM_WREN                     0x06
#define EEPROM_RDSR                     0x05
#define EEPROM_WRSR                     0x01

//
//  EEPROM Status Register Bits.
//
#define EEPROM_WRITE_IN_PROGRESS        0
#define EEPROM_WRITE_ENABLE_LATCH       1
#define EEPROM_BLOCK_PROTECT_0          2
#define EEPROM_BLOCK_PROTECT_1          3

//
//  EEPROM Status Register Bits.
//
#define EEPROM_BYTES_PER_PAGE           64
#define EEPROM_BYTES_MAX                0x7FFF

//*****************************************************************************
//
//  Prototypes for the API
//
//*****************************************************************************

extern void EEPROM_init(void);
extern uint8_t EEPROM_read_byte(uint16_t address);
extern void EEPROM_write_byte(uint16_t address, uint8_t byte);

#endif  // __24LC256_H__
