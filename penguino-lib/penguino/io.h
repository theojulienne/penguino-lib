#ifndef PENGUINO_IO_H
#define PENGUINO_IO_H
/************************************************************************
Title:    I/O Interface for Penguino AVR
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

#include "avr/io.h"

#define LED_PINS ((1<<7) | (1<<6))
#define GREEN_STATUS (1<<6)
#define RED_STATUS (1<<7)
#define ORANGE_STATUS (GREEN_STATUS | RED_STATUS)

static inline void statusLed_off( ) {
	PORTC &= (~LED_PINS);
}

static inline void statusLed_red( ) {
	statusLed_off( );
	PORTC |= RED_STATUS;
}

static inline void statusLed_green( ) {
   statusLed_off( );
	PORTC |= GREEN_STATUS;
}

static inline void statusLed_orange( ) {
	statusLed_off( );
	PORTC |= ORANGE_STATUS;
}

static inline void statusLed_init( ) {
	DDRC |= LED_PINS;
	statusLed_off( );
}

static inline void adc_init( ) {
   // enable the ADC, ADPS[0..2] bits = div clock by 128
   ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
        
   // clear out the ADMUX bits
   ADMUX = 0x00;
        
   // use AVCC (the pin) as reference (REFS[0..1] = 01)
   // pin 'AVCC' on Penguino should be connected to VCC (use a cap for extra noise reduction)
   ADMUX |= (1<<REFS0);
}

static inline uint16_t adc_read( uint8_t pin ) {
   // set flip the lower bits of ADMUX (previously zero) to choose the ADC pin
   ADMUX ^= pin;
   
   // start a conversion
   ADCSRA |= (1<<ADSC);
   
   // wait for the conversion to complete
   while ( ADCSRA & (1<<ADSC) ) {
      // contemplate the meaning of life
   }
   
   // unset the pin (back to zero)
   ADMUX ^= pin;

   return ADCW; // avr-libc short-cut for combining ADCL and ADCH into a 16-bit register
}


#endif
