/*
 * SPI-master.cpp
 *
 * Created: 11-11-2020 17:13:12
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
1) When configured as master,
   MOSI,SS,SCK are configured as OUTPUT and MISO as Slave
   a) MOSI: The data which is written on SPDR register is send in binary form via this pin
   b) SS: the desired SS pin is made LOW to select the corresponding Slave
   c) SCL: The Synchronized clock Pulses (High and Low Bits) are generated via this pin and fed to SCK pin of Slave
            SPR1:0 and SPI2 configure the frequency for SPI clock

2) by making SS pin LOW slave is selected and Data from shift register is shifted out.

3) If SS pin is configured as Input , it should be checked that it's line should not be 
made low by Peripheral Circuit , if it does then SPI system of MCU interprets that another master has 
made the SS pin low and will start acting like salve

4) When 3rd point is occurred , MSTR bit in SPCR register is cleared and
MOSI and SCK line automatically becomes input as MCU is configured as slave.

5) On completion of data transmission from MOSI line/MISO line SPIF flag is set , 
thus every time when SPIF is set 1 during Communication Session , MSTR bit should be checked and made 1
for re-enabling SPI master MODE

*/
#ifndef F_CPU
#define F_CPU 16000000UL
#endif
#include "GB_uarts.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "GB_SPI_master.h"

int main(void)
{   
	GB_UART_Init0();
	GB_MA_SPI0_init_master();                     //Initialize SPI Master
	GB_MA_SPI0_disable_interrupt();
    char gb_ch[30],gb_bh[30];
	memset(gb_ch, '\0', 30);
	memset(gb_bh, '\0', 30);
	GB_printString0("SPI-master-sending\n");
	sei();
	int8_t gb_c=0;
	while(1)
	{
		  
	
		  if(gb_c<1)
		  {

			  GB_printString0("SPI-master-Sending\n");
			  GB_MA_SPI0_send_string("Subscribe Gettobyte");
			  GB_MA_SPI0_send_string("Kunal Gupta");
			  GB_MA_SPI0_send_byte('p');
			  GB_printString0("\n");
			  _delay_ms(100);
			  gb_c++;
			  break;
		  }
		  
		  
		  

   }
}




//For master sending
/*
if(gb_c<1)
{

GB_printString0("SPI-master-Sending\n");
GB_MA_SPI0_send_string("Subscribe Gettobyte");
GB_MA_SPI0_send_string("Kunal Gupta");
GB_MA_SPI0_send_byte('p');
GB_printString0("\n");
_delay_ms(100);
gb_c++;
break;
}
*/

//For Master Receiving
/*
		 GB_MA_SPI0_read_block(gb_ch,19);
		  GB_MA_SPI0_read_block(gb_bh,11);
		  uint8_t gb_a = GB_MA_SPI0_read_byte();
		  
		  GB_printString0(gb_ch);
		 GB_printString0("\n");
		  GB_printString0(gb_bh);
		  GB_printString0("\n");
		  GB_UART_TxChar0(gb_a);
		  GB_printString0("\n");
		  
		  _delay_ms(100);
*/