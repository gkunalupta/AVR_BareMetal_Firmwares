/*
 * led_fadein_PWM.cpp
 *
 * Created: 09-02-2021 19:29:01
 * Author : kunal
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "timer_pwm.h"
#include "uarts.h"







int main(void)
{
	FAST_PWM_Init(PWMpin);
    //pinMode(PB7,&DDRB,OUTPUT);
//DDRB |=(1<<PB7);

	
    while (1) 
    {
// 		digitalWrite(PB7,&PORTB,HIGH);
// 		_delay_ms(1000);
// 		digitalWrite(PB7,&PORTB,LOW);
// 		_delay_ms(1000);
		//PORTB |=(1<<PB7);
		//OCR1C =2000;
		//duty_cycle(90);
		
		for(int i=0;i<100;i++)
			 		{
				 		duty_cycle(i);
				 		_delay_ms(100);
			 		}
			 		_delay_ms(500);
			 		for(int i=100;i>0;i--)
			 		{
				 		duty_cycle(i);
				 		_delay_ms(100);
			 		}
			 		_delay_ms(500);
			 
    }
	
}

