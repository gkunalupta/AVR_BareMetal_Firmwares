/*
 * lcdscreen2560.cpp
 *
 * Created: 02-11-2020 15:59:53
 * Author : kunal
 
 // for atmega 2560
 #define LCD_D0 0  //  Digital pin - 49(PL0)
 #define LCD_D1 1  //  Digital pin - 48(PL1)
 #define LCD_D2 2  //  Digital pin - 47(PL2)
 #define LCD_D3 3  //  Digital pin - 46(PL3)
 #define LCD_D4 4  //  Digital pin - 45(PL4)
 #define LCD_D5 5  //  Digital pin - 44(PL5)
 #define LCD_D6 6  //  Digital pin - 43(PL6)
 #define LCD_D7 7  //  Digital pin - 42(PL7)

                            // for atmega 2560
 //RW                 Digital pin - 12(PB6)  
 //RS                 Digital pin - 13(PB7)
 //Enable             Digital pin - 11(PB5)


 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>
#include "GB_uarts.h"
#include "GB_lcd.h"

uint8_t gb_Character[8] =
{
	0b00100,
	0b00100,
	0b01010,
	0b10001,
	0b10001,
	0b10001,
	0b10001,
	0b10001
};


int main(void)
{    int gb_a = 0;
	GB_UART_Init0();
	GB_LCD_init();
	_delay_ms(20);
	GB_LCD_string("LCD Datasheet ");
	GB_lcd_setcursor(0,1);    //col,row
	GB_lcd_printint(0);
	GB_LCD_string(" ");
	GB_LCD_data(gb_a);
	GB_LCD_string(" ");
	GB_lcd_printint_num(1);
// 	LCD_string("ST7066 ");
//     LCD_string("GETOBYTE");
	//_delay_ms(3000);
	//lcd_clear();
	//_delay_ms(1000);
	//LCD_string("Subs Channel");
	GB_LCD_sendpattern(0,gb_Bell);
// 	LCD_sendpattern(1,Alien);
// 	LCD_sendpattern(2,Lock);
// 	LCD_sendpattern(3,Sound);
// 	LCD_sendpattern(4,Skull);
// 	LCD_sendpattern(5,Heart);
// 	LCD_sendpattern(6,Speaker);
// 	LCD_sendpattern(7,Check);
	GB_lcd_setcursor(15,1);
	GB_LCD_printpattern(0);
// 	LCD_printpattern(1);
// 	LCD_printpattern(2);
// 	LCD_printpattern(3);
// 	LCD_printpattern(4);
// 	LCD_printpattern(5);
// 	LCD_printpattern(6);
// 	LCD_printpattern(7);

	
	
	

    while (1) 
   
   { 

   }
   
}


