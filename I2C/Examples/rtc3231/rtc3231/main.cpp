/*
 * rtc3231.cpp
 *
 * Created: 4/13/2020 4:57:40 PM
 * Author : kunal
 */ 

#include <avr/io.h>


#include "GB_i2c master.h"

#include "GB_uarts.h"

#include "GB_rtc3231.h"

int main(void)
{   
	
		
	GB_UART_Init0();
	GB_rtc3231_init();
	GB_printString0("***********rtcds3231********************");
	float gb_a;
	gb_rtc_time gb_rt;
	gb_rtc_date gb_rd;
	GB_setdatetime(&gb_rt,&gb_rd);
	
	//rtc3231_32khz_output();
	    /* Replace with your application code */
    while (1) 
    {    
		  GB_printString0("Temperature : ");
		  gb_a=GB_DS3231_getTemperature();
	      GB_decimel0(gb_a);
		  GB_printString0("\n");
		  
// 		  rtc3231_read_date(&rd);
// 		 displaydate((&rd));
		  
		 GB_rtc3231_read_datetime(&gb_rt,&gb_rd);
		  GB_dispalytimedate(&gb_rt,&gb_rd);
		  
		  GB_printString0("\n");
		  _delay_ms(1000);
	}
}

