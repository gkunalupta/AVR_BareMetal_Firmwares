/*
 * rtc3231.cpp
 *
 * Created: 4/13/2020 4:57:40 PM
 * Author : kunal
 */ 

#include <avr/io.h>


#include "i2c master.h"

#include "uarts.h"

#include "rtc3231.h"

int main(void)
{   
	
		
	UART_Init0();
	rtc3231_init();
	printString0("***********rtcds3231********************");
	float a;
	rtc_time rt;
	rtc_date rd;
	setdatetime(&rt,&rd);
	
	//rtc3231_32khz_output();
	    /* Replace with your application code */
    while (1) 
    {    
		  printString0("Temperature : ");
		  a=DS3231_getTemperature();
	      decimel0(a);
		  printString0("\n");
		  
// 		  rtc3231_read_date(&rd);
// 		 displaydate((&rd));
		  
		  rtc3231_read_datetime(&rt,&rd);
		  dispalytimedate(&rt,&rd);
		  
		  printString0("\n");
		  _delay_ms(1000);
	}
}

