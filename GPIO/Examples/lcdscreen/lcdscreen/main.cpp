/*
 * lcdscreen.cpp
 *
 * Created: 08-07-2020 20:09:19
 * Author : kunal
 */ 

/*
 * lcdscreen.cpp
 *
 * Created: 08-07-2020 20:09:19
 * Author : kunal
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "lcd.h"

int main(void)
{    int u=1;
	LCD_init();
	lcd_clear();
	_delay_ms(20);
	LCD_string("ghhjh");
	_delay_us(50);
     UART_Init0();
	 printString0("kunal");
	lcd_setcursor(15,1);    //col,row
	_delay_us(50);
	lcd_printint(u);
	_delay_us(50);
	//LCD_string("kunal");
	_delay_ms(2000);
	int c=0;
	lcd_clear();
    while (1) 
 { 
	 if(c<1)
	 {
		 LCD_string("Gupta");
		 _delay_us(50);
		 lcd_setcursor(0,1);
		 LCD_string("Kunal");
		 _delay_ms(1000);
		 LCD_data('.');
		 _delay_us(50);
		 c++;
	 }
	 
}
}