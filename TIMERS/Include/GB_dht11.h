#include "GB_uarts.h"
#include "avr/delay.h"
#define SET_BIT(byte, bit) (byte |= (1 << bit))
#define CLEAR_BIT(byte,bit) (byte &= ~(1 << bit))
#define IS_SET(byte,bit) ((byte) & (1<<bit))

 //uint8_t data [5];

void GB_Timer_delay_check_oscil(void);

	
void GB_dht11_init();

//Now you have to check pin status of DHT11..

int GB_dht11_find_response();

int GB_dht11_receivedht();

void GB_dht11();

uint8_t GB_dht11_hum();

float GB_dht11_temp();
//int dht11_receivedht(int x[]);
// 
 void GB_dht11_init10();

// //Now you have to check pin status of DHT11..

int GB_dht11_find_response10();
// 
 int GB_dht11_receivedht10(uint8_t* gb_arr);

#include "GB_DHT11.cpp"