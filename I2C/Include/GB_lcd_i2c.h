#ifndef GB_LCD_I2C_H_
#define GB_LCD_I2C_H_

#include "GB_i2c master.h"
#include <util/delay.h>

//Function Set
//Rs RW DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// 0 0  0    0   1   DL  N   F   -   -
// 8bit (DL=1) , 4bit (DL=0)
// 1line (N=0) , 2line (N-1)
#define gb_lcd_8bit_1line 0b00110000
#define gb_lcd_8bit_2line 0b00111000
#define gb_lcd_4bit_1line 0b00100000
#define gb_lcd_4bit_2line 0b00101000

//Display ON/OFF control -
//Rs RW DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// 0 0  0    0   0   0   1   D   C   B
//DN- display on(D=1), CN- Cursor on(C=1 ), BN- blink on(B=1)
//DF-display off(D=0), CF- cursor off(C=1), BF- blink off(B=0)
#define gb_lcd_DN_CN_BN 0b00001111
#define gb_lcd_DN_CF_BF 0b00001100
#define gb_lcd_DN_CN_BF 0b00001110
#define gb_lcd_DF_CF_BF 0b00001000
#define gb_lcd_DF_CN_BN 0b00001011

//Entry mode set
//Rs RW DB7 DB6 DB5 DB4 DB3 DB2 DB1  DB0
// 0 0  0    0   0   0   0   1  I/D  S/H
//CMR -cursor move right(I/D=1) , DMF- display move off(S/H=0)
//CML -cursor move left(I/D=0) , DMR - display move right(S/H=1)
//DML- display move left(S/H=1)
#define gb_lcd_CMR_DMF 0b00000110
#define gb_lcd_CML_DMF 0b00000100
#define gb_lcd_CMR_DMR 0b00000111
#define gb_lcd_CML_DML 0b00000101

#define gb_lcd_clear_all 0b00000001
#define gb_lcd_rhome     0b00000010
#define gb_lcd_SETDDRAMADDR 0x80

/*
// macros for rs,rw,en pins of lcd
#define En 00000100  // Enable bit
#define Rw 00000010  // Read/Write bit
#define Rs 00000001  // Register select bit
*/
uint8_t gb_LCD_En = 0x04; //00000100
uint8_t gb_LCD_Rw = 0x00; //00000000: 1st bit
uint8_t gb_LCD_Rs = 0x01; //00000001

#define gb_pcf8574_WADDR 0b01111110  //Slave Write
#define gb_pcf8574_RADDR 0b01111111   //Slave Read
#define gb_LCD_BACKLIGHT         0x08
#define gb_LCD_NOBACKLIGHT       0x00
#define gb_display_rate 50
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

void GB_lcd_ioexander(unsigned char gb_Data);
void GB_pulse_enable( uint8_t gb_data);
void GB_lcd_write4bit(unsigned char gb_nibble);
/*
For command register: RS=0,RW=0

*/
void GB_LCD_command(unsigned char gb_command);
void GB_lcd_setcursor(uint8_t gb_col, uint8_t gb_row);
void GB_lcd_clear();
void GB_lcd_Rethome();
/*
For Data Register: RS=1,RW=0
*/
void GB_LCD_data(unsigned char gb_data);
/*
for printing integers in form 001,023,015,006,007
*/
void GB_lcd_printint(int gb_value);
/*
 for printing integers in form 1,23,15,6,7
 Mainly used for printing 0-9
 */
void GB_lcd_printint_num(int gb_value);
/*
send string function
*/
void GB_LCD_string(const char*gb_str);
void GB_lcd_print1line(const char *gb_buff);
void GB_lcd_print2line(const char *gb_buff);
void GB_lcd_bit(unsigned char gb_val);
void GB_LCD_init();

#include "GB_lcd_i2c.cpp"

#endif