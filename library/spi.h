//*****************************************************************************
//
//  Prototypes for the SPI Interface.
//  File:     spi.h
//  Version:  1.0v
//  Author:   Ronald Rodriguez Ruiz.
//  Date:     April 10, 2016.
//  ---------------------------------------------------------------------------
//  Specifications:
//  Runs on 8-bit AVR Microcontrollers (ATmega series).
//
//*****************************************************************************

#ifndef __SPI_H__
#define __SPI_H__

//*****************************************************************************
//
//  Prototypes for the API
//
//*****************************************************************************

extern void SPI_init(void);
extern uint8_t SPI_transfer(uint8_t data);

#endif  // __SPI_H__
