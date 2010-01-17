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


#define PORT_SHIFT 5
#define PORT_MASK (0x1F)

typedef enum { A=0, B=1, C=2, D=3 } Port;


typedef enum {
	A0 = ((A << PORT_SHIFT) | 0),
	A1 = ((A << PORT_SHIFT) | 1),
	A2 = ((A << PORT_SHIFT) | 2),
	A3 = ((A << PORT_SHIFT) | 3),
	A4 = ((A << PORT_SHIFT) | 4),
	A5 = ((A << PORT_SHIFT) | 5),
	A6 = ((A << PORT_SHIFT) | 6),
	A7 = ((A << PORT_SHIFT) | 7),
	
	B0 = ((B << PORT_SHIFT) | 0),
	B1 = ((B << PORT_SHIFT) | 1),
	B2 = ((B << PORT_SHIFT) | 2),
	B3 = ((B << PORT_SHIFT) | 3),
	B4 = ((B << PORT_SHIFT) | 4),
	B5 = ((B << PORT_SHIFT) | 5),
	B6 = ((B << PORT_SHIFT) | 6),
	B7 = ((B << PORT_SHIFT) | 7),
	
	C0 = ((C << PORT_SHIFT) | 0),
	C1 = ((C << PORT_SHIFT) | 1),
	
	D2 = ((D << PORT_SHIFT) | 2),
	D3 = ((D << PORT_SHIFT) | 3),
	D4 = ((D << PORT_SHIFT) | 4),
	D5 = ((D << PORT_SHIFT) | 5),
	D6 = ((D << PORT_SHIFT) | 6),
	D7 = ((D << PORT_SHIFT) | 7)
} Pin;

typedef enum { low=0, high=1, Low=0, High=1 } PinValue;

// Status LED

#define LED_PINS ((1<<7) | (1<<6))
#define GREEN_STATUS (1<<6)
#define RED_STATUS (1<<7)
#define ORANGE_STATUS (GREEN_STATUS | RED_STATUS)

static inline void statusLed_off( void ) {
	PORTC &= (~LED_PINS);
}

static inline void statusLed_red( void ) {
	statusLed_off( );
	PORTC |= RED_STATUS;
}

static inline void statusLed_green( void ) {
	statusLed_off( );
	PORTC |= GREEN_STATUS;
}

static inline void statusLed_orange( void ) {
	statusLed_off( );
	PORTC |= ORANGE_STATUS;
}

static inline void statusLed_init( void ) {
	DDRC |= LED_PINS;
	statusLed_off( );
}




// Digital I/O

static inline void floatingInput_init( Pin portPin ) {
	uint8_t pin  = PORT_MASK & portPin;
	Port    port = portPin >> PORT_SHIFT;
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

static inline void floatingInput_initPort( Port port ) {
	switch( port ) {
		case A:
			DDRA  = 0x00;
			PORTA = 0x00; 
			break;
		case B:
			DDRB  = 0x00;
			PORTB = 0x00;
			break;
		case C:
			DDRC  = 0x00;
			PORTC = 0x00;
			break;
		case D:
			DDRD  = 0x00;
			PORTD = 0x00;	
			break;
		default:
			break;
	}	
}

static inline void pullupInput_init( Pin portPin ) {
	uint8_t pin  = PORT_MASK & portPin;
	Port    port = portPin >> PORT_SHIFT;
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

static inline void pullupInput_initPort( Port port ) {
	switch( port ) {
		case A:
			DDRA  = 0x00;
			PORTA = 0xFF; 
			break;
		case B:
			DDRB  = 0x00;
			PORTB = 0xFF;
			break;
		case C:
			DDRC  = 0x00;
			PORTC = 0xFF;
			break;
		case D:
			DDRD  = 0x00;
			PORTD = 0xFF;	
			break;
		default:
			break;
	}	
}

static inline void output_init( Pin portPin ) {
	uint8_t pin  = PORT_MASK & portPin;
	Port    port = portPin >> PORT_SHIFT;
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

static inline void output_initPort( Port port ) {
	switch( port ) {
		case A:
			DDRA  = 0xFF;
			PORTA = 0x00; 
			break;
		case B:
			DDRB  = 0xFF;
			PORTB = 0x00;
			break;
		case C:
			DDRC  = 0xFF;
			PORTC = 0x00;
			break;
		case D:
			DDRD  = 0xFF;
			PORTD = 0x00;	
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

static inline PinValue readPin( Pin portPin ) {
	uint8_t pin  = PORT_MASK & portPin;
	Port    port = portPin >> PORT_SHIFT;
	uint8_t portMask = (1<<pin);
	
	return (readPort( port ) & portMask) != 0;
}

static inline void drivePort( Port port, uint8_t value ) {
	switch( port ) {
		case A: PORTA = value; break; 
		case B: PORTB = value; break;
		case C: PORTC = value; break;
		case D: PORTD = value; break;
		default: break;
	}
}

static inline void drivePin( Pin portPin, PinValue value ) {
	uint8_t pin  = PORT_MASK & portPin;
	Port    port = portPin >> PORT_SHIFT;
	uint8_t mask = (1<<pin);
	if ( value == High ) {
		switch( port ) {
			case A: PORTA |= mask; break; 
			case B: PORTB |= mask; break;
			case C: PORTC |= mask; break;
			case D: PORTD |= mask; break;
			default: break;
		}
	} else {
		switch( port ) {
			case A: PORTA &= ~mask; break; 
			case B: PORTB &= ~mask; break;
			case C: PORTC &= ~mask; break;
			case D: PORTD &= ~mask; break;
			default: break;
		}		
	}
}




// ADC
static inline void adcInput_init( Pin portPin ) {
	floatingInput_init( portPin );
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

static inline uint16_t adc_read( Pin portPin ) {
	uint8_t pin  = PORT_MASK & portPin;
	
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
