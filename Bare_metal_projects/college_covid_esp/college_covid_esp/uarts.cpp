void UART_Init0()
{
	//103 fpr 9600
	//8 for 115200
	uart0_baudrate = 103;
	uart0_ucsrB = (1<<TXEN0)|(1<<RXEN0)|(1<<RXCIE0); //00001000, 00010000
}
void UART_TxChar0(uint16_t data)
{
	while((uart0_ucsrA & (1<<UDRE0))==0); //00100000
	uart0_UDR = data;
	
}
char UART_RxChar0()
{
	while(!(uart0_ucsrA & (1<<RXC0)));  // 1000000
	return uart0_UDR;
}

void rxstring0(char *buff)
{
	int i=0;
	char myValue;
	do
	{

		myValue = UART_RxChar0();
		if(myValue!='\n')
		{
			buff[i]=myValue;
			i++;
		}    else
		{
			buff[i]='\0';
			break;
		}

	}
	while( !(uart0_ucsrA & (1<<RXC0)));
}

void printString0(const char *myString)      /////to print any string
{

	
	while (*myString)
	{
		UART_TxChar0(*myString++);
	}
}
/*
Remember the passed inetger should have
'\n' as its last element
*/
void printint0( uint8_t num [])
{
	int i=0;
	for(i=0;num[i]!='\n'; i++)
	{
		UART_TxChar0(num[i]);
	}
}
void bit0(uint32_t val)
{
	int8_t ptr;
	for(ptr=7;ptr>=0;ptr--)
	{
		if ((val & (1<<ptr))==0)
		{
			UART_TxChar0('0');
		}
		else
		{
			UART_TxChar0('1');
		}
	}
}
void decimel0(uint32_t val)
{
	unsigned char buf[5];
	int8_t ptr;
	for(ptr=0;ptr<5;++ptr) {
		buf[ptr] = (val % 10) + '0';
		val /= 10;
	}
	for(ptr=4;ptr>0;--ptr) {
		if (buf[ptr] != '0') break;
	}
	for(;ptr>=0;--ptr) {
		UART_TxChar0(buf[ptr]);
	}
}
void float_value0(float value)
{
	char float_buff[10];
	sprintf(float_buff,"%f",value);
	printString0(float_buff);
	
}





void UART_Init1()  // baudrate =115200
{
	//103 for 9600
	//8 for 115200
	
	uart1_baudrate = 8;
	uart1_ucsrB = (1<<TXEN1)|(1<<RXEN1)|(1<<RXCIE1); //00001000, 00010000
    
	
}
void UART_TxChar1(uint8_t data)
{
	while((uart1_ucsrA & (1<<UDRE1))==0); //00100000
	uart1_UDR = data;
	
}
char UART_RxChar1()
{
	while(!(uart1_ucsrA & (1<<RXC1)));  // 1000000
	return uart1_UDR;
}
void rxstring1(char *buff)
{
	int i=0;
	char myValue;
	do
	{

		myValue = UART_RxChar1();
		if(myValue!='\n')
		{
			buff[i]=myValue;
			i++;
		}    else
		{
			buff[i]='\0';
			break;
		}

	}
	while( !(uart1_ucsrA & (1<<RXC1)));
}
void printString1(const char *myString)      /////to print any string
{

	
	while (*myString)
	{
		UART_TxChar1(*myString++);
	}
}
void bit1(uint16_t val)
{
	int8_t ptr;
	for(ptr=7;ptr>=0;ptr--)
	{
		if ((val & (1<<ptr))==0)
		{
			UART_TxChar1('0');
		}
		else
		{
			UART_TxChar1('1');
		}
	}
}
void decimel1(uint16_t val) {
	unsigned char buf[5];
	int8_t ptr;
	for(ptr=0;ptr<5;++ptr) {
		buf[ptr] = (val % 10) + '0';
		val /= 10;
	}
	for(ptr=4;ptr>0;--ptr) {
		if (buf[ptr] != '0') break;
	}
	for(;ptr>=0;--ptr) {
		UART_TxChar1(buf[ptr]);
	}
}



void UART_Init2()  // baudrate =115200
{
	//103 fpr 9600
	//8 for 115200
	uart2_baudrate = 103;
	uart2_ucsrB = (1<<TXEN2)|(1<<RXEN2); //00001000, 00010000
}
void UART_TxChar2(uint8_t data)
{
	while((uart2_ucsrA & (1<<UDRE2))==0); //00100000
	uart2_UDR = data;
	
}
char UART_RxChar2()
{
	while(!(uart2_ucsrA & (1<<RXC2)));  // 1000000
	return uart2_UDR;
}
void rxstring2(char *buff)
{
	int i=0;
	char myValue;
	do
	{

		myValue = UART_RxChar2();
		if(myValue!='\n')
		{
			buff[i]=myValue;
			i++;
		}    else
		{
			buff[i]='\0';
			break;
		}

	}
	while( !(uart2_ucsrA & (1<<RXC2)));
}
void printString2(  const char myString[] )
{
	char i = 0;
	while (myString[i])
	{
		UART_TxChar2(myString[i]);
		i++;
		
	}
}
void bit2(uint16_t val)
{
	int8_t ptr;
	for(ptr=7;ptr>=0;ptr--)
	{
		if ((val & (1<<ptr))==0)
		{
			UART_TxChar2('0');
		}
		else
		{
			UART_TxChar2('1');
		}
	}
}
void decimel2(uint16_t val) {
	unsigned char buf[5];
	int8_t ptr;
	for(ptr=0;ptr<5;++ptr) {
		buf[ptr] = (val % 10) + '0';
		val /= 10;
	}
	for(ptr=4;ptr>0;--ptr) {
		if (buf[ptr] != '0') break;
	}
	for(;ptr>=0;--ptr) {
		UART_TxChar2(buf[ptr]);
	}
}




void UART_Init3()
{
	//103 fpr 9600
	//8 for 115200
	uart3_baudrate = 103;
	uart3_ucsrB = (1<<TXEN3)|(1<<RXEN3); //00001000, 00010000
}
void UART_TxChar3(char  data)
{
	while((uart3_ucsrA & (1<<UDRE3))==0); //00100000
	uart3_UDR = data;
	
}
char UART_RxChar3()
{
	while(!(uart3_ucsrA & (1<<RXC3)));
	return uart3_UDR;
	
	
}
void rxstring3(char *buff)
{
	int i=0;
	char myValue;
	//do
	
	while( !(uart3_ucsrA  & (1<<RXC3)));
	{
		
		myValue = uart3_UDR;
		if(myValue!='\n')
		{
			
			buff[i]=myValue;
			
			i++;
		}    else
		{
			
			buff[i]=' ';
			
		}
		
	}
	
}

void printString3(char *myString)      /////to print any string
{

	while (*myString)
	{
		UART_TxChar3(*myString++);
	}
}
void bit3(uint16_t val)
{
	
	int8_t ptr;
	for(ptr=7;ptr>=0;ptr--)
	{
		if ((val & (1<<ptr))==0)
		{
			UART_TxChar3('0');
		}
		else
		{
			UART_TxChar3('1');
		}
	}
}
void decimel3(uint16_t val)
{
	unsigned char buf[5];
	int8_t ptr;
	for(ptr=0;ptr<5;++ptr) {
		buf[ptr] = (val % 10) + '0';
		val /= 10;
	}
	for(ptr=4;ptr>0;--ptr) {
		if (buf[ptr] != '0') break;
	}
	for(;ptr>=0;--ptr) {
		UART_TxChar3(buf[ptr]);
	}
}