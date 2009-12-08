#include <stdio.h>

#include "penguino/uart/uart.h"
#include "penguino/uart/uart-stdio.h"
#include "penguino/io.h"
#include "penguino/time.h"

#define UART_BAUD_RATE 500000

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
   
   
   // take ADC readings
   adc_init( );
   
   while( 1 ) {
      // read ADC reading on port A, pin 0
      uint16_t potReading = adc_read( 0 );
      
      if ( potReading < LOW_READING ) {
         statusLed_green( );
      } else if ( potReading > HIGH_READING ) {
         statusLed_red( );
      } else {
         // in the middle
         statusLed_orange( );
      }
      
      printf( "ADC Reading: %d\r\n", potReading );
   }

   return 0;
}
