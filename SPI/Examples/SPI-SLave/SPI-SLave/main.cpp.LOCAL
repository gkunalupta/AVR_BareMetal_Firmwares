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
char RECV_DATA_SPI0[RECV_BUFFER_SIZE_SPI0];
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
}
	/* reading from interrupt buffer*/
char SL_SPI0_INTRPT_read_byte() 
	{
		char SPI0_recv_char;
		SPI0_recv_char = RECV_BUFFER_SPI0[RECV_Rd_Index_SPI0]; /* get one from the buffer..*/
		if(++RECV_Rd_Index_SPI0 > RECV_BUFFER_SIZE_SPI0) /* wrap the pointer */
		RECV_Rd_Index_SPI0 = 0;
		if(RECV_Counter_SPI0)
		RECV_Counter_SPI0--; /* keep a count (buffer size) */
		return SPI0_recv_char;//return char *
		//printString0("n \n ");
	}
void SL_SPI0_INTRPT_read_string()
	{
// 		printString0(" Number of characters received : ");
// 		decimel0(RECV_No_of_bytes_SPI0);
//		printString0("\n");
		uint8_t x=0;
		memset(RECV_DATA_SPI0, '\0',RECV_BUFFER_SIZE_SPI0);
		while (RECV_Counter_SPI0)
		{
			RECV_DATA_SPI0[x]= SL_SPI0_INTRPT_read_byte();
			x++;
		}
		printString0(RECV_DATA_SPI0);
		//printString0("\n ");
		
	}
void SL_SPI0_INTRPT_read_block(char *buff, uint8_t size)
{
   for(uint8_t i=0;i<size; i++)
   {
	   buff[i] = RECV_BUFFER_SPI0[i];
   }
   printString0(buff);
}
void SL_SPI0_init_slave (void)
{
	   spi_data_direc =(1<<MISO);   //MISO as OUTPUT       
       spi_control_reg |= (1<<SPE);      //Enable SPI

	   
}
void SL_SPI0_enable_interrupt()
{
	spi_control_reg |= (1<<SPIE);
}
void SL_SPI0_disable_interrupt()
{
	spi_control_reg &= ~(1<<SPIE);
}
//Function to send and receive data
uint16_t SL_SPI0_exchange_byte (uint16_t data)
{ 
	
    SPDR = data;  // Load data into the buffer
    while(!(SPSR & (1<<SPIF) ));  //Wait until transmission complete
    return(SPDR);  //Return received data
	
}
/*
For sending single characters or Numbers
E.g: spi_master_send('a');
     spi_master_send('1');
Also to send ascii characters by passing their
decimal and hex values.
E.g: spi_master_send(65) : will send A( Decimal value of ASCII A is 65)
     spi_master_send(0x41): will send A( Hexadecimal value of ASCII A is 41)
	 spi_master_send(0b01000001) : will send A ( binary value of ASCII A is 01000001)
*/
void SL_SPI0_send_byte(uint8_t data)
{
	spi_data_direc=(1<<MISO);   //MISO as OUTPUT
	spi_data_reg = data;
	UART_TxChar0(data);
	while(!(SPSR &(1<<SPIF)));
	spi_port &= ~(1<<SS);
}
/*
For sending Strings 
E.g: spi_send_stringM("subscribe Gettobyte\0");
     spi_send_stringM("12345kunal\0");
	  spi_send_string(buff);
*/
void SL_SPI0_send_string(const char * buff)
{
	char c;
	for (const char * p = buff; c = *p; p++)
	{
		SL_SPI0_send_byte(c);
		//UART_TxChar0(a);
	}
}
/*
for sending integers in decimal format from 0-65535 range
E.g: spi_send_int(12345);
     spi_send_int(9876); 
*/
void SL_SPI0_send_int(uint16_t num)
{
	unsigned char buf[5];
	int8_t ptr;
	
	for(ptr=0;ptr<5;++ptr) 
	{
		buf[ptr] = (num % 10) + '0';
	    num /= 10;
	}
	for(ptr=4;ptr>0;--ptr) 
	if (buf[ptr] != '0') break;
	
	for(;ptr>=0;--ptr) 
	SL_SPI0_send_byte(buf[ptr]);

}
/*
For sending array of integer format.
*/
void SL_SPI0_send_intarray(const uint16_t * buff)
{
	char c;
	for (const uint16_t * p = buff; c = *p; p++)
	{
		SL_SPI0_send_byte(c);
	}
	//SL_SPI0_send_byte('\0');

}
/* receives one byte
E.G: char ch = SL_SPI0_read_byte()
*/
uint8_t SL_SPI0_read_byte()
{
	while(!(SPSR & (1<<SPIF) ));                  //Wait until transmission complete
	return(SPDR);                                 //Return received data
}
/*
Read the incoming data till size bytes
E.G: SL_SPIO_read_block(ch,15);
*/
void SL_SPI0_read_block(char block[], uint8_t size)
{
	memset(block, '\0', size);
	uint8_t i=0;
	volatile uint8_t spi_recv_char=0;
	
	//uint8_t *b = (uint8_t *)block;
	//decimel0(*b);
	
	while ((size--)!= 0) {
	spi_data_reg = 0;
	while (!(SPSR & (1 << SPIF)));
	spi_recv_char = spi_data_reg;
	block[i++] = spi_recv_char;
	//*b = spi_data_reg;
	 //b++;
	 
	 }
}

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
	  
	   _delay_us(100);
//    memset(ch, '\0', 30);
// 	  memset(bh, '\0', 30);
   }
}




//_delay_us(1);
// decimel0(spi_data_recieved);
// printString0("&\n");
// _delay_us(1);


// SPI_0_read_block(bh,12);
// printString0(bh);
// printString0("\n");
// _delay_us(100);
//getstring_UART1();

// spi_read_block(ch,22);
// printString0("\n");
// _delay_us(100);
// spi_read_block(bh,12);
// printString0("\n");
// _delay_us(100);

// 	       if((spi_data_recieved == 1))
// 	       {
// 		       printString0(".\n");
// 		       spi_data_recieved = 0;
// 			   //_delay_us(10);
// 		       printString0(data_array);
// 		       data_index = 0;
// 			  // break;
// 	       }
// 	       _delay_ms(100);
//        
// 	  printString0("#\n");
//    memset(ch, '\0', 50);
// 	}
// }