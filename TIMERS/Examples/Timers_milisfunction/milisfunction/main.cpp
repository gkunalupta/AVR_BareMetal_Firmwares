/*
 * milisfunction.cpp
 *
 * Created: 07-08-2020 23:59:28
 * Author : kunal
 */ 

#include <avr/io.h>
/* 
The millis() function known from Arduino
Calling millis() will return the milliseconds since the program started
Tested on atmega328p
Using content from http://www.adnbr.co.uk/articles/counting-milliseconds
Author: Monoclecat, https://github.com/monoclecat/avr-millis-function
REMEMBER: Add sei(); after init_millis() to enable global interrupts!
 */

#include <GB_millis.h>
#include <GB_uarts.h>
int main(void)
{   GB_UART_Init0();
	GB_init_millis(16000000UL); //frequency the atmega328p is running at
	unsigned long gb_prev_millis; //the last time the led was toggled
	gb_prev_millis = GB_millis();
	sei();
	for(;;)
	{
		if (GB_millis() - gb_prev_millis < 1000)
		{
			//printString0("kunal");
			GB_decimel0(GB_millis());
			GB_printString0("\n");
			//prev_millis = millis();
		}
		//prev_millis = millis();
	}
	return 0;
    /* Replace with your application code */
    while (1) 
    {
    }
}

