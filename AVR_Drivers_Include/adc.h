/*
 * GccApplication5atmega2560.cpp
 *
 * Created: 1/9/2020 1:44:57 PM
 * Author : kunal
 */ 

#ifndef ADC_H_
#define ADC_H_


#define ADC1 0x01  //(00000001)
#define ADC2 0x02  //(00000010)
#define ADC3 0x03  //(00000011)
#define ADC4 0x04  //(00000100)
/*
  you can write for all the adc pins like these seeing in the datsheet


*/


#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>
#include "uarts.h"
char sbuff[100];
void ADC_setup(void);
int ADC_select(uint8_t chan) ;    //for channel selection

void ADC_read(void);

#include "adc.cpp"

#endif