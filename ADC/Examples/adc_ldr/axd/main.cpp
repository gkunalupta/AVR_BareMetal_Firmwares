/*
 * axd.cpp
 *
 * Created: 10-07-2020 04:06:52
 * Author : kunal
 */ 

/*
 * GccApplication4.cpp
 *
 * Created: 1/3/2020 1:30:55 PM
 * Author : kunal
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

void UART_Init();
void UART_TxChar(char data);
char UART_RxChar();
void bit(uint8_t val);
void printString( char *myString);

void UART_Init()
{
    UBRR0L = 103;
    UCSR0B = (1<<TXEN0)|(1<<RXEN0);
    UCSR0C = (1<<UCSZ00)|(1<<UCSZ01);
}
void UART_TxChar(char data)
{
    while((UCSR0A & (1<<UDRE0))==0);
    UDR0 = data;
    
}
char UART_RxChar()
{
    while( (UCSR0A & (1<<RXC0))==0);
    return UDR0;
}

void bit(uint8_t val)
{
    uint8_t count = 8;
    while(count--)
    {
        if (val & 0x80)
        {
            UART_TxChar('1');
        }
        else
        {
            UART_TxChar('0');
        }
        val <<=1;
    }
}
  void printString(char *myString)      /////to print any string
  {

      while (*myString)
      {
          UART_TxChar(*myString++);
      }
  }
  
      
  
int main(void)
{   vfprintf ;
	
	uint16_t iDelay;
     DDRD=  0xff;
    char sbuff[100];
    
    UART_Init();
    ADCSRA=0x87;
    ADMUX=0b01000000;
  printString("kunal");
    while (1) 
    { 
        //put the adc code in its own function!!
        ADCSRA |= (1<<ADSC);
        while( ADCSRA & (1<<ADSC) );
    
        bit(ADCH);
        bit(ADCL);
        printString("\n");
		iDelay = ADCL;
		iDelay += (ADCH << 8);
        
        sprintf(sbuff,"%03d\n",ADC);
        printString(sbuff);
        _delay_ms(1000);
		
		if(ADC>500&ADC<600)
		PORTD=(1<<2)|(1<<4);
		if(ADC>800&ADC<900)
		PORTD=(1<<2)|(1<<3);
		if(ADC<800&ADC>700)
PORTD=(1<<3)|(1<<4)|(1<<5);   
	if(ADC>1000)
	PORTD=(1<<5)|(1<<2);
	if(ADC<100)
	PORTD=(1<<4)|(1<<5);
	} 
    return 0;
}
