void GB_init_millis(unsigned long gb_f_cpu)
{
	unsigned long gb_ctc_match_overflow;
	gb_ctc_match_overflow = ((gb_f_cpu / 1000) / 8); //when timer1 is this value, 1ms has passed
	
	// (Set timer to clear when matching ctc_match_overflow) | (Set clock divisor to 8)
	TCCR1B = (1 << WGM12) | (1 << CS11);
	
	// high byte first, then low byte
	OCR1AH = (gb_ctc_match_overflow >> 8);
	OCR1AL = gb_ctc_match_overflow;
	
	// Enable the compare match interrupt
	TIMSK1 |= (1 << OCIE1A);
	//REMEMBER TO ENABLE GLOBAL INTERRUPTS AFTER THIS WITH sei(); !!!
}

unsigned long GB_millis ()
{
	GB_init_millis(16000000UL);
	unsigned long gb_millis_return=0;
	
	// Ensure this cannot be disrupted
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
		gb_millis_return = gb_timer1_millis;
	}
	return gb_millis_return;
}