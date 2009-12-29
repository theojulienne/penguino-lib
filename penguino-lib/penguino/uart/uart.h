#ifndef UART_H
#define UART_H
/************************************************************************
Title:    UART for the Penguino AVR
Author:   David Collien (Icy Labs)
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

#include "../io.h"

extern void uart_init( uint32_t baudrate );

extern void uart_putc( unsigned char data );

extern void uart_puts( const char *s );

extern bool uart_hasData( void );

extern unsigned char uart_getc( void );

#endif
