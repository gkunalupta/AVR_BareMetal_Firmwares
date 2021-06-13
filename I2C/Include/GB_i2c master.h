/*
 * i2cmaster2011.cpp
 *
 * Created: 4/12/2020 2:56:40 AM
 * Author : kunal
 */ 
#ifndef GB_I2C MASTER_H_
#define GB_I2C MASTER_H_

// Program for Master Mode
// Check Code2 for Slave Mode Program
#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>
#include <string.h>
//#include "uarts.h"
/*
uint8_t I2C_start(uint8_t address)
This function needs to be called any time a connection to a new slave device should be established. 
The function returns 1 if an error has occurred, otherwise it returns 0.

The syntax to start a operation write to a device is either: I2C_start(SLAVE_ADDRESS+I2C_WRITE); or 
I2C_start(SLAVE_WRITE_ADDRESS);

The syntax to start a read operation from a device is either: I2C_start(SLAVE_ADDRESS+I2C_READ); or
 I2C_start(SLAVE_READ_ADDRESS);
 */
void GB_TWI_start(void);

void GB_TWI_repeated_start(void);
void GB_TWI_init_master(void);
void GB_TWI_write_slave_address(uint8_t);
void GB_TWI_read_slave_address(uint8_t);
void GB_TWI_write_data(uint8_t);
void GB_TWI_write_datastring( char * gb_data);
/*
uint8_t TWI_read_dataAck(void)
This function is used to read one byte from a device and request another byte of data after
the transmission is complete by sending the acknowledge bit.
This function returns the received byte.
*/
uint8_t GB_TWI_read_dataAck(void);
/*
uint8_t TWI_read_dataNack(void)
This function is used to read one byte from a device and then not requesting another byte
and therefore stopping the current transmission.
This function returns the received byte.
*/
uint8_t GB_TWI_read_dataNack(void);
uint8_t GB_i2c_readReg( uint8_t* gb_data, uint16_t gb_length);
  /*
  void I2C_stop(void)
  This function disables the TWI peripheral completely and therefore disconnects
  the device from the bus.
   */
void GB_TWI_stop(void);

uint8_t gb_write_data , gb_recv_data;

#include "GB_i2c master.cpp"

#endif