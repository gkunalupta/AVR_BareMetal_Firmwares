#include "uarts.h"
#include "avr/delay.h"
#define SET_BIT(byte, bit) (byte |= (1 << bit))
#define CLEAR_BIT(byte,bit) (byte &= ~(1 << bit))
#define IS_SET(byte,bit) ((byte) & (1<<bit))

 //uint8_t data [5];

void Timer_delay_check_oscil(void);

	
void dht11_init();

//Now you have to check pin status of DHT11..

int dht11_find_response();

int dht11_receivedht(int x[]);
// 
// void dht11_init10();

// //Now you have to check pin status of DHT11..

int dht11_find_response10();
// 
// int dht11_receivedht10(uint8_t* arr);

#include "DHT11.cpp"