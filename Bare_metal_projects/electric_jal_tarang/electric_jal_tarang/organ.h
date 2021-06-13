#include <avr/io.h>
#include <util/delay.h>

#define SPEAKER                 PD7                            /* OC0A */
#define SPEAKER_PORT            PORTD
#define SPEAKER_PIN             PIND
#define SPEAKER_DDR             DDRD

//#include "pinDefines.h"
// Plays a note for the given duration.  None of these times are
//  calibrated to actual notes or tempi.  It's all relative to TIMEBASE.
void GB_playNote(uint16_t gb_period, uint16_t gb_duration);

// Does nothing for a time equal to the passed duration.
void GB_rest(uint16_t gb_duration);


void GB_playNote(uint16_t gb_period, uint16_t gb_duration) {
	uint16_t gb_elapsed;
	uint16_t gb_i;
	for (gb_elapsed = 0; gb_elapsed < gb_duration; gb_elapsed += gb_period) {
		/* For loop with variable delay selects the pitch */
		for (gb_i = 0; gb_i < gb_period; gb_i++) {
			_delay_us(1);
		}
		SPEAKER_PORT ^= (1 << SPEAKER);
	}
}

void GB_rest(uint16_t gb_duration) {
	do {
		_delay_us(1);
	} while (--gb_duration);
}// ------------- Function prototypes -------------- //

