/*
 * electric_jal_tarang.cpp
 *
 * Created: 18-10-2020 10:51:13
 * Author : kunal
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "GB_uarts.h"
#include "scale16.h"
#include "organ.h"
#define gb_NOTE_DURATION     0xF000        /* determines long note length */




int main(void) {

	// -------- Inits --------- //
	SPEAKER_DDR |= (1 << SPEAKER);                 /* speaker for output */
	GB_UART_Init0();
	GB_printString0("----- Serial Organ ------\r\n");

	char gb_fromCompy;                        /* used to store serial input */
	uint16_t gb_currentNoteLength = gb_NOTE_DURATION / 2;
	const uint8_t gb_keys[] = { 'a', 'w', 's', 'e', 'd', 'f', 't',
		'g', 'y', 'h', 'j', 'i', 'k', 'o',
		'l', 'p', ';', '\''
	};
	const uint16_t gb_notes[] = { G4, Gx4, A4, Ax4, B4, C5, Cx5,
		D5, Dx5, E5, F5, Fx5, G5, Gx5,
		A5, Ax5, B5, C6
	};
	uint8_t gb_isNote;
	uint8_t gb_i;

	// ------ Event loop ------ //
	while (1) {

		/* Get Key */
		gb_fromCompy = GB_UART_RxChar0();      /* waits here until there is input */
		GB_UART_TxChar0('N');     /* alert computer we're ready for next note */

		/* Play Notes */
		gb_isNote = 0;
		for (gb_i = 0; gb_i < sizeof(gb_keys); gb_i++) {
			if (gb_fromCompy == gb_keys[gb_i]) {       /* found match in lookup table */
				GB_playNote(gb_notes[gb_i], gb_currentNoteLength);
				gb_isNote = 1;                  /* record that we've found a note */
				break;                               /* drop out of for() loop */
			}
		}

		/* Handle non-note keys: tempo changes and rests */
		if (!gb_isNote) {
			if (gb_fromCompy == '[') {                   /* code for short note */
				gb_currentNoteLength = gb_NOTE_DURATION / 2;
			}
			else if (gb_fromCompy == ']') {               /* code for long note */
				gb_currentNoteLength = gb_NOTE_DURATION;
			}
			else {                                /* unrecognized, just rest */
				GB_rest(gb_currentNoteLength);
			}
		}

		}                                                  /* End event loop */
		return 0;
	}



