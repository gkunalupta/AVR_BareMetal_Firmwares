#ifndef GB_UARTS_H_
#define GB_UARTS_H_


/*
UART device driver(Polling) for AVR MCU
Device driver is developed for ATMEGA 260 and Atmega 328,
*/


#define F_CPU 16000000
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>

 /** 
 * To Initialize and configure settings for UART Peripheral.
 * Baud Rate settings,interrupts, enable/disable receive and transmit
 */
void GB_UART_Init0();  
 /** 
 * @brief Function to transmit single byte
   @param[in] gb_tx_data(unsigned short(0-65535))
 */
void GB_UART_TxChar0(uint16_t gb_tx_data);
char GB_UART_RxChar0();
void GB_printString0(const char *gb_myString);
void GB_printint0( uint8_t gb_num []);
void GB_rxstring0();
void GB_bit0(uint32_t gb_val);//unsigned short (0-65535)
void GB_decimel0(uint32_t gb_val);
void GB_float_value0(float gb_value);


void GB_UART_Init1();
char GB_UART_RxChar1();
void GB_UART_TxChar1(uint8_t gb_data);
void GB_printString1(const char gb_myString[]);
void GB_rxstring1();
void GB_bit1(uint16_t gb_val);//unsigned short (0-65535)
void GB_decimel1(uint16_t gb_val);
void GB_float_value1(float gb_value);
void GB_printint1( uint8_t gb_num []);

void GB_UART_Init2();
char GB_UART_RxChar2();
void GB_UART_TxChar2(uint8_t gb_data);
void GB_printString2( const char gb_myString[]);
void GB_rxstring2();
void GB_bit2(uint16_t gb_val);//unsigned short (0-65535)
void GB_decimel2(uint16_t gb_val);
void GB_printint2( uint8_t gb_num []);
void GB_float_value2(float gb_value);


void GB_UART_Init3();
char GB_UART_RxChar3();
void GB_UART_TxChar3(char gb_data);
void GB_printString3( char *gb_myString);
void GB_rxstring3();
void GB_bit3(uint16_t gb_val);//unsigned short (0-65535)
void GB_decimel3(uint16_t gb_val);
void GB_printint3( uint8_t gb_num []);
void GB_float_value3(float gb_value);


char gb_myValue;

#define uart0_ucsrA UCSR0A
#define uart0_ucsrB UCSR0B
#define uart0_ucsrC UCSR0C
#define uart0_UDR UDR0
#define uart0_baudrate UBRR0

#define uart1_ucsrA UCSR1A
#define uart1_ucsrB UCSR1B
#define uart1_ucsrC UCSR1C
#define uart1_UDR UDR1
#define uart1_baudrate UBRR1


#define uart2_ucsrA UCSR2A
#define uart2_ucsrB UCSR2B
#define uart2_ucsrC UCSR2C
#define uart2_UDR UDR2
#define uart2_baudrate UBRR2


#define uart3_ucsrA UCSR3A
#define uart3_ucsrB UCSR3B
#define uart3_ucsrC UCSR3C
#define uart3_UDR UDR3
#define uart3_baudrate UBRR3

#include "GB_uarts.cpp"

#endif