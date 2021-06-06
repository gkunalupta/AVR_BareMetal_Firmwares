/*
 * SPI-SLave.cpp
 *
 * Created: 11-11-2020 17:17:47
 * Author : kunal
 */ 
/* 
MISO -50(PB3)  --> Master In SLave out: Master Receives data from salve via this line
MOSI -51(PB2)  --> Moster Out Slave In: Master Sends data to Slave Via this line
SCK  -52(PB1)  --> Synchronous Clock: From this line clock is generated
SS   -53(PB0)  --> Slave Select: Slave is selected from this line by making the desired 
                   SS pin Low.
*/

/*
When Configured as Slave
1) MOSI,SCK,SS Are selected as input pins as these pins will be drived from the master SPI pins
2) MISO is selected as output when data has to be send from slave to master

*/

#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uarts.h"
#include "SPI_slave.h"


int main(void)
{     
	UART_Init0();
	SL_SPI0_init_slave();                             //Initialize slave SPI
	SL_SPI0_disable_interrupt();
	char ch[30],bh[30];
	memset(ch, '\0', 30);
	memset(bh, '\0', 30);
	sei();
	printString0("SPI-Slave-receiving\n");
	int8_t c=0;
	while(1)
	{
       	   _delay_us(100);
       	   SL_SPI0_read_block(ch,19);
       	   SL_SPI0_read_block(bh,11);
       	   UART_TxChar0(SL_SPI0_read_byte());
       	   
       	   
       	   printString0("\n");
       	   printString0(ch);
       	   printString0("\n");
       	   printString0(bh);
       	   printString0("\n");
       	   
       	   memset(ch, '\0', 30);
       	   memset(bh, '\0', 30);
       	   _delay_us(100);
	    
   }
}



//Slave Receiving
/*
	   _delay_us(100);
	   SL_SPI0_read_block(ch,19);
	   SL_SPI0_read_block(bh,11);
	   UART_TxChar0(SL_SPI0_read_byte());
	   
	   
	   printString0("\n");
	   printString0(ch);
	   printString0("\n");
	   printString0(bh);
	   printString0("\n");
	   
	   memset(ch, '\0', 30);
	   memset(bh, '\0', 30);
	   _delay_us(100);
*/


//Slave Sending
/*	       
SL_SPI0_send_string("Subscribe Gettobyte");
SL_SPI0_send_string("Kunal Gupta");
SL_SPI0_send_byte('p');
*/

