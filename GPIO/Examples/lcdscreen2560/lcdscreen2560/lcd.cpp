/*
Enable pin: Starts Read/Write Operation
Enable pin is Toggled from high to low for final execution of command/data
Enable Rise/Fall time: will be determined by one Machine Cycle
Enable Pulse width : Will be determined by amount of delay
if to change the speed for displaying  characters of a string then 
change second delay(lower the value: fast it print)
                    (Higher the value: Slower it prints)
*/
void lcd_enable_pulse()
{
	LCD_command_port |= (1<<EN);
	_delay_ms(1);
	LCD_command_port &= ~(1<<EN);
	_delay_ms(1); // change this to vary the speed for printing characters of a string
}
/*
8-bit mode writing function 
Writes data to be send to 8 pins of LCD , by sending Data signals to
GPIO pins of MCU(which are connected to LCd data pins)
So GPIO pins are set as OUTPUT and then value is equated to them
Then for final execution Enable pulse is send
if enable pulse is not send then data/command will not be executed
*/
void lcd_write8bit(uint8_t value)
{   
    LCD_data_dir |=(1<<LCD_D0)|(1<<LCD_D1)|(1<<LCD_D2)|(1<<LCD_D3)|(1<<LCD_D4)|(1<<LCD_D5)|(1<<LCD_D6)|(1<<LCD_D7);    // Data pins of MCU(Which are connected to LCD) are set as output 
	LCD_data_port = (value&0b11111111);
	lcd_enable_pulse();
}
/*
4-bit mode writing function
Writes data to be send to 4 pins of LCD , by sending Data signals to
GPIO pins of MCU(which are connected to LCd data pins)
So GPIO pins are set as OUTPUT and then value is equated to them 
first HIGHER 4 bits are send , then Followed by LOWER 4 bits
Then for final execution Enable pulse is send
if enable pulse is not send then data/command will not be executed
*/
void lcd_write4bit(uint8_t value)
{
	LCD_data_dir |= (1<<LCD_D4)|(1<<LCD_D5)|(1<<LCD_D6)|(1<<LCD_D7);    // Data pins of MCU(Which are connected to lcd) are set as output
	LCD_data_port = (value&0b11110000);    // Sending Higher 4 bits(D7,D6,D5,D4) first
	lcd_enable_pulse();
	LCD_data_port = ((value&0b00001111)<<4);    //Sending LOWER 4 bits(D3,D2,D1,D0)
	lcd_enable_pulse();
}
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
uint8_t read_BF_adress()
{  
	LCD_data_dir = 0x00;  //  data pins input
	LCD_command_port &= ~(1<<RS);
	LCD_command_port |= (1<<RW);
	LCD_command_port |= (1<<EN);
	_delay_ms(1);
	address_counter = LCD_PIN;
	LCD_command_port &= ~(1<<EN);
	_delay_ms(1);
	return address_counter;
}
/*
LCD_wait():
Reads the address counter (which contains the busy flag) and loops until
the busy flag is cleared.
BF=1(Internal operation is happening), BF=0(Internal Operation is completed)
by the end of lcd_wait function : 
R/W will be 1, RS will be 0 and data ports will be input
*/
int LCD_wait(void)
{
	//get address and busy flag
	//and loop until busy flag (bit7) cleared
	while((read_BF_adress() & 0x80) == 0x80);
	return 1;
	
}
/*
Command Write function:
RS = 0 for selecting Instruction Register
R/W = 0 for writing data
clear display, display on/off, cursor blink , 
scroll of text , cursor/display shift all such features are set by 
Selecting Instruction Register.
*/
void LCD_command(uint8_t cmnd)
{   
	
	 if(LCD_wait())
	 {
	LCD_command_port &= ~(1<<RS);
	LCD_command_port &= ~(1<<RW);
	lcd_write8bit(cmnd);            //this function takes care of enable pulse also
	 }
	 else
	 {
		 bit0(address_counter);
		 printString0("\n");
		 
	 }
}
void lcd_clear()
{
	LCD_command(lcd_clear_all); //clear display
	_delay_ms(2);
}
void lcd_Rethome()
{
	LCD_command(lcd_rhome);
	_delay_ms(2);
}
void lcd_setcursor(uint8_t col, uint8_t row)
{
	LCD_command((0x80|(row<<6))+col);
	_delay_us(40);
}
void LCD_init()
{
	LCD_command_dir |= (1<<RS)|(1<<RW)|(1<<EN); //  command pins of LCD will be controlled by Avr digital pins , so digitals pins will be set high or low thus these pins are set as output.
	
	_delay_ms(50);  // LCD Power ON delay always >15ms
	{
		LCD_command(lcd_8bit_2line); //Function set -->8-bit mode is selected,2lines
		_delay_us(50);
		LCD_command(lcd_8bit_2line); //Function set -->8-bit mode is selected,2lines
		_delay_us(50);
	}
	LCD_command(lcd_DN_CF_BF); // Display ON/OFF control -->dispaly is on ,cursor is on and cursor blink is off
	_delay_us(45);
	LCD_command(lcd_CMR_DMF); // Entry mode set --> cursor moves to right and DRAM is incremented by 1 , shift of display is off
	_delay_us(45);
	lcd_clear();
	_delay_ms(5);
}

void setramaddr(uint8_t address)
{
	LCD_command(address);
	_delay_us(50);
	
}
/* Data write function 
--> send dat to be printed to data pins  -  data_port
--> make the RS pin set to 1 so that HD44780 comes 
to know that data register is being used
-->Set RW pin to low 0 to write to LCD
-->EN pin is set to 1 for finaly execution of command and then some
 delay and then again set pin to 0.
 */
void LCD_data(uint8_t data)
{   
	LCD_command_port |= (1<<RS);
	LCD_command_port &= ~(1<<RW);
	lcd_write8bit(data);           //this function takes care of enable pulse also
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

		hundreds = ((value - thousands*1000)-1) / 100;
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
void LCD_sendpattern(uint8_t loc,  uint8_t pattern[])
{
	int i;
	if(loc<8)
	{
	setramaddr((lcd_SETCGRAMADDR+(loc*8)));
	for(i=0;i<8;i++)
	LCD_data(pattern[i]);
		//_delay_us(45);
	}
}
void LCD_printpattern(uint8_t loc)
{
	
	LCD_data((0x00+loc));
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
uint8_t ReadDDRAM()
{
	uint8_t data;
	//LCD_data_dir = 0x00;
	LCD_command_port |= (1<<RS);
	LCD_command_port |= (1<<RW);
	data = LCD_PIN;
	//lcd_enable_pulse();
	return data;
}