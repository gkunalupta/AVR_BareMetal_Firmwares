
void GB_ADC_setup(void)
{
	ADMUX = (1<<REFS0) | (1<<REFS1)|(0<<ADLAR); // select external AREF
	//DIDR2 = (1<<ADC8D) | (1<<ADC9D); // digital input disable
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0); // enable ADC, 128 clk divider
}
int GB_ADC_select(uint8_t gb_chan)
{
	int gb_adc_value =0;
	ADMUX = (ADMUX & 0xE0) | (gb_chan);   //select channel (MUX0-4 bits)
	ADCSRB = (ADCSRB & 0xDF) | (gb_chan);   //select channel (MUX5 bit)
	ADCSRA|=(1<<ADSC);
	gb_adc_value = ADCW;
	return gb_adc_value;
	//printString0("\n");

}

void GB_ADC_read(void)
{
	//bit(ADCSRA);
	
	GB_decimel0(ADCW);
	
	//char sbuff[100];
	//sprintf(sbuff,"%0d\n",ADCW);
	//printString0(sbuff);
	//_delay_ms(8000);
	//bit(ADCSRA);
}