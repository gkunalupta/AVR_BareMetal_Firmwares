/*
 * preprototypesanitation.cpp
 *
 * Created: 10-07-2020 15:21:57
 * Author : kunal
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer_delay.h"
#include "uarts328.h"
int a=1;
ISR(INT0_vect)
{    
	Timer_4_secs();
	lcd_setcursor(13,1);
	lcd_printint(a);
	a++;
	EIFR |=(1<<INTF0);
}
int main(void)
{   UART_Init0();
	DDRD |= (0<<2);   // PD2 as input
	EIMSK |=(1<<INT0);
	EICRA |=(1<<ISC01)|(1<<ISC00);
	sei();
	
	
	
	
	
	int q =9;
	int a=1;
	
	uint8_t prev_state , prev_state2;
	uint8_t curr_state;
	const char abc[5]="1.3";
	// connect led to pin PC0
	LCD_init();
	lcd_clear();
	_delay_ms(20);
	LCD_string("PEOPLE:");
	_delay_us(50);
	lcd_setcursor(0,1);
	LCD_string("LIQUID TIME:");
	_delay_ms(10);
	printString0("kunal");
	//LCD_string(abc);
	lcd_printint(q);
	_delay_ms(1000);
	DDRB |= (1 << PB4)|(0<<PB5)|(1<<PB3);  //-->D12 - output , D13 -input
	prev_state |= ((PINB) & (1<<5));
	//prev_state = 0b0000100;
	//lcd_bit(prev_state);
	
	while(1)
	{
		/*
		   //should be off
					//lcd_setcursor(8,0);
			prev_state2 = ((PINB) & (1<<5));		//lcd_bit(prev_state);
					//int x=0;
		while(IS_SET(PINB,PB5))
		{  lcd_print2line("seven");
			PORTB ^=(1<<3);
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
			prev_state = ((PINB) & (1<<5));
			lcd_setcursor(8,0);
			lcd_bit(prev_state);
		    }
			else
		    {  
				lcd_print2line("break");
				_delay_ms(100);
				prev_state = ((PINB) & (1<<5));
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
