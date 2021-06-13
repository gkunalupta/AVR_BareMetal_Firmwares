/*
 * led_fadein_PWM.cpp
 *
 * Created: 09-02-2021 19:29:01
 * Author : kunal
 */ 
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "GB_timer_pwm.h"
#include "GB_uarts.h"

int main(void)
{
	GB_FAST_PWM_Init(gb_PWMpin);
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
		
		
		
		for(int gb_i=0;gb_i<100;gb_i++)
			 		{
				 		GB_duty_cycle(gb_i);
				 		_delay_ms(100);
			 		}
			 		_delay_ms(500);
			 		for(int gb_i=100;gb_i>0;gb_i--)
			 		{
				 		GB_duty_cycle(gb_i);
				 		_delay_ms(100);
			 		}
			 		_delay_ms(500);
			 
    }
	
}

