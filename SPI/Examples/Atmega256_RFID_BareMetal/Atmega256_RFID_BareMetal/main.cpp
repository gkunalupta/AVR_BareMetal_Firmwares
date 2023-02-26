/*
 * Atmega256_RFID_BareMetal.cpp
 *
 * Created: 2/10/2023 9:56:20 PM
 * Author : acer
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "GB_uarts.h"
#include "GB_spi_master.h"
#include "GPIO.h"
#include "GB_millis.h"
#include "GB_MFRC522.h"


int main(void)
{
	uint8_t gb_a = 0x00;
	GB_UART_Init0();
	GB_init_millis(16000000UL); //frequency the atmega328p is running at
	GB_MA_SPI0_init_master();
	pinMode(gb_MFRC522_CE,&DDRB, OUTPUT);
	/* Replace with your application code */
	GB_MFRC522Version();
		
	MFRC522_init();
	_delay_ms(100);
	
    while (1) 
    {
        GB_MFRC522Version();
        _delay_ms(3000);
		
		GB_PICC_IsNewCardPresent();
		
		  //  _delay_ms(3000);
		    
		
		
    }
}





