#ifndef PENGUINO_IO_H
#define PENGUINO_IO_H
/************************************************************************
Title:    I/O Interface for Penguino AVR
Author:   David Collien (Icy Labs)
Software: AVR-GCC 4.1, AVR Libc 1.4
Hardware: Penguino AVR
License:  MIT License

DESCRIPTION:
    Interface for initialising, driving and reading pins
    
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

#include "common.h"
#include "avr/io.h"


typedef enum { A, B, C, D } Port;
typedef enum { low=0, high=1, Low=0, High=1 } PinValue;

// Status LED

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




// Digital I/O

static inline void floatingInput_init( Port port, uint8_t pin ) {
	uint8_t mask = ~(1<<pin);
	switch( port ) {
		case A:
			DDRA  &= mask;
			PORTA &= mask; 
			break;
		case B:
			DDRB  &= mask;
			PORTB &= mask;
			break;
		case C:
			DDRC  &= mask;
			PORTC &= mask;
			break;
		case D:
			DDRD  &= mask;
			PORTD &= mask;		
			break;
		default:
			break;
	}
}

static inline void pullupInput_init( Port port, uint8_t pin ) {
	uint8_t ddrMask  = ~(1<<pin);
	uint8_t portMask = (1<<pin);
	switch( port ) {
		case A:
			DDRA  &= ddrMask;
			PORTA |= portMask; 
			break;
		case B:
			DDRB  &= ddrMask;
			PORTB |= portMask;
			break;
		case C:
			DDRC  &= ddrMask;
			PORTC |= portMask;
			break;
		case D:
			DDRD  &= ddrMask;
			PORTD |= portMask;	
			break;
		default:
			break;
	}	
}

static inline void output_init( Port port, uint8_t pin ) {
	uint8_t ddrMask  = (1<<pin);
	uint8_t portMask = ~(1<<pin);
	switch( port ) {
		case A:
			DDRA  |= ddrMask;
			PORTA &= portMask; 
			break;
		case B:
			DDRB  |= ddrMask;
			PORTB &= portMask;
			break;
		case C:
			DDRC  |= ddrMask;
			PORTC &= portMask;
			break;
		case D:
			DDRD  |= ddrMask;
			PORTD &= portMask;	
			break;
		default:
			break;
	}	
}

static inline uint8_t readPort( Port port ) {

	switch( port ) {
		case A: return PINA; 
		case B: return PINB;
		case C: return PINC;
		case D: return PIND;
		default: break;
	}
	
	return 0;
}

static inline bool readPin( Port port, uint8_t pin ) {
	uint8_t portMask = (1<<pin);
	
	return (readPort( port ) & portMask) != 0;
}

static inline void drivePort( Port port, uint8_t value ) {
	switch( port ) {
		case A: PORTA = value; 
		case B: PORTB = value;
		case C: PORTC = value;
		case D: PORTD = value;
		default: break;
	}
}

static inline void drivePin( Port port, uint8_t pin, PinValue value ) {
	uint8_t mask = (1<<pin);
	if ( value == High ) {
		switch( port ) {
			case A: PORTA |= mask; 
			case B: PORTB |= mask;
			case C: PORTC |= mask;
			case D: PORTD |= mask;
			default: break;
		}
	} else {
		switch( port ) {
			case A: PORTA &= ~mask; 
			case B: PORTB &= ~mask;
			case C: PORTC &= ~mask;
			case D: PORTD &= ~mask;
			default: break;
		}		
	}
}




// ADC

#define ADC_PORT A

static inline void adcInput_init( uint8_t pin ) {
	floatingInput_init( ADC_PORT, pin );
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
