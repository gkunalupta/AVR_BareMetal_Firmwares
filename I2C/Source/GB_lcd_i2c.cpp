void GB_lcd_ioexander(unsigned char gb_Data)
{
	GB_TWI_start();
	GB_TWI_write_slave_address(gb_pcf8574_WADDR);
	GB_TWI_write_data(gb_Data | gb_LCD_BACKLIGHT);
	//TWI_write_data(Data);
	GB_TWI_stop();
}

void GB_pulse_enable( uint8_t gb_data)
{
	GB_lcd_ioexander(gb_data | gb_LCD_En);  //enable pulse high
	_delay_us(1);
	GB_lcd_ioexander(gb_data & ~gb_LCD_En); //enable pulse low
	_delay_us(50);
}

void GB_lcd_write4bit(unsigned char gb_nibble)
{
	gb_nibble |= (gb_LCD_Rs|gb_LCD_Rw);
	GB_lcd_ioexander(gb_nibble | 0x04);
	GB_lcd_ioexander(gb_nibble & 0xFB);
	_delay_ms(gb_display_rate);
}
/*
For command register: RS=0,RW=0

*/
void GB_LCD_command(unsigned char gb_command)
{ 
	gb_LCD_Rs = 0b00000000;
	gb_LCD_Rw = 0b00000000;
	uint8_t gb_highnib = gb_command & 0xf0;
	uint8_t gb_lownib = (gb_command<<4) & 0xf0;
	GB_lcd_write4bit(gb_highnib);
	GB_lcd_write4bit(gb_lownib);
}
void GB_lcd_setcursor(uint8_t gb_col, uint8_t gb_row)
{
	static uint8_t gb_offsets[] = {0x00,0x40,0x14,0x54 };
	//LCD_command(lcd_SETDDRAMADDR | (col + offsets[row]));
	GB_LCD_command((0x80|(gb_row<<6))+gb_col);
	_delay_us(40);
}
void GB_lcd_clear()
{
	GB_LCD_command(gb_lcd_clear_all); //clear display
	_delay_ms(20);
}
void GB_lcd_Rethome()
{
	GB_LCD_command(gb_lcd_rhome);
	_delay_ms(2);
}


/*
For Data Register: RS=1,RW=0
*/
void GB_LCD_data(unsigned char gb_data)
{
		gb_LCD_Rs = 0b00000001;
		gb_LCD_Rw = 0b00000000;
	uint8_t gb_highnib = gb_data & 0xf0;
	uint8_t gb_lownib = (gb_data<<4) & 0xf0;
	GB_lcd_write4bit(gb_highnib);
	GB_lcd_write4bit(gb_lownib);
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

	gb_hundreds = ((gb_value - gb_thousands*1000)) / 100;
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
 Mainly used for printing 0-9
 */
void GB_lcd_printint_num(int gb_value)
{

	unsigned char gb_thousands,gb_hundreds,gb_tens,gb_ones;
	
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
	
	
	
	void GB_LCD_init()
	{
		GB_TWI_init_master();
		_delay_us(100);
		GB_lcd_ioexander(0x00);
		//printString0("kunal\n");
		_delay_ms(25);  // LCD Power ON delay always >15ms
		{
			GB_LCD_command(gb_lcd_4bit_2line); //Function set -->8-bit mode is selected,2lines
			_delay_ms(5);
			GB_LCD_command(gb_lcd_4bit_2line); //Function set -->8-bit mode is selected,2lines
			_delay_us(160);
			GB_LCD_command(gb_lcd_4bit_2line); //Function set -->8-bit mode is selected,2lines
		}
		GB_LCD_command(gb_lcd_4bit_2line); //Function set -->8-bit mode is selected,2lines
		_delay_us(45);
		GB_LCD_command(gb_lcd_DN_CF_BF); // Display ON/OFF control -->dispaly is on ,cursor is on and cursor blink is off
		_delay_ms(1);
		//lcd_clear();
		GB_LCD_command(gb_lcd_CML_DMF); // Entry mode set --> cursor moves to right and DRAM is incremented by 1 , shift of display is off
		_delay_us(40);
		
		//printString0("gupta\n");
	}