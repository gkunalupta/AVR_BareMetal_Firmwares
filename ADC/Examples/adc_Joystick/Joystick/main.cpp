/*
 * Joystick.cpp
 *
 * Created: 06-06-2021 23:00:21
 * Author : kunal
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


#include "adc.h"
#include "uarts.h"

uint16_t jolangle(uint16_t val)
{    uint16_t anser;
	anser= val*0.175;
	return anser;

}

int main(void)
{
	 ADC_setup();
	 UART_Init0();

	 printString0("*************Joystick********************\n");
	 _delay_ms(100);
	 int x = 0, y= 0 ;
	 
    /* Replace with your application code */
    while (1) 
    {
		printString0(" x axis \n");
			x = ADC_select(ADC1);
			printString0(" y axis \n");
			y = ADC_select(ADC2);
    }
}

