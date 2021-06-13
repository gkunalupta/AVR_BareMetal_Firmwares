void GB_nrf_trans_config()
{
	_delay_ms(200);
	
	gb_nrf_ss_enable;
	GB_MA_SPI0_send_byte_conti(gb_write_command | gb_config_reg);
	gb_nrf_ss_disable;
	
}
