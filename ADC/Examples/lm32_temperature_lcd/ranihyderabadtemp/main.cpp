/*
 * ranihyderabadtemp.cpp
 *
 * Created: 18-06-2020 02:25:14
 * Author : kunal
 */ 

#include <avr/io.h> //header to enable data flow control over pins
#include <avr/interrupt.h>


#define F_CPU 1000000  //telling controller crystal frequency attached

#include <util/delay.h> //header to enable delay function in program

#define    E   5 //giving name “enable”  to 5th pin of PORTD, since it Is connected to LCD enable pin

#define RS  6 //giving name “registerselection” to 6th pin of PORTD, since is connected to LCD RS pin

void send_a_command(unsigned char command);

void send_a_character(unsigned char character);

void send_a_string(char *string_of_characters);
	
	int16_t COUNTA = 0;//storing digital output
	
	
	char SHOWA [3];//displaying digital output as temperature in 16*2 lcd

ISR (ADC_vect)
{
	 //since the resolution (2.56/2^10 = 0.0025) is 2.5mV there will be an increment of 4 for every 10mV input,
	 // that means for every degree raise there will be increment of 4 in digital value. So to get the temperature
	 // we have to divide ADC output by four.
	 COUNTA = ADC/4;
	 //command for putting variable number in LCD(variable number,
	 //in which character to replace, which base is variable(ten here as we are counting number in base10))
	 itoa(COUNTA,SHOWA,10);

	
	
	
	}

int main(void)

{

	DDRB = 0xFF; //putting portB and portD as output pins
     sei();
	DDRD = 0xFF;

	_delay_ms(50);//giving delay of 50ms




   /*initializing ADC*/
	DDRA = 0;//Taking portA as input.
   //Set ADLAR bit to 1 for left shifting the ADC value so that 10 bit value can be divided by 4.
   //choose bit vale of REFS0 and REFS1 for setting reference voltage 
	ADMUX |=(1<<REFS0)|(1<<REFS1)|(1<<ADLAR);//setting the reference of ADC
    // Set ADEN to enable the ADC
	//Choose bit value of ADPS0,ADPS1,ADPS2 according to the prescaler 
	// set ADATE for auto trigger
	//set ADIE for interrupt
	ADCSRA |=(1<<ADEN)|(1<<ADATE)|(1<<ADIE)|(1<<ADPS0)|(1<<ADPS1)|(1<<ADPS2);  
	//Clear ADTS2..0 in ADCSRB to set trigger mode to free running.
	// This means that as soon as an ADC has finished, the next will be
	// immediately started.
	ADCSRB |=(0<<ADTS2)|(0<<ADTS1)|(0<<ADTS0);
	

    /*initializing LCD display*/
	send_a_command(0x01); //Clear Screen 0x01 = 00000001

	_delay_ms(50);

	send_a_command(0x38);//telling lcd we are using 8bit command /data mode

	_delay_ms(50);

	send_a_command(0b00001111);//LCD SCREEN ON and courser blinking

	

	while(1)

	{   uint8_t chan;

		send_a_string ("CIRCUIT DIGEST ");//displaying name

		send_a_command(0x80 + 0x40 + 0); // shifting cursor  to 1st  shell  of second line

		send_a_string ("Temp(C)=");// displaying name

		send_a_command(0x80 + 0x40 + 8); // shifting cursor  to 9st  shell  of second line
		
		
		/* Reading ADC vale...*/
		//select channel (MUX0-4 bits)
		ADMUX = (ADMUX & 0xE0) | (chan);   
	    //select channel (MUX5 bit)
		ADCSRB = (ADCSRB & 0xDF) | (chan);
		//starting ADC conversion
		ADCSRA |=(1<<ADSC);      
		//( after this it will go to interrupt service routine if enabled)
		
		
		/*   
		******************** if not using interrupt then uncomment this block****************************
		// Wait until end of conversion by polling ADC interrupt flag 
	    while ((ADCSRA & (1<<ADSC)));     
		           
	    //since the resolution (2.56/2^10 = 0.0025) is 2.5mV there will be an increment of 4 for every 10mV input,
	    // that means for every degree raise there will be increment of 4 in digital value. So to get the temperature
	    // we have to divide ADC output by four.
	    COUNTA = ADC/4;
        //command for putting variable number in LCD(variable number, 
		//in which character to replace, which base is variable(ten here as we are counting number in base10))
        itoa(COUNTA,SHOWA,10);

         */


		send_a_string(SHOWA); //telling the display to show character(replaced by variable number) of first person after positioning the courser on LCD

		send_a_string ("      ");

		send_a_command(0x80 + 0);//retuning to first line first shell

		if(SHOWA>14)
		{
			PD2=1;
			PD3=1;
		}
		if( SHOWA<40)
		{
			PD2=1;
			PD4=1;
		}
		else
		{
			PD2=0;
			PD3=0;
			PD4=0;
		}

	}

}

void send_a_command(unsigned char command)

{

	PORTA = command;

	PORTD &= ~ (1<<RS); //putting 0 in RS to tell lcd we are sending command

	PORTD |= 1<<E; //telling lcd to receive command /data at the port

	_delay_ms(50);

	PORTD &= ~1<<E;//telling lcd we completed sending data

	PORTA= 0;

}

void send_a_character(unsigned char character)

{

	PORTA= character;

	PORTD |= 1<<RS;//telling LCD we are sending data not commands

	PORTD |= 1<<E;//telling LCD to start receiving command/data

	_delay_ms(50);

	PORTD &= ~1<<E;//telling lcd we completed sending data/command

	PORTA = 0;

}

void send_a_string(char *string_of_characters)

{

	while(*string_of_characters > 0)

	{

		send_a_character(*string_of_characters++);

	}

}
