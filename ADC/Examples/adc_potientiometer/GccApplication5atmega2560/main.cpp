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
#include "uarts.h"

#include "adc.h"


int main(void)
{  
	float val;
	ADC_setup();
	UART_Init0();
while (1)
{
	int potien_value = ADC_select(ADC1);
	//float potien_voltage = (332 * 5)/1023;
	
	float potien_voltage = (static_cast<float>(potien_value) * 4)/1023;
	printString0("\npotientiometer value:");
	decimel0(potien_value);
	printString0("\npotientiometer voltage value:");
	float_value0(potien_voltage);
	
//ADC_select(ADC2);
//printString0(" navigation keys \n");
//ADC_read();
//ADC_select(ADC3);
//ADC_read();

_delay_ms(1000);


}
}

