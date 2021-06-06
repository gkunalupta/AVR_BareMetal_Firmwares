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
int a=000;
/*
                     // atmega 2560                    
#define reset_sinput_dir DDRD
#define reset_sinput_pinport PIND
#define sensor_pin 0 // digital 21(PD0) 
#define reset_pin 1 // digital 20(PD1)
#define PIN_NO 2   // digital  19(PD2)     //outputmotor
#define Flow_pin 3  //digital 18(PD3)
*/
                         // atmega 328
#define reset_sinput_dir DDRB						 
#define reset_sinput_pinport PINB
#define sensor_pin 5 // digital 13(PB5) 
#define PIN_NO 4     // digital 12(PB4)
#define reset_pin 3 // digital 3(PD3) (described in lcd.h)
#define Flow_pin 2 // digital 2(PD2) (described in lcd.h)
//#define LCD_data_dir DDRD  
//#define LCD_data_port PORTD 


ISR(INT1_vect)
{
	a=000;
	lcd_setcursor(6,0);
	lcd_printint(a);
}
int main(void)
{  
	 UART_Init0();
	 // when using external interrupts INT pins then pin has to be declared as output (1), 
	 //when  using with general pooling method then pin has to be declared as input (0)
	 
	 //for atmega 2560
	reset_sinput_dir |= (1<<sensor_pin)|(1<<reset_pin)|(1<<PIN_NO)|(0<<Flow_pin);   // PD0 as input for reading sensor by relay , PD1 for reset button  , PD2 as pin for operating mtor
	
	//for atmega 328
	reset_sinput_dir |= (1<<sensor_pin)|(1<<PIN_NO); 
	LCD_data_dir |= (1<<reset_pin)|(0<<Flow_pin);
	
	EIMSK |=(1<<INT1);          // external interrupt for reset button
	EICRA |=(1<<ISC01)|(1<<ISC00)|(1<<ISC11)|(1<<ISC10);
	sei();
	
	
	
	
	
	int q =4;
	
	uint8_t prev_state;
	uint8_t curr_state;
	LCD_init();
	//lcd_clear();
	_delay_ms(20);
	LCD_string("COUNT:");
	_delay_us(50);
	lcd_setcursor(0,1);
	LCD_string("TIME(ms):");
	_delay_ms(10);
	lcd_printint_num(q);
	_delay_ms(10);
	prev_state |= ((reset_sinput_pinport) & (1<<sensor_pin));
	//prev_state = 0b0000100;
	//lcd_bit(prev_state);
	//Timer_4_secs();
	while(1)
	{
		
		//printString0("seven");
		//_delay_ms(1000);
		
		   //should be off
					//lcd_setcursor(8,0);
			//prev_state = ((PIND) & (1<<sensor_pin));		//lcd_bit(prev_state);
					//int x=0;
		while(IS_SET(reset_sinput_pinport,sensor_pin))
		{  //lcd_print2line("seven");
			curr_state = ((reset_sinput_pinport) & (1<<sensor_pin));
			//lcd_print2line("seven");
			//lcd_bit(curr_state);
			//lcd_setcursor(8,0);
			//lcd_bit(prev_state);

			if(prev_state != curr_state)
			{
			lcd_setcursor(6,0);
			a++;
			lcd_printint(a);
			//lcd_print2line("Gupta");
			//_delay_ms(100);
			Timer_4_secs();
			prev_state = ((reset_sinput_pinport) & (1<<sensor_pin));
			//lcd_setcursor(8,0);
			//lcd_bit(prev_state);
		    }
			else
		    {  
				//lcd_print2line("break");
				//_delay_ms(100);
				prev_state = ((reset_sinput_pinport) & (1<<sensor_pin));
				//lcd_setcursor(8,0);
				//lcd_bit(prev_state);
				//_delay_ms(1000);
				break;
				
				}
				//lcd_print2line("getto");
				//prev_state = ((PIND) & (1<<sensor_pin));
				//prev_state |= ((PINB) & (1<<5));
		}
		/*
		if(IS_SET(reset_sinput_pinport,Flow_pin))
		{   bit0(PIND);
			printString0("ku \n");
			char tank[7] = "ENOUGH";
			lcd_setcursor(10,0);
			LCD_string(tank);
		}
		else
		{bit0(PIND);
			printString0("Gu \n");
			char tank[6] = "EMPTY";
				lcd_setcursor(10,0);
				LCD_string(tank);
				LCD_string(" ");
		}
		
		//lcd_print2line("machi");
// 			PORTD |=(1<<2);
// 			_delay_ms(10);
// 			PORTD &= ~(1<<2);
// 			_delay_ms(10);
		*/
	 
	}

}
