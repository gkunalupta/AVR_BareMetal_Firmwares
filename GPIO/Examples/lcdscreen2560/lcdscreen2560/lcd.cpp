/*
Enable pin: Starts Read/Write Operation
Enable pin is Toggled from high to low for final execution of command/data
Enable Rise/Fall time: will be determined by one Machine Cycle
Enable Pulse width : Will be determined by amount of delay
if to change the speed for displaying  characters of a string then 
change second delay(lower the value: fast it print)
                    (Higher the value: Slower it prints)
*/
void GB_lcd_enable_pulse()
{
	LCD_command_port |= (1<<gb_LCD_EN);
	_delay_ms(1);
	LCD_command_port &= ~(1<<gb_LCD_EN);
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
void GB_lcd_write8bit(uint8_t gb_value)
{   
    gb_LCD_data_dir |=(1<<gb_LCD_D0)|(1<<gb_LCD_D1)|(1<<gb_LCD_D2)|(1<<gb_LCD_D3)|(1<<gb_LCD_D4)|(1<<gb_LCD_D5)|(1<<gb_LCD_D6)|(1<<gb_LCD_D7);    // Data pins of MCU(Which are connected to LCD) are set as output 
	gb_LCD_data_port = (gb_value&0b11111111);
	GB_lcd_enable_pulse();
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
void GB_lcd_write4bit(uint8_t gb_value)
{
	gb_LCD_data_dir |= (1<<gb_LCD_D4)|(1<<gb_LCD_D5)|(1<<gb_LCD_D6)|(1<<gb_LCD_D7);    // Data pins of MCU(Which are connected to lcd) are set as output
	gb_LCD_data_port = (value&0b11110000);    // Sending Higher 4 bits(D7,D6,D5,D4) first
	GB_lcd_enable_pulse();
	gb_LCD_data_port = ((value&0b00001111)<<4);    //Sending LOWER 4 bits(D3,D2,D1,D0)
	GB_lcd_enable_pulse();
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
uint8_t GB_read_BF_adress()
{  
	gb_LCD_data_dir = 0x00;  //  data pins input
	gb_LCD_command_port &= ~(1<<gb_LCD_RS);
	gb_LCD_command_port |= (1<<gb_LCD_RW);
	gb_LCD_command_port |= (1<<gb_LCD_EN);
	_delay_ms(1);
	gb_address_counter = gb_LCD_PIN;
	gb_LCD_command_port &= ~(1<<gb_LCD_EN);
	_delay_ms(1);
	return gb_address_counter;
}
/*
LCD_wait():
Reads the address counter (which contains the busy flag) and loops until
the busy flag is cleared.
BF=1(Internal operation is happening), BF=0(Internal Operation is completed)
by the end of lcd_wait function : 
R/W will be 1, RS will be 0 and data ports will be input
*/
int GB_LCD_wait(void)
{
	//get address and busy flag
	//and loop until busy flag (bit7) cleared
	while((GB_read_BF_adress() & 0x80) == 0x80);
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
void GB_LCD_command(uint8_t gb_cmnd)
{   
	
	 if(GB_LCD_wait())
	 {
	gb_LCD_command_port &= ~(1<<gb_LCD_RS);
	gb_LCD_command_port &= ~(1<<gb_LCD_RW);
	GB_lcd_write8bit(gb_cmnd);            //this function takes care of enable pulse also
	 }
	 else
	 {
		 GB_bit0(gb_address_counter);
		 GB_printString0("\n");
		 
	 }
}
void GB_lcd_clear()
{
	GB_LCD_command(gb_lcd_clear_all); //clear display
	_delay_ms(2);
}
void GB_lcd_Rethome()
{
	GB_LCD_command(gb_lcd_rhome);
	_delay_ms(2);
}
void GB_lcd_setcursor(uint8_t gb_col, uint8_t gb_row)
{
	GB_LCD_command((0x80|(gb_row<<6))+gb_col);
	_delay_us(40);
}
void GB_LCD_init()
{
	gb_LCD_command_dir |= (1<<gb_LCD_RS)|(1<<gb_LCD_RW)|(1<<gb_LCD_EN); //  command pins of LCD will be controlled by Avr digital pins , so digitals pins will be set high or low thus these pins are set as output.
	
	_delay_ms(50);  // LCD Power ON delay always >15ms
	{
		GB_LCD_command(gb_lcd_8bit_2line); //Function set -->8-bit mode is selected,2lines
		_delay_us(50);
		GB_LCD_command(gb_lcd_8bit_2line); //Function set -->8-bit mode is selected,2lines
		_delay_us(50);
	}
	GB_LCD_command(gb_lcd_DN_CF_BF); // Display ON/OFF control -->dispaly is on ,cursor is on and cursor blink is off
	_delay_us(45);
	GB_LCD_command(gb_lcd_CMR_DMF); // Entry mode set --> cursor moves to right and DRAM is incremented by 1 , shift of display is off
	_delay_us(45);
	GB_lcd_clear();
	_delay_ms(5);
}

void GB_setramaddr(uint8_t gb_address)
{
	GB_LCD_command(gb_address);
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
void GB_LCD_data(uint8_t gb_data)
{   
	gb_LCD_command_port |= (1<<gb_LCD_RS);
	gb_LCD_command_port &= ~(1<<gb_LCD_RW);
	GB_lcd_write8bit(gb_data);           //this function takes care of enable pulse also
}
/* 
for printing integers in form 001,023,015,006,007
*/
void GB_lcd_printint(int gb_value)
{

		unsigned char gb_thousands,gb_hundreds,gb_tens,gb_ones;
		
		gb_thousands = gb_value / 1000;
        if(gb_thousands!=0)
		GB_LCD_data(gb_thousands + 0x30);

		gb_hundreds = ((gb_value - gb_thousands*1000)-1) / 100;
        //if(hundreds!=0)
		GB_LCD_data( gb_hundreds + 0x30);
		
		gb_tens=(gb_value%100)/10;
        //if(tens!=0)
		GB_LCD_data( gb_tens + 0x30);
		
		gb_ones=gb_value%10;
        //if(ones!=0)
		GB_LCD_data( gb_ones + 0x30);
	
}
/*
 for printing integers in form 1,23,15,6,7
 */
void GB_lcd_printint_num(int gb_value)
{

	unsigned char gb_thousands,gb_hundreds,gb_tensgb_,ones;
	
	gb_thousands = gb_value / 1000;
	if(gb_thousands!=0)
	GB_LCD_data(gb_thousands + 0x30);

	gb_hundreds = ((gb_value - gb_thousands*1000)-1) / 100;
	if(gb_hundreds!=0)
	GB_LCD_data( gb_hundreds + 0x30);
	
	gb_tens=(gb_value%100)/10;
	if(gb_tens!=0)
	GB_LCD_data( gb_tens + 0x30);
	
	gb_ones=gb_value%10;
	//if(ones!=0)
	GB_LCD_data( gb_ones + 0x30);
	
}
/* 
send string function
*/
void GB_LCD_string(const char*gb_str)
{
	int gb_i;
	for(gb_i=0;gb_str[gb_i]!=0;gb_i++)
	{
		
		GB_LCD_data(gb_str[gb_i]);
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
void GB_LCD_sendpattern(uint8_t gb_loc,  uint8_t gb_pattern[])
{
	int gb_i;
	if(gb_loc<8)
	{
	GB_setramaddr((gb_lcd_SETCGRAMADDR+(gb_loc*8)));
	for(gb_i=0;gb_i<8;gb_i++)
	GB_LCD_data(gb_pattern[gb_i]);
		//_delay_us(45);
	}
}
void GB_LCD_printpattern(uint8_t gb_loc)
{
	
	GB_LCD_data((0x00+gb_loc));
}
void GB_lcd_print1line(const char *gb_buff)
{
	GB_lcd_setcursor(0,0);
	GB_LCD_string(gb_buff);
}
void GB_lcd_print2line(const char *gb_buff)
{

	GB_lcd_setcursor(0,1);
	GB_LCD_string(gb_buff);
}
void GB_lcd_bit(unsigned char gb_val)
{
	//lcd_setcursor(0,1);
	//_delay_us(40);
	int  gb_ptr;
	for(gb_ptr=7;gb_ptr>=0;gb_ptr--)
	{
		if ((gb_val & (1<<gb_ptr))==0)
		{
			GB_LCD_string("0");
		}
		else
		{
			GB_LCD_string("1");
		}
	}
}
uint8_t GB_ReadDDRAM()
{
	uint8_t gb_data;
	//LCD_data_dir = 0x00;
	gb_LCD_command_port |= (1<<gb_LCD_RS);
	gb_LCD_command_port |= (1<<gb_LCD_RW);
	gb_data = gb_LCD_PIN;
	//lcd_enable_pulse();
	return gb_data;
}