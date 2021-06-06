/*
 * nrf24l01-transmit.cpp
 *
 * Created: 20-11-2020 03:17:58
 * Author : kunal
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include "uarts.h"
#include "spi_master.h"

#include "nrf24l01.h"



int main(void)
{
	UART_Init0();
	MA_SPI0_init_master();
    while (1) 
    {
		_delay_ms(100);
		nrf_ss_enable;
		_delay_us(10);
		MA_SPI0_send_byte_conti(write_command |  (config_reg+1));
		_delay_us(10);
		MA_SPI0_read_byte();
	_delay_us(10);
		nrf_ss_disable;
		_delay_ms(100);
	
		
		
    }
}

