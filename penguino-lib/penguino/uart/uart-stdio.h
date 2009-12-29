#ifndef UART_STDIO_H
#define UART_STDIO_H
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

extern void uart_stdio_init( );

// enables or disables echo of received characters useful when accepting 
// user input, but should be disabled for software interaction.
// by default echo is disabled.
extern void uart_stdio_echo( bool enable );

#endif
