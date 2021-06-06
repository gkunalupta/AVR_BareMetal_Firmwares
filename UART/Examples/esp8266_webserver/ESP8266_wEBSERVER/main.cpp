/*
 * ESP8266_wEBSERVER.cpp
 *
 * Created: 15-09-2020 23:37:40
 * Author : kunal
 */ 
//#include <uarts.h>
#include <avr/interrupt.h>
#include <string.h>
#include <stdio.h>
#include "uarts.h"
#include "millis.h"
#include "dht11.h"
#include "esp8266webpage.h"
#include "esp8266_comman.h"
#include "esp8266_server.h"
#define debug false

		/*const char * webpage = "
		<!DOCTYPE HTML><html>
		<head>
		<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">
		<script src="https://code.highcharts.com/highcharts.js"></script>
		<style>
		body {
			min-width: 310px;
			max-width: 800px;
			height: 400px;
			margin: 0 auto;
		}
		h2 {
			font-family: Arial;
			font-size: 2.5rem;
			text-align: center;
		}
		</style>
		</head>
		<body>
		<h2>ESP8266 Distance Plot</h2>
		<div id="chart-distance" class="container"></div>
		</body>
		<script>
		var chartT = new Highcharts.Chart({
			chart:{ renderTo : 'chart-distance' },
			title: { text: 'HC-SR04 Distance' },
			series: [{
				showInLegend: false,
				data: []
			}],
			plotOptions: {
				line: { animation: false,
					dataLabels: { enabled: true }
				},
				series: { color: '#059e8a' }
			},
			xAxis: { type: 'datetime',
				dateTimeLabelFormats: { second: '%H:%M:%S' }
			},
			yAxis: {
				title: { text: 'Distance (CM)' }
			},
			credits: { enabled: false }
		});
		setInterval(function ( ) {
			var xhttp = new XMLHttpRequest();
			xhttp.onreadystatechange = function() {
				if (this.readyState == 4 && this.status == 200) {
					var x = (new Date()).getTime(),
					y = parseFloat(this.responseText);
					//console.log(this.responseText);
					if(chartT.series[0].data.length > 40) {
						chartT.series[0].addPoint([x, y], true, true, true);
						} else {
						chartT.series[0].addPoint([x, y], true, false, true);
					}
				}
			};
			xhttp.open("GET", "/distance", true);
			xhttp.send();
		}, 3000 ) ;
		</script>
		</html>\r\n";
				*/
		
		int main(void)
		{
			
			init_millis(16000000UL); //frequency the atmega328p is running at
			UART_Init0();
			UART_Init1();       ///for esp baudrate is selected 115200
			printString0("******************ESP8266 AT Commands firmware: Webserver (using embedded C)*****************");
			printString0("\n");
			sei();
			int i=0;
			int c=0;
			char staip[20],stamac[20];
			while(1)
			{
			
				
				if(c<1)
{
	//Configure as Station
	send_command("AT+CWMODE=1\r\n");
	getstring_UART1();

	//Start Multiple connection
	send_command("AT+CIPMUX=1\r\n");
	getstring_UART1();
	
	send_command("AT+CIPSERVER=1,80\r\n");
    RFR_UART1(1000);	
	printString0(RX_DATA_UART1);
	
		send_command("AT+CWJAP?\r\n");
		getstring_UART1();


		//Connect To wifi
	send_command("AT+CWJAP=\"JioFiber 2.4ghz\",\"Mansi5481\"\r\n");
	RFR_UART1(16000);
	
	
send_command("AT+CIFSR\r\n");
RFR_UART1(1000);

 memset(staip, '\0',sizeof(staip));
 memset(stamac, '\0',sizeof(stamac));
 
 char * p = strstr(RX_DATA_UART1,"+CIFSR:STAIP");
 p += strlen("+CWJAP:STAIP")+2;
 char * q=strchr(p,'"');
 strncpy(staip,p,q-p);
 printString0("IP address of Station is :");
 printString0(staip);

printString0("\n");
printString0(p);
char * r = strstr(RX_DATA_UART1,"+CIFSR:STAMAC");
r += strlen("+CIFSR:STAMAC")+2;
char * s =strchr(r,'"');
strncpy(stamac,r,s-r);
//printString0("\n Mac address of Station is :");
//printString0(stamac);

send_command("AT+CIPSTO?\r\n");
getstring_UART1();


c++;
}


uint32_t g=0;
g = getstring_ESP8266FORSERVER(staip);
printString0("\n");
decimel0(g);
printString0("\n");
	//if(g==1)
	{
		esp8266_serverdatatoclientcipsend();
		_delay_ms(1000);
	esp8266_webpagedata();
	_delay_ms(1000);
	//esp8266_webpageclose();
	//_delay_ms(1000);
	}
		
	_delay_ms(5000);
	
			}
		
		
		
		}

