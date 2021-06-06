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
#include "uarts.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "SPI_master.h"

int main(void)
{   
	UART_Init0();
	MA_SPI0_init_master();                     //Initialize SPI Master
	MA_SPI0_disable_interrupt();
    char ch[30],bh[30];
	memset(ch, '\0', 30);
	memset(bh, '\0', 30);
	printString0("SPI-master-sending\n");
	sei();
	int8_t c=0;
	while(1)
	{
		  
	
		  if(c<1)
		  {

			  printString0("SPI-master-Sending\n");
			  MA_SPI0_send_string("Subscribe Gettobyte");
			  MA_SPI0_send_string("Kunal Gupta");
			  MA_SPI0_send_byte('p');
			  printString0("\n");
			  _delay_ms(100);
			  c++;
			  break;
		  }
		  
		  
		  

   }
}




//For master sending
/*
if(c<1)
{

printString0("SPI-master-Sending\n");
MA_SPI0_send_string("Subscribe Gettobyte");
MA_SPI0_send_string("Kunal Gupta");
MA_SPI0_send_byte('p');
printString0("\n");
_delay_ms(100);
c++;
break;
}
*/

//For Master Receiving
/*
		  MA_SPI0_read_block(ch,19);
		  MA_SPI0_read_block(bh,11);
		  uint8_t a = MA_SPI0_read_byte();
		  
		  printString0(ch);
		  printString0("\n");
		  printString0(bh);
		  printString0("\n");
		  UART_TxChar0(a);
		  printString0("\n");
		  
		  _delay_ms(100);
*/