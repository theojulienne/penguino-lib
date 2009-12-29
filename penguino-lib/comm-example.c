#include <stdio.h>

#include "penguino/uart/uart.h"
#include "penguino/uart/uart-stdio.h"
#include "penguino/io.h"
#include "penguino/time.h"

#define UART_BAUD_RATE 115200

int main( void ) {
    char name[80];
    int age = 0;
    
	// initalise UART
	uart_init( UART_BAUD_RATE );
	
	// enable UART as stdio
	uart_stdio_init( );
	
	// enable echo on the UART stdin so the user can see what they are typing
    uart_stdio_echo( true );
	
	while ( 1 ) {
	    printf( "\r\n\r\nHello there, I'm a Penguino AVR!\r\n\r\n" );
	    
	    printf( "What's your name? " );
        scanf( "%s", name ); // sorry for the format vulnerability! example only
        
        printf( "\r\n\r\n" );
        
        printf( "Why hello, %s! How old are you? ", name );
        scanf( "%d", &age );
        
        printf( "\r\n\r\n" );
        
        printf( "Thanks, %s, for telling me you're %d years old!\r\n\r\n", name, age );
	    
	    // snooze
	    delay_ms( 300 );
	}

	return 0;
}
