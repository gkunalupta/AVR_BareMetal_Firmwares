/*
 * Pointers_AVR2560.cpp
 *
 * Created: 12-09-2020 23:40:51
 * Author : kunal
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include "uarts.h"
//#define b PORTB

int main(void)
{ 
	char buff[20];
	UART_Init0();
	printString0("Kunal\n");
	
	uint8_t a =1;
	uint8_t volatile *p ;
	p = &PORTB;
	sprintf(buff, "%p\n",p );
	//printf(" Address of a: %p\n", p);
	printString0(p);
	//RT_TxChar0(p);
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

