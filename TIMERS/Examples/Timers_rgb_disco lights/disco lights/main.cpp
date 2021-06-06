/*
 * disco lights.cpp
 *
 * Created: 4/7/2020 3:22:04 PM
 * Author : kunal
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "pinDefines.h"
#include "uarts.h"

void null()
{
	OCR1C= 0;
	OCR4C= 0;
	OCR4B= 0;
	OCR4A= 0;
	OCR1B= 0;
	//OCR1C= 0;
}
void glow()
{
	
	//led1
	OCR4A=40000;  //PH3-6
	//led2
	OCR4B=40000;  //PH4-7
	//led3
	OCR4C=40000;  //PH5-8
	//led4
	OCR1B=40000; //PB6-12
	OCR1C=15000;  //PB7-13
}


static inline void initTimer1Servo(void)
{
	/* Set up Timer1 (16bit) to give a pulse every 20ms */
	/* Use Fast PWM mode, counter max in ICR1 */
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);
	TCCR1B |= (1 << CS11);  /* /1 prescaling -- counting in microseconds */
	ICR1 = 40000;                                    /* TOP value = 20ms */
	TCCR1A |= (1 << COM1A1)|(1<<COM1B1)|(1<<COM1C1);              /* Direct output on PB1 / OC1A */
	// DDRB |= (1 << PB5)|(1<<PB6)|(1<<PB7);                            /* set pin for output */
}
static inline void initTimer4Servo(void)
{
	/* Set up Timer1 (16bit) to give a pulse every 20ms */
	/* Use Fast PWM mode, counter max in ICR1 */
	TCCR4A |= (1 << WGM41);
	TCCR4B |= (1 << WGM42) | (1 << WGM43);
	TCCR4B |= (1 << CS41);  /* /1 prescaling -- counting in microseconds */
	ICR4 = 40000;                                    /* TOP value = 20ms */
	TCCR4A |= (1 << COM4A1)|(1<<COM4B1)|(1<<COM4C1);              /* Direct output on PB1 / OC1A */
	// DDRH |= (1 << PH3)|(1<<PH4)|(1<<PH5);                            /* set pin for output */
	
}
void fun1(int angle)
{   //uint16_t count =count_maximum-count_minimum;
	
	OCR4A=(angle*22.22)+1000;
	decimel0(OCR4A);
	printString0("\n");
	
	_delay_ms(50000);
	
}
void demo()
{  printString0(" demo \n");
	null();
	_delay_ms(500);
	for(int i=0;i<5;i++)
	{
		
		glow();
		_delay_ms(10000);
		DDRH &= ~(1<<PH3);
		DDRH &= ~(1<<PH4);
		DDRH &= ~(1<<PH5);
		DDRB &= ~(1<<PB6);
		DDRB &= ~(1<<PB7);
		_delay_ms(10000);
		//null();
		DDRB |= (1 << PB5)|(1<<PB6)|(1<<PB7);
		DDRH |= (1 << PH3)|(1<<PH4)|(1<<PH5);
		//null();
		_delay_ms(10000);
		
	}
	glow();
}
void firstpattern()
{   null();
	DDRB |= (1 << PB5)|(1<<PB6)|(1<<PB7);
	DDRH |= (1 << PH3)|(1<<PH4)|(1<<PH5);
	_delay_ms(500);
	printString0(" first pattern \n");
	//led1
	OCR4A=40000;  //PH3-6
	_delay_ms(20000);
	DDRH &= ~(1<<PH3);
	//led2
	OCR4B=40000;  //PH4-7
	_delay_ms(20000);
	DDRH &= ~(1<<PH4);
	//led3
	OCR4C=40000;  //PH5-8
	_delay_ms(20000);
	DDRH &= ~(1<<PH5);
	//led4
	OCR1B=40000; //PB6-12
	OCR1C=15000;  //PB7-13
	_delay_ms(20000);
	DDRB &= ~(1<<PB6);
	DDRB &= ~(1<<PB7);
}
void secondpattern()
{  printString0(" second pattern \n");
	null();
	_delay_ms(500);
	DDRB |= (1 << PB5)|(1<<PB6)|(1<<PB7);
	DDRH |= (1 << PH3)|(1<<PH4)|(1<<PH5);
	//led4
	
	OCR1B=40000; //PB6-12
	OCR1C=15000;  //PB7-13
	_delay_ms(20000);
	DDRB &= ~(1<<PB6);
	DDRB &= ~(1<<PB7);
	//led3
	
	OCR4C=40000;  //PH5-8
	_delay_ms(20000);
	DDRH &= ~(1<<PH5);
	//led2
	
	OCR4B=40000;  //PH4-7
	_delay_ms(20000);
	DDRH &= ~(1<<PH4);
	//led1
	;
	OCR4A=40000;  //PH3-6
	_delay_ms(20000);
	DDRH &= ~(1<<PH3);
	_delay_ms(100);
	
	
}
void thirdpattern()
{  printString0(" third pattern \n");
	null();
	_delay_ms(500);
	DDRB |= (1 << PB5)|(1<<PB6)|(1<<PB7);
	DDRH |= (1 << PH3)|(1<<PH4)|(1<<PH5);
	//led1
	OCR4A=40000;  //PH3-6
	
	//led2
	OCR4B=40000;  //PH4-7
	_delay_ms(20000);
	DDRH &= ~(1<<PH4);
	DDRH &= ~(1<<PH3);
	
	//led3
	OCR4C=40000;  //PH5-8
	
	//led4
	OCR1B=40000; //PB6-12
	OCR1C=15000;  //PB7-13
	_delay_ms(20000);
	DDRB &= ~(1<<PB6);
	DDRB &= ~(1<<PB7);
	DDRH &= ~(1<<PH5);
	//_delay_ms(2000);
	// null();
	DDRB |= (1 << PB5)|(1<<PB6)|(1<<PB7);
	DDRH |= (1 << PH3)|(1<<PH4)|(1<<PH5);
	
	//led2
	OCR4B=40000;  //PH4-7
	//led3
	OCR4C=40000;  //PH5-8
	_delay_ms(20000);
	DDRH &= ~(1<<PH4);
	DDRH &= ~(1<<PH5);
	//led1
	OCR4A=40000;  //PH3-6
	//led4
	OCR1B=40000; //PB6-12
	OCR1C=15000;  //PB7-13
	_delay_ms(20000);
	DDRB &= ~(1<<PB6);
	DDRB &= ~(1<<PB7);
	DDRH &= ~(1<<PH3);
	
	
	
}
void fourthpattern()
{   printString0("fourth paaterm \n");
	null();
	_delay_ms(500);
	DDRB |= (1 << PB5)|(1<<PB6)|(1<<PB7);
	DDRH |= (1 << PH3)|(1<<PH4)|(1<<PH5);
	for (uint16_t i=0;i<1024;i++)
	{
		
		//decimel0(i);
		//printString0("/n");
		OCR4C= (i*39.06);
		OCR4B= (i*39.06);
		OCR4A= (i*39.06);
		OCR1B= (i*39.06);
		OCR1C= ((i*39.06)/2);
		_delay_ms(200);
		
	}
	
}

uint16_t map(uint16_t x)
{
	return (x*39.06);
	
}
void fadeout ()
{
	for (uint16_t i=0;i<1024;i++)
	{
		decimel0(i);
		printString0("/n");
		OCR4C=map(i);
		//_delay_ms(100);
		
	}
}


int main(void)
{
	
	
	

	// -------- Inits --------- //
	
	initTimer4Servo();
	initTimer1Servo();
	char  val;
	UART_Init0();
	
	
	printString0("DICO LIGHTS \n");
	printString0("1. 1st Pattern \n");
	printString0("2. 2nd Pattern \n");
	printString0("3. 3rd Pattern \n");
	printString0("4. 4th Pattern \n");
	demo();
	
	while (1)
	{
		//firstpattern();
		//secondpattern();
		
		//	val= rxstring0();
		//UART_TxChar0(val);
		char option = UART_RxChar0();
		UART_TxChar0(option);
		switch (option)
		{
			case '1' : {
				firstpattern();
				break;
			}
			case '2' : {
				secondpattern();
				break;
			}
			case '3' : {
				thirdpattern();
				break;
			}
			case '4' : {
				fourthpattern();
				break;
				
			}
		}
	}
}