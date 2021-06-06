
/*
Write enable for volatile status register
instruction: 0x50
*/
void WEFVSR()
{
	Flash_CE_pin_low;
	MA_SPI0_send_byte_conti(Write_Enab_for_Vol_status_regist);
	Flash_CE_pin_high;
}
/*WriteEnable_flash()
Enable the write operation on Flash by sending Write Enable instruction: 06h
after sending this instruction WEL bit in SR1 is set to 1
As WEL bit in SR1 must be set prior to every Page Program, Quad Page Program,
Sector erase, Block Erase,chip erase,write status register and Erase/Program
security register
*/
void WriteEnable_flash()
{
	Flash_CE_pin_low;
	//Sending 06h byte to enable the write operation
	MA_SPI0_send_byte_conti(WriteEnable);  //0x06
	Flash_CE_pin_high;
}
/*
Write disable
*/
void Writedisable()
{
	Flash_CE_pin_low;
	MA_SPI0_send_byte_conti(WriteDisable);
	Flash_CE_pin_high;
}
//******************************status register Read Write API****************************//
/*REad Status Register instruction()
For reading the register contents, simple send the instruction 
SR1->0x05: ReadSR1 : by default = 0x00
SR2->0x35: ReadSR2: 0x00
SR3->0x15: ReadSR3: 0x60
*/
uint8_t ReadSR(uint8_t SR_read)
{       
	    uint8_t RSR =0;
		Flash_CE_pin_low;
		MA_SPI0_send_byte_conti(SR_read);
		RSR = MA_SPI0_read_byte();
		Flash_CE_pin_high;
		_delay_us(100);
		return RSR;
}
/* Write Status register()
write the SR_data value on the SR_address
*/
void WriteSR(uint8_t SR_address, uint8_t SR_data)
{
	WriteEnable_flash();  //06h
	Flash_CE_pin_low;
	MA_SPI0_send_byte_conti(SR_address); //send 01,31,11 address for writing on SR
	MA_SPI0_send_byte_conti(SR_data); //send status register data
	Flash_CE_pin_high;
}

//
uint8_t Readbyte(uint32_t addr)
{
	uint8_t byte = 0;
	Flash_CE_pin_low;
	MA_SPI0_send_byte_conti(ReadData);
	MA_SPI0_send_byte_conti(((read_addr2>>16) & (0xff)));
	MA_SPI0_send_byte_conti(((read_addr2>>8) & (0xff)));
	MA_SPI0_send_byte_conti(read_addr2 & 0xff);
	byte = MA_SPI0_read_byte();
	Flash_CE_pin_high;
	return byte;
}
void Writebyte(uint32_t addr,uint8_t byte)
{
	WriteEnable_flash();
	Flash_CE_pin_low;
	MA_SPI0_send_byte_conti(WriteData);
	MA_SPI0_send_byte_conti(((read_addr2>>16) & (0xff)));
	MA_SPI0_send_byte_conti(((read_addr2>>8) & (0xff)));
	MA_SPI0_send_byte_conti(read_addr2 & 0xff);
	MA_SPI0_send_byte_conti(byte);
	Flash_CE_pin_low;
	
}
/*
Writedata()
*/

void Write_wq12_data(uint32_t addr,char block[],uint8_t size)
{
	//uint8_t i=0;
	WriteEnable_flash();//0x06
	Flash_CE_pin_low;
	MA_SPI0_send_byte_conti(WriteData); //0x02h
	MA_SPI0_send_byte_conti(((addr>>16) & (0xff))); //	24bit address of memory location
	MA_SPI0_send_byte_conti(((addr>>8) & (0xff)));
	MA_SPI0_send_byte_conti(addr & 0xff);
	for(uint8_t i = 0;i<size;i++)
   // while ((size--)!= 0)            //Buffer for Writing required number of bytes
   {
	   MA_SPI0_send_byte_conti(block[i]);
	}
	Flash_CE_pin_high;
}
/*
Read data()
*/
void read_wq128_data(uint32_t addr,char block[], uint8_t size)
{
	volatile uint8_t spi_recv_char=0;
	uint8_t i=0;
	Flash_CE_pin_low;
	MA_SPI0_send_byte_conti(ReadData); //0x03h
	MA_SPI0_send_byte_conti(((addr>>16) & (0xff))); //	24bit address of memory location
	MA_SPI0_send_byte_conti(((addr>>8) & (0xff)));
	MA_SPI0_send_byte_conti(addr & 0xff);
	while ((size--)!= 0)                             //Buffer for reading required number of bytes
	{
		
		spi_recv_char= MA_SPI0_read_byte();
		block[i++] = spi_recv_char;
	}
	Flash_CE_pin_high;
}

/* 
erase sector 4KB
*/
void erase_sector4KB(uint32_t addr)
{
	WriteEnable_flash();//x06
	Flash_CE_pin_low;
	MA_SPI0_send_byte_conti(SectErase4KB); //0x20
	MA_SPI0_send_byte_conti(((addr>>16) & (0xff)));
	MA_SPI0_send_byte_conti(((addr>>8) & (0xff)));
	MA_SPI0_send_byte_conti(addr & 0xff);
	Flash_CE_pin_high;
}
/*
erase sector 32KB
*/
void erase_sector32KB(uint32_t addr)
{
	WriteEnable_flash();
	Flash_CE_pin_low;
	MA_SPI0_send_byte_conti(SectErase32KB); //0x20
	MA_SPI0_send_byte_conti(((addr>>16) & (0xff)));
	MA_SPI0_send_byte_conti(((addr>>8) & (0xff)));
	MA_SPI0_send_byte_conti(addr & 0xff);
	Flash_CE_pin_high;
}
/*
erase sector 64KB
*/
void erase_sector64KB(uint32_t addr)
{
	WriteEnable_flash();
	Flash_CE_pin_low;
	MA_SPI0_send_byte_conti(SectErase64KB); //0x20
	MA_SPI0_send_byte_conti(((addr>>16) & (0xff)));
	MA_SPI0_send_byte_conti(((addr>>8) & (0xff)));
	MA_SPI0_send_byte_conti(addr & 0xff);
	Flash_CE_pin_high;
}
void chip_erase()
{
	WriteEnable_flash();
	Flash_CE_pin_low;
	MA_SPI0_send_byte_conti(chiperase); //0xc7
	Flash_CE_pin_high;
}
/*
 Fast Read data()
*/
void FastReadData()
{
	Flash_CE_pin_low;
	MA_SPI0_send_byte_conti(ReadDataFast); //0x0Bh
	/*
	24bit address of memory location
	*/
	MA_SPI0_send_byte_conti(0x00); //dummy bytes
	/*
	Buffer for reading required number of bytes
	*/
	Flash_CE_pin_high;
}


void JED_id()
{
	uint8_t x = 0x00;
	uint8_t y = 0x00;
	uint8_t z = 0x00;
	
	Flash_CE_pin_low;
	MA_SPI0_send_byte_conti(JEDECID);  //0x9F
	x = MA_SPI0_read_byte();  //0xEF
	y = MA_SPI0_read_byte();  //0x40
	z = MA_SPI0_read_byte();  //0x18
	Flash_CE_pin_high;
	
		_delay_us(100);
	//	decimel0(x);
	//	printString0("\n");
	
}
void Uinque_ID(uint8_t uinque[])
{
	
	//uint8_t x = 0x00;
	uint8_t y = 0x00;
	uint8_t z = 0x00;
	
	Flash_CE_pin_low;
	MA_SPI0_send_byte_conti(UinqueID);  //0x9F
	for (uint8_t i=0;i<4;i++)
	MA_SPI0_read_byte();
	for ( uint8_t x =0;x<8;x++)
	uinque[x] = MA_SPI0_read_byte();

	Flash_CE_pin_high;
	
}