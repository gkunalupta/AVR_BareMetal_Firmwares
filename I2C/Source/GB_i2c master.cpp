
void GB_TWI_init_master(void) // Function to initialize master
{
	TWBR=0x48; //SCL frequency is 50K for 16Mhz: SCL freq= F_CPU/(16+2(TWBR).4^TWPS)
	TWSR=(0<<TWPS1)|(0<<TWPS0); // Setting prescalar bits
}

void GB_TWI_start(void)
{
	// Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
	TWCR= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT))); // Wait till start condition is transmitted
	while((TWSR & 0xF8)!= 0x08); // Check for the acknowledgement
	//printString0("Kunal\n");
}

void GB_TWI_repeated_start(void)
{
	// Clear TWI interrupt flag, Put start condition on SDA, Enable TWI
	TWCR= (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT))); // wait till restart condition is transmitted
	while((TWSR & 0xF8)!= 0x10); // Check for the acknoledgement
}

void GB_TWI_write_slave_address(uint8_t gb_data)
{    //printString1("Kunal\n");
	TWDR=gb_data; // Address and write instruction
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte transmitted
	//printString0("Kunl\n");
	//bit0(TWSR & 0xF8);
	while((TWSR & 0xF8)!= 0x18);  // Check for the acknoledgement
	//printString0("kunal");
}

void GB_TWI_read_slave_address(uint8_t gb_data)
{
	TWDR=gb_data; // Address and read instruction
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte received
	while((TWSR & 0xF8)!= 0x40);  // Check for the acknoledgement
}
// writes single byte like 'a',1110001, etc.
void GB_TWI_write_data(uint8_t gb_data)
{
	TWDR=gb_data; // put data in TWDR
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte transmitted
	while((TWSR & 0xF8) != 0x28); // Check for the acknoledgement
}
// when string has to be transmitted like ("kklmk",string a, etc)

void GB_TWI_write_datastring( char * gb_data)
{
	
	for (int gb_i = 0; gb_i<strlen(gb_data); gb_i++)/* Write array data */
	{
		GB_TWI_write_data(gb_data[gb_i]);
	}
}
//read data ..
// when data to be read is character ('a',']','1',etc ) use  UART_TxChar1() function
// when to be read in binary form (11100010,etc) use bit1()
// when data to be read is in decimal form (229,103,etc) use decimel1()
uint8_t GB_TWI_read_dataNack(void)
{
	TWCR=(1<<TWINT)|(1<<TWEN);    // Clear TWI interrupt flag,Enable TWI
	while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte transmitted
	while((TWSR & 0xF8) != 0x58); // Check for the acknoledgement
	return TWDR;

}
uint8_t GB_TWI_read_dataAck(void)
{
	// 		bit1(TWCR);           //10000100
	// 	 		 			printString1("\n");
	// 		 			bit1(TWSR);           //01000000
	// 			 			printString1("\n");
	TWCR=(1<<TWINT)|(1<<TWEN)|(1<<TWEA);    // Clear TWI interrupt flag,Enable TWI
	// 			bit1(TWCR);           //01000100
	// 			printString1("\n");
	// 			bit1(TWSR);           //01010000
	// 			printString1("\n");
	while (!(TWCR & (1<<TWINT))); // Wait till complete TWDR byte transmitted
	// 			bit1(TWCR);           //11000100
	// 			printString1("\n");
	// 			bit1(TWSR);           //01010000
	// 			printString1("\n");
	while((TWSR & 0xF8) != 0x50); // Check for the acknoledgement
	// 	  		bit1(TWCR);           //10000100
	// 	  		printString1("\n");
	// 	  		bit1(TWSR);           //01000000
	// 	  		printString1("\n");
	return TWDR;
}

uint8_t GB_i2c_readReg( uint8_t* gb_data, uint16_t gb_length)
{
	

	for (uint16_t gb_i = 0; gb_i < (gb_length-1); gb_i++)
	{
		gb_data[gb_i] = GB_TWI_read_dataAck();
	}
	gb_data[(gb_length-1)] = GB_TWI_read_dataNack();

	GB_TWI_stop();

	return 0;
}
void GB_TWI_stop(void)
{
	// Clear TWI interrupt flag, Put stop condition on SDA, Enable TWI
	TWCR= (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
	while((TWCR & (1<<TWSTO)));  // Wait till stop condition is transmitted
}