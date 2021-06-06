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

#include <millis.h>
#include <uarts.h>
int main(void)
{   UART_Init0();
	init_millis(16000000UL); //frequency the atmega328p is running at
	unsigned long prev_millis; //the last time the led was toggled
	prev_millis = millis();
	sei();
	for(;;)
	{
		if (millis() - prev_millis < 1000)
		{
			//printString0("kunal");
			decimel0(millis());
			printString0("\n");
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

