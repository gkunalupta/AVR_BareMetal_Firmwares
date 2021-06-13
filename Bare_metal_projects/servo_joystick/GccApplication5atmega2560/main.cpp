/*
 * GccApplication5atmega2560.cpp
 *
 * Created: 1/9/2020 1:44:57 PM
 * Author : kunal
 */ 
# define F_CPU 16000000UL
#define ADC1 0x01  //(00000001)
#define ADC2 0x02  //(00000010)
#define ADC3 0x03  //(00000011)
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "adc.h"
char x[10],y[10];
static inline void initTimer1Servo(void) 
{
	/* Set up Timer1 (16bit) to give a pulse every 20ms */
	/* Use Fast PWM mode, counter max in ICR1 */
	TCCR1A |= (1 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << WGM13);
	TCCR1B |= (1 << CS11);  /* /1 prescaling -- counting in microseconds */
	ICR1 = 40000;                                    /* TOP value = 20ms */
	TCCR1A |= (1 << COM1A1)|(1<<COM1B1);              /* Direct output on PB5 / OC1A */
	DDRB |= (1 << PB5)|(1<<PB6);                            /* set pin for output */

}
void fun1(uint16_t angle)
{   //uint16_t count =count_maximum-count_minimum;
	
	OCR1A=(angle*22.22)+1000;
	decimel0(OCR1A);
	printString0("\n");
}


uint16_t jolangle(uint16_t val)
{    uint16_t anser;
    anser= val*0.175;
	return anser;

}


int main(void)
{  
   initTimer1Servo();
 //  ADC_setup();
UART_Init0();

printString0("\r\nWelcome to the Servo Demo\r\n");
fun1(0);
_delay_ms(100);
while (1)
{
// 	fun1(175);
// 	_delay_ms(1000);
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
		
		
	
	/*
	ADC_select(ADC1);
	printString0(" x axis \n");
    ADC_read();
	strcpy(x,sbuff);
ADC_select(ADC2);
//printString0(" y axis \n");
//ADC_read();
strcpy(y,sbuff);
    uint16_t z=atoi(x);
	decimel0(z);
	printString0("\n");
	uint16_t i= jolangle(z);
	decimel0(i);
	printString0("\n");
	fun1(i);
	*/


}

}

