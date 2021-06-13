/*
 * ServoMg90s.cpp
 *
 * Created: 01-11-2020 14:54:43
 * Author : kunal
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 16000000UL
#include "GB_uarts.h"
#include "GB_servo.h"



int main(void)
{  
	GB_initServo();
	GB_UART_Init0();

	GB_printString0("\r\nWelcome to the Servo Demo\r\n");
	GB_fun1(0);
	_delay_ms(100);
	while (1)
	{
		GB_fun1(0);
		_delay_ms(1000);
		
		GB_fun1(45);
		_delay_ms(1000);
		
		GB_fun1(90);
		_delay_ms(1000);
		
		GB_fun1(135);
		_delay_ms(1000);
		
		GB_fun1(180);
		_delay_ms(1000);
		
		GB_fun1(135);
		_delay_ms(1000);
		
		GB_fun1(90);
		_delay_ms(1000);
		
		GB_fun1(45);
		_delay_ms(1000);
		
		GB_fun1(0);
		_delay_ms(1000);
		
	}
	
}
	
		
