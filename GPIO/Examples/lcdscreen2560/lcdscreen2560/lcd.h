/*
 * lcdscreen.cpp
 *
 * Created: 08-07-2020 20:09:19
 * Author : kunal
 */ 
/*
ST7066U: has two Registers Instruction Register(IR) & Data Register(DR)
If RS = 1 DR is selected
   RS = 0 IR is selected
When Instruction Register is selected we send Commands for setting up the LCD
When Data Register is selected we send Data for printing on the LCD

R/W pins : configures when to Read/Write
R/W = 1 Read
R/W = 0 Write
Before writing any Command or data Busy Flag should be checked.


Enable Pin: is used for Starting Read or Write Operation
After equating values to Data pins of LCD , Enable pin 
should be toggled from High to low for data/command execution.
if Enable pulse is not their then no command/data will be executed 
Thus Lcd_wait is used in lcd_command() and lcd_data()

The chip has two kind of interface 8 bit or 4-bit:
If 8 bit mode has to be used then all D0-7 pins are used
if 4 bit moder is used then D4-D7 pins is used in which first 4 high bits(D7-4) are send 
followed by last 4 bits(D0-D3)

*/

#include <avr/io.h>
#include <stdlib.h>
#include <util/delay.h>

                            // for atmega 2560
 //RW                 Digital pin - 12(PB6)  
 //RS                 Digital pin - 13(PB7)
 //Enable             Digital pin - 11(PB5)
                                              
#define LCD_command_dir DDRB        // --> sets the output and input for commands registers
#define LCD_command_port PORTB     // --> sets the high low of pins
                                                       

//for atmega 2560
#define LCD_data_dir DDRL           // data pins 0-7 (PD0:7-D0:7)--> sets the output or input for data pins
#define LCD_data_port PORTL        // data pins 0-7 (PD0:7-D0:7)--> sets the high low for data pins that is data to be send  is passed to this constant
#define LCD_PIN PINL

#define debug false
#define RW 6     // Define Read(1)/Write(0) signal pin 
#define RS 7       //Define Register Select (data(1)/command reg(0))pin 
#define EN 5        // Define Enable signal pin: Set to 1 for final execution of data/command to d0-7 pins

                  // for atmega 2560                
#define LCD_D0 0  //  Digital pin - 49(PL0)
#define LCD_D1 1  //  Digital pin - 48(PL1)
#define LCD_D2 2  //  Digital pin - 47(PL2)
#define LCD_D3 3  //  Digital pin - 46(PL3)
#define LCD_D4 4  //  Digital pin - 45(PL4)                
#define LCD_D5 5  //  Digital pin - 44(PL5)                
#define LCD_D6 6  //  Digital pin - 43(PL6)                
#define LCD_D7 7  //  Digital pin - 42(PL7)                



#define SET_BIT(byte, bit) ((byte) |= (1UL << (bit)))
#define CLEAR_BIT(byte,bit) ((byte) &= ~(1UL << (bit)))
#define IS_SET(byte,bit) (((byte) & (1UL << (bit))) >> (bit))
int c=0; 
//Function Set
//Rs RW DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
// 0 0  0    0   1   DL  N   F   -   -
// 8bit (DL=1) , 4bit (DL=0)
// 1line (N=0) , 2line (N-1)
#define lcd_8bit_1line 0b00110000
#define lcd_8bit_2line 0b00111000
#define lcd_4bit_1line 0b00100000
#define lcd_4bit_2line 0b00101000
#define lcd_8bit_1line_11 0b00110100
#define lcd_8bit_2line_11 0b00111100
#define lcd_4bit_1line_11 0b00100100
#define lcd_4bit_2line_11 0b00101100
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
//CML -cursor move left(I/D=0) , DMR - display move is performed:right(S/H=1)
//DML- display move is performed: left(S/H=1)
#define lcd_CMR_DMF 0b00000110
#define lcd_CML_DMF 0b00000100
#define lcd_CMR_DMR 0b00000111
#define lcd_CML_DML 0b00000101

#define lcd_clear_all 0b00000001
#define lcd_rhome     0b00000010
#define lcd_SETDDRAMADDR 0x80
#define lcd_SETCGRAMADDR 0x40

uint8_t address_counter=0; // Variable to store Address counter and Busy Flag(7th bit) Status
/*
Enable pin: Starts Read/Write Operation
Enable pin is Toggled from high to low for final execution of command/data
Enable Rise/Fall time: will be determined by one Machine Cycle
Enable Pulse width : Will be determined by amount of delay
if to change the speed for displaying  characters of a string then 
change second delay(lower the value: fast it print)
                    (Higher the value: Slower it prints)
*/
void lcd_enable_pulse();
/*
8-bit mode writing function 
Writes data to be send to 8 pins of LCD , by sending Data signals to
GPIO pins of MCU(which are connected to LCd data pins)
So GPIO pins are set as OUTPUT and then value is equated to them
Then for final execution Enable pulse is send
if enable pulse is not send then data/command will not be executed
*/
void lcd_write8bit(uint8_t value);
/*
4-bit mode writing function
Writes data to be send to 4 pins of LCD , by sending Data signals to
GPIO pins of MCU(which are connected to LCd data pins)
So GPIO pins are set as OUTPUT and then value is equated to them 
first HIGHER 4 bits are send , then Followed by LOWER 4 bits
Then for final execution Enable pulse is send
if enable pulse is not send then data/command will not be executed
*/
void lcd_write4bit(uint8_t value);
/*
Read Busy flag/address:
After execution of Command , it has to be checked that whether internal operation
(execution of command is completed or not).
It is done by reading BF flag.
By setting RS =0, and R/W = 1: Busy flag and Address of command being executing can be read
Thus data pins of LCD are set as Input For this stage and 8 bit data 
is stored in Variable by reading PIN value of Data port
BF Flag output is given at &the bit
Enable pulse is Important
*/
uint8_t read_BF_adress();
/*
LCD_wait():
Reads the address counter (which contains the busy flag) and loops until
the busy flag is cleared.
BF=1(Internal operation is happening), BF=0(Internal Operation is completed)
by the end of lcd_wait function : 
R/W will be 1, RS will be 0 and data ports will be input
*/
int LCD_wait(void);
/*
Command Write function:
RS = 0 for selecting Instruction Register
R/W = 0 for writing data
clear display, display on/off, cursor blink , 
scroll of text , cursor/display shift all such features are set by 
Selecting Instruction Register.
*/

void LCD_command(uint8_t cmnd);
void lcd_clear();
void lcd_Rethome();
void lcd_setcursor(uint8_t col, uint8_t row);
void LCD_init();

/* Data write function 
--> send dat to be printed to data pins  -  data_port
--> make the RS pin set to 1 so that HD44780 comes 
to know that data register is being used
-->Set RW pin to low 0 to write to LCD
-->EN pin is set to 1 for finaly execution of command and then some
 delay and then again set pin to 0.
 */
void LCD_data(uint8_t data);
/*
 for printing integers in form 001,023,015,006,007
 */
void lcd_printint(int value);
/* 
for printing integers in form 1,23,15,6,7
*/
void lcd_printint_num(int value);
/* 
send string function
*/
void LCD_string(const char*str);
/*
This function is for sending custom made
characters to address of CGRAM(0x40-0x7F)

Each custom character need 8 CGRAM location
so only 8 custom characters can be made each character
occupying 8 address location of CGRAM.

So at these locations Custom Characters are stored:
(0x40,0x48,0x50,0x58,0x60,0x68,0x70,0x78).

Before storing custom characters to these location,
we have to SET CGRAM address to any of these:
(0x40,0x48,0x50,0x58,0x60,0x68,0x70,0x78).That is done by command
setramaddr((lcd_SETCGRAMADDR)) in the main function
*/
void LCD_sendpattern(uint8_t pattern[]);
void lcd_print1line(const char *buff);
void lcd_print2line(const char *buff);
void lcd_bit(unsigned char val);

uint8_t Heart[8] = {
	0b00000,
	0b01010,
	0b11111,
	0b11111,
	0b01110,
	0b00100,
	0b00000,
	0b00000
};

uint8_t Bell[8] = {
	0b00100,
	0b01110,
	0b01110,
	0b01110,
	0b11111,
	0b00000,
	0b00100,
	0b00000
};


uint8_t Alien[8] = {
	0b11111,
	0b10101,
	0b11111,
	0b11111,
	0b01110,
	0b01010,
	0b11011,
	0b00000
};

uint8_t Check[8] = {
	0b00000,
	0b00001,
	0b00011,
	0b10110,
	0b11100,
	0b01000,
	0b00000,
	0b00000
};

uint8_t Speaker[8] = {
	0b00001,
	0b00011,
	0b01111,
	0b01111,
	0b01111,
	0b00011,
	0b00001,
	0b00000
};


uint8_t Sound[8] = {
	0b00001,
	0b00011,
	0b00101,
	0b01001,
	0b01001,
	0b01011,
	0b11011,
	0b11000
};


uint8_t Skull[8] = {
	0b00000,
	0b01110,
	0b10101,
	0b11011,
	0b01110,
	0b01110,
	0b00000,
	0b00000
};

uint8_t Lock[8] = {
	0b01110,
	0b10001,
	0b10001,
	0b11111,
	0b11011,
	0b11011,
	0b11111,
	0b00000
};
#include "lcd.cpp"

