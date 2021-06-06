#ifndef W25Q128JV_H_
#define W25Q128JV_H_


#include "SPI_master.h"
#include "GPIO.h"


#define WriteEnable 0x06
#define WriteDisable 0x04
#define Dummybyte 0xA5


#define Flash_CE PB0
#define Flash_CE_pin_low spi_port &= ~(1<<SS)
#define Flash_CE_pin_high spi_port |= (1<<SS)

#define ReadSR1 0x05
#define WriteSR1 0x01
#define ReadSR2 0x35  //0x35: 00110101
#define WriteSR2 0x31
#define ReadSR3 0x15
#define WriteSR3 0x11


#define Write_Enab_for_Vol_status_regist 0x50

#define ReadData 0x03
#define WriteData 0x02
#define ReadDataFast 0x0B


#define JEDECID 0x9F
#define UinqueID 0x4B

#define SectErase4KB 0x20
#define SectErase32KB 0x52
#define SectErase64KB 0xD8
#define chiperase 0xC7

#define reset1 0x66
#define reset2 0x99

#define read_addr2 0x020000
#define read_addr3 0x030000
#define read_addr4 0x040000

/*
Write enable for volatile status register
instruction: 0x50
*/
void WEFVSR();
/*WriteEnable_flash()
Enable the write operation on Flash by sending Write Enable instruction: 06h
after sending this instruction WEL bit in SR1 is set to 1
As WEL bit in SR1 must be set prior to every Page Program, Quad Page Program,
Sector erase, Block Erase,chip erase,write status register and Erase/Program
security register
*/
void WriteEnable_flash();
/*
Write disable
*/
void Writedisable();
//******************************status register Read Write API****************************//
/*REad Status Register instruction()
For reading the register contents, simple send the instruction 
SR1->0x05: ReadSR1 : by default = 0x00
SR2->0x35: ReadSR2: 0x00
SR3->0x15: ReadSR3: 0x60
*/
uint8_t ReadSR(uint8_t SR_read);
/* Write Status register()
write the SR_data value on the SR_address
*/
void WriteSR(uint8_t SR_address, uint8_t SR_data);

//
uint8_t Readbyte(uint32_t addr);
void Writebyte(uint32_t addr,uint8_t byte);
/*
Writedata()
*/

void Write_wq12_data(uint32_t addr,char block[],uint8_t size);
/*
Read data()
*/
void read_wq128_data(uint32_t addr,char block[], uint8_t size);
/* 
erase sector 4KB
*/
void erase_sector4KB(uint32_t addr);
/*
erase sector 32KB
*/
void erase_sector32KB(uint32_t addr);
/*
erase sector 64KB
*/
void erase_sector64KB(uint32_t addr);
void chip_erase();
/*
 Fast Read data()
*/
void FastReadData();


void JED_id();
void Uinque_ID(uint8_t uinque[]);

#include "w25q128jv.cpp"

#endif