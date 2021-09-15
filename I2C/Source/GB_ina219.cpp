

float CR_LSB =0;
float PW_LSB =0;
void ina219_init()
{
	GB_TWI_init_master();
	
	CR_LSB = 0.0001;
	PW_LSB = 0.002;
	
	
	uint16_t ina219_calvalue = 4096;
	uint8_t ina219_cal_temp;
	ina219_cal_temp = (uint16_t)ina219_calvalue;
// 	GB_decimel0(ina219_cal_temp);
// 	GB_printString0("\n");
	ina219_calvalue >>= 8;
// 		GB_decimel0(ina219_calvalue);
// 		GB_printString0("\n");
	
	uint16_t ina219_confvalue = INA219_CONFIG_BVOLTAGERANGE_32V |
	INA219_CONFIG_GAIN_8_320MV | INA219_CONFIG_BADCRES_12BIT |
	INA219_CONFIG_SADCRES_12BIT_1S_532US |
	INA219_CONFIG_MODE_SANDBVOLT_CONTINUOUS;
	

	uint8_t ina219_conf_temp;
	ina219_conf_temp = (uint8_t)ina219_confvalue;
// 			GB_decimel0(ina219_conf_temp);
// 			GB_printString0("\n");
	ina219_confvalue >>= 8;
// 	GB_decimel0(ina219_confvalue);
// 	GB_printString0("\n");
	
	
	GB_TWI_start();
	GB_TWI_write_slave_address(ina219_WA);
	GB_TWI_write_data(ina219_CAL);
	GB_TWI_write_data((uint8_t)ina219_calvalue);
	GB_TWI_write_data(ina219_cal_temp);
	GB_TWI_stop();
	
	GB_TWI_start();
	GB_TWI_write_slave_address(ina219_WA);
	GB_TWI_write_data(ina219_CONF);
	GB_TWI_write_data((uint8_t)ina219_confvalue);
	GB_TWI_write_data(ina219_conf_temp);
	GB_TWI_stop();
	
}


void ina219_busvoltage()
{
	uint16_t ret;
	
	GB_TWI_start();
	GB_TWI_write_slave_address(ina219_WA);
	GB_TWI_write_data(ina219_BV);
	GB_TWI_stop();
	
	GB_TWI_start();
	GB_TWI_read_slave_address(ina219_RA);
	ret = GB_TWI_read_dataAck();
	ret <<= 8;
	ret |= GB_TWI_read_dataNack();
	
	GB_TWI_stop();
	
// 	GB_decimel0(ret);
// 	GB_printString0("\n");
	
	uint16_t temp;
	float BV;
	temp = ret;
	temp >>= 3;
	BV =  temp * 0.004;
	
// 	GB_decimel0(temp);
// 	GB_printString0("\n");
	
	GB_float_value0(BV);

	
	 
	
}


void ina219_shuntvoltage()
{
	uint16_t ret;
	
	GB_TWI_start();
	GB_TWI_write_slave_address(ina219_WA);
	GB_TWI_write_data(ina219_SV);
	GB_TWI_stop();
	
	GB_TWI_start();
	GB_TWI_read_slave_address(ina219_RA);
	ret = GB_TWI_read_dataAck();
	ret <<= 8;
	ret |= GB_TWI_read_dataNack();
	
	GB_TWI_stop();
	
	float SV;
	SV =  ret * 0.01;
	
	GB_float_value0(SV);

	
}

void ina219_shuntcurrent()
{
	uint16_t ret;
	
	GB_TWI_start();
	GB_TWI_write_slave_address(ina219_WA);
	GB_TWI_write_data(ina219_CR);
	GB_TWI_stop();
	
	GB_TWI_start();
	GB_TWI_read_slave_address(ina219_RA);
	ret = GB_TWI_read_dataAck();
	ret <<= 8;
	ret |= GB_TWI_read_dataNack();
	
	GB_TWI_stop();
	
	float CR;
	CR =  ret * CR_LSB * 1000;
	
	GB_float_value0(CR);

	
}

void ina219_Loadpower()
{
	uint16_t ret;
	
	GB_TWI_start();
	GB_TWI_write_slave_address(ina219_WA);
	GB_TWI_write_data(ina219_PW);
	GB_TWI_stop();
	
	GB_TWI_start();
	GB_TWI_read_slave_address(ina219_RA);
	ret = GB_TWI_read_dataAck();
	ret <<= 8;
	ret |= GB_TWI_read_dataNack();
	
	GB_TWI_stop();
	
	float PW;
	PW =  ret * PW_LSB * 1000;
	
	GB_float_value0(PW);

	
}