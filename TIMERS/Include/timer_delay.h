#ifndef TIMER_DELAY_H_
#define TIMER_DELAY_H_


#include <avr/io.h>
#include <avr/interrupt.h>
#include <lcd.h>
// global variable to count the number of overflows
volatile uint8_t tot_overflow;
#define SET_BIT(byte, bit) ((byte) |= (1UL << (bit)))
#define CLEAR_BIT(byte,bit) ((byte) &= ~(1UL << (bit)))
#define IS_SET(byte,bit) (((byte) & (1UL << (bit))) >> (bit))




/*
Just for demonstration purpuse , blinking one onf the GPIO pin in delay function
*/

//for atmega 2560
//#define PIN_NO 2 // (output motor)
//#define PIN_PORT PORTD

//for atmega 328
#define PIN_NO 4    //(output motor)
#define PIN_PORT PORTB

// initialize timer, interrupt and variable
void timer1_init();
void Timer_100_msecs();
void Timer_200_msecs();
void Timer_300_msecs();
void Timer_400_msecs();
void Timer_500_msecs();
void Timer_600_msecs();
void Timer_700_msecs();
void Timer_800_msecs();
void Timer_900_msecs();


void Timer_1_sec();
void Timer_2_secs();
void Timer_3_secs();
void Timer_4_secs();

#include "timer_delay.cpp"

#endif
