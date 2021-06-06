
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
#include "uarts.h"
#include "timer_inputcapture.h"
#include <stdlib.h>




int main(void)
{    
    UART_Init0();
	printString0("Welcome \n");
    float pw,tp,freq;
    char PW[30],TP[30],FRE[30];
    while (1) 
    {  
		timerinputcapture();
		//TCCR1B = 0;
		if(a<b && b<c)  	/* Check for valid condition, 
					        to avoid timer overflow reading */
		{  
			
			tp=(float)cx/62500;                 //time period(dividing factor depends on the clock of timer)
		        pw =(float)bx/62500;                 //pulse width(dividing factor depends on the clock of timer)
			freq=1/tp;
			sprintf(PW,"PW=%f\r\n",pw);
			sprintf(TP,"TP=%f\r\n",tp);
			sprintf(FRE,"FREQ=%f\r\n",freq);
			printString0(" pulse width : ");
			printString0(PW);
			printString0("\n");
		         printString0(" time period : ");
			printString0(TP);
			printString0("\n");
			printString0(" frequency : ");
			printString0(FRE);
			printString0("\n");
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


