/*
 * i2cmaster2011.cpp
 *
 * Created: 4/12/2020 2:56:40 AM
 * Author : kunal
 */ 
#ifndef I2C MASTER_H_
#define I2C MASTER_H_

// Program for Master Mode
// Check Code2 for Slave Mode Program
#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>
#include <string.h>
//#include "uarts.h"
void TWI_start(void);
void TWI_repeated_start(void);
void TWI_init_master(void);
void TWI_write_slave_address(uint8_t);
void TWI_read_slave_address(uint8_t);
void TWI_write_data(uint8_t);
void TWI_write_datastring( char * data);
uint8_t TWI_read_dataAck(void);
uint8_t TWI_read_dataNack(void);
uint8_t i2c_readReg( uint8_t* data, uint16_t length);

void TWI_stop(void);

uint8_t write_data , recv_data;

#include "i2c master.cpp"

#endif