/*
 * ServoMg90s.cpp
 *
 * Created: 01-11-2020 14:54:43
 * Author : kunal
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 16000000UL
#include "uarts.h"

static inline void initServo(void)
{
	/* Set up Timer1 (16bit) to give a pulse every 20ms or we can say 50 mhz signal 
	  Now clock frequency of crystal oscillator is : 16000000mhz*/
	
	// Use Fast PWM mode: using mode 14 , counter max is ICR4, So TOP = ICR4.
	TCCR4A |= (1 << WGM41);
	TCCR4B |= (1 << WGM42) | (1 << WGM43);
	
	 //Set the prescalor to 8 so N=8, 
	TCCR4B |= (1 << CS41);  /* /1 prescaling -- counting in microseconds */
	
	//TOP = 40000
	ICR4 = 40000;                                    /* TOP value = 20ms */
	
	//Non inverting Mode and I/O operation discontinued
	TCCR4A |= (1 << COM4C1);              /* Direct output on PB5 / OC1A */
	
	// Set pin to output for genrating OutputWave
	DDRH |= (1 << PH5);                            /* set pin for output */

}

void fun1(uint16_t angle)
{   //uint16_t count =count_maximum-count_minimum;
	
	OCR4C=(angle*22.22)+1000;
	decimel0(OCR4C);
	printString0("\n");
	
}

int main(void)
{  
	initServo();
	UART_Init0();

	printString0("\r\nWelcome to the Servo Demo\r\n");
	fun1(0);
	_delay_ms(100);
	while (1)
	{
		fun1(0);
		_delay_ms(1000);
		
		fun1(45);
		_delay_ms(1000);
		
		fun1(90);
		_delay_ms(1000);
		
		fun1(135);
		_delay_ms(1000);
		
		fun1(180);
		_delay_ms(1000);
		
		fun1(135);
		_delay_ms(1000);
		
		fun1(90);
		_delay_ms(1000);
		
		fun1(45);
		_delay_ms(1000);
		
		fun1(0);
		_delay_ms(1000);
		
	}
	
}
	
		
