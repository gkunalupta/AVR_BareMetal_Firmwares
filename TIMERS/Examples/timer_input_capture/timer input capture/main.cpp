
 /*
 * timer input capture.cpp
 *
 * Created: 2/20/2020 10:04:58 PM
 * Author : kunal
 */ 
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "GB_uarts.h"
#include "GB_timer_inputcapture.h"
#include <stdlib.h>




int main(void)
{    
    GB_UART_Init0();
	GB_printString0("Welcome \n");
    float gb_pw,gb_tp,gb_freq;
    char gb_PW[30],gb_TP[30],gb_FRE[30];
    while (1) 
    {  
		GB_timerinputcapture();
		//TCCR1B = 0;
		if(gb_a<gb_b && gb_b<gb_c)  	/* Check for valid condition, 
					        to avoid timer overflow reading */
		{  
			
			gb_tp=(float)gb_cx/62500;                 //time period(dividing factor depends on the clock of timer)
		        gb_pw =(float)gb_bx/62500;                 //pulse width(dividing factor depends on the clock of timer)
			gb_freq=1/gb_tp;
			sprintf(gb_PW,"PW=%f\r\n",gb_pw);
			sprintf(gb_TP,"TP=%f\r\n",gb_tp);
			sprintf(gb_FRE,"FREQ=%f\r\n",gb_freq);
			GB_printString0(" pulse width : ");
			GB_printString0(gb_PW);
			GB_printString0("\n");
		         GB_printString0(" time period : ");
			GB_printString0(gb_TP);
			GB_printString0("\n");
			GB_printString0(" frequency : ");
			GB_printString0(gb_FRE);
			GB_printString0("\n");
			_delay_ms(2000);
	
		}
	
     }
}

	
		/*
		long frequency=F_CPU/tp;//calculate period
		float dutycycle=((float )pw/(float)tp)*100;//calculate dutyccycle
	//	itoa((int)dutycycle,duty,10);//converts int to string(char) ..decimel
	//	ltoa(frequency,freq,10);//converts long to string(char)...decimel
	//	itoa(tp,timeperiod,10);
	//	itoa(pw,pulsewidth,10);
		printint1(duty);//prints dutycycle
		printString1("\n");
		printint1(freq);//prints frequency
		printString1("\n");
		printint1(timeperiod);//prints timeperiod
		printString1("\n");
		printint1(pulsewidth);//prints pulsewidth
		printString1("\n");
		
		
		
		
		
		printString1("wrong");
		*/


