/*
 * Data_type_converstion_atmega2560.cpp
 *
 * Created: 06-06-2021 00:19:19
 * Author : kunal
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "stdio.h"
#include "math.h"
#include "uarts.h"


int main(void)
{
	UART_Init0();
	int a = 50;
    /* Replace with your application code */
    while (1) 
    {
		float x = static_cast<float>(a);
		float_value0(x);
		//float x = a;
		//float_value0(x);
		
		//char c = (a);
		//UART_TxChar0(c);
		
		_delay_ms(100);
		printString0("\n");
		
		
    }
}

