/*
 * arduino-keypad(pid419).cpp
 *
 * Created: 27-10-2020 13:05:28
 * Author : kunal
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include "keypad.h"
#include <uarts.h>


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

int main()
{

	UART_Init0();
	uint8_t firstnum[3];
	uint8_t r=0;
    int num =0;
	while (1)
	{   
		uint16_t k=0;
		printString0("\nenter Number\n");
		for(int a=0;a<4;a++)
		{
			r = getKey();
			k = ((10 * k) + (r-48));
			UART_TxChar0(r);
		}
		printString0("\n");
		decimel0(k);
		printString0("\n");
		_delay_ms(1000);
	}
}
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
// 		for(int a=0;a<4;a++)
// 		{
// 					  r = getKey();
// 					  if(r == '#')
// 			          {
// 				            a--;
// 							firstnum[a] = '\0';
// 							lcd_setcursor(13,1);
// 							lcd_printint(firstnum);
// 							
// 							
							
// 							printString0(" \n inside if \n");
// 				            firstnum[--a] = '\0';
// 				            UART_TxChar0(firstnum[a]);
// 					   }
// 			           else
// 			           {   
// 						   firstnum[a] = r;
// 				           UART_TxChar0(firstnum[a]);
// 				         printString0("\n");
// 				        decimel0(k);
// 						}
// 				}
// 		
// 		num = intarray_to_integer(firstnum);
//        
// 	   decimel0(num);
//        printString0("\n");
//        _delay_ms(2000);
	   
// 	   printString0("\n");
// 	   decimel0(k);
// 	   printString0("\n");
// 	   _delay_ms(1000);



