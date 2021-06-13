#ifndef GB_W25Q128JV_H_
#define GB_W25Q128JV_H_


#include "GB_SPI_master.h"
#include "GPIO.h"


#define gb_WriteEnable 0x06
#define gb_WriteDisable 0x04
#define gb_Dummybyte 0xA5


#define gb_Flash_CE PB0
#define gb_Flash_CE_pin_low gb_spi_port &= ~(1<<gb_SPI_SS)
#define gb_Flash_CE_pin_high gb_spi_port |= (1<<gb_SPI_SS)

#define gb_ReadSR1 0x05
#define gb_WriteSR1 0x01
#define gb_ReadSR2 0x35  //0x35: 00110101
#define gb_WriteSR2 0x31
#define gb_ReadSR3 0x15
#define gb_WriteSR3 0x11


#define gb_Write_Enab_for_Vol_status_regist 0x50

#define gb_ReadData 0x03
#define gb_WriteData 0x02
#define gb_ReadDataFast 0x0B


#define gb_JEDECID 0x9F
#define gb_UinqueID 0x4B

#define gb_SectErase4KB 0x20
#define gb_SectErase32KB 0x52
#define gb_SectErase64KB 0xD8
#define gb_chiperase 0xC7

#define gb_reset1 0x66
#define gb_reset2 0x99

#define gb_read_addr2 0x020000
#define gb_read_addr3 0x030000
#define gb_read_addr4 0x040000

/*
Write enable for volatile status register
instruction: 0x50
*/
void GB_WEFVSR();
/*WriteEnable_flash()
Enable the write operation on Flash by sending Write Enable instruction: 06h
after sending this instruction WEL bit in SR1 is set to 1
As WEL bit in SR1 must be set prior to every Page Program, Quad Page Program,
Sector erase, Block Erase,chip erase,write status register and Erase/Program
security register
*/
void GB_WriteEnable_flash();
/*
Write disable
*/
void GB_Writedisable();
//******************************status register Read Write API****************************//
/*REad Status Register instruction()
For reading the register contents, simple send the instruction 
SR1->0x05: ReadSR1 : by default = 0x00
SR2->0x35: ReadSR2: 0x00
SR3->0x15: ReadSR3: 0x60
*/
uint8_t GB_ReadSR(uint8_t gb_SR_read);
/* Write Status register()
write the SR_data value on the SR_address
*/
void GB_WriteSR(uint8_t gb_SR_address, uint8_t gb_SR_data);

//
uint8_t GB_Readbyte(uint32_t gb_addr);
void GB_Writebyte(uint32_t gb_addr,uint8_t gb_byte);
/*
Writedata()
*/

void GB_Write_wq12_data(uint32_t gb_addr,char gb_block[],uint8_t gb_size);
/*
Read data()
*/
void GB_read_wq128_data(uint32_t gb_addr,char gb_block[], uint8_t gb_size);
/* 
erase sector 4KB
*/
void GB_erase_sector4KB(uint32_t gb_addr);
/*
erase sector 32KB
*/
void GB_erase_sector32KB(uint32_t gb_addr);
/*
erase sector 64KB
*/
void GB_erase_sector64KB(uint32_t gb_addr);
void GB_chip_erase();
/*
 Fast Read data()
*/
void GB_FastReadData();


void GB_JED_id();
void GB_Uinque_ID(uint8_t gb_uinque[]);

#include "GB_w25q128jv.cpp"

#endif