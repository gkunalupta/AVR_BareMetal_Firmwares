//#include <uarts.h>
#include <avr/interrupt.h>
#include <string.h>
#include "millis.h"
#include "dht11.h"
#include "uarts.h"
#include "esp8266_comman.h"
#include "esp8266_client.h"
#include <stdio.h>
#define debug false
  
  // UART Port 0 is connected between MCU(Atmega 2560) and Laptop for printing data on terminal screen
  // UART Port 1 is connected between MCU( ATmega 2560) and ESP8266 for sending and receiving data via AT commands
  
  //const char urlpath[100] ="/data/2.5/weather?q=delhi&appid=885e9149105e8901c9809ac018ce8658";
  //const char url[100] = "api.openweathermap.org";
  const char urlpath[100] ="/update?api_key=K86PTN9OPANWW8MF&field1";
  const char url[100] = "api.thingspeak.com";
  
int main(void)
{  
	init_millis(16000000UL); //frequency the atmega328p is running at
	UART_Init0();
	UART_Init1();       ///for esp baudrate is selected 115200
	printString0("******************ESP8266 AT Commands firmware (using embedded C)*****************");
	printString0("\n");
	esp8266_initialise();
    sei();
	int i=0;
	int c=0;
	while(1)
	{   
	
		dht11();
		uint8_t t = dht11_temp();
		printString0("Temp ");
		decimel0(t);
		printString0("\n");
				
		esp8266_connectTCPserver(url,80);
		esp8266_cipsend(t,urlpath);
		esp8266_tcpgetcommand(urlpath,t);
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