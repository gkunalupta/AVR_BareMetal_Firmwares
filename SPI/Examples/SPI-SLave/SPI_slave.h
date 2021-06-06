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

//interrupt functions
/* reading from interrupt buffer*/
char SL_SPI0_INTRPT_read_byte();
void SL_SPI0_INTRPT_read_string();
void SL_SPI0_INTRPT_read_block(char *buff, uint8_t size);
void SL_SPI0_init_slave (void);
void SL_SPI0_enable_interrupt();
void SL_SPI0_disable_interrupt();
uint16_t SL_SPI0_exchange_byte (uint16_t data);
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
void SL_SPI0_send_byte(uint8_t data);
/*
For sending Strings 
E.g: spi_send_stringM("subscribe Gettobyte\0");
     spi_send_stringM("12345kunal\0");
	  spi_send_string(buff);
*/
void SL_SPI0_send_string(const char * buff);
/*
for sending integers in decimal format from 0-65535 range
E.g: spi_send_int(12345);
     spi_send_int(9876); 
*/
void SL_SPI0_send_int(uint16_t num);
/*
For sending array of integer format.
*/
void SL_SPI0_send_intarray(const uint16_t * buff);
/* receives one byte
E.G: char ch = SL_SPI0_read_byte()
*/
uint8_t SL_SPI0_read_byte();
/*
Read the incoming data till size bytes
E.G: SL_SPIO_read_block(ch,15);
*/
void SL_SPI0_read_block(char block[], uint8_t size);

#include "SPI_slave.cpp"