void nrf_trans_config()
{
	_delay_ms(200);
	
	nrf_ss_enable;
	MA_SPI0_send_byte_conti(write_command | config_reg);
	nrf_ss_disable;
	
}
