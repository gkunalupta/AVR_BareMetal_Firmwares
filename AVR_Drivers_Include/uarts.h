#ifndef UARTS_H_
#define UARTS_H_


#define F_CPU 16000000
#include <avr/interrupt.h>
#include <stdio.h>
#include <string.h>


void UART_Init0();
char UART_RxChar0();
void UART_TxChar0(uint16_t data);//unsigned short(0-65535)
void printString0(const char *myString);
void printint0( uint8_t num []);
void rxstring0();
void bit0(uint32_t val);//unsigned short (0-65535)
void decimel0(uint32_t val);
void float_value0(float value);


void UART_Init1();
char UART_RxChar1();
void UART_TxChar1(uint8_t data);
void printString1(const char myString[]);
void rxstring1();
void bit1(uint16_t val);//unsigned short (0-65535)
void decimel1(uint16_t val);


void UART_Init2();
char UART_RxChar2();
void UART_TxChar2(uint8_t data);
void printString2( const char myString[]);
void rxstring2();
void bit2(uint16_t val);//unsigned short (0-65535)
void decimel2(uint16_t val);


void UART_Init3();
char UART_RxChar3();
void UART_TxChar3(char data);
void printString3( char *myString);
void rxstring3();
void bit3(uint16_t val);//unsigned short (0-65535)
void decimel3(uint16_t val);

char myValue;

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

#include "uarts.cpp"

#endif