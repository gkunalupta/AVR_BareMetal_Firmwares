void lcd_ioexander(unsigned char Data)
{
	TWI_start();
	TWI_write_slave_address(pcf8574_WADDR);
	TWI_write_data(Data | LCD_BACKLIGHT);
	//TWI_write_data(Data);
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
		_delay_us(100);
		lcd_ioexander(0x00);
		//printString0("kunal\n");
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
		LCD_command(lcd_DN_CF_BF); // Display ON/OFF control -->dispaly is on ,cursor is on and cursor blink is off
		_delay_ms(1);
		//lcd_clear();
		LCD_command(lcd_CML_DMF); // Entry mode set --> cursor moves to right and DRAM is incremented by 1 , shift of display is off
		_delay_us(40);
		
		//printString0("gupta\n");
	}