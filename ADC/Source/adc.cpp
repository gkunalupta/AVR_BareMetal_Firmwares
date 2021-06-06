
void ADC_setup(void)
{
	ADMUX = (1<<REFS0) | (1<<REFS1)|(0<<ADLAR); // select external AREF
	//DIDR2 = (1<<ADC8D) | (1<<ADC9D); // digital input disable
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // enable ADC, 128 clk divider
}
int ADC_select(uint8_t chan)
{
	int adc_value =0;
	ADMUX = (ADMUX & 0xE0) | (chan);   //select channel (MUX0-4 bits)
	ADCSRB = (ADCSRB & 0xDF) | (chan);   //select channel (MUX5 bit)
	ADCSRA|=(1<<ADSC);
	adc_value = ADCW;
	return adc_value;
	//printString0("\n");

}

void ADC_read(void)
{
	//bit(ADCSRA);
	
	decimel0(ADCW);
	
	//char sbuff[100];
	//sprintf(sbuff,"%0d\n",ADCW);
	//printString0(sbuff);
	//_delay_ms(8000);
	//bit(ADCSRA);
}