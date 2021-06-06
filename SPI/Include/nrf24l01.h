
#ifndef NRF24L01_H_
#define NRF24L01_H_

#define nrf_ss_enable spi_port &= ~(1<<SS)
#define nrf_ss_disable spi_port |= (1<<SS)

// read_command & regist_name :: 00011111 & 000AAAAA= 000AAAAA
#define read_command 0x1f  //00011111
// write_command | regist_name :: 00100000 | 000AAAAA = 001AAAAA
#define write_command 0x20 //001AAAAA

//Register names: AAAAA
#define config_reg 0x00
#define en_aa 0x01
#define en_rxaddr 0x02
#define setup_aw 0x03
#define setup_retr 0x04
#define rf_ch 0x05
#define rf_setup 0x06
#define status 0x07
#define Obser_tx 0x08
#define rpd 0x09
#define rx_addr_p0 0x0A
#define rx_addr_p1 0x0B
#define rx_addr_p2 0x0C
#define rx_addr_p3 0x0D
#define rx_addr_p4 0x0E
#define rx_addr_p5 0x0F
#define tx_addr 0x10
#define rx_pw_p0 0x11
#define rx_pw_p1 0x12
#define rx_pw_p2 0x13
#define rx_pw_p3 0x14
#define rx_pw_p4 0x15
#define rx_pw_p5 0x16
#define fifo_status 0x17
#define dynpd 0x1C
#define feature 0x1D

void nrf_trans_config();

#include "nrf24l01.cpp"

#endif