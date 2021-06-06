/*
 * experimenting ccpp.cpp
 *
 * Created: 18-03-2021 19:22:50
 * Author : kunal
 */ 

#include <avr/io.h>
#include "uarts.h"
#include <avr/delay.h>

void f()__attribute__
{
	UART_TxChar0("i greater then 0\n");
	
}

int main(void)
{
	UART_Init0();
	uint8_t i =0;
    /* Replace with your application code */
	UART_TxChar0("code for understanding attribute keyword\n")
    while (1) 
    {
		f();
		_delay_ms(1000);
		
    }
}

