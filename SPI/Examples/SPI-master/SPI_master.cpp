-ISR(SPI_STC_vect)
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
char MA_SPI0_INTRPT_read_byte()
	{
		char SPI0_recv_char;
		SPI0_recv_char = RECV_BUFFER_SPI0[RECV_Rd_Index_SPI0]; /* get one from the buffer..*/
		if(++RECV_Rd_Index_SPI0 > RECV_BUFFER_SIZE_SPI0) /* wrap the pointer */
		RECV_Rd_Index_SPI0 = 0;
		if(RECV_Counter_SPI0)
		RECV_Counter_SPI0--; /* keep a count (buffer size) */
		return SPI0_recv_char ;//return char *
		//printString0("n \n ");
	}
void MA_SPI0_INTRPT_read_string()
	{
		// 		printString0(" Number of characters received : ");
		// 		decimel0(RECV_No_of_bytes_SPI0);
		//		printString0("\n");
		uint8_t x=0;
		memset(RECV_DATA_SPI0, '\0',RECV_BUFFER_SIZE_SPI0);
		while (RECV_Counter_SPI0)
		{
			RECV_DATA_SPI0[x]= MA_SPI0_INTRPT_read_byte();
			x++;
		}
		printString0(RECV_DATA_SPI0);
		//printString0("\n ");
	}
void MA_SPI0_INTRPT_read_block(char *buff, uint8_t size)
	{
		for(uint8_t i=0;i<size; i++)
		{
			buff[i] = RECV_BUFFER_SPI0[i];
		}
		printString0(buff);
	}
//Initialize SPI Master Device
void MA_SPI0_init_master (void)
{
	spi_data_direc = (1<<MOSI)|(1<<SCK)|(1<<SS);              //Set MOSI, SCK, SS as Output
	spi_control_reg = (1<<SPE)|(1<<MSTR)|(1<<SPR0); //Enable SPI, Set as Master
	                                     //Prescaler: Fosc/16, Enable Interrupts
}
void MA_slave_select_low(uint8_t ss)
{
	spi_port &= ~(1<<ss);
}
void MA_slave_select_high(uint8_t ss)
{
	spi_port |= (1<<ss);
}
void MA_SPI0_enable_interrupt()
{
	spi_control_reg |= (1<<SPIE);
}
void MA_SPI0_disable_interrupt()
{
	spi_control_reg &= ~(1<<SPIE);
}
//Function to send and receive data
uint16_t MA_SPI0_exchange_byte (uint16_t data)
{
	spi_port &= ~(1<<SS);
	SPDR = data;  // Load data into the buffer
	while(!(SPSR & (1<<SPIF) ));  //Wait until transmission complete
	spi_port = (0x01 & (1<<SS));
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
void MA_SPI0_send_byte(uint8_t data)
{
	spi_port &= ~(1<<SS);
	spi_data_reg = data;                       //Load data into the buffer
	while(!(SPSR &(1<<SPIF)));
	spi_port |= (1<<SS);
}
/*
For sending Strings 
E.g: spi_send_stringM("subscribe Gettobyte\0");
     spi_send_stringM("12345kunal\0");
	 spi_send_string(buff);
*/
void MA_SPI0_send_string(const char * buff)
{
	char c;
	for (const char * p = buff; c = *p; p++)
	{
		MA_SPI0_send_byte(c);
		//UART_TxChar0(a);
	}
}
/*
for sending integers in decimal format from 0-65535 range
E.g: spi_send_int(12345);
     spi_send_int(9876); 
*/
void MA_SPI0_send_int(uint16_t num)
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
	MA_SPI0_send_byte(buf[ptr]);
}
/*
For sending array of integer format. 
*/
void MA_SPI0_send_intarray(const uint16_t * buff)
{
	char c;
	for (const uint16_t * p = buff; c = *p; p++)
	{
		MA_SPI0_send_byte(c);
	}
	MA_SPI0_send_byte('\0');

}
/* receives one byte 
E.G: char ch = MA_SPI0_read_byte()
*/
uint8_t MA_SPI0_read_byte()
{    	
	spi_port &= ~(1<<SS);
    uint8_t recv_char=0;
	
	spi_data_reg = NULL;

	while(!(SPSR & (1<<SPIF)));                  //Wait until transmission complete

    return(spi_data_reg);
                               //Return received data
   spi_port |= (1<<SS);
}
/*
Read the incoming data till size bytes
E.G: MA_SPIO_read_block(ch,15);
*/
void MA_SPI0_read_block(char block[], uint8_t size)
{
	memset(block, '\0', size);
	uint8_t i=0;
	volatile uint8_t spi_recv_char=0;
	
	spi_port &= ~(1<<SS);
	_delay_us(1);
	while ((size--)!= 0) {
	spi_data_reg = 0;
	while (!(SPSR & (1 << SPIF)));
	spi_recv_char= spi_data_reg;
	block[i++] = spi_recv_char;
	 }
	 spi_port |= (1<<SS);
}
