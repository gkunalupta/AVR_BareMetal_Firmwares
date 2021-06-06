/*
 * lcd_i2c_PCF8574.cpp
 *
 * Created: 07-03-2021 12:13:03
 * Author : kunal
 */ 

#include <avr/io.h>

#include "uarts.h"
#include "i2c master.h"
#include "GPIO.h"
#include <util/delay.h>
#include <inttypes.h>
#include <string.h>

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

#define pcf8574_add 0x3f
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
void lcd_ioexander(unsigned char Data)
{
	TWI_start();
	TWI_write_slave_address(pcf8574_WADDR);
	TWI_write_data(Data | LCD_BACKLIGHT);
	TWI_stop();
}

void pulse_enable( uint8_t data)
{
	lcd_ioexander(data | En);  //enable pulse high
	_delay_us(1);
	lcd_ioexander(data & ~En); //enable pulse low
	_delay_us(50);
}

void lcd_write4bit(unsigned char nibble)
{
	nibble |= (Rs|Rw);
	lcd_ioexander(nibble | 0x04);
	lcd_ioexander(nibble & 0xFB);
	_delay_ms(display_rate);
}
/*
For command register: RS=0,RW=0

*/
void LCD_command(unsigned char command)
{ 
	Rs = 0b00000000;
	Rw = 0b00000000;
	uint8_t highnib = command & 0xf0;
	uint8_t lownib = (command<<4) & 0xf0;
	lcd_write4bit(highnib);
	lcd_write4bit(lownib);
}
void lcd_setcursor(uint8_t col, uint8_t row)
{
	static uint8_t offsets[] = {0x00,0x40,0x14,0x54 };
	//LCD_command(lcd_SETDDRAMADDR | (col + offsets[row]));
	LCD_command((0x80|(row<<6))+col);
	_delay_us(40);
}
void lcd_clear()
{
	LCD_command(lcd_clear_all); //clear display
	_delay_ms(20);
}
void lcd_Rethome()
{
	LCD_command(lcd_rhome);
	_delay_ms(2);
}


/*
For Data Register: RS=1,RW=0
*/
void LCD_data(unsigned char data)
{
		Rs = 0b00000001;
		Rw = 0b00000000;
	uint8_t highnib = data & 0xf0;
	uint8_t lownib = (data<<4) & 0xf0;
	lcd_write4bit(highnib);
	lcd_write4bit(lownib);
}
/*
for printing integers in form 001,023,015,006,007
*/
void lcd_printint(int value)
{

	unsigned char thousands,hundreds,tens,ones;
	
	thousands = value / 1000;
	if(thousands!=0)
	LCD_data(thousands + 0x30);

	hundreds = ((value - thousands*1000)) / 100;
	//if(hundreds!=0)
	LCD_data( hundreds + 0x30);
	
	tens=(value%100)/10;
	//if(tens!=0)
	LCD_data( tens + 0x30);
	
	ones=value%10;
	//if(ones!=0)
	LCD_data( ones + 0x30);
	
}
/*
 for printing integers in form 1,23,15,6,7
 Mainly used for printing 0-9
 */
void lcd_printint_num(int value)
{

	unsigned char thousands,hundreds,tens,ones;
	
	thousands = value / 1000;
	if(thousands!=0)
	LCD_data(thousands + 0x30);

	hundreds = ((value - thousands*1000)-1) / 100;
	if(hundreds!=0)
	LCD_data( hundreds + 0x30);
	
	tens=(value%100)/10;
	if(tens!=0)
	LCD_data( tens + 0x30);
	
	ones=value%10;
	//if(ones!=0)
	LCD_data( ones + 0x30);
	
}	
/*
send string function
*/
void LCD_string(const char*str)
{
	int i;
	for(i=0;str[i]!=0;i++)
	{
		
		LCD_data(str[i]);
		_delay_us(45);
	}
}
void lcd_print1line(const char *buff)
{
	lcd_setcursor(0,0);
	LCD_string(buff);
}
void lcd_print2line(const char *buff)
{

	lcd_setcursor(0,1);
	LCD_string(buff);
}
void lcd_bit(unsigned char val)
{
	//lcd_setcursor(0,1);
	//_delay_us(40);
	int  ptr;
	for(ptr=7;ptr>=0;ptr--)
	{
		if ((val & (1<<ptr))==0)
		{
			LCD_string("0");
		}
		else
		{
			LCD_string("1");
		}
	}
}
	
	
	
	void LCD_init()
	{
		TWI_init_master();
		lcd_ioexander(0x00);
		_delay_ms(25);  // LCD Power ON delay always >15ms
		{
			LCD_command(lcd_4bit_2line); //Function set -->8-bit mode is selected,2lines
			_delay_ms(5);
			LCD_command(lcd_4bit_2line); //Function set -->8-bit mode is selected,2lines
			_delay_us(160);
			LCD_command(lcd_4bit_2line); //Function set -->8-bit mode is selected,2lines
		}
		LCD_command(lcd_4bit_2line); //Function set -->8-bit mode is selected,2lines
		_delay_us(45);
		LCD_command(lcd_DN_CN_BN); // Display ON/OFF control -->dispaly is on ,cursor is on and cursor blink is off
		_delay_ms(1);
		//lcd_clear();
		LCD_command(lcd_CML_DMF); // Entry mode set --> cursor moves to right and DRAM is incremented by 1 , shift of display is off
		_delay_us(40);
	}
int main(void)
{
	UART_Init0();
	//TWI_init_master();
	
	LCD_init();
	lcd_clear();

	//	LCD_string("Gettobyte");
	LCD_string("G");
		//lcd_setcursor(0,1);
	//	LCD_string("LCD_I2C");
	while (1) 
    {
		//	LCD_command(lcd_4bit_1line);
			
		LCD_string("k");
		_delay_ms(100);
		
    }
}

