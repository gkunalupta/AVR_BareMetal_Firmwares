/*
 * INA219_csa_mega.cpp
 *
 * Created: 12-09-2021 11:36:20
 * Author : kunal
 */ 
#include <avr/interrupt.h>
#include <util/delay.h>
#include "GB_millis.h"
#include "GB_uarts.h"
#include "GB_esp8266_comman.h"
#include "GB_esp8266_client.h"
#include "GB_i2c master.h"
#include "GB_ina219.h"

int main(void)
{
	
	GB_UART_Init0();
	GB_printString0("Welcome to Gettobyte\n");
	GB_printString0("INA219 Driver\n");
	ina219_init();
	
		GB_printString0("INA219\n");
    /* Replace with your application code */
    while (1) 
    {
		GB_printString0("Bus Voltage: ");
		ina219_busvoltage();
		GB_printString0("V\n");
		
		GB_printString0("Shunt Voltage: ");
		ina219_shuntvoltage();
		GB_printString0("mV\n");
		
		GB_printString0("Shunt Current: ");
		ina219_shuntcurrent();
		GB_printString0("mA\n");
			
		GB_printString0("Load Power : ");
		ina219_Loadpower();
		GB_printString0("mW\n");
			
			
		GB_printString0("\n");
		GB_printString0("\n");
		GB_printString0("\n");
		
		_delay_ms(1000);
		
    }
}

