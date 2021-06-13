
/*
Write enable for volatile status register
instruction: 0x50
*/
void GB_WEFVSR()
{
	gb_Flash_CE_pin_low;
	GB_MA_SPI0_send_byte_conti(gb_Write_Enab_for_Vol_status_regist);
	gb_Flash_CE_pin_high;
}
/*WriteEnable_flash()
Enable the write operation on Flash by sending Write Enable instruction: 06h
after sending this instruction WEL bit in SR1 is set to 1
As WEL bit in SR1 must be set prior to every Page Program, Quad Page Program,
Sector erase, Block Erase,chip erase,write status register and Erase/Program
security register
*/
void GB_WriteEnable_flash()
{
	gb_Flash_CE_pin_low;
	//Sending 06h byte to enable the write operation
	GB_MA_SPI0_send_byte_conti(gb_WriteEnable);  //0x06
	gb_Flash_CE_pin_high;
}
/*
Write disable
*/
void GB_Writedisable()
{
	gb_Flash_CE_pin_low;
	GB_MA_SPI0_send_byte_conti(gb_WriteDisable);
	gb_Flash_CE_pin_high;
}
//******************************status register Read Write API****************************//
/*REad Status Register instruction()
For reading the register contents, simple send the instruction 
SR1->0x05: ReadSR1 : by default = 0x00
SR2->0x35: ReadSR2: 0x00
SR3->0x15: ReadSR3: 0x60
*/
uint8_t GB_ReadSR(uint8_t gb_SR_read)
{       
	    uint8_t gb_RSR =0;
		gb_Flash_CE_pin_low;
		GB_MA_SPI0_send_byte_conti(gb_SR_read);
		gb_RSR = GB_MA_SPI0_read_byte();
		gb_Flash_CE_pin_high;
		_delay_us(100);
		return gb_RSR;
}
/* Write Status register()
write the SR_data value on the SR_address
*/
void GB_WriteSR(uint8_t gb_SR_address, uint8_t gb_SR_data)
{
	GB_WriteEnable_flash();  //06h
	gb_Flash_CE_pin_low;
	GB_MA_SPI0_send_byte_conti(gb_SR_address); //send 01,31,11 address for writing on SR
	GB_MA_SPI0_send_byte_conti(gb_SR_data); //send status register data
	gb_Flash_CE_pin_high;
}

//
uint8_t GB_Readbyte(uint32_t gb_addr)
{
	uint8_t gb_byte = 0;
	gb_Flash_CE_pin_low;
	GB_MA_SPI0_send_byte_conti(gb_ReadData);
	GB_MA_SPI0_send_byte_conti(((gb_read_addr2>>16) & (0xff)));
	GB_MA_SPI0_send_byte_conti(((gb_read_addr2>>8) & (0xff)));
	GB_MA_SPI0_send_byte_conti(gb_read_addr2 & 0xff);
	gb_byte = GB_MA_SPI0_read_byte();
	gb_Flash_CE_pin_high;
	return gb_byte;
}
void GB_Writebyte(uint32_t gb_addr,uint8_t gb_byte)
{
	GB_WriteEnable_flash();
	gb_Flash_CE_pin_low;
	GB_MA_SPI0_send_byte_conti(gb_WriteData);
	GB_MA_SPI0_send_byte_conti(((gb_read_addr2>>16) & (0xff)));
	GB_MA_SPI0_send_byte_conti(((gb_read_addr2>>8) & (0xff)));
	GB_MA_SPI0_send_byte_conti(gb_read_addr2 & 0xff);
	GB_MA_SPI0_send_byte_conti(gb_byte);
	gb_Flash_CE_pin_low;
	
}
/*
Writedata()
*/

void GB_Write_wq12_data(uint32_t gb_addr,char gb_block[],uint8_t gb_size)
{
	//uint8_t i=0;
	GB_WriteEnable_flash();//0x06
	gb_Flash_CE_pin_low;
	GB_MA_SPI0_send_byte_conti(gb_WriteData); //0x02h
	GB_MA_SPI0_send_byte_conti(((gb_addr>>16) & (0xff))); //	24bit address of memory location
	GB_MA_SPI0_send_byte_conti(((gb_addr>>8) & (0xff)));
	GB_MA_SPI0_send_byte_conti(gb_addr & 0xff);
	for(uint8_t gb_i = 0;gb_i<gb_size;gb_i++)
   // while ((size--)!= 0)            //Buffer for Writing required number of bytes
   {
	   GB_MA_SPI0_send_byte_conti(gb_block[gb_i]);
	}
	gb_Flash_CE_pin_high;
}
/*
Read data()
*/
void GB_read_wq128_data(uint32_t gb_addr,char gb_block[], uint8_t gb_size)
{
	volatile uint8_t gb_spi_recv_char=0;
	uint8_t gb_i=0;
	gb_Flash_CE_pin_low;
	GB_MA_SPI0_send_byte_conti(gb_ReadData); //0x03h
	GB_MA_SPI0_send_byte_conti(((gb_addr>>16) & (0xff))); //	24bit address of memory location
	GB_MA_SPI0_send_byte_conti(((gb_addr>>8) & (0xff)));
	GB_MA_SPI0_send_byte_conti(gb_addr & 0xff);
	while ((gb_size--)!= 0)                             //Buffer for reading required number of bytes
	{
		
		gb_spi_recv_char= GB_MA_SPI0_read_byte();
		gb_block[gb_i++] = gb_spi_recv_char;
	}
	gb_Flash_CE_pin_high;
}

/* 
erase sector 4KB
*/
void GB_erase_sector4KB(uint32_t gb_addr)
{
	GB_WriteEnable_flash();//x06
	gb_Flash_CE_pin_low;
	GB_MA_SPI0_send_byte_conti(gb_SectErase4KB); //0x20
	GB_MA_SPI0_send_byte_conti(((gb_addr>>16) & (0xff)));
	GB_MA_SPI0_send_byte_conti(((gb_addr>>8) & (0xff)));
	GB_MA_SPI0_send_byte_conti(gb_addr & 0xff);
	gb_Flash_CE_pin_high;
}
/*
erase sector 32KB
*/
void GB_erase_sector32KB(uint32_t gb_addr)
{
	GB_WriteEnable_flash();
	gb_Flash_CE_pin_low;
	GB_MA_SPI0_send_byte_conti(gb_SectErase32KB); //0x20
	GB_MA_SPI0_send_byte_conti(((gb_addr>>16) & (0xff)));
	GB_MA_SPI0_send_byte_conti(((gb_addr>>8) & (0xff)));
	GB_MA_SPI0_send_byte_conti(gb_addr & 0xff);
	gb_Flash_CE_pin_high;
}
/*
erase sector 64KB
*/
void GB_erase_sector64KB(uint32_t gb_addr)
{
	GB_WriteEnable_flash();
	gb_Flash_CE_pin_low;
	GB_MA_SPI0_send_byte_conti(gb_SectErase64KB); //0x20
	GB_MA_SPI0_send_byte_conti(((gb_addr>>16) & (0xff)));
	GB_MA_SPI0_send_byte_conti(((gb_addr>>8) & (0xff)));
	GB_MA_SPI0_send_byte_conti(gb_addr & 0xff);
	gb_Flash_CE_pin_high;
}
void GB_chip_erase()
{
	GB_WriteEnable_flash();
	gb_Flash_CE_pin_low;
	GB_MA_SPI0_send_byte_conti(gb_chiperase); //0xc7
	gb_Flash_CE_pin_high;
}
/*
 Fast Read data()
*/
void GB_FastReadData()
{
	gb_Flash_CE_pin_low;
	GB_MA_SPI0_send_byte_conti(gb_ReadDataFast); //0x0Bh
	/*
	24bit address of memory location
	*/
	GB_MA_SPI0_send_byte_conti(0x00); //dummy bytes
	/*
	Buffer for reading required number of bytes
	*/
	gb_Flash_CE_pin_high;
}


void GB_JED_id()
{
	uint8_t gb_x = 0x00;
	uint8_t gb_y = 0x00;
	uint8_t gb_z = 0x00;
	
	gb_Flash_CE_pin_low;
	GB_MA_SPI0_send_byte_conti(gb_JEDECID);  //0x9F
	gb_x = GB_MA_SPI0_read_byte();  //0xEF
	gb_y = GB_MA_SPI0_read_byte();  //0x40
	gb_z = GB_MA_SPI0_read_byte();  //0x18
	gb_Flash_CE_pin_high;
	
		_delay_us(100);
	//	decimel0(x);
	//	printString0("\n");
	
}
void GB_Uinque_ID(uint8_t gb_uinque[])
{
	
	//uint8_t x = 0x00;
	uint8_t gb_y = 0x00;
	uint8_t gb_z = 0x00;
	
	gb_Flash_CE_pin_low;
	GB_MA_SPI0_send_byte_conti(gb_UinqueID);  //0x9F
	for (uint8_t gb_i=0;gb_i<4;gb_i++)
	GB_MA_SPI0_read_byte();
	for ( uint8_t gb_x =0;gb_x<8;gb_x++)
	gb_uinque[gb_x] = GB_MA_SPI0_read_byte();

	gb_Flash_CE_pin_high;
	
}