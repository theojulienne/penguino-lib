#include <avr/sleep.h>

typedef enum {
	SleepIdle = 0,
	SleepADCNoiseReduction = _BV(SM0),
	SleepPowerDown = _BV(SM1),
	SleepPowerSave = (_BV(SM0) | _BV(SM1)),
	SleepStandby = (_BV(SM1) | _BV(SM2)),
	SleepExtendedStandby = (_BV(SM0) | _BV(SM1) | _BV(SM2))
} SleepMode;

static inline void sleep_setMode( uint8_t mode ) {
	set_sleep_mode( mode );
}

static inline void sleep_startSleeping( void ) {
	sleep_mode( );
}
