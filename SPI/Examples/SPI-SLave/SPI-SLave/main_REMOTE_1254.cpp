*
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

#define RECV_BUFFER_SIZE_SPI0 255
uint8_t RECV_BUFFER_SPI0[RECV_BUFFER_SIZE_SPI0]; // character array (buffer)
uint8_t RECV_Wr_Index_SPI0 =0; //index of next char to be put into the buffer  // head
uint8_t RECV_Rd_Index_SPI0=0; //index of next char to be fetched from the buffer    //tail
uint8_t RECV_Counter_SPI0=0; //a total count of characters in the buffer
uint8_t RECV_No_of_bytes_SPI0=0;
bool RECV_Buffer_Overflow_SPI0; // This flag is set on USART Receiver // buffer overflow
char rx_byte;
ISR(SPI_STC_vect)
{
	
	rx_byte = spi_data_reg;
	RECV_BUFFER_SPI0[RECV_Wr_Index_SPI0]= rx_byte;   /* put received char in buffer */
	if(++RECV_Wr_Index_SPI0 > RECV_BUFFER_SIZE_SPI0)
	RECV_Wr_Index_SPI0 = 0;
	if(++RECV_Counter_SPI0 > RECV_BUFFER_SIZE_SPI0) /* keep a character count */
	{
		/* overflow check.. */
		RECV_Counter_SPI0 = RECV_BUFFER_SIZE_SPI0; /* if too many chars came */
		RECV_Buffer_Overflow_SPI0 = 1;            /* in before they could be used */
		}                                          /* that could cause an error!! */
		RECV_No_of_bytes_SPI0=RECV_Counter_SPI0 ;
		//UART_TxChar0(rx_byte);
		
	}
	/* reading from interrupt buffer*/
	char  getchar_UART1()             // <--->   Serial.read()
	{
		
		
		char c;

		c = RECV_BUFFER_SPI0[RECV_Rd_Index_SPI0]; /* get one from the buffer..*/
		
		if(++RECV_Rd_Index_SPI0 > RECV_BUFFER_SIZE_SPI0) /* wrap the pointer */
		RECV_Rd_Index_SPI0 = 0;
		if(RECV_Counter_SPI0)
		RECV_Counter_SPI0--; /* keep a count (buffer size) */
		return c ;//return char *
		//printString0("n \n ");
	}

	char RECV_DATA_SPI0[RECV_BUFFER_SIZE_SPI0];
	void getstring_UART1()
	{
		uint8_t x=0;
		memset(RECV_DATA_SPI0, '\0',RECV_BUFFER_SIZE_SPI0);
		while (RECV_Counter_SPI0)
		{
			RECV_DATA_SPI0[x]= getchar_UART1();
			x++;
		}
		printString0(RECV_DATA_SPI0);
		//printString0("\n ");
		
	}

void spi_read_block(char *buff, uint8_t size)
{
   for(uint8_t i=0;i<size; i++)
   {
	   buff[i] = RECV_BUFFER_SPI0[i];
   }
   printString0(buff);
}
void spi_init_slave (void)
{
	   spi_data_direc =(1<<MISO);   //MISO as OUTPUT       
       spi_control_reg |= (1<<SPE);      //Enable SPI

	   
}
void spi_enable_interrupt()
{
	spi_control_reg |= (1<<SPIE);
}
void spi_disable_interrupt()
{
	spi_control_reg &= ~(1<<SPIE);
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

// Directly read this function//
void SPI_0_read_block(char block[], uint8_t size)
{
	memset(block, '\0', size);
	uint8_t *b = (uint8_t *)block;
	while ((size--)!= 0) {
	spi_data_reg = 0;
	while (!(SPSR & (1 << SPIF)));
	*b = spi_data_reg;
	b++;
	 }

}

int main(void)
{     
	UART_Init0();
	spi_init_slave();                             //Initialize slave SPI
	spi_disable_interrupt();
	char ch[30],bh[30];
	memset(ch, '\0', 50);
	sei();
	printString0("SPI-Slave-receiving\n");
	while(1)
	{
		_delay_us(100);
      SPI_0_read_block(ch,15);
      printString0(ch);
      printString0("\n");
      _delay_us(100);
      memset(ch, '\0', 50);
   }
}
