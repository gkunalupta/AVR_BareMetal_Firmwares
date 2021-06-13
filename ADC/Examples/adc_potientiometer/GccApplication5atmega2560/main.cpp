/*
 * GccApplication5atmega2560.cpp
 *
 * Created: 1/9/2020 1:44:57 PM
 * Author : kunal
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "math.h"
#include "GB_uarts.h"

#include "GB_adc.h"


int main(void)
{  
	float gb_val;
	GB_ADC_setup();
	GB_UART_Init0();
while (1)
{
	int gb_potien_value = GB_ADC_select(ADC1);
	//float potien_voltage = (332 * 5)/1023;
	
	float gb_potien_voltage = (static_cast<float>(gb_potien_value) * 4)/1023;
	GB_printString0("\npotientiometer value:");
	GB_decimel0(gb_potien_value);
	GB_printString0("\npotientiometer voltage value:");
	GB_float_value0(gb_potien_voltage);
	
//ADC_select(ADC2);
//printString0(" navigation keys \n");
//ADC_read();
//ADC_select(ADC3);
//ADC_read();

_delay_ms(1000);


}
}

