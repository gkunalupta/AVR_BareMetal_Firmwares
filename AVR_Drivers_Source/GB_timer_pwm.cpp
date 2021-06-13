
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
static inline void GB_FAST_PWM_Init(uint8_t gb_PWM_pin) 
{
	
	/* Set up Timer1 (16bit) to give a pulse every 20ms */
	/* Use Fast PWM mode, counter max in ICR1 */
	/* 1) First select the waveform generation mode: Fast PWM,CTC,Phase PWM,Normal PWM*/
	TCCR4A |= (1 << WGM41);   
	TCCR4B |= (1 << WGM42) | (1 << WGM43);
	/*2) Select the clock prescalor value for Timer Clock*/
	TCCR4B |= (1 << CS41);  //8 prescaling 
	/*3) assign the TOP value */
	ICR4 = 40000;
	/*4)  Select the Compare output mode for particular PWM pin: inverting, non inverting*/
	TCCR4A |= (1 << COM4A1);  /* Direct output on PB7 / OC1C */
	/* 5) output the corresponding PWM pin*/
	DDRH |= (1 << (gb_PWM_pin));  /* set pin for output */
}
void GB_duty_cycle(int gb_duty)
{
	OCR4A = 400 * gb_duty;
}