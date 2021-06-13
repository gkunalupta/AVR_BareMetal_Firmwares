/*
 * experimenting ccpp.cpp
 *
 * Created: 18-03-2021 19:22:50
 * Author : kunal
 */ 

#include <avr/io.h>
#include "GB_uarts.h"
#include <avr/delay.h>

void f()__attribute__
{
	GB_UART_TxChar0("i greater then 0\n");
}

int main(void)
{
	GB_UART_Init0();
	uint8_t gb_i =0;
    /* Replace with your application code */
	GB_UART_TxChar0("code for understanding attribute keyword\n")
    while (1) 
    {
		f();
		_delay_ms(1000);
		
    }
}

