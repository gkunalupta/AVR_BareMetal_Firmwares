ISR(SPI_STC_vect)
{
	
	gb_rx_byte = gb_spi_data_reg;
	gb_RECV_BUFFER_SPI0[gb_RECV_Wr_Index_SPI0]= gb_rx_byte;   /* put received char in buffer */
	if(++gb_RECV_Wr_Index_SPI0 > gb_RECV_BUFFER_SIZE_SPI0)
	gb_RECV_Wr_Index_SPI0 = 0;
	if(++gb_RECV_Counter_SPI0 > gb_RECV_BUFFER_SIZE_SPI0) /* keep a character count */
	{
		/* overflow check.. */
		gb_RECV_Counter_SPI0 = gb_RECV_BUFFER_SIZE_SPI0; /* if too many chars came */
		gb_RECV_Buffer_Overflow_SPI0 = 1;            /* in before they could be used */
		}                                          /* that could cause an error!! */
		gb_RECV_No_of_bytes_SPI0=gb_RECV_Counter_SPI0 ;
	}
	/* reading from interrupt buffer*/
	char GB_SL_SPI0_INTRPT_read_byte()
	{
		char gb_SPI0_recv_char;
		gb_SPI0_recv_char = gb_RECV_BUFFER_SPI0[gb_RECV_Rd_Index_SPI0]; /* get one from the buffer..*/
		if(++gb_RECV_Rd_Index_SPI0 > gb_RECV_BUFFER_SIZE_SPI0) /* wrap the pointer */
		gb_RECV_Rd_Index_SPI0 = 0;
		if(gb_RECV_Counter_SPI0)
		gb_RECV_Counter_SPI0--; /* keep a count (buffer size) */
		return gb_SPI0_recv_char ;//return char *
		//printString0("n \n ");
	}
	void GB_SL_SPI0_INTRPT_read_string()
	{
		// 		printString0(" Number of characters received : ");
		// 		decimel0(RECV_No_of_bytes_SPI0);
		//		printString0("\n");
		uint8_t gb_x=0;
		memset(gb_RECV_DATA_SPI0, '\0',gb_RECV_BUFFER_SIZE_SPI0);
		while (gb_RECV_Counter_SPI0)
		{
			gb_RECV_DATA_SPI0[gb_x]= GB_SL_SPI0_INTRPT_read_byte();
			gb_x++;
		}
		GB_printString0(gb_RECV_DATA_SPI0);
		//printString0("\n ");
	}
	void GB_SL_SPI0_INTRPT_read_block(char *gb_buff, uint8_t gb_size)
	{
		for(uint8_t gb_i=0;gb_i<gb_size; gb_i++)
		{
			gb_buff[gb_i] = gb_RECV_BUFFER_SPI0[gb_i];
		}
		GB_printString0(gb_buff);
	}
void GB_SL_SPI0_init_slave (void)
{
	   gb_spi_data_direc =(1<<gb_SPI_MISO);   //MISO as OUTPUT       
       gb_spi_control_reg |= (1<<SPE);      //Enable SPI

gb_spi_control_reg |= (1<<CPOL) | (1<<CPHA);
	   
}
void GB_SL_SPI0_enable_interrupt()
{
	gb_spi_control_reg |= (1<<SPIE);
}
void GB_SL_SPI0_disable_interrupt()
{
	gb_spi_control_reg &= ~(1<<SPIE);
}
//Function to send and receive data
uint16_t GB_SL_SPI0_exchange_byte (uint16_t gb_data)
{ 
	
    SPDR = gb_data;  // Load data into the buffer
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
void GB_SL_SPI0_send_byte(uint8_t gb_data)
{
	gb_spi_data_direc=(1<<gb_SPI_MISO);   //MISO as OUTPUT
	gb_spi_data_reg = gb_data;
	while(!(SPSR &(1<<SPIF)));

}
/*
For sending Strings 
E.g: spi_send_stringM("subscribe Gettobyte\0");
     spi_send_stringM("12345kunal\0");
	  spi_send_string(buff);
*/
void GB_SL_SPI0_send_string(const char * gb_buff)
{
	char gb_c;
	for (const char * gb_p = gb_buff; gb_c = *gb_p; gb_p++)
	{
		GB_SL_SPI0_send_byte(gb_c);
		//UART_TxChar0(a);
	}
}
/*
for sending integers in decimal format from 0-65535 range
E.g: spi_send_int(12345);
     spi_send_int(9876); 
*/
void GB_SL_SPI0_send_int(uint16_t gb_num)
{
	unsigned char gb_buf[5];
	int8_t gb_ptr;
	
	for(gb_ptr=0;gb_ptr<5;++gb_ptr) 
	{
		gb_buf[gb_ptr] = (gb_num % 10) + '0';
	    gb_num /= 10;
	}
	for(gb_ptr=4;gb_ptr>0;--gb_ptr) 
	if (gb_buf[gb_ptr] != '0') break;
	
	for(;gb_ptr>=0;--gb_ptr) 
	GB_SL_SPI0_send_byte(gb_buf[gb_ptr]);
}
/*
For sending array of integer format.
*/
void GB_SL_SPI0_send_intarray(const uint16_t * gb_buff)
{
	char gb_c;
	for (const uint16_t * gb_p = gb_buff; gb_c = *gb_p; gb_p++)
	{
		GB_SL_SPI0_send_byte(gb_c);
	}
	//SL_SPI0_send_byte('\0');

}
/* receives one byte
E.G: char ch = SL_SPI0_read_byte()
*/
uint8_t GB_SL_SPI0_read_byte()
{
	while(!(SPSR & (1<<SPIF) ));                  //Wait until transmission complete
	return(SPDR);                                 //Return received data
}
/*
Read the incoming data till size bytes
E.G: SL_SPIO_read_block(ch,15);
*/
void GB_SL_SPI0_read_block(char gb_block[], uint8_t gb_size)
{
	memset(gb_block, '\0', gb_size);
	uint8_t gb_i=0;
	volatile uint8_t gb_spi_recv_char=0;

	while ((gb_size--)!= 0) {
	gb_spi_data_reg = 0;
	while (!(SPSR & (1 << SPIF)));
	gb_spi_recv_char = gb_spi_data_reg;
	gb_block[gb_i++] = gb_spi_recv_char;

	 }
}