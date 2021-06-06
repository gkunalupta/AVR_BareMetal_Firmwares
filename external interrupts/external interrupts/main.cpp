/*
 * external interrupts.cpp
 *
 * Created: 3/14/2020 10:37:49 AM
 * Author : kunal
 */ 

#include<avr/io.h>
#include <avr/interrupt.h>
#include<util/delay.h>
#include "uarts.h"

volatile int cnt_zero,cnt_one;
volatile unsigned long timer[6];
volatile byte last_channel[5]={0,0,0,0,0};
volatile int input[5]={1500,1500,1500,1500,1500};



ISR(INT0_vect)
{
	printString0("signal occured in pin21\n");
	
}
ISR(INT1_vect)
{
	printString0("signal occured in pin20\n");
	
}

ISR(INT2_vect)
{
	printString0("signal occured in pin19\n");
	
}
ISR(INT3_vect)
{
	printString0("signal occured in pin18\n");
	
}



ISR (PCINT1_vect)          //External interrupt_zero ISR
{
	cnt_zero++;
}

unsigned long timer[4];
byte last_channel[4];
int input[4];

ISR(PCINT0_vect)
{
	timer[0]=micros();
	//channel 1 ----
	
	if(last_channel[0]==0&& PINB & 00000001) //makes sure that the first pin was initially low and is now high
	{                                         //PINB & B00000001 is equivalent to digitalRead but faster
		last_channel[0]=1;
		timer[1]=timer[0];
	}
	else if(last_channel[0]==1 && !(PINB & 00000001))
	{
		last_channel[0]=0;
		input[0]=timer[0]-timer[1];
	}

	//channel 2---
	if(last_channel[1]==0 && PINB & 00000010) //makes sure that the first pin was initially low and is now high
	{                                         //PINB & B00000001 is equivalent to digitalRead but faster
		last_channel[1]=1;
		timer[2]=timer[0];
	}
	else if(last_channel[1]==1 && !(PINB & 00000010))
	{
		last_channel[1]=0;
		input[1]=timer[0]-timer[2];
	}
	
	//channel 3--
	if(last_channel[2]==0&& PINB & 00000100) //makes sure that the first pin was initially low and is now high
	{                                         //PINB & B00000001 is equivalent to digitalRead but faster
		last_channel[2]=1;
		timer[3]=timer[0];
	}
	else if(last_channel[2]==1 && !(PINB & 00000100))
	{
		last_channel[2]=0;
		input[2]=timer[0]-timer[3];
	}
	//channel 4--
	if(last_channel[3]==0&& PINB & 00001000) //makes sure that the first pin was initially low and is now high
	{                                         //PINB & B00000001 is equivalent to digitalRead but faster
		last_channel[3]=1;
		timer[4]=timer[0];
	}
	else if(last_channel[3]==1 && !(PINB & 00001000))
	{
		last_channel[3]=0;
		input[3]=timer[0]-timer[4];
	}

	//channel 5--
	if(last_channel[4]==0&& PINB & 00010000) //makes sure that the first pin was initially low and is now high
	{                                         //PINB & B00000001 is equivalent to digitalRead but faster
		last_channel[4]=1;
		timer[5]=timer[0];
	}
	else if(last_channel[4]==1 && !(PINB & 00010000))
	{
		last_channel[4]=0;
		input[4]=timer[0]-timer[5];
	}
}
		 
			 
			 
			 
			 

int main()
{UART_Init0();
	//initTimer4_2560();
	//DDRC=0xff;   //Configure PORTC(Lcd databus) as output
	//DDRB=0x00;   //Configure INT0,INT1 as input and PORTD5-PORTD7(rs,rw,en) as output
	PORTB=0xff;
	PCICR|=(1<<PCIE0);                    //interupt on PCINT7:0 is enables
	PCMSK0|=(1<<PCINT4)|(1<<PCINT5)|(1<<PCINT6);   // pins 10,11,12 are made to have interrupt
	printString0("dmckd\n");
	
	EICRA=(1<<ISC31)|(1<<ISC21)|(1<<ISC11)|(1<<ISC01);
	EIMSK=(1<<INT0)|(1<<INT1)|(1<<INT2)|(1<<INT3);
	//initTimer4_2560();
	sei();     // Enable global interrupts by setting global interrupt enable bit in SREG
	
	while(1)
	{
		
	}
}

