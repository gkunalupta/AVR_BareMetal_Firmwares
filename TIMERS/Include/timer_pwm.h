#ifndef TIMER_PWM_H_
#define TIMER_PWM_H_

#define PWMpin PH3

/* 
1/Freq_PWM = Time_period_ofPWM(TMP)
TMP = TON+TOFF(TON = PWM_HIGH_TIME, TOFF = PWM_LOW_TIME)
Duty_cycle:
+Duty_cycle = (TON/TMP)*100
-Duty_cycle = (TOFF/TMP)*100
************************************************FAST_PWM*********************************************************
To Produce the fast PWM signal :
Freq_PWM_in_FASTPWM_mode= (Freq_clk)/N(1+TOP):
Freq_clk = 16000000Mhz, N= Prescalor value, TOP = Value assigned to ICRn or OCR1A

1) First select the Mode of timer as FAST PWM from WGMnx pins and 
corresponding TOP value(ICR1 or OCRnA)
2) Then select the clock prescalor value from CSn2:0 pins of TCCR1B
3) Assign the TOP value : ICR1 is it is selected as TOP
                          OCRnA if it selected as TOP
4)	Select 	the Compare Output Mode for corresponding PWM pin channel:=inverting/non-inverting				  
5) Output the GPIO pin which is selected as PWM pin

*/

static inline void FAST_PWM_Init(uint8_t PWM_pin) ;
void duty_cycle(int duty);

#include "timer_pwm.cpp"

#endif