/*
 * Servo_keypad_lcd.cpp
 *
 * Created: 09-11-2020 12:13:38
 * Author : kunal
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "uarts.h"
#include "stdlib.h"
#include "lcd.h"

/*
R1 : PC0(37)
R2 : PC1(36)
R3 : PC2(35)
R4 : PC3(34)
C1 : PC4(33)
C2 : PC5(32)
C3 : PC6(31)
*/

#define R1 0
#define R2 1
#define R3 2
#define R4 3
#define C1 4
#define C2 5
#define C3 6

 uint8_t getkey()
 {
	  uint8_t keypressed=0;
	  
	  DDRC = 0b00001111;           // Column as input (PC6,PC5,PC4 th bit ) : set as 0(C3,C2,C1)
	                               // Row as output (PC3,PC2,PC1,PC0 th bit ) : set as 1(R4,R3,R2,R1)
	  _delay_ms(1);
	  PORTC = 0b11110000;          // Column pins:Input pins pull up resistor is activated by setting 1 to PORTC column pins
	                               //Row pins: Output pins are set to Low(0)
	  _delay_ms(1);
	  
	  
	  while(PINC == 0b11110000);    // If any button will be pressed then either of the PC6,PC5,PC4th bit (C3,C2,C1) will be made to 0 , hence
	                                // it will come out of while loop
	                                // if C1 is pressed : 11100000
	                                // if C2 is pressed : 11010000
	                                // if C3 is pressed : 10110000
	                                
									
	  keypressed = PINC;           //Stores the Value of which column is pressed in keypressed variable
	  
	  DDRC = 0b01110000;           //Columns as output(PC6,PC5,PC4 th bit): set as 1(C3,C2,C1)
	                               //Row as input(PC3,PC2,PC1,PC0 th bit) : set as 0(R4,R3,R2,R1)
	  _delay_ms(1);
	  PORTC = 0b10001111;          // Column pins:Output pins are set to Low(0)
	                              //Row pins: Input pins pull up resistor is activated by setting 1 to PORTC column pins
	  _delay_ms(1);
                                   //Now on setting Row as input and column as output : PINC will give 10001111 value(when no key is pressed)
                                   // if R1 is pressed --> 10001110
                                   // if R2 is pressed --> 10001101
                                   // if R3 is pressed --> 10001011
                                   // if R4 is pressed --> 10000111
	  
	  keypressed |= PINC;          // ORing the value of ROW and Column pressed when they are set as input respectively
	  
	 // bit0(keypressed);
	  printString0("\n");

	  switch (keypressed)
	  {
		 case(0b11101110):  //decimel0(1);               //C1:   11100000
		                                                 //R1: | 10001110
		                    //printString0(": ");
							return('1');
							break;
							 
		 case(0b11011110):  //decimel0(2);               //C2:   11010000
		                                                 //R1: | 10001110
		                    //printString0(": ");
		                    return('2');
		                    break;
		 
		 case(0b10111110):  //decimel0(3);               //C3:   10110000
		                    //printString0(": ");        //R1: | 10001110
		                    return('3');
							break;
							
		 case(0b11101101):  //decimel0(4);               //C1:   11100000
		                    //printString0(": ");        //R2: | 10001101
		                    return('4');
							break;
							
		 case(0b11011101):  //decimel0(5);               //C2:   11010000
		  		            //printString0(": ");        //R2: | 10001101
							 return('5'); 
							break;
							
		  case(0b10111101): //decimel0(6);              //C3:   10110000
		                    //printString0(": ");      //R2:  | 10001101
							return('6');
							break;
							
		  case(0b11101011):// decimel0(7);              //C1:   11100000
		                    //printString0(": ");       //R3: | 10001011
							return('7');
							break;
							
		  case(0b11011011): //decimel0(8);              //C2:   11010000
		                    //printString0(": ");       //R3: | 10001011
							return('8');
							break;
							
		  case(0b10111011): //decimel0(9);             //C3:   10110000
		                    //printString0(": ");      //R3: | 10001011
							return('9');
							break;
							
		  case(0b11100111):// UART_TxChar0('*');       //C1:   11100000
		                    //printString0(": ");      //R4: | 10000111
							return('*');
							break;
						
		  case(0b11010111): //decimel0(0);             //C2:   11010000
		                   // printString0(": ");      //R4: | 10000111
		                   return('0');
							break;
							
		  case(0b10110111):  //UART_TxChar0('#');       //C3:   10110000
		                     //printString0(": ");      //R4: | 10000111
							 return('#');
							 break;
							 
	  }
	 
	
     _delay_ms(100);
}
bool flag = 0;
//char a=0;
 uint8_t getKey()
 {
	 uint8_t keypressed = 0;
	 uint8_t colomn_input = 0;
	 char a=0;
	 

	 
	 
      STAT:DDRC = 0b00001111;           // Column as input (PC6,PC5,PC4 th bit ) : set as 0(C3,C2,C1)
	                                    // Row as output (PC3,PC2,PC1,PC0 th bit ) : set as 1(R4,R3,R2,R1)
	 _delay_ms(1);
	 PORTC = 0b11110000;               // Column pins:Input pins pull up resistor is activated by setting 1 to PORTC column pins
	                                   //Row pins: Output pins are set to Low(0)
	 _delay_ms(1);
	 
	 colomn_input = PINC;
	 

	 
	 if((colomn_input!= 0b11110000) & (flag == 1))    // If any button will be pressed then either of the PC6,PC5,PC4th bit (C3,C2,C1) will be made to 0 , hence
	      { 
			   colomn_input = PINC;
			   keypressed = PINC; 
			   DDRC = 0b01110000;           //Columns as output(PC6,PC5,PC4 th bit): set as 1(C3,C2,C1)
	                                        //Row as input(PC3,PC2,PC1,PC0 th bit) : set as 0(R4,R3,R2,R1)
	           _delay_ms(1);
	           PORTC = 0b10001111;          // Column pins:Output pins are set to Low(0)
                                            //Row pins: Input pins pull up resistor is activated by setting 1 to PORTC column pins
	          _delay_ms(1);
	          keypressed |= PINC;          // ORing the value of ROW and Column pressed when they are set as input respectively
			  switch (keypressed)
	               {
		                   case(0b11101110):        
		                                                flag = 0;
		                                                a ='1';
														break;
														
						  case(0b11011110):            
						                               flag = 0;
		                                               a='2';
		                                               break;
		                
					      case(0b10111110):            
						                               flag = 0;
		                                               a='3';
		                                               break;
		 
		                 case(0b11101101):             
						                               flag = 0;
		                                               a='4';
		                                               break;
		 
		                case(0b11011101):             
						                              flag = 0;
		                                              a='5';
		                                              break;
		 
		               case(0b10111101):              
					                                  flag = 0;
		                                              a='6';
		                                              break;
		 
		              case(0b11101011):            
					                                  flag = 0;
		                                              a='7';
		                                              break;
		 
		              case(0b11011011):           
					                                 flag = 0;
		                                             a='8';
		                                             break;
		 
		              case(0b10111011):             
					                               flag = 0;
		                                           a='9';
		                                           break;
		 
		             case(0b11100111):                            //Enter : '\n'
					                              flag = 0;
		                                          a='\n';
		                                          break;
		 
		            case(0b11010111):        
					                             flag = 0;
		                                         a='0';
		                                         break;
		 
		            case(0b10110111):            
					                       flag = 0;
		                                   a='#';
		                                   break;
		 
	              }
 	
           return a;
    }
else if(colomn_input == 0b11110000)
  {
	  while( colomn_input == 0b11110000)
	  {   		 
					  flag = 1;
					  goto STAT;
	  }
   } else if(colomn_input!= 0b11110000)
   {
	   while(colomn_input!= 0b11110000)
	   {
			flag = 0;
		    goto STAT;
		 }
   
   }
   
   
}
/*
when using this last element of given array should have 
'/n' as last element otherwise it will not come out of 
for loop

*/
int intarray_to_integer(uint8_t intarra [])
{
	int i,k=0;
	for(i=0; intarra[i]!='\n'; i++)
	{
		k = ((10 * k) + (intarra[i]-48));
	}

	return k;
}

static inline void initTimer1Servo(void)
{
	/* Set up Timer1 (16bit) to give a pulse every 20ms */
	/* Use Fast PWM mode, counter max in ICR1 */
	TCCR4A |= (1 << WGM41);
	TCCR4B |= (1 << WGM42) | (1 << WGM43);
	TCCR4B |= (1 << CS41);  /* /1 prescaling -- counting in microseconds */
	ICR4 = 40000;                                    /* TOP value = 20ms */
	TCCR4A |= (1 << COM4C1);              /* Direct output on PB5 / OC1A */
	DDRH |= (1 << PH5);                            /* set pin for output */

}

void fun1(uint16_t angle)
{   //uint16_t count =count_maximum-count_minimum;
	
	OCR4C=(angle*22.22)+1000;
	decimel0(OCR4C);
	printString0("\n");
}


int main()
{
	initTimer1Servo();
	LCD_init();
	UART_Init0();
	uint8_t r=0;
	uint8_t firstnum[3];
	
	while (1)
	{   
		
		uint16_t k=0;
		
		
		printString0("\n enter first Number \n");
		
		lcd_setcursor(0,0);
		LCD_string("Enter Angle for");
		lcd_setcursor(0,1);
		LCD_string("Servo(0-180) ");
		
		
	    for(int a=0;a<3;a++)
		{
			printString0("value of a:");
			decimel0(a);
			printString0("\n");
			
			r = getKey();
		   if(r == '#')
			{
				printString0("Backspace pressed \n");
				a--;
				firstnum[a] = '\0';
				
				k = ((10 * k) + (firstnum[a]-48));
				
				// for terminal screen
				decimel0(k);
				printString0("\n");
				
				//for lcd screen
				lcd_setcursor(13,1);
				lcd_printint(k);
			}
			else
			{
				firstnum[a] = r;
				
				if(firstnum[a]!= '\n' )
				k = ((10 * k) + (firstnum[a]-48));
				
				//for lcd screen
				lcd_printint_num(r-48);
			
			    // for terminal screen
				UART_TxChar0(firstnum[a]);
				printString0("\n");
				decimel0(k);
				printString0("\n");
				
			}
		}
		 
		  //for LCD screen
		  lcd_setcursor(13,1);
		  lcd_printint(k);
		  
		  fun1(k);
		  
		  // for terminal screen
		  decimel0(k);
		  printString0("\n");
		  _delay_ms(2000);
		  
		  lcd_clear();
		  



	}
	
	
}



/*

	{
		printString0("value of a:");
		decimel0(a);
		printString0("\n");
		
		r = getKey();
		if(r == '#')
		{
			lcd_setcursor(13,1);
			lcd_printint(k);
			r = getKey();
			if(r!= '\n' )
			k = ((10 * k) + (r-48));
			UART_TxChar0(r);
			lcd_printint_num(r-48);
			printString0("\n");
			decimel0(k);
			
		}else
		{
			if(r!= '\n' )
			k = ((10 * k) + (r-48));
			UART_TxChar0(r);
			lcd_printint_num(r-48);
			printString0("\n");
			decimel0(k);
		}
		
		
		
		*/