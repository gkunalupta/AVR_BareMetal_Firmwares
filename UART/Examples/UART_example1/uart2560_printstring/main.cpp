/*
 * uart2560_printstring.cpp
 *
 * Created: 03-05-2021 06:12:17
 * Author : kunal
 */ 

#include <avr/io.h>
#include <util/delay.h>

#include "uarts.h""


int main(void)
{
		UART_Init0();
		printString0("Kunal Gettobyte\n");   // printing string
		UART_TxChar0(0b01100100);            // printing single word by passing its Binary value 
		printString0("\n");                  // New Line
		UART_TxChar0(0x61);                  // printing single word by passing Hex value
		printString0("\n");                  // New Line
		decimel0(255);                       // printing decimal value 
		printString0("\n");
		bit0('a');                           // printing binary value of passed argument 
		
	    char recv[100];
		char a;
		float x = 23.76;
    /* Replace with your application code */
    while (1) 
    {
		
		printString0("\nGettobyte YouTube \n");
		_delay_ms(100);
		
		// Receive String
		rxstring0(recv);
		printString0("Received data string : ");
		printString0(recv);            
		printString0("\n");
		
		// Receive Word
		a = UART_RxChar0();
		printString0("Received single word : ");
		UART_TxChar0(a);
		printString0("\n");
		
		//print float value
		float_value0(x);
		
		_delay_ms(100);
		
    }
}

