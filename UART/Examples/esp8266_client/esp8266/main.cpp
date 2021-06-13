//#include <uarts.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>
#include "GB_millis.h"
#include "GB_dht11.h"
#include "GB_uarts.h"
#include "GB_esp8266_comman.h"
#include "GB_esp8266_client.h"
#define debug false
  
  // UART Port 0 is connected between MCU(Atmega 2560) and Laptop for printing data on terminal screen
  // UART Port 1 is connected between MCU( ATmega 2560) and ESP8266 for sending and receiving data via AT commands
  
  //const char gb_urlpath[100] ="/data/2.5/weather?q=delhi&appid=885e9149105e8901c9809ac018ce8658";
  //const char gb_url[100] = "api.openweathermap.org";
  const char gb_urlpath[100] ="/update?api_key=K86PTN9OPANWW8MF&field1";
  const char gb_url[100] = "api.thingspeak.com";
  
int main(void)
{  
	GB_init_millis(16000000UL); //frequency the atmega328p is running at
	GB_UART_Init0();
	GB_UART_Init1();       ///for esp baudrate is selected 115200
	GB_printString0("******************ESP8266 AT Commands firmware (using embedded C)*****************");
	GB_printString0("\n");
	GB_esp8266_initialise_client();
    sei();
	int gb_i=0;
	int gb_c=0;
	while(1)
	{   
	
		GB_dht11();
		uint8_t gb_t = GB_dht11_temp();
		GB_printString0("Temp ");
		GB_decimel0(gb_t);
		GB_printString0("\n");
				
		GB_esp8266_connectTCPserver(gb_url,80);
		GB_esp8266_cipsend(gb_t,gb_urlpath);
		GB_esp8266_tcpgetcommand(gb_urlpath,gb_t);
		_delay_ms(2000);
		

		
	}
}





































































/*

		if(c<0)
		{
			
			
			esp8266_connectTCPserver(url,80);
			esp8266_cipsend(senseval);
			esp8266_tcpgetcommand(urlpath,senseval);
			c++;
			
		}
		if(c<0)
		{
			send_command("AT+RST\r\n");
			int rsp = RFR_UART1("OK", 4000);
			if(rsp==1) printString0(RX_DATA_UART1);
			c++;
		}
	}
	
	*/