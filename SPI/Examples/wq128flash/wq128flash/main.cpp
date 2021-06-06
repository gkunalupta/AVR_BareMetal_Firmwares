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
#include "uarts.h"
#include "spi_master.h"
#include "GPIO.h"
#include "w25q128jv.h"

//#define Flash_CE PB0

int main(void)
{
	UART_Init0();
	MA_SPI0_init_master();
	pinMode(Flash_CE,&DDRB, OUTPUT);
	uint8_t x = 0x00;
	uint8_t y = 0x00;
	uint8_t z = 0x00;
	uint8_t p = 0x00;
	
	char senddata[25] = "Kunal gupta gettobyte";
	char receivedata[25] = {0};
		
	uint8_t SR1 = 0;
	
    while (1) 
    {
		
	erase_sector4KB(read_addr2);
	_delay_ms(50);
	
	
	Write_wq12_data(read_addr2,senddata,20);
	_delay_ms(1000);
	read_wq128_data(read_addr2,receivedata,18);
	_delay_ms(50);
	printString0(receivedata);
		printString0("\n");
	//JED_id();
	/*
	ReadSR(ReadSR1);
	ReadSR(ReadSR2);
	ReadSR(ReadSR3);
	_delay_ms(100);
	*/
	/*
	UART_TxChar0(x);
	UART_TxChar0(y);
	UART_TxChar0(z);
	printString0("\n");
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
erase_sector(read_addr2);
_delay_ms(50);
WriteEnable_flash();
Flash_CE_pin_low;
MA_SPI0_send_byte_conti(WriteData);
MA_SPI0_send_byte_conti(((read_addr2>>16) & (0xff)));
MA_SPI0_send_byte_conti(((read_addr2>>8) & (0xff)));
MA_SPI0_send_byte_conti(read_addr2 & 0xff);
MA_SPI0_send_byte_conti('m');
MA_SPI0_send_byte_conti('y');
MA_SPI0_send_byte_conti('p');
MA_SPI0_send_byte_conti('i');
Flash_CE_pin_high;





*************************Read data bytes on specifoed address***************************
Para:
SS-> is slave select pin
ReadData(0x03)-> instruc address to read data on wq128
read_addr2-> address of memory which has to be written
and then Read bytes of data , after reading last byte make the SS pin High again
MA_SPI0_read_byte() --> function for reading byte


Code:
Flash_CE_pin_low;
MA_SPI0_send_byte_conti(ReadData);
MA_SPI0_send_byte_conti(((read_addr2>>16) & (0xff)));
MA_SPI0_send_byte_conti(((read_addr2>>8) & (0xff)));
MA_SPI0_send_byte_conti(read_addr2 & 0xff);
//_delay_us(10);

x = MA_SPI0_read_byte();
y = MA_SPI0_read_byte();
z = MA_SPI0_read_byte();
p = MA_SPI0_read_byte();

receivedata[0] = MA_SPI0_read_byte();
receivedata[1] = MA_SPI0_read_byte();
receivedata[2] = MA_SPI0_read_byte();
receivedata[3] = MA_SPI0_read_byte();

Flash_CE_pin_high;








*************************example1*****************************
read and write functions example code for wq128

Para:
char senddata[25] = "Kunal gupta gettobyte";
char receivedata[25] = {0};
readaddr1--> is macro to address of memory of spi flash
Code:
    erase_sector(read_addr2);
    _delay_ms(50);
	Write_wq12_data(read_addr2,senddata,10);
	_delay_ms(1000);
	read_wq128_data(read_addr2,receivedata,8);
	_delay_ms(50);
	printString0(receivedata);
	
	
	
*************************example2*****************************
Para: First write data bytes 
and then read data bytes




***Write data bytes***
    erase_sector(read_addr2);
    _delay_ms(50);
	WriteEnable_flash();
	Flash_CE_pin_low;
	MA_SPI0_send_byte_conti(WriteData);
	MA_SPI0_send_byte_conti(((read_addr2>>16) & (0xff)));
	MA_SPI0_send_byte_conti(((read_addr2>>8) & (0xff)));
	MA_SPI0_send_byte_conti(read_addr2 & 0xff);
	MA_SPI0_send_byte_conti('z');
	MA_SPI0_send_byte_conti('y');
	MA_SPI0_send_byte_conti('x');
	MA_SPI0_send_byte_conti('w');
	Flash_CE_pin_high;
	
	_delay_ms(1000);
	
***read data bytes ***
	Flash_CE_pin_low;
	MA_SPI0_send_byte_conti(ReadData);
	MA_SPI0_send_byte_conti(((read_addr2>>16) & (0xff)));
	MA_SPI0_send_byte_conti(((read_addr2>>8) & (0xff)));
	MA_SPI0_send_byte_conti(read_addr2 & 0xff);
	x = MA_SPI0_read_byte();
	y = MA_SPI0_read_byte();
	z = MA_SPI0_read_byte();
	p = MA_SPI0_read_byte();
	//receivedata[0] = MA_SPI0_read_byte();
	//receivedata[1] = MA_SPI0_read_byte();
	//receivedata[2] = MA_SPI0_read_byte();
	//receivedata[3] = MA_SPI0_read_byte();
	Flash_CE_pin_high;
	
	
	_delay_ms(100);
	
	
	UART_TxChar0(x);
	UART_TxChar0(y);
	UART_TxChar0(z);
	UART_TxChar0(p);
*/