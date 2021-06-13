/*
 * uart2560_printstring.cpp
 *
 * Created: 03-05-2021 06:12:17
 * Author : kunal
 */ 

#include <avr/io.h>
#include <util/delay.h>

#include "GB_uarts.h""


int main(void)
{
		GB_UART_Init0();
		GB_printString0("Kunal Gettobyte\n");   // printing string
		GB_UART_TxChar0(0b01100100);            // printing single word by passing its Binary value 
		GB_printString0("\n");                  // New Line
		GB_UART_TxChar0(0x61);                  // printing single word by passing Hex value
		GB_printString0("\n");                  // New Line
		GB_decimel0(255);                       // printing decimal value 
		GB_printString0("\n");
		GB_bit0('a');                           // printing binary value of passed argument 
		
	    char gb_recv[100];
		char gb_a;
		float gb_x = 23.76;
    /* Replace with your application code */
    while (1) 
    {
		
		GB_printString0("\nGettobyte YouTube \n");
		_delay_ms(100);
		
		// Receive String
		GB_rxstring0(gb_recv);
		GB_printString0("Received data string : ");
		GB_printString0(gb_recv);            
		GB_printString0("\n");
		
		// Receive Word
		gb_a = GB_UART_RxChar0();
		GB_printString0("Received single word : ");
		GB_UART_TxChar0(gb_a);
		GB_printString0("\n");
		
		//print float value
		GB_float_value0(gb_x);
		
		_delay_ms(100);
		
    }
}

