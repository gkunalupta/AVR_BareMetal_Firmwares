/*
 * nrf24l01 receiver.cpp
 *
 * Created: 23-04-2021 15:47:49
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
	    MA_SPI0_send_byte_conti(rpd & read_command);
	    MA_SPI0_read_byte();
	    nrf_ss_disable;
	    _delay_ms(100);
	    
    }
}

