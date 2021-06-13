/*
 * arduino-keypad(pid419).cpp
 *
 * Created: 27-10-2020 13:05:28
 * Author : kunal
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "stdlib.h"
#include "GB_keypad.h"
#include <GB_uarts.h>


/*
when using this last element of given array should have 
'/n' as last element otherwise it will not come out of 
for loop

*/
int GB_intarray_to_integer(uint8_t gb_intarra [])
{
	int gb_i,gb_k=0;
	for(gb_i=0; gb_intarra[gb_i]!='\n'; gb_i++)
	{
		gb_k = ((10 * gb_k) + (gb_intarra[gb_i]-48));
	}
	return gb_k;
}

int main()
{

	GB_UART_Init0();
	uint8_t gb_firstnum[3];
	uint8_t gb_r=0;
    int gb_num =0;
	while (1)
	{   
		uint16_t gb_k=0;
		GB_printString0("\nenter Number\n");
		for(int gb_a=0;gb_a<4;gb_a++)
		{
			gb_r = GB_getKey();
			gb_k = ((10 * gb_k) + (gb_r-48));
			GB_UART_TxChar0(gb_r);
		}
		GB_printString0("\n");
		GB_decimel0(gb_k);
		GB_printString0("\n");
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



