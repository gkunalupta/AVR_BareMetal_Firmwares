/*
 * wq128flash.cpp
 *
 * Created: 22-03-2021 11:12:42
 * Author : kunal
 */ 

#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "GB_uarts.h"
#include "GB_spi_master.h"
#include "GPIO.h"
#include "GB_w25q128jv.h"

//#define Flash_CE PB0

int main(void)
{
	GB_UART_Init0();
	GB_MA_SPI0_init_master();
	pinMode(gb_Flash_CE,&DDRB, OUTPUT);
	uint8_t gb_x = 0x00;
	uint8_t gb_y = 0x00;
	uint8_t gb_z = 0x00;
	uint8_t gb_p = 0x00;
	
	char gb_senddata[25] = "Kunal gupta gettobyte";
	char gb_receivedata[25] = {0};
		
	uint8_t gb_SR1 = 0;
	
    while (1) 
    {
		
	GB_erase_sector4KB(gb_read_addr2);
	_delay_ms(50);
	
	
	GB_Write_wq12_data(gb_read_addr2,gb_senddata,20);
	_delay_ms(1000);
	GB_read_wq128_data(gb_read_addr2,gb_receivedata,18);
	_delay_ms(50);
	GB_printString0(gb_receivedata);
		GB_printString0("\n");
	//JED_id();
	/*
	GB_ReadSR(gb_ReadSR1);
	GB_ReadSR(gb_ReadSR2);
	GB_ReadSR(gb_ReadSR3);
	_delay_ms(100);
	*/
	/*
	GB_UART_TxChar0(gb_x);
	GB_UART_TxChar0(gb_y);
	GB_UART_TxChar0(gb_z);
	GB_printString0("\n");
	*/
	_delay_ms(100);
}
	
}




/*

*********************write data bytes on specified address*************************
Para:
SS-> is slave select pin
WriteData(0x02)-> instruc address to write data on wq128
read_addr2-> address of memory which has to be written
and then send bytes of data , after sending last byte make the SS pin High again
MA_SPI0_send_byte_conti('i') --> function for writing a byte

code:
GB_erase_sector(gb_read_addr2);
_delay_ms(50);
GB_WriteEnable_flash();
gb_Flash_CE_pin_low;
GB_MA_SPI0_send_byte_conti(gb_WriteData);
GB_MA_SPI0_send_byte_conti(((gb_read_addr2>>16) & (0xff)));
GB_MA_SPI0_send_byte_conti(((gb_read_addr2>>8) & (0xff)));
GB_MA_SPI0_send_byte_conti(gb_read_addr2 & 0xff);
GB_MA_SPI0_send_byte_conti('m');
GB_MA_SPI0_send_byte_conti('y');
GB_MA_SPI0_send_byte_conti('p');
GB_MA_SPI0_send_byte_conti('i');
gb_Flash_CE_pin_high;





*************************Read data bytes on specifoed address***************************
Para:
SS-> is slave select pin
ReadData(0x03)-> instruc address to read data on wq128
read_addr2-> address of memory which has to be written
and then Read bytes of data , after reading last byte make the SS pin High again
MA_SPI0_read_byte() --> function for reading byte


Code:
gb_Flash_CE_pin_low;
GB_MA_SPI0_send_byte_conti(gb_ReadData);
GB_MA_SPI0_send_byte_conti(((gb_read_addr2>>16) & (0xff)));
GB_MA_SPI0_send_byte_conti(((gb_read_addr2>>8) & (0xff)));
GB_MA_SPI0_send_byte_conti(gb_read_addr2 & 0xff);
//_delay_us(10);

gb_x = GB_MA_SPI0_read_byte();
gb_y = GB_MA_SPI0_read_byte();
gb_z = GB_MA_SPI0_read_byte();
gb_p = GB_MA_SPI0_read_byte();

gb_receivedata[0] = GB_MA_SPI0_read_byte();
gb_receivedata[1] = GB_MA_SPI0_read_byte();
gb_receivedata[2] = GB_MA_SPI0_read_byte();
gb_receivedata[3] = GB_MA_SPI0_read_byte();

gb_Flash_CE_pin_high;








*************************example1*****************************
read and write functions example code for wq128

Para:
char gb_senddata[25] = "Kunal gupta gettobyte";
char gb_receivedata[25] = {0};
readaddr1--> is macro to address of memory of spi flash
Code:
    GB_erase_sector(gb_read_addr2);
    _delay_ms(50);
	GB_Write_wq12_data(gb_read_addr2,gb_senddata,10);
	_delay_ms(1000);
	GB_read_wq128_data(gb_read_addr2,gb_receivedata,8);
	_delay_ms(50);
	GB_printString0(gb_receivedata);
	
	
	
*************************example2*****************************
Para: First write data bytes 
and then read data bytes




***Write data bytes***
    GB_erase_sector(gb_read_addr2);
    _delay_ms(50);
	GB_WriteEnable_flash();
	gb_Flash_CE_pin_low;
	GB_MA_SPI0_send_byte_conti(gb_WriteData);
	GB_MA_SPI0_send_byte_conti(((gb_read_addr2>>16) & (0xff)));
	GB_MA_SPI0_send_byte_conti(((gb_read_addr2>>8) & (0xff)));
	GB_MA_SPI0_send_byte_conti(gb_read_addr2 & 0xff);
	GB_MA_SPI0_send_byte_conti('z');
	GB_MA_SPI0_send_byte_conti('y');
	GB_MA_SPI0_send_byte_conti('x');
	GB_MA_SPI0_send_byte_conti('w');
	gb_Flash_CE_pin_high;
	
	_delay_ms(1000);
	
***read data bytes ***
	gb_Flash_CE_pin_low;
	GB_MA_SPI0_send_byte_conti(gb_ReadData);
	GB_MA_SPI0_send_byte_conti(((gb_read_addr2>>16) & (0xff)));
	GB_MA_SPI0_send_byte_conti(((gb_read_addr2>>8) & (0xff)));
	GB_MA_SPI0_send_byte_conti(gb_read_addr2 & 0xff);
	gb_x = GB_MA_SPI0_read_byte();
	gb_y = GB_MA_SPI0_read_byte();
	gb_z = GB_MA_SPI0_read_byte();
	gb_p = GB_MA_SPI0_read_byte();
	//gb_receivedata[0] =GB_MA_SPI0_read_byte();
	//gb_receivedata[1] = GB_MA_SPI0_read_byte();
	//gb_receivedata[2] = GB_MA_SPI0_read_byte();
	//gb_receivedata[3] = GB_MA_SPI0_read_byte();
	gb_Flash_CE_pin_high;
	
	
	_delay_ms(100);
	
	
	UART_TxChar0(gb_x);
	UART_TxChar0(gb_y);
	UART_TxChar0(gb_z);
	UART_TxChar0(gb_p);
*/