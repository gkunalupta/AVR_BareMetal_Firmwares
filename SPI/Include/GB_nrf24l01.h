
#ifndef GB_NRF24L01_H_
#define GB_NRF24L01_H_

#define gb_nrf_ss_enable gb_spi_port &= ~(1<<gb_SPI_SS)
#define gb_nrf_ss_disable gb_spi_port |= (1<<gb_SPI_SS)

// read_command & regist_name :: 00011111 & 000AAAAA= 000AAAAA
#define gb_read_command 0x1f  //00011111
// write_command | regist_name :: 00100000 | 000AAAAA = 001AAAAA
#define gb_write_command 0x20 //001AAAAA

//Register names: AAAAA
#define gb_config_reg 0x00
#define gb_en_aa 0x01
#define gb_en_rxaddr 0x02
#define gb_setup_aw 0x03
#define gb_setup_retr 0x04
#define gb_rf_ch 0x05
#define gb_rf_setup 0x06
#define gb_status 0x07
#define gb_Obser_tx 0x08
#define gb_rpd 0x09
#define gb_rx_addr_p0 0x0A
#define gb_rx_addr_p1 0x0B
#define gb_rx_addr_p2 0x0C
#define gb_rx_addr_p3 0x0D
#define gb_rx_addr_p4 0x0E
#define gb_rx_addr_p5 0x0F
#define gb_tx_addr 0x10
#define gb_rx_pw_p0 0x11
#define gb_rx_pw_p1 0x12
#define gb_rx_pw_p2 0x13
#define gb_rx_pw_p3 0x14
#define gb_rx_pw_p4 0x15
#define gb_rx_pw_p5 0x16
#define gb_fifo_status 0x17
#define gb_dynpd 0x1C
#define gb_feature 0x1D

void gb_nrf_trans_config();

#include "GB_nrf24l01.cpp"

#endif