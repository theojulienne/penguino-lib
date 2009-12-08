#include <stdio.h>

#include "penguino/uart/uart.h"
#include "penguino/uart/uart-stdio.h"
#include "penguino/io.h"

#define UART_BAUD_RATE 9600

#define LOW_READING  341
#define HIGH_READING 682

int main( void ) {
   // initalise UART
   uart_init( UART_BAUD_RATE );
   
   // enable UART as stdio
   uart_stdio_init( );
   
   printf( "Hello World\r\n" );
   
   adc_init( );

   statusLed_init( );
   
   while( 1 ) {
      
      uint16_t potReading = adc_read( 0 );
      
      if ( potReading < LOW_READING ) {
         statusLed_green( );
      } else if ( potReading > HIGH_READING ) {
         statusLed_red( );
      } else {
         // in the middle
         statusLed_orange( );
      }
      
      printf( "Reading Pot: %d\r\n", potReading );
   }

   return 0;
}
