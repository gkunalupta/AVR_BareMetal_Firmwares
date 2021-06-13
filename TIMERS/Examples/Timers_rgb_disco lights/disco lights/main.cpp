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
#include "GB_uarts.h"

void GB_null()
{
	OCR1C= 0;
	OCR4C= 0;
	OCR4B= 0;
	OCR4A= 0;
	OCR1B= 0;
	//OCR1C= 0;
}
void GB_glow()
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


static inline void GB_initTimer1Servo(void)
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
static inline void GB_initTimer4Servo(void)
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
void GB_fun1(int gb_angle)
{   //uint16_t count =count_maximum-count_minimum;
	
	OCR4A=(gb_angle*22.22)+1000;
	GB_decimel0(OCR4A);
	GB_printString0("\n");
	
	_delay_ms(50000);
	
}
void GB_demo()
{  GB_printString0(" demo \n");
	GB_null();
	_delay_ms(500);
	for(int gb_i=0;gb_i<5;gb_i++)
	{
		
		GB_glow();
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
	GB_glow();
}
void GB_firstpattern()
{   GB_null();
	DDRB |= (1 << PB5)|(1<<PB6)|(1<<PB7);
	DDRH |= (1 << PH3)|(1<<PH4)|(1<<PH5);
	_delay_ms(500);
	GB_printString0(" first pattern \n");
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
void GB_secondpattern()
{  GB_printString0(" second pattern \n");
	GB_null();
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
void GB_thirdpattern()
{  GB_printString0(" third pattern \n");
	GB_null();
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
void GB_fourthpattern()
{   GB_printString0("fourth paaterm \n");
	GB_null();
	_delay_ms(500);
	DDRB |= (1 << PB5)|(1<<PB6)|(1<<PB7);
	DDRH |= (1 << PH3)|(1<<PH4)|(1<<PH5);
	for (uint16_t gb_i=0;gb_i<1024;gb_i++)
	{
		
		//decimel0(i);
		//printString0("/n");
		OCR4C= (gb_i*39.06);
		OCR4B= (gb_i*39.06);
		OCR4A= (gb_i*39.06);
		OCR1B= (gb_i*39.06);
		OCR1C= ((gb_i*39.06)/2);
		_delay_ms(200);
		
	}
	
}

uint16_t GB_map(uint16_t gb_x)
{
	return (gb_x*39.06);
	
}
void GB_fadeout ()
{
	for (uint16_t gb_i=0;gb_i<1024;gb_i++)
	{
		GB_decimel0(gb_i);
		GB_printString0("/n");
		OCR4C=GB_map(gb_i);
		//_delay_ms(100);
		
	}
}


int main(void)
{
	
	
	

	// -------- Inits --------- //
	
	GB_initTimer4Servo();
	GB_initTimer1Servo();
	char  GB_val;
	GB_UART_Init0();
	
	
	GB_printString0("DICO LIGHTS \n");
	GB_printString0("1. 1st Pattern \n");
	GB_printString0("2. 2nd Pattern \n");
	GB_printString0("3. 3rd Pattern \n");
	GB_printString0("4. 4th Pattern \n");
	GB_demo();
	
	while (1)
	{
		//firstpattern();
		//secondpattern();
		
		//	val= rxstring0();
		//UART_TxChar0(val);
		char gb_option = GB_UART_RxChar0();
		GB_UART_TxChar0(gb_option);
		switch (gb_option)
		{
			case '1' : {
				GB_firstpattern();
				break;
			}
			case '2' : {
				GB_secondpattern();
				break;
			}
			case '3' : {
				GB_thirdpattern();
				break;
			}
			case '4' : {
				GB_fourthpattern();
				break;
				
			}
		}
	}
}