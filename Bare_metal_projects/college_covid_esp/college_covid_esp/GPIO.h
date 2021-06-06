#ifndef GPIO_H_
#define GPIO_H_


#define SET_BIT(byte, bit) (byte |= (1 << bit))
#define CLEAR_BIT(byte,bit) (byte &= ~(1 << bit))
#define IS_SET(byte,bit) ((byte) & (1<<bit))
void pinMode( uint8_t pin , uint8_t volatile *pin_data_direction_register, bool Mode );
void digitalWrite( uint8_t pin ,uint8_t volatile *port_data_pin_register, bool state);
uint8_t digitalRead( uint8_t pin , uint8_t volatile *port_input_pin_register);
// Macro variables for equating MODE in pinMode()
#define OUTPUT 1
#define INPUT 0

//Macro Variables for equating State in digitalWrite()
#define HIGH 1
#define LOW 0
#include "GPIO.cpp"

#endif