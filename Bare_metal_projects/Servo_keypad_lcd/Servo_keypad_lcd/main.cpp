/*
 * Servo_keypad_lcd.cpp
 *
 * Created: 09-11-2020 12:13:38
 * Author : kunal
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "GB_uarts.h"
#include "stdlib.h"
#include "GB_lcd.h"
#include "GB_keypad.h"
/*
when using this last element of given array should have 
'/n' as last element otherwise it will not come out of 
for loop

*/
int GB_intarray_to_integer(uint8_t gb_intarra [])
{
	int gb_i,gb_k=0;
	for(gb_i=0; gb_intarra[gb_i]!='\n'; gb_i++)
	{
		gb_k = ((10 * gb_k) + (gb_intarra[gb_i]-48));
	}

	return gb_k;
}

static inline void GB_initTimer1Servo(void)
{
	/* Set up Timer1 (16bit) to give a pulse every 20ms */
	/* Use Fast PWM mode, counter max in ICR1 */
	TCCR4A |= (1 << WGM41);
	TCCR4B |= (1 << WGM42) | (1 << WGM43);
	TCCR4B |= (1 << CS41);  /* /1 prescaling -- counting in microseconds */
	ICR4 = 40000;                                    /* TOP value = 20ms */
	TCCR4A |= (1 << COM4C1);              /* Direct output on PB5 / OC1A */
	DDRH |= (1 << PH5);                            /* set pin for output */

}

void GB_fun1(uint16_t gb_angle)
{   //uint16_t count =count_maximum-count_minimum;
	
	OCR4C=(gb_angle*22.22)+1000;
	GB_decimel0(OCR4C);
	GB_printString0("\n");
}


int main()
{
	GB_initTimer1Servo();
	GB_LCD_init();
	GB_UART_Init0();
	uint8_t gb_r=0;
	uint8_t gb_firstnum[3];
	
	while (1)
	{   
		
		uint16_t gb_k=0;
		
		
		GB_printString0("\n enter first Number \n");
		
		GB_lcd_setcursor(0,0);
		GB_LCD_string("Enter Angle for");
		GB_lcd_setcursor(0,1);
		GB_LCD_string("Servo(0-180) ");
		
		
	    for(int gb_a;gb_a<3;gb_a++)
		{
			GB_printString0("value of a:");
			GB_decimel0(gb_a);
			GB_printString0("\n");
			
			gb_r = GB_getKey();
		   if(gb_r == '#')
			{
				GB_printString0("Backspace pressed \n");
				gb_a--;
				gb_firstnum[gb_a] = '\0';
				
				gb_k = ((10 * gb_k) + (gb_firstnum[gb_a]-48));
				
				// for terminal screen
				GB_decimel0(gb_k);
				GB_printString0("\n");
				
				//for lcd screen
				GB_lcd_setcursor(13,1);
				GB_lcd_printint(gb_k);
			}
			else
			{
				gb_firstnum[gb_a] = gb_r;
				
				if(gb_firstnum[gb_a]!= '\n' )
				gb_k = ((10 * gb_k) + (gb_firstnum[gb_a]-48));
				
				//for lcd screen
				GB_lcd_printint_num(gb_r-48);
			
			    // for terminal screen
				GB_UART_TxChar0(gb_firstnum[gb_a]);
				GB_printString0("\n");
				GB_decimel0(gb_k);
				GB_printString0("\n");
				
			}
		}
		 
		  //for LCD screen
		  GB_lcd_setcursor(13,1);
		  GB_lcd_printint(gb_k);
		  
		  GB_fun1(gb_k);
		  
		  // for terminal screen
		  GB_decimel0(gb_k);
		  GB_printString0("\n");
		  _delay_ms(2000);
		  
		  GB_lcd_clear();
		  



	}
	
	
}



/*

	{
		printString0("value of a:");
		decimel0(a);
		printString0("\n");
		
		r = getKey();
		if(r == '#')
		{
			lcd_setcursor(13,1);
			lcd_printint(k);
			r = getKey();
			if(r!= '\n' )
			k = ((10 * k) + (r-48));
			UART_TxChar0(r);
			lcd_printint_num(r-48);
			printString0("\n");
			decimel0(k);
			
		}else
		{
			if(r!= '\n' )
			k = ((10 * k) + (r-48));
			UART_TxChar0(r);
			lcd_printint_num(r-48);
			printString0("\n");
			decimel0(k);
		}
		
		
		
		*/