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


#include "GB_adc.h"
#include "GB_uarts.h"

uint16_t GB_jolangle(uint16_t gb_val)
{    uint16_t gb_anser;
	gb_anser= gb_val*0.175;
	return gb_anser;

}

int main(void)
{
	 GB_ADC_setup();
	 GB_UART_Init0();

	 GB_printString0("*************Joystick********************\n");
	 _delay_ms(100);
	 int gb_x = 0, gb_y= 0 ;
	 
    /* Replace with your application code */
    while (1) 
    {
		GB_printString0(" x axis \n");
			gb_x = GB_ADC_select(ADC1);
			GB_printString0(" y axis \n");
			gb_y = GB_ADC_select(ADC2);
    }
}

