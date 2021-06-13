/*
 * Pointers_AVR2560.cpp
 *
 * Created: 12-09-2020 23:40:51
 * Author : kunal
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include "GB_uarts.h"
//#define b PORTB

int main(void)
{ 
	char gb_buff[20];
	GB_UART_Init0();
	GB_printString0("Kunal\n");
	
	uint8_t gb_a =1;
	uint8_t volatile *gb_p ;
	gb_p = &PORTB;
	sprintf(gb_buff, "%p\n",gb_p );
	//printf(" Address of a: %p\n", p);
	GB_printString0(gb_p);
	//RT_TxChar0(p);
	
    /* Replace with your application code */
    while (1) 
    {
    }
}

