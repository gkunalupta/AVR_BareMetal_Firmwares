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
#include "GB_uarts.h"
#include "GB_millis.h"
#include "GB_dht11.h"
#include "esp8266webpage.h"
#include "GB_esp8266_comman.h"
#include "GB_esp8266_server.h"
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
			
			GB_init_millis(16000000UL); //frequency the atmega328p is running at
			GB_UART_Init0();
			GB_UART_Init1();       ///for esp baudrate is selected 115200
			GB_printString0("******************ESP8266 AT Commands firmware: Webserver (using embedded C)*****************");
			GB_printString0("\n");
			sei();
			int gb_i=0;
			int gb_c=0;
			char gb_staip[20],gb_stamac[20];
			while(1)
			{
			
				
				if(gb_c<1)
{
	//Configure as Station
	GB_send_command("AT+CWMODE=1\r\n");
	GB_getstring_UART1();

	//Start Multiple connection
	GB_send_command("AT+CIPMUX=1\r\n");
	GB_getstring_UART1();
	
	GB_send_command("AT+CIPSERVER=1,80\r\n");
    GB_RFR_UART1(1000);	
	GB_printString0(gb_RX_DATA_UART1);
	
		GB_send_command("AT+CWJAP?\r\n");
		GB_getstring_UART1();


		//Connect To wifi
	GB_send_command("AT+CWJAP=\"JioFiber 2.4ghz\",\"Mansi5481\"\r\n");
	GB_RFR_UART1(16000);
	
	
GB_send_command("AT+CIFSR\r\n");
GB_RFR_UART1(1000);

 memset(gb_staip, '\0',sizeof(gb_staip));
 memset(gb_stamac, '\0',sizeof(gb_stamac));
 
 char * gb_p = strstr(gb_RX_DATA_UART1,"+CIFSR:STAIP");
 gb_p += strlen("+CWJAP:STAIP")+2;
 char * gb_q=strchr(gb_p,'"');
 strncpy(gb_staip,gb_p,gb_q-gb_p);
 GB_printString0("IP address of Station is :");
 GB_printString0(gb_staip);

GB_printString0("\n");
GB_printString0(gb_p);
char * gb_r = strstr(gb_RX_DATA_UART1,"+CIFSR:STAMAC");
gb_r += strlen("+CIFSR:STAMAC")+2;
char * gb_s =strchr(gb_r,'"');
strncpy(gb_stamac,gb_r,gb_s-gb_r);
//printString0("\n Mac address of Station is :");
//printString0(stamac);

GB_send_command("AT+CIPSTO?\r\n");
GB_getstring_UART1();


gb_c++;
}


uint32_t gb_g=0;
gb_g = GB_getstring_ESP8266FORSERVER(gb_staip);
GB_printString0("\n");
GB_decimel0(gb_g);
GB_printString0("\n");
	//if(g==1)
	{
		GB_esp8266_serverdatatoclientcipsend();
		_delay_ms(1000);
	GB_esp8266_webpagedata();
	_delay_ms(1000);
	//esp8266_webpageclose();
	//_delay_ms(1000);
	}
		
	_delay_ms(5000);
	
			}
		
		
		
		}

