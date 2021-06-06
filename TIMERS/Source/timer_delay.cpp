
// initialize timer, interrupt and variable
void timer1_init()
{
	// set up timer with prescaler = 1024
	TCCR1B |= (1 << CS12)|(1<<CS10);
	
	// initialize counter
	TCNT1 = 0;
	
	// enable overflow interrupt
	//TIMSK1 |= (1 << TOIE1);
	
	// enable global interrupts
	//sei();
	
	// initialize overflow counter variable
	tot_overflow = 0;
}
void Timer_100_msecs()
{
	// set up timer with prescaler = 64 , Timer_frequency=250khz,
	// period= 4*10^-6 secs, Max_delay=262.14 milisecs , normal mode
	TCCR1B |= (1 << CS11)|(1<<CS10);
	
	// initialize counter
	TCNT1 = 0;
	
	while (TCNT1 <= 2499)
	{
		PIN_PORT |= (1 << PIN_NO);    // toggles the led
	}
	TCNT1 = 0;            // reset counter
	CLEAR_BIT(PIN_PORT,PIN_NO);
}
void Timer_200_msecs()
{
	// set up timer with prescaler = 64 , Timer_frequency=250khz,
	// period= 4*10^-6 secs, Max_delay=262.14 milisecs , normal mode
	TCCR1B |= (1 << CS11)|(1<<CS10);
	
	// initialize counter
	TCNT1 = 0;
	
	while (TCNT1 <= 49999)
	{
		PIN_PORT |= (1 << PIN_NO);    // toggles the led
	}
	TCNT1 = 0;            // reset counter
	CLEAR_BIT(PIN_PORT,PIN_NO);
}
void Timer_300_msecs()
{
	// set up timer with prescaler = 256 , Timer_frequency=62500 hz,
	// period= 1.6*10^-5 secs, Max_delay=1.048secs , normal mode
	TCCR1B |= (1 << CS12);
	
	// initialize counter
	TCNT1 = 0;
	
	while (TCNT1 <= 18749)
	{
		PIN_PORT |= (1 << PIN_NO);    // toggles the led
	}
	TCNT1 = 0;            // reset counter
	CLEAR_BIT(PIN_PORT,PIN_NO);
	
}
void Timer_400_msecs()
{
	// set up timer with prescaler = 256 , Timer_frequency=62500 hz,
	// period= 1.6*10^-5 secs, Max_delay=1.048secs , normal mode
	TCCR1B |= (1 << CS12);
	
	// initialize counter
	TCNT1 = 0;
	
	while (TCNT1 <= 24999)
	{
		PIN_PORT |= (1 << PIN_NO);    // toggles the led
	}
	TCNT1 = 0;            // reset counter
	CLEAR_BIT(PIN_PORT,PIN_NO);
}
void Timer_500_msecs()
{
	// set up timer with prescaler = 256 , Timer_frequency=62500 hz,
	// period= 1.6*10^-5 secs, Max_delay=1.048secs , normal mode
	TCCR1B |= (1 << CS12);
	
	// initialize counter
	TCNT1 = 0;
	
	while (TCNT1 <= 31249)
	{
		PIN_PORT |= (1 << PIN_NO);    // toggles the led
	}
	TCNT1 = 0;            // reset counter
	CLEAR_BIT(PIN_PORT,PIN_NO);
	
}
void Timer_600_msecs()
{
	// set up timer with prescaler = 256 , Timer_frequency=62500 hz,
	// period= 1.6*10^-5 secs, Max_delay=1.048secs , normal mode
	TCCR1B |= (1 << CS12);
	
	// initialize counter
	TCNT1 = 0;
	
	while (TCNT1 <= 37499)
	{
		PIN_PORT |= (1 << PIN_NO);    // toggles the led
	}
	TCNT1 = 0;            // reset counter
	CLEAR_BIT(PIN_PORT,PIN_NO);
}
void Timer_700_msecs()
{
	// set up timer with prescaler = 256 , Timer_frequency=62500 hz,
	// period= 1.6*10^-5 secs, Max_delay=1.048secs , normal mode
	TCCR1B |= (1 << CS12);
	
	// initialize counter
	TCNT1 = 0;
	
	while (TCNT1 <= 43749)
	{
		PIN_PORT |= (1 << PIN_NO);    // toggles the led
	}
	TCNT1 = 0;            // reset counter
	CLEAR_BIT(PIN_PORT,PIN_NO);
}
void Timer_800_msecs()
{
	// set up timer with prescaler = 256 , Timer_frequency=62500 hz,
	// period= 1.6*10^-5 secs, Max_delay=1.048secs , normal mode
	TCCR1B |= (1 << CS12);
	
	// initialize counter
	TCNT1 = 0;
	
	while (TCNT1 <= 49999)
	{
		PIN_PORT |= (1 << PIN_NO);    // toggles the led
	}
	TCNT1 = 0;            // reset counter
	CLEAR_BIT(PIN_PORT,PIN_NO);
}
void Timer_900_msecs()
{
	// set up timer with prescaler = 256 , Timer_frequency=62500 hz,
	// period= 1.6*10^-5 secs, Max_delay=1.048secs , normal mode
	TCCR1B |= (1 << CS12);
	
	// initialize counter
	TCNT1 = 0;
	
	while (TCNT1 <= 56249)
	{
		PIN_PORT |= (1 << PIN_NO);    // toggles the led
	}
	TCNT1 = 0;            // reset counter
	CLEAR_BIT(PIN_PORT,PIN_NO);
}


void Timer_1_sec()
{
	// set up timer with prescaler = 1024 , Timer_frequency=15625 hz,
	// period= 6.4*10^-5, Max_delay=4.194secs , normal mode
	TCCR1B |= (1 << CS12)|(1<<CS10);
	
	// initialize counter
	TCNT1 = 0;
	
	while (TCNT1 <= 15624)
	{
		PIN_PORT |= (1 << PIN_NO);    // toggles the led
	}
	TCNT1 = 0;            // reset counter
	CLEAR_BIT(PIN_PORT,PIN_NO);
	
}
void Timer_2_secs()
{
	// set up timer with prescaler = 1024 , Timer_frequency=15625 hz,
	// period= 6.4*10^-5, Max_delay=4.194secs , normal mode
	TCCR1B |= (1 << CS12)|(1<<CS10);
	
	// initialize counter
	TCNT1 = 0;
	
	while (TCNT1 <= 31249)
	{
		PIN_PORT |= (1 << PIN_NO);    // toggles the led
	}
	TCNT1 = 0;            // reset counter
	CLEAR_BIT(PIN_PORT,PIN_NO);
}
void Timer_3_secs()
{
	// set up timer with prescaler = 1024 , Timer_frequency=15625 hz,
	// period= 6.4*10^-5, Max_delay=4.194secs , normal mode
	TCCR1B |= (1 << CS12)|(1<<CS10);
	
	// initialize counter
	TCNT1 = 0;
	
	while (TCNT1 <= 46874)
	{
		PIN_PORT |= (1 << PIN_NO);    // toggles the led
	}
	TCNT1 = 0;            // reset counter
	CLEAR_BIT(PIN_PORT,PIN_NO);
}
void Timer_4_secs()
{
	//lcd_print2line("4 sec");
	// set up timer with prescaler = 1024 , Timer_frequency=15625 hz,
	// period= 6.4*10^-5, Max_delay=4.194secs , normal mode
	TCCR1B |= (1 << CS12)|(1<<CS10);
	
	// initialize counter
	TCNT1 = 0;
	int c=0;
	while (TCNT1 <= 62499)
	{   if(c<1)
		{
			PIN_PORT |= (1 << PIN_NO);    // toggles the led
			//  lcd_print2line("moton");
			c++;
		}
	}
	TCNT1 = 0;            // reset counter
	CLEAR_BIT(PIN_PORT,PIN_NO);
	//	lcd_print2line("motof");
}

