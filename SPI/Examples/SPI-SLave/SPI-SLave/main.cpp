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
#include "GB_uarts.h"
#include "GB_SPI_slave.h"


int main(void)
{     
	GB_UART_Init0();
	GB_SL_SPI0_init_slave();                             //Initialize slave SPI
	GB_SL_SPI0_disable_interrupt();
	char gb_ch[30],gb_bh[30];
	memset(gb_ch, '\0', 30);
	memset(gb_bh, '\0', 30);
	sei();
	GB_printString0("SPI-Slave-receiving\n");
	int8_t gb_c=0;
	while(1)
	{
       	   _delay_us(100);
       	   GB_SL_SPI0_read_block(gb_ch,19);
       	   GB_SL_SPI0_read_block(gb_bh,11);
       	   GB_UART_TxChar0(GB_SL_SPI0_read_byte());
       	   
       	   
       	  GB_printString0("\n");
       	  GB_printString0(gb_ch);
       	   GB_printString0("\n");
       	   GB_printString0(gb_bh);
       	   GB_printString0("\n");
       	   
       	   memset(gb_ch, '\0', 30);
       	   memset(gb_bh, '\0', 30);
       	   _delay_us(100);
	    
   }
}



//Slave Receiving
/*
	   _delay_us(100);
	   GB_SL_SPI0_read_block(gb_ch,19);
	   GB_SL_SPI0_read_block(gb_bh,11);
	   GB_UART_TxChar0(GB_SL_SPI0_read_byte());
	   
	   
	   GB_printString0("\n");
	   GB_printString0(gb_ch);
	   GB_printString0("\n");
	   GB_printString0(gb_bh);
	   GB_printString0("\n");
	   
	   memset(gb_ch, '\0', 30);
	   memset(gb_bh, '\0', 30);
	   _delay_us(100);
*/


//Slave Sending
/*	       
GB_SL_SPI0_send_string("Subscribe Gettobyte");
GB_SL_SPI0_send_string("Kunal Gupta");
GB_SL_SPI0_send_byte('p');
*/

