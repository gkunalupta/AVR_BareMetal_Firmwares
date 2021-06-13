/*
 * nrf24l01-transmit.cpp
 *
 * Created: 20-11-2020 03:17:58
 * Author : kunal
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "GB_uarts.h"
#include "GB_spi_master.h"

#include "GB_nrf24l01.h"



int main(void)
{
	GB_UART_Init0();
	GB_MA_SPI0_init_master();
    while (1) 
    {
		_delay_ms(100);
		gb_nrf_ss_enable;
		_delay_us(10);
		GB_MA_SPI0_send_byte_conti(gb_write_command |  (gb_config_reg+1));
		_delay_us(10);
		GB_MA_SPI0_read_byte();
	_delay_us(10);
		gb_nrf_ss_disable;
		_delay_ms(100);
	
		
		
    }
}

