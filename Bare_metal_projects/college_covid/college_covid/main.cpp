/*
 * college_covid.cpp
 *
 * Created: 08-03-2021 01:59:15
 * Author : kunal
 */ 

#include <avr/io.h>
#include "GB_lcd_i2c.h"
#include "GPIO.h"
#include "GB_dht11.h"

#define gb_Mode PB5  //11
#define gb_Arrow PB6 //12
#define gb_Menu_total_keys 2
uint8_t gb_Menu_key_switch = 0;
uint8_t gb_menu_key_value = 0;
int gb_keys[2] = {0};
	
	
void GB_menu_pin_setup()
{
	pinMode(gb_Mode,&DDRB,INPUT);
	digitalWrite(gb_Mode,&PORTB,HIGH);
	
	pinMode(gb_Arrow,&DDRB,INPUT);
	digitalWrite(gb_Arrow,&PORTB,HIGH);
}

void GB_timer2_init()
{
	// set up timer0 with prescaler = 256, MAx delay = 4.09 ms
	TCCR2B |= (1 << CS21);
	
	// initialize counter
	TCNT2 = 0;
	
	//enable overflow interrupt
	TIMSK2 |= (1 << TOIE2);
	
	//enable global interrupts
	sei();
	
	// initialize overflow counter variable of timer 0

}
void GB_menu_key_search()
{
	//keys[0] = 0,keys[1] = 0;
	switch(gb_Menu_key_switch)
	{
		case 0:
		{
			if(!(digitalRead(gb_Mode,&PINB)))
			{
				gb_keys[0]++;                      //Mode button
			}
			break;
		}
		case 1:
		{
			if(!(digitalRead(gb_Arrow,&PINB)))
			{
				gb_keys[1]++;                       //Arrow button
			}
			break;
		}
	}
	
	gb_Menu_key_switch++;
	if(gb_Menu_key_switch > gb_Menu_total_keys-1)
	gb_Menu_key_switch = 0;
	
}
 //uint8_t t = 0;
 
ISR(TIMER2_OVF_vect)
{
	// keep a track of number of overflows
	//tot_overflow++;
	PORTB ^= (1 << 7);    // toggles the led
	
	
	//TCNT1 = 0;
	GB_menu_key_search();
	
}

void GB_GetMenukeypressed()
{
	uint8_t gb_i;
	//menu_key_value = 0;
	//decimel0(menu_key_value);
	//printString0("z\n");
	for(gb_i =0; gb_i<gb_Menu_total_keys; gb_i++)
	{
		//decimel0(keys[i]);
		//printString0("p\n");
		
		if(gb_keys[gb_i] > 20)
		{
			gb_menu_key_value = gb_i+1;    // 1- mode menu, 2- arrow menu
			for (gb_i=0; gb_i<gb_Menu_total_keys; gb_i++)
			{	gb_keys[gb_i]=0;}
			//decimel0(menu_key_value);
			//printString0("k\n");
			break;
		}
	}
}

uint8_t gb_Menu_State = 0;
#define gb_Mode_button 1
#define gb_Arrow_button 2

#define  gb_Menu_state_idle 0
#define gb_Mode_menu 1
#define gb_Arrow_menu 2


uint8_t gb_cali_temp = 0;
uint8_t gb_ff_temp_to_cal = 0;

 uint8_t GB_menu()
 {
	 GB_lcd_setcursor(0,0);
	 GB_LCD_string("Temp Calibrat ");
	 GB_lcd_setcursor(0,1);
	// cali_temp = 0;
	 GB_lcd_printint_num(gb_ff_temp_to_cal);
	 
	 /*
	 LCD_string("screen1")
	 LCD_string("Rishabh   ");
	 lcd_setcursor(0,1);
	 LCD_string("Kunal   ");
	 return 1;
	 */
 }
 uint8_t GB_arrow()
 {
	 GB_lcd_setcursor(0,0);
	 GB_LCD_string("Gettobyte");
	 GB_lcd_setcursor(0,1);
	 GB_LCD_string("Sparrow");
	 return 1;
 }
  char gb_mystr[1]  = {0};
  float gb_t  = 0;
 void GB_ManageHome()
 {
	 
	 
	 GB_dht11();
	 
	 gb_t = GB_dht11_temp();
	 sprintf(gb_mystr,"%f",gb_t);
	 
	 GB_lcd_setcursor(0,0);
	 GB_LCD_string("Temper: ");
	 //lcd_printint_num(t);
	 GB_lcd_setcursor(0,1);
	 GB_LCD_string(gb_mystr);
	 
	 GB_lcd_setcursor(5,1);
	 GB_LCD_string("    ");
	 /*
	 //lcd_clear();
	 
	 dht11();
	// uint8_t t = dht11_temp();
	 lcd_setcursor(0,0);
	 LCD_string("Temper: ");
	 
	 lcd_printint_num(data[2]);
	 LCD_string(".");
	 lcd_printint_num(data[3]);
	 
	// lcd_printint_num(t);
	 
	 */
	 
 }
 uint8_t gb_arrow_flag = 0;
void GB_UInterface(void)
{
	//lcd_printint_num(menu_key_value);
	//_delay_ms(1);
	GB_GetMenukeypressed();
	//printString0("1\n");
	
	switch(gb_Menu_State)
	{
		case gb_Menu_state_idle:
		{
			//decimel0(Menu_State);
			//lcd_printint_num(menu_key_value);
			//printString0(" idle2\n");
		    //lcd_clear();
			GB_ManageHome();
			//lcd_printint_num(menu_key_value);
			if(gb_menu_key_value == gb_Mode_button)
			{
				gb_Menu_State = gb_Mode_menu;
				//beep sound function to be added
				GB_lcd_clear();
			}
			if(gb_menu_key_value == gb_Arrow_button)
			{
				gb_Menu_State = gb_Menu_state_idle;
				//beep sound function to be added
				//lcd_clear();
			}
			break;
		}
		case gb_Mode_menu:
		{
			//decimel0(Menu_State);
			//lcd_printint_num(menu_key_value);
			//printString0(" mode4\n");
			GB_menu();
			if((gb_menu_key_value == gb_Mode_button))     // enter OK
			{
				gb_ff_temp_to_cal = gb_cali_temp;        //to be used with fan PWM
				gb_Menu_State = gb_Menu_state_idle;
				// beep sound with longer delay
				GB_lcd_clear();
			}
			if((gb_menu_key_value == gb_Arrow_button))    //increment the number
			{
				gb_Menu_State = gb_Arrow_menu;
				gb_arrow_flag = 1;
				//beep function sound
			    //lcd_clear();
			}
			break;
		}
		case gb_Arrow_menu:
		{
			//decimel0(Menu_State);
			//lcd_printint_num(menu_key_value);
			//printString0(" arrow5\n");
				//if((arrow()))
				_delay_ms(1000);
			//	{}
				//lcd_printint_num(ff_temp_to_cal++);
				if(gb_arrow_flag == 1)
				{
					GB_lcd_setcursor(0,1);
				    gb_cali_temp = gb_cali_temp + 1;
				    GB_lcd_printint_num(gb_cali_temp);
					gb_Menu_State = gb_Arrow_menu;
					gb_arrow_flag = 0;
				}
				
				if((gb_menu_key_value == gb_Mode_button))
				{
					gb_ff_temp_to_cal = gb_cali_temp;
					gb_Menu_State = gb_Mode_menu;
					
				    GB_lcd_clear();
					//beep sound function
				}
				
				
				if ((gb_menu_key_value == gb_Arrow_button))
				{
					GB_lcd_setcursor(0,1);
					gb_cali_temp = gb_cali_temp + 1;
					GB_lcd_printint_num(gb_cali_temp);
					gb_Menu_State = gb_Arrow_menu;//lcd_clear();
				  //lcd_clear();
				}
				
				break;
		}
	//printString0("3\n");
	
      }
	  
	 // decimel0(Menu_State);
	 gb_menu_key_value = 0;
	  
}

int main(void)
{
	gb_keys[0] = 0,gb_keys[1] = 0;
	//DDRB |= (1 << 7);
	GB_timer2_init();
	GB_UART_Init0();
	GB_LCD_init();
	GB_lcd_clear();
	
	GB_LCD_string("Gettobyte:");
	GB_lcd_setcursor(0,1);
	GB_LCD_string("LCD_I2C");
	_delay_ms(1000);
    
	GB_menu_pin_setup();
	GB_lcd_clear();
    while (1) 
    {
		
		GB_UInterface();
		
		/*
		
		while(!(digitalRead(Arrow,&PINB)))
		{
			lcd_setcursor(0,0);
			LCD_string("Rishabh  ");
			lcd_setcursor(0,1);
			LCD_string("Kunal   ");
			
		}
		
	   while(!(digitalRead(Mode,&PINB)))
	   {
		   lcd_setcursor(0,0);
		   LCD_string("Gettobyte");
		   lcd_setcursor(0,1);
		   LCD_string("Sparrow");
	   }
	   
			*/
    }
}

