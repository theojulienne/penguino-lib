/************************************************************************
Title:    Use UART as stdio stream
Author:   Theo Julienne (Icy Labs)
Software: AVR-GCC 4.1, AVR Libc 1.4
Hardware: Penguino AVR
License:  MIT License

DESCRIPTION:
    Allows UART to be used with printf and scanf, as if it were stdio
    
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

#include "../io.h"
#include <avr/io.h>
#include <stdio.h>
#include "uart.h"

static bool echo_enabled = false;

static int uart_stdio_putchar( char c, FILE *stream ) {
	uart_putc( c );
	
	return 0;
}

static int uart_stdio_getchar( FILE *stream ) {
    while ( !uart_hasData( ) )
        ; // wait...
    
    int c = uart_getc( );
	
	if ( echo_enabled && c != _FDEV_ERR && c != _FDEV_EOF ) {
        uart_putc( c );
	}
	
    return c;
}

static FILE uart_io = FDEV_SETUP_STREAM( uart_stdio_putchar, uart_stdio_getchar, _FDEV_SETUP_RW );

void uart_stdio_init( ) {
	stdout = &uart_io;
	stdin = &uart_io;
}

void uart_stdio_echo( bool enable ) {
    echo_enabled = enable;
}
