/************************************************************************
Title:	 UART for the Penguino AVR
Author:	David Collien (Icy Labs)
Software: AVR-GCC 4.1, AVR Libc 1.4
Hardware: Penguino AVR
License:  MIT License

DESCRIPTION:
	 Interface for initialising, sending and receiving data over UART
	 
LICENSE:
	 Copyright (C) 2009 Icy Labs Pty Ltd.
	 http://www.icy.com.au/

	  Permission is hereby granted, free of charge, to any person
	  obtaining a copy of this software and associated documentation
	  files (the "Software"), to deal in the Software without
	  restriction, including without limitation the rights to use,
	  copy, modify, merge, publish, distribute, sublicense, and/or sell
	  copies of the Software, and to permit persons to whom the
	  Software is furnished to do so, subject to the following
	  conditions:

	  The above copyright notice and this permission notice shall be
	  included in all copies or substantial portions of the Software.

	  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
	  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
	  OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
	  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
	  WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
	  FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
	  OTHER DEALINGS IN THE SOFTWARE.

	 
************************************************************************/

#include "../common.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

#define SPI_DDR DDRB
#define SPI_PORT PORTB

#define SPI_PIN_MOSI _BV(5)
#define SPI_PIN_MISO _BV(6)
#define SPI_PIN_SCK  _BV(7)
#define SPI_PINS     (SPI_PIN_MOSI | SPI_PIN_MISO | SPI_PIN_SCK)

void spiMaster_init( ubyte clockRate ) {
	// ensure the port isn't driving anything
	SPI_PORT &= ~(SPI_PINS);
	
	// prepare pin states
	SPI_DDR &= ~(SPI_PINS);
	SPI_DDR |= SPI_PIN_MOSI | SPI_PIN_SCK;
	
	// enable: SPI, Master, and set clock rate
	SPCR = (1 << SPE) | (1 << MSTR) | clockRate;
	
	SPSR = 0x00;
}

void spiMaster_disable( ) {
	// disable SPI
	SPCR &= ~(1 << SPE);
	
	// reset GPIO states
	SPI_PORT &= ~(SPI_PINS);
	SPI_DDR &= ~(SPI_PINS);
}

void spiMaster_transmit( ubyte data ) {
	// start transmission
	SPDR = data;
	
	// wait for transmission to complete
	while ( !( SPSR & (1 << SPIF) ) )
		; // snooze
}

ubyte spiMaster_receive( ) {
	return SPDR;
}
