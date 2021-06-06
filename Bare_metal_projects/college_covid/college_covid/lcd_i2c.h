#ifndef LCD_I2C_H_
#define LCD_I2C_H_

#include "i2c master.h"
#include <util/delay.h>

//Function Set
//Rs RW DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// 0 0  0    0   1   DL  N   F   -   -
// 8bit (DL=1) , 4bit (DL=0)
// 1line (N=0) , 2line (N-1)
#define lcd_8bit_1line 0b00110000
#define lcd_8bit_2line 0b00111000
#define lcd_4bit_1line 0b00100000
#define lcd_4bit_2line 0b00101000

//Display ON/OFF control -
//Rs RW DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// 0 0  0    0   0   0   1   D   C   B
//DN- display on(D=1), CN- Cursor on(C=1 ), BN- blink on(B=1)
//DF-display off(D=0), CF- cursor off(C=1), BF- blink off(B=0)
#define lcd_DN_CN_BN 0b00001111
#define lcd_DN_CF_BF 0b00001100
#define lcd_DN_CN_BF 0b00001110
#define lcd_DF_CF_BF 0b00001000
#define lcd_DF_CN_BN 0b00001011

//Entry mode set
//Rs RW DB7 DB6 DB5 DB4 DB3 DB2 DB1  DB0
// 0 0  0    0   0   0   0   1  I/D  S/H
//CMR -cursor move right(I/D=1) , DMF- display move off(S/H=0)
//CML -cursor move left(I/D=0) , DMR - display move right(S/H=1)
//DML- display move left(S/H=1)
#define lcd_CMR_DMF 0b00000110
#define lcd_CML_DMF 0b00000100
#define lcd_CMR_DMR 0b00000111
#define lcd_CML_DML 0b00000101

#define lcd_clear_all 0b00000001
#define lcd_rhome     0b00000010
#define lcd_SETDDRAMADDR 0x80

/*
// macros for rs,rw,en pins of lcd
#define En 00000100  // Enable bit
#define Rw 00000010  // Read/Write bit
#define Rs 00000001  // Register select bit
*/
uint8_t En = 0x04; //00000100
uint8_t Rw = 0x00; //00000000: 1st bit
uint8_t Rs = 0x01; //00000001

#define pcf8574_WADDR 0b01111110  //Slave Write
#define pcf8574_RADDR 0b01111111   //Slave Read
#define LCD_BACKLIGHT         0x08
#define LCD_NOBACKLIGHT       0x00
#define display_rate 50
/*
P7- D7
P6-D6
P5-D5
P4-D4-
P3 -
P2 E
P1- RW
P0- RS

D7-D4 are data port pins
E: enable pin has to be switched from High to Low after sendind data on port pins
R/W: read(1) and write(0) pin control
RS: Command(0) and data(1) register control
*/

void lcd_ioexander(unsigned char Data);
void pulse_enable( uint8_t data);
void lcd_write4bit(unsigned char nibble);
/*
For command register: RS=0,RW=0

*/
void LCD_command(unsigned char command);
void lcd_setcursor(uint8_t col, uint8_t row);
void lcd_clear();
void lcd_Rethome();
/*
For Data Register: RS=1,RW=0
*/
void LCD_data(unsigned char data);
/*
for printing integers in form 001,023,015,006,007
*/
void lcd_printint(int value);
/*
 for printing integers in form 1,23,15,6,7
 Mainly used for printing 0-9
 */
void lcd_printint_num(int value);
/*
send string function
*/
void LCD_string(const char*str);
void lcd_print1line(const char *buff);
void lcd_print2line(const char *buff);
void lcd_bit(unsigned char val);
void LCD_init();

#include "lcd_i2c.cpp"

#endif