/*
 * college_covid.cpp
 *
 * Created: 08-03-2021 01:59:15
 * Author : kunal
 */ 

#include <avr/io.h>
#include "lcd_i2c.h"
#include "GPIO.h"
#include "dht11.h"

#define Mode PB5  //11
#define Arrow PB6 //12
#define Menu_total_keys 2
uint8_t Menu_key_switch = 0;
uint8_t menu_key_value = 0;
int keys[2] = {0};
	
	
void menu_pin_setup()
{
	pinMode(Mode,&DDRB,INPUT);
	digitalWrite(Mode,&PORTB,HIGH);
	
	pinMode(Arrow,&DDRB,INPUT);
	digitalWrite(Arrow,&PORTB,HIGH);
}

void timer2_init()
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
void menu_key_search()
{
	//keys[0] = 0,keys[1] = 0;
	switch(Menu_key_switch)
	{
		case 0:
		{
			if(!(digitalRead(Mode,&PINB)))
			{
				keys[0]++;                      //Mode button
			}
			break;
		}
		case 1:
		{
			if(!(digitalRead(Arrow,&PINB)))
			{
				keys[1]++;                       //Arrow button
			}
			break;
		}
	}
	
	Menu_key_switch++;
	if(Menu_key_switch > Menu_total_keys-1)
	Menu_key_switch = 0;
	
}
 //uint8_t t = 0;
 
ISR(TIMER2_OVF_vect)
{
	// keep a track of number of overflows
	//tot_overflow++;
	PORTB ^= (1 << 7);    // toggles the led
	
	
	//TCNT1 = 0;
	menu_key_search();
	
}

void GetMenukeypressed()
{
	uint8_t i;
	//menu_key_value = 0;
	//decimel0(menu_key_value);
	//printString0("z\n");
	for(i =0; i<Menu_total_keys; i++)
	{
		//decimel0(keys[i]);
		//printString0("p\n");
		
		if(keys[i] > 20)
		{
			menu_key_value = i+1;    // 1- mode menu, 2- arrow menu
			for (i=0; i<Menu_total_keys; i++)
			{	keys[i]=0;}
			//decimel0(menu_key_value);
			//printString0("k\n");
			break;
		}
	}
}

uint8_t Menu_State = 0;
#define Mode_button 1
#define Arrow_button 2

#define  Menu_state_idle 0
#define Mode_menu 1
#define Arrow_menu 2


uint8_t cali_temp = 0;
uint8_t ff_temp_to_cal = 0;

 uint8_t menu()
 {
	 lcd_setcursor(0,0);
	 LCD_string("Temp Calibrat ");
	 lcd_setcursor(0,1);
	// cali_temp = 0;
	 lcd_printint_num(ff_temp_to_cal);
	 
	 /*
	 LCD_string("screen1")
	 LCD_string("Rishabh   ");
	 lcd_setcursor(0,1);
	 LCD_string("Kunal   ");
	 return 1;
	 */
 }
 uint8_t arrow()
 {
	 lcd_setcursor(0,0);
	 LCD_string("Gettobyte");
	 lcd_setcursor(0,1);
	 LCD_string("Sparrow");
	 return 1;
 }
  char mystr[1]  = {0};
  float t  = 0;
 void ManageHome()
 {
	 
	 
	 dht11();
	 
	 t = dht11_temp();
	 sprintf(mystr,"%f",t);
	 
	 lcd_setcursor(0,0);
	 LCD_string("Temper: ");
	 //lcd_printint_num(t);
	 lcd_setcursor(0,1);
	 LCD_string(mystr);
	 
	 lcd_setcursor(5,1);
	 LCD_string("    ");
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
 uint8_t arrow_flag = 0;
void UInterface(void)
{
	//lcd_printint_num(menu_key_value);
	//_delay_ms(1);
	GetMenukeypressed();
	//printString0("1\n");
	
	switch(Menu_State)
	{
		case Menu_state_idle:
		{
			//decimel0(Menu_State);
			//lcd_printint_num(menu_key_value);
			//printString0(" idle2\n");
		    //lcd_clear();
			ManageHome();
			//lcd_printint_num(menu_key_value);
			if(menu_key_value == Mode_button)
			{
				Menu_State = Mode_menu;
				//beep sound function to be added
				lcd_clear();
			}
			if(menu_key_value == Arrow_button)
			{
				Menu_State = Menu_state_idle;
				//beep sound function to be added
				//lcd_clear();
			}
			break;
		}
		case Mode_menu:
		{
			//decimel0(Menu_State);
			//lcd_printint_num(menu_key_value);
			//printString0(" mode4\n");
			menu();
			if((menu_key_value == Mode_button))     // enter OK
			{
				ff_temp_to_cal = cali_temp;        //to be used with fan PWM
				Menu_State = Menu_state_idle;
				// beep sound with longer delay
				lcd_clear();
			}
			if((menu_key_value == Arrow_button))    //increment the number
			{
				Menu_State = Arrow_menu;
				arrow_flag = 1;
				//beep function sound
			    //lcd_clear();
			}
			break;
		}
		case Arrow_menu:
		{
			//decimel0(Menu_State);
			//lcd_printint_num(menu_key_value);
			//printString0(" arrow5\n");
				//if((arrow()))
				_delay_ms(1000);
			//	{}
				//lcd_printint_num(ff_temp_to_cal++);
				if(arrow_flag == 1)
				{
					lcd_setcursor(0,1);
				    cali_temp = cali_temp + 1;
				    lcd_printint_num(cali_temp);
					Menu_State = Arrow_menu;
					arrow_flag = 0;
				}
				
				if((menu_key_value == Mode_button))
				{
					ff_temp_to_cal = cali_temp;
					Menu_State = Mode_menu;
					
				    lcd_clear();
					//beep sound function
				}
				
				
				if ((menu_key_value == Arrow_button))
				{
					lcd_setcursor(0,1);
					cali_temp = cali_temp + 1;
					lcd_printint_num(cali_temp);
					Menu_State = Arrow_menu;//lcd_clear();
				  //lcd_clear();
				}
				
				break;
		}
	//printString0("3\n");
	
      }
	  
	 // decimel0(Menu_State);
	 menu_key_value = 0;
	  
}

int main(void)
{
	keys[0] = 0,keys[1] = 0;
	//DDRB |= (1 << 7);
	timer2_init();
	UART_Init0();
	LCD_init();
	lcd_clear();
	
	LCD_string("Gettobyte:");
	lcd_setcursor(0,1);
	LCD_string("LCD_I2C");
	_delay_ms(1000);
    
	menu_pin_setup();
	lcd_clear();
    while (1) 
    {
		
		UInterface();
		
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

