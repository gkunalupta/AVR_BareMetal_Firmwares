/*
 * nrf24l01 receiver.cpp
 *
 * Created: 23-04-2021 15:47:49
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
	    GB_MA_SPI0_send_byte_conti(gb_rpd & gb_read_command);
	    GB_MA_SPI0_read_byte();
	    gb_nrf_ss_disable;
	    _delay_ms(100);
	    
    }
}

