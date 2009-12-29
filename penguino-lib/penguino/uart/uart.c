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
#include "RingBuff.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include "uart.h"
 
#define UART_STATUS  UCSRA
#define UART_DATA	 UDR
#define UART_CONTROL UCSRB


static volatile RingBuff_t UARTInputBuffer;  // for receiving
static volatile RingBuff_t UARTOutputBuffer; // for sending
static volatile unsigned char lastRxError;


// Receive from UART
ISR( USART_RXC_vect ) {
	unsigned char data = UART_DATA;
	
	lastRxError = UART_STATUS & (_BV( FE ) | _BV( DOR ));
	
	Buffer_StoreElement( &UARTInputBuffer, data );
}

// Send over UART
ISR( USART_UDRE_vect ) {
	
	// check if there's something to send
	if ( UARTOutputBuffer.Elements > 0 ) {
		UART_DATA = Buffer_GetElement( &UARTOutputBuffer );
	} else {
		// disable the sending interrupt
		UART_CONTROL &= ~_BV( UDRIE );
	}
}

void uart_init( uint32_t baudrate ) {
	
	unsigned int scaledBaud = ((F_CPU/16)/baudrate)-1;
	
	// enable interrupts
	sei( );
	
	// initialise buffers for sending and receiving data
	Buffer_Initialize( &UARTInputBuffer );
	Buffer_Initialize( &UARTOutputBuffer );
	
	// set baud rate
	UBRRH = (unsigned char)(scaledBaud >> 8);
	UBRRL = (unsigned char) scaledBaud;
	
	// enable uart interrupts and start interrupting for receiving
	UART_CONTROL = _BV( RXCIE ) | (1 << RXEN) | (1 << TXEN);
	
	// set the frame format
	// URSEL bit selects the UCSRC register as the target
	UCSRC = (1 << URSEL) | (3 << UCSZ0);
}

void uart_putc( unsigned char data ) {
	Buffer_StoreElement( &UARTOutputBuffer, data );
	
	// enable the sending interrupt
	UART_CONTROL |= _BV( UDRIE );
}


void uart_puts( const char *s ) {
	while ( *s ) {
		uart_putc(*s++);
	}
}

bool uart_hasData( void ) {
	return (UARTInputBuffer.Elements > 0);
}

unsigned char uart_getc( void ) {	 
	return Buffer_GetElement( &UARTInputBuffer );
}
