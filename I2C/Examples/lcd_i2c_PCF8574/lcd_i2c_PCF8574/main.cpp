/*
 * lcd_i2c_PCF8574.cpp
 *
 * Created: 07-03-2021 12:13:03
 * Author : kunal
 */ 

#include <avr/io.h>

#include "GB_uarts.h"
#include "GB_i2c master.h"
#include "GPIO.h"
#include "GB_lcd_i2c.h"
#include <util/delay.h>
#include <inttypes.h>
#include <string.h>


int main(void)
{
	GB_UART_Init0();
	//TWI_init_master();
	
	GB_LCD_init();
	GB_lcd_clear();

	//	LCD_string("Gettobyte");
	GB_LCD_string("G");
		//lcd_setcursor(0,1);
	//	LCD_string("LCD_I2C");
	while (1) 
    {
		//	LCD_command(lcd_4bit_1line);
			
		GB_LCD_string("k");
		_delay_ms(100);
		
    }
}

