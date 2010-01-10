#include <stdio.h>

#include "penguino/uart/uart.h"
#include "penguino/uart/uart-stdio.h"
#include "penguino/io.h"
#include "penguino/time.h"

#define UART_BAUD_RATE 115200

#define LOW_READING  341
#define HIGH_READING 682

int main( void ) {
	// initalise UART
	uart_init( UART_BAUD_RATE );
	
	// enable UART as stdio
	uart_stdio_init( );
	
	printf( "Hello World\r\n" );

	
	// flash status LED
	statusLed_init( );
	
	statusLed_red( );
	delay_ms( 300 );
	
	statusLed_orange( );
	delay_ms( 300 );
	
	statusLed_green( );
	delay_ms( 300 );
	
	statusLed_off( );
	delay_ms( 300 );
	
	
	// Port B pin 0 is an output
	output_init( B0 );
	
	// Port B pin 1 is an input with a pull-up
	pullupInput_init( B1 );
	
	// initialise ADC
	adc_init( );
	
	// port A pin 0 is for ADC reading
	adcInput_init( 0 );
	
	// take ADC readings
	while( 1 ) {
		// read ADC reading on port A, pin 0
		uint16_t potReading = adc_read( A0 );
		
		if ( potReading < LOW_READING ) {
			statusLed_green( );
		} else if ( potReading > HIGH_READING ) {
			statusLed_red( );
		} else {
			// in the middle
			statusLed_orange( );
		}
		
		printf( "ADC Reading: %d\r\n", potReading );
		
		if ( readPin( B1 ) ) {
			printf( "Port B Pin 1 Active\r\n" );
			
			// drive B0 high whenever B1 is high
			drivePin( B0, high );
		} else {
			
			drivePin( B0, low );
		}
        
        // sleep for a bit to avoid flooding UART
        delay_ms( 300 );
	}

	return 0;
}
