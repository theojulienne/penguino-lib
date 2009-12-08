#ifndef PENGUINO_TIME_H
#define PENGUINO_TIME_H

#include <util/delay.h>

static inline void delay_ms( uint32_t ms ) {
	while ( ms ) {
		_delay_ms( 1 );
		ms--;
	}
}

#endif
