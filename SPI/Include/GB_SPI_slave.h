#ifndef GB_SPI_SLAVE_H_
#define GB_SPI_SLAVE_H_

#define gb_SPI_MISO PB3
#define gb_SPI_MOSI PB2
#define gb_SPI_SCK  PB1
#define gb_SPI_SS   PB0

#define gb_spi_data_direc DDRB
#define gb_spi_port PORTB
#define gb_spi_pin PINB

#define gb_spi_data_reg SPDR
#define gb_spi_status_reg SPSR
#define gb_spi_control_reg SPCR

#define SET_BIT(byte, bit) (byte |= (1 << bit))
#define CLEAR_BIT(byte,bit) (byte &= ~(1 << bit))
#define IS_SET(byte,bit) ((byte) & (1<<bit))
#define gb_spi_data_direc DDRB
#define gb_spi_port PORTB
#define gb_spi_pin PINB

//for uno
/*
#define MISO PB4
#define MOSI PB3
#define SCK  PB5
#define SS   PB2
*/


//for mega
#define gb_SPI_MISO PB3  //DO :50
#define gb_SPI_MOSI PB2  //DI:51
#define gb_SPI_SCK  PB1  //CSK :52
#define gb_SPI_SS   PB0  //CS:53

#define gb_spi_data_reg SPDR
#define gb_spi_status_reg SPSR
#define gb_spi_control_reg SPCR

#define SET_BIT(byte, bit) (byte |= (1 << bit))
#define CLEAR_BIT(byte,bit) (byte &= ~(1 << bit))
#define IS_SET(byte,bit) ((byte) & (1<<bit))

// Macros for interrupt
#define gb_RECV_BUFFER_SIZE_SPI0 255
uint8_t gb_RECV_BUFFER_SPI0[gb_RECV_BUFFER_SIZE_SPI0]; // character array (buffer)
uint8_t gb_RECV_Wr_Index_SPI0 =0; //index of next char to be put into the buffer  // head
uint8_t gb_RECV_Rd_Index_SPI0=0; //index of next char to be fetched from the buffer    //tail
uint8_t gb_RECV_Counter_SPI0=0; //a total count of characters in the buffer
uint8_t gb_RECV_No_of_bytes_SPI0=0;
bool gb_RECV_Buffer_Overflow_SPI0; // This flag is set on USART Receiver // buffer overflow
char gb_rx_byte;
char gb_RECV_DATA_SPI0[gb_RECV_BUFFER_SIZE_SPI0];

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
void GB_SL_SPI0_send_byte(uint8_t gb_data);
/*
For sending Strings 
E.g: spi_send_stringM("subscribe Gettobyte\0");
     spi_send_stringM("12345kunal\0");
	  spi_send_string(buff);
*/
void GB_SL_SPI0_send_string(const char * gb_buff);
/*
for sending integers in decimal format from 0-65535 range
E.g: spi_send_int(12345);
     spi_send_int(9876); 
*/
void GB_SL_SPI0_send_int(uint16_t gb_num);
/*
For sending array of integer format.
*/
void GB_SL_SPI0_send_intarray(const uint16_t * gb_buff);
/* receives one byte
E.G: char ch = SL_SPI0_read_byte()
*/
uint8_t GB_SL_SPI0_read_byte();
/*
Read the incoming data till size bytes
E.G: SL_SPIO_read_block(ch,15);
*/
void GB_SL_SPI0_read_block(char gb_block[], uint8_t gb_size);

#include "GB_SPI_slave.cpp"

#endif