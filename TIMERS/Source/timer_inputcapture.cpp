
void timerinputcapture()
{    //initialize timer
	//normal mode
	TCCR4A=0x00;                          //(output compare mode for all 3 channels set to 00 and WGM11 and WGM10 and WGM11 set to zero)
	TCCR4B=0b01000100;                    //(rising edge enable,clk/64)
	ACSR=(0<ACIC);                        //(icpp pin event source)
	
	//positive edge
	while((TIFR4&(1<<ICF4))==0);           //check for rising event
	a=ICR4;
	TIFR4=(1<<ICF4);                       //clear flag
	
	
	//negative edge
	TCCR4B|=(0<<ICES4);                     //falling edge enable
	while((TIFR4&(1<<ICF4))==0);           //check for falling event
	b=ICR4;
	bx=ICR4-a;
	TIFR4=(1<<ICF4);                       //clear flag
	
	
	//positive edge
	TCCR4B|=(1<<ICES4);                   //rising edge enable
	while((TIFR4&(1<<ICF4))==0);           //check for rising event
	c=ICR4;
	cx=ICR4-a;
	printString1("\n");
	TIFR4=(1<<ICF4);                       //clear flag
	
}