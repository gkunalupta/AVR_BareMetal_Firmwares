/* 
The millis() function known from Arduino
Calling millis() will return the milliseconds since the program started
Tested on atmega328p
Using content from http://www.adnbr.co.uk/articles/counting-milliseconds
Author: Monoclecat, https://github.com/monoclecat/avr-millis-function
REMEMBER: Add sei(); after init_millis() to enable global interrupts!
 */
#ifndef GB_MILLIS_H_
#define GB_MILLIS_H_


#include <avr/io.h>
#include <util/atomic.h>
#include <avr/interrupt.h>

volatile unsigned long gb_timer1_millis; 
//NOTE: A unsigned long holds values from 0 to 4,294,967,295 (2^32 - 1). It will roll over to 0 after reaching its maximum value.
//DDRB  =(1<<PB7);
ISR(TIMER1_COMPA_vect)
{
	//printString0("k\n");
  gb_timer1_millis++;  
}

void GB_init_millis(unsigned long gb_f_cpu);
unsigned long GB_millis ();

#include "GB_millis.cpp"

#endif