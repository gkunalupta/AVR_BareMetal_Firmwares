void GB_UART_Init0()
{
	//103 fpr 9600
	//8 for 115200
	uart0_baudrate = 103;
	uart0_ucsrB = (1<<TXEN0)|(1<<RXEN0)|(1<<RXCIE0); //00001000, 00010000
}
void GB_UART_TxChar0(uint16_t gb_data)
{
	while((uart0_ucsrA & (1<<UDRE0))==0); //00100000
	uart0_UDR = gb_data;
	
}
char GB_UART_RxChar0()
{
	while(!(uart0_ucsrA & (1<<RXC0)));  // 1000000
	return uart0_UDR;
}
void GB_rxstring0(char *gb_buff)
{
	int gb_i=0;
	char gb_myValue;
	do
	{

		gb_myValue = GB_UART_RxChar0();
		if(gb_myValue!='\n')
		{
			gb_buff[gb_i]=gb_myValue;
			gb_i++;
		}    else
		{
			gb_buff[gb_i]='\0';
			break;
		}

	}
	while( !(uart0_ucsrA & (1<<RXC0)));
	}
void GB_printString0(const char *gb_myString)      /////to print any string
{

	
	while (*gb_myString)
	{
		GB_UART_TxChar0(*gb_myString++);
	}
}
/*
Remember the passed inetger should have
'\n' as its last element
*/
void GB_printint0( uint8_t gb_num [])
{
	int gb_i=0;
	for(gb_i=0;gb_num[gb_i]!='\n'; gb_i++)
	{
		GB_UART_TxChar0(gb_num[gb_i]);
	}
}
void GB_bit0(uint32_t gb_val)
{
	int8_t gb_ptr;
	for(gb_ptr=7;gb_ptr>=0;gb_ptr--)
	{
		if ((gb_val & (1<<gb_ptr))==0)
		{
			GB_UART_TxChar0('0');
		}
		else
		{
			GB_UART_TxChar0('1');
		}
	}
}
void GB_decimel0(uint32_t gb_val)
{
	unsigned char gb_buf[5];
	int8_t gb_ptr;
	for(gb_ptr=0;gb_ptr<5;++gb_ptr) {
		gb_buf[gb_ptr] = (gb_val % 10) + '0';
		gb_val /= 10;
	}
	for(gb_ptr=4;gb_ptr>0;--gb_ptr) {
		if (gb_buf[gb_ptr] != '0') break;
	}
	for(;gb_ptr>=0;--gb_ptr) {
		GB_UART_TxChar0(gb_buf[gb_ptr]);
	}
}
void GB_float_value0(float gb_value)
{
	char gb_float_buff[10];
	sprintf(gb_float_buff,"%f",gb_value);
	GB_printString0(gb_float_buff);
	
}



void GB_UART_Init1()  // baudrate =115200
{
	//103 for 9600
	//8 for 115200
	
	uart1_baudrate = 8;
	uart1_ucsrB = (1<<TXEN1)|(1<<RXEN1)|(1<<RXCIE1); //00001000, 00010000
    
	
}
void GB_UART_TxChar1(uint8_t gb_data)
{
	while((uart1_ucsrA & (1<<UDRE1))==0); //00100000
	uart1_UDR = gb_data;
	
}
char GB_UART_RxChar1()
{
	while(!(uart1_ucsrA & (1<<RXC1)));  // 1000000
	return uart1_UDR;
}
void GB_rxstring1(char *gb_buff)
{
	int gb_i=0;
	char gb_myValue;
	do
	{

		gb_myValue = GB_UART_RxChar1();
		if(gb_myValue!='\n')
		{
			gb_buff[gb_i]=gb_myValue;
			gb_i++;
		}    else
		{
			gb_buff[gb_i]='\0';
			break;
		}

	}
	while( !(uart1_ucsrA & (1<<RXC1)));
}
void GB_printString1(const char *gb_myString)      /////to print any string
{

	
	while (*gb_myString)
	{
		GB_UART_TxChar1(*gb_myString++);
	}
}
/*
Remember the passed inetger should have
'\n' as its last element
*/
void GB_printint1( uint8_t gb_num [])
{
	int gb_i=0;
	for(gb_i=0;gb_num[gb_i]!='\n'; gb_i++)
	{
		GB_UART_TxChar1(gb_num[gb_i]);
	}
}
void GB_bit1(uint32_t gb_val)
{
	int8_t gb_ptr;
	for(gb_ptr=7;gb_ptr>=0;gb_ptr--)
	{
		if ((gb_val & (1<<gb_ptr))==0)
		{
			GB_UART_TxChar1('0');
		}
		else
		{
			GB_UART_TxChar1('1');
		}
	}
}
void GB_decimel1(uint32_t gb_val)
{
	unsigned char gb_buf[5];
	int8_t gb_ptr;
	for(gb_ptr=0;gb_ptr<5;++gb_ptr) {
		gb_buf[gb_ptr] = (gb_val % 10) + '0';
		gb_val /= 10;
	}
	for(gb_ptr=4;gb_ptr>0;--gb_ptr) {
		if (gb_buf[gb_ptr] != '0') break;
	}
	for(;gb_ptr>=0;--gb_ptr) {
		GB_UART_TxChar1(gb_buf[gb_ptr]);
	}
}
void GB_float_value1(float gb_value)
{
	char gb_float_buff[10];
	sprintf(gb_float_buff,"%f",gb_value);
	GB_printString1(gb_float_buff);
	
}


void GB_UART_Init2()  // baudrate =115200
{
	//103 fpr 9600
	//8 for 115200
	uart2_baudrate = 103;
	uart2_ucsrB = (1<<TXEN2)|(1<<RXEN2); //00001000, 00010000
}
void GB_UART_TxChar2(uint8_t gb_data)
{
	while((uart2_ucsrA & (1<<UDRE2))==0); //00100000
	uart2_UDR = gb_data;
	
}
char GB_UART_RxChar2()
{
	while(!(uart2_ucsrA & (1<<RXC2)));  // 1000000
	return uart2_UDR;
}
void GB_rxstring2(char *gb_buff)
{
	int gb_i=0;
	char gb_myValue;
	do
	{

		gb_myValue = GB_UART_RxChar2();
		if(gb_myValue!='\n')
		{
			gb_buff[gb_i]=gb_myValue;
			gb_i++;
		}    else
		{
			gb_buff[gb_i]='\0';
			break;
		}

	}
	while( !(uart2_ucsrA & (1<<RXC2)));
}
void GB_printString2(const char *gb_myString)      /////to print any string
{

	
	while (*gb_myString)
	{
		GB_UART_TxChar1(*gb_myString++);
	}
}
/*
Remember the passed inetger should have
'\n' as its last element
*/
void GB_printint2( uint8_t gb_num [])
{
	int gb_i=0;
	for(gb_i=0;gb_num[gb_i]!='\n'; gb_i++)
	{
		GB_UART_TxChar2(gb_num[gb_i]);
	}
}
void GB_bit2(uint32_t gb_val)
{
	int8_t gb_ptr;
	for(gb_ptr=7;gb_ptr>=0;gb_ptr--)
	{
		if ((gb_val & (1<<gb_ptr))==0)
		{
			GB_UART_TxChar2('0');
		}
		else
		{
			GB_UART_TxChar2('1');
		}
	}
}
void GB_decimel2(uint32_t gb_val)
{
	unsigned char gb_buf[5];
	int8_t gb_ptr;
	for(gb_ptr=0;gb_ptr<5;++gb_ptr) {
		gb_buf[gb_ptr] = (gb_val % 10) + '0';
		gb_val /= 10;
	}
	for(gb_ptr=4;gb_ptr>0;--gb_ptr) {
		if (gb_buf[gb_ptr] != '0') break;
	}
	for(;gb_ptr>=0;--gb_ptr) {
		GB_UART_TxChar2(gb_buf[gb_ptr]);
	}
}
void GB_float_value2(float gb_value)
{
	char gb_float_buff[10];
	sprintf(gb_float_buff,"%f",gb_value);
	GB_printString2(gb_float_buff);
	
}


void GB_UART_Init3()
{
	//103 fpr 9600
	//8 for 115200
	uart3_baudrate = 103;
	uart3_ucsrB = (1<<TXEN3)|(1<<RXEN3); //00001000, 00010000
}
void GB_UART_TxChar3(char  gb_data)
{
	while((uart3_ucsrA & (1<<UDRE3))==0); //00100000
	uart3_UDR = gb_data;
	
}
char GB_UART_RxChar3()
{
	while(!(uart3_ucsrA & (1<<RXC3)));
	return uart3_UDR;
	
	
}
void GB_rxstring3(char *gb_buff)
{
	int gb_i=0;
	char gb_myValue;
	//do
	
	while( !(uart3_ucsrA  & (1<<RXC3)));
	{
		
		gb_myValue = uart3_UDR;
		if(gb_myValue!='\n')
		{
			
			gb_buff[gb_i]=gb_myValue;
			
			gb_i++;
		}    else
		{
			
			gb_buff[gb_i]=' ';
			
		}
		
	}
	
}

void GB_printString3(const char *gb_myString)      /////to print any string
{

	
	while (*gb_myString)
	{
		GB_UART_TxChar3(*gb_myString++);
	}
}
/*
Remember the passed inetger should have
'\n' as its last element
*/
void GB_printint3( uint8_t gb_num [])
{
	int gb_i=0;
	for(gb_i=0;gb_num[gb_i]!='\n'; gb_i++)
	{
		GB_UART_TxChar3(gb_num[gb_i]);
	}
}
void GB_bit3(uint32_t gb_val)
{
	int8_t gb_ptr;
	for(gb_ptr=7;gb_ptr>=0;gb_ptr--)
	{
		if ((gb_val & (1<<gb_ptr))==0)
		{
			GB_UART_TxChar3('0');
		}
		else
		{
			GB_UART_TxChar3('1');
		}
	}
}
void GB_decimel3(uint32_t gb_val)
{
	unsigned char gb_buf[5];
	int8_t gb_ptr;
	for(gb_ptr=0;gb_ptr<5;++gb_ptr) {
		gb_buf[gb_ptr] = (gb_val % 10) + '0';
		gb_val /= 10;
	}
	for(gb_ptr=4;gb_ptr>0;--gb_ptr) {
		if (gb_buf[gb_ptr] != '0') break;
	}
	for(;gb_ptr>=0;--gb_ptr) {
		GB_UART_TxChar3(gb_buf[gb_ptr]);
	}
}
void GB_float_value3(float gb_value)
{
	char gb_float_buff[10];
	sprintf(gb_float_buff,"%f",gb_value);
	GB_printString3(gb_float_buff);
	
}
