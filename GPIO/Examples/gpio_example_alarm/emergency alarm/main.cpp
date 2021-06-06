/*
 * emergency alarm.cpp
 *
 * Created: 13-09-2020 17:08:28
 * Author : kunal
 */ 

#include <avr/io.h>
#include <avr/delay.h>
#include "uarts.h"

#include "GPIO.h"




// For buzzer alarm using Capacitive sensor
#define buzzer PJ1    // buzzer connected to 14 digital pin
#define cap_sensor PJ0  // cap_sensor connected tp 15 digital pin



int main(void)
{
	UART_Init0();
	pinMode(buzzer,&DDRJ, OUTPUT);
	
	printString0("Gettobyte Youtube cahnnel GPIO_Example\n");

	pinMode(cap_sensor, &DDRJ,INPUT);

	while (1)
	{
		if(digitalRead(cap_sensor,&PINJ))
		digitalWrite(buzzer,&PORTJ,HIGH);
		else
		digitalWrite(buzzer,&PORTJ,LOW);
	}

}
