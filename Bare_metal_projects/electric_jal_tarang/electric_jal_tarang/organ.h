#include <avr/io.h>
#include <util/delay.h>

#define SPEAKER                 PD7                            /* OC0A */
#define SPEAKER_PORT            PORTD
#define SPEAKER_PIN             PIND
#define SPEAKER_DDR             DDRD

//#include "pinDefines.h"
// Plays a note for the given duration.  None of these times are
//  calibrated to actual notes or tempi.  It's all relative to TIMEBASE.
void playNote(uint16_t period, uint16_t duration);

// Does nothing for a time equal to the passed duration.
void rest(uint16_t duration);


void playNote(uint16_t period, uint16_t duration) {
	uint16_t elapsed;
	uint16_t i;
	for (elapsed = 0; elapsed < duration; elapsed += period) {
		/* For loop with variable delay selects the pitch */
		for (i = 0; i < period; i++) {
			_delay_us(1);
		}
		SPEAKER_PORT ^= (1 << SPEAKER);
	}
}

void rest(uint16_t duration) {
	do {
		_delay_us(1);
	} while (--duration);
}// ------------- Function prototypes -------------- //

