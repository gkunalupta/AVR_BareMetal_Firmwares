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

#define ACK 0x7E

#define MISO PB3
#define MOSI PB2
#define SCK  PB1
#define SS   PB0

#define spi_data_direc DDRB
#define spi_port PORTB
#define spi_pin PINB

#define spi_data_reg SPDR
#define spi_status_reg SPSR
#define spi_control_reg SPCR

#define SET_BIT(byte, bit) (byte |= (1 << bit))
#define CLEAR_BIT(byte,bit) (byte &= ~(1 << bit))
#define IS_SET(byte,bit) ((byte) & (1<<bit))

char data_array[50];
uint8_t data_index;
uint8_t spi_data_recieved;


ISR(SPI_STC_vect)
{
	
	char c = SPDR;
	if ((data_index < sizeof data_array))
	data_array[data_index++] = c;
	else
	data_index = 0;
	//UART_TxChar0(c);
	if(c == '\0')
	spi_data_recieved = 1;
	
}

void spi_init_slave (void)
{
	   spi_data_direc =(1<<MISO);   //MISO as OUTPUT       
       spi_control_reg |= (1<<SPE)|(1<<SPIE);      //Enable SPI
	   data_index = 0;
	   spi_data_recieved = 0;
	   
}

void spi_enable_interrupt()
{
	spi_control_reg |= (1<<SPIE);
}
void spi_disable_interrupt()
{
	spi_control_reg |= ~(1<<SPIE);
}

//Function to send and receive data
uint16_t spi_tranceiver (uint16_t data)
{ 
	
    SPDR = data;  // Load data into the buffer
    while(!(SPSR & (1<<SPIF) ));  //Wait until transmission complete
    return(SPDR);  //Return received data
	
}
void spi_slave_send(uint8_t data)           //-->done
{
	spi_data_direc=(1<<MISO);   //MISO as OUTPUT
	spi_data_reg = data;
	UART_TxChar0(data);
	while(!(SPSR &(1<<SPIF)));
	printString0("g\n");
	spi_port &= ~(1<<SS);
}
uint8_t spi_slave_receive()                  //--> done
{
	while(!(SPSR & (1<<SPIF) ));                  //Wait until transmission complete
	return(SPDR);                                 //Return received data
}
void spi_slave_rxstring0()
{
	uint8_t x=0;
	
	for(int i=0; i<4; i++)
	{
	  x=spi_slave_receive();  // receive data from SPDR and sends it to variable x
	  UART_TxChar0(x);
	  }
  
}

int main(void)
{     
	UART_Init0();
	spi_init_slave();                             //Initialize slave SPI
	//spi_enable_interrupt();
	
	uint16_t data;   
    uint8_t x = 100;
	char ch[5];
    uint16_t tranc = 0;
	uint16_t t = 150;
	sei();



bit0(spi_control_reg);
printString0("\n");
	printString0("SPI-Slave-receiving\n");
	while(1)
	{

//decimel0(spi_data_recieved);
//printString0("\n");
	       if((spi_data_recieved == 1))
	       {
		       printString0("\n");
		       spi_data_recieved = 0;
		       printString0(data_array);
		       data_index = 0;
	       }
	       _delay_us(100);
       }
	   
	   memset(data_array , '\0', 50);
}