/*
 * preprototypesanitation_2560.cpp
 *
 * Created: 12-07-2020 06:17:34
 * Author : kunal
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer_delay.h"
#include "uarts.h"
int a=0;
#define sensor_pin 0    // digital 21 as input
#define reset_pin 1 // digital 20 as output
ISR(INT0_vect)
{  
	 lcd_setcursor(7,0);
	 a++;
	lcd_printint(a);
	 printString0("gupta\n");
	Timer_4_secs();
	EIFR |=(1<<INTF0);
}
ISR(INT1_vect)
{
	a=0;
	lcd_setcursor(7,0);
	lcd_printint(a);
}
int main(void)
{  
	 UART_Init0();
	DDRD |= (1<<sensor_pin)|(1<<reset_pin);   // PD0 as input for reading sensor by relay , PD1 for reset button
	EIMSK |=(1<<INT0)|(1<<INT1);
	//EIMSK |=(1<<INT1);
	EICRA |=(1<<ISC01)|(1<<ISC00)|(1<<ISC11)|(1<<ISC10);
	sei();
	
	
	
	
	
	int q =4;
	int a=1;
	
	uint8_t prev_state , prev_state2;
	uint8_t curr_state;
	const char abc[5]="1.3";
	// connect led to pin PC0
	LCD_init();
	//lcd_clear();
	_delay_ms(20);
	LCD_string("PEOPLE:");
	_delay_us(50);
	lcd_setcursor(0,1);
	LCD_string("On TIME(sec):");
	_delay_ms(10);
	printString0("kunal");
	//LCD_string(abc);
	lcd_printint(q);
	_delay_ms(10);
	DDRB |= (1 << PB4)|(0<<PB5)|(1<<PB3);  //-->D12 - output , D13 -input
	prev_state |= ((PIND) & (1<<sensor_pin));
	//prev_state = 0b0000100;
	//lcd_bit(prev_state);
	//Timer_4_secs();
	while(1)
	{
		/*
		//printString0("seven");
		//_delay_ms(1000);
		
		   //should be off
					//lcd_setcursor(8,0);
			prev_state2 = ((PIND) & (1<<sensor_pin));		//lcd_bit(prev_state);
					//int x=0;
		while(IS_SET(PIND,sensor_pin))
		{  lcd_print2line("seven");
			//curr_state = ((PINB) & (1<<5));    // should be on
			lcd_bit(prev_state2);
			//_delay_ms(1000);
			lcd_setcursor(8,0);
			lcd_bit(prev_state);
			//_delay_ms(1000);
			//int x=0;
			if(prev_state != prev_state2)
			{
			//lcd_print2line("Gupta");
			_delay_ms(100);
			Timer_4_secs();
            lcd_setcursor(13,1);
			lcd_printint(a);
			a++;
			prev_state = ((PIND) & (1<<sensor_pin));
			lcd_setcursor(8,0);
			lcd_bit(prev_state);
		    }
			else
		    {  
				lcd_print2line("break");
				_delay_ms(100);
				prev_state = ((PIND) & (1<<sensor_pin));
				lcd_setcursor(8,0);
				lcd_bit(prev_state);
				_delay_ms(1000);
				break;
				
				}
				lcd_print2line("getto");
				//prev_state |= ((PINB) & (1<<5));
		}
		//lcd_print2line("machi");
// 			PORTD |=(1<<2);
// 			_delay_ms(10);
// 			PORTD &= ~(1<<2);
// 			_delay_ms(10);
		
	 */
	}

}
