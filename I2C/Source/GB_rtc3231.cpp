

void GB_rtc3231_32khz_output()
{
	GB_TWI_start();
	GB_TWI_write_slave_address(gb_RTC_WADDR);  // Slave address with Write mode
	GB_TWI_write_data(gb_Status_reg);   // Address of Status Register of RTC3231
	GB_TWI_write_data(0b00000000);  //Data for Status register of RTC3231
	GB_TWI_stop();
}
void GB_rtc3231_init(void)
{
	GB_printString0("Initialize \n");
	GB_TWI_init_master();
	GB_printString0("start  \n");
	GB_TWI_start();
	GB_printString0("write address \n");
	GB_TWI_write_slave_address(gb_RTC_WADDR);
	GB_printString0(" address of control register \n");
	GB_TWI_write_data(gb_Control_reg);
	GB_printString0(" data for control register \n");
	GB_TWI_write_data(0b00101000);     //convert Temp, No alarm interrupt on INT pin
	GB_printString0("data for status register \n");
	GB_TWI_write_data(0x00001000);     //Enable 32K square signal
	GB_printString0("stop \n");
	GB_TWI_stop();
	GB_printString0("Rtc initialized \n");
}
void GB_rtc3231_read_time(struct gb_rtc_time *gb_time)
{
	GB_TWI_start();
	GB_TWI_read_slave_address(gb_RTC_RADDR);
	gb_time->gb_sec = GB_bcdToDec(GB_TWI_read_dataAck());
	gb_time->gb_min = GB_bcdToDec(GB_TWI_read_dataAck());
	gb_time->gb_hour =GB_bcdToDec(GB_TWI_read_dataNack());
	GB_TWI_stop();
}
void GB_rtc3231_read_date(struct gb_rtc_date *gb_date)
{
	GB_TWI_start();
	GB_TWI_write_slave_address(gb_RTC_WADDR);
	GB_TWI_write_data(gb_Date_reg);
	GB_TWI_stop();
	
	GB_TWI_start();
	GB_TWI_read_slave_address(gb_RTC_RADDR);
	gb_date->gb_wday = GB_bcdToDec(GB_TWI_read_dataAck());
	gb_date->gb_day = GB_bcdToDec(GB_TWI_read_dataAck());
	gb_date->gb_month = GB_bcdToDec(GB_TWI_read_dataAck());
	gb_date->gb_year =GB_bcdToDec(GB_TWI_read_dataNack());
	GB_TWI_stop();

}
void GB_rtc3231_read_datetime(struct gb_rtc_time *gb_time, struct gb_rtc_date *gb_date)
{
	GB_TWI_start();
	GB_TWI_read_slave_address(gb_RTC_RADDR);
	gb_time->gb_sec = GB_bcdToDec(GB_TWI_read_dataAck());
	gb_time->gb_min = GB_bcdToDec(GB_TWI_read_dataAck());
	gb_time->gb_hour = GB_bcdToDec(GB_TWI_read_dataAck());
	gb_date->gb_wday = GB_bcdToDec(GB_TWI_read_dataAck());
	gb_date->gb_day = GB_bcdToDec(GB_TWI_read_dataAck());
	gb_date->gb_month = GB_bcdToDec(GB_TWI_read_dataAck());
	gb_date->gb_year = GB_bcdToDec(GB_TWI_read_dataNack());
	GB_TWI_stop();
}
void GB_dispalytimedate(struct gb_rtc_time *gb_time, struct gb_rtc_date *gb_date)
{
	GB_decimel0(gb_date->gb_day);
	GB_printString0("/");
	GB_decimel0(gb_date->gb_month);
	GB_printString0("/");
	GB_decimel0(gb_date->gb_year);
	GB_printString0("   , ");
	GB_decimel0(gb_date->gb_wday);
	GB_printString0("   , ");
	GB_decimel0(gb_time->gb_hour);
	GB_printString0(":");
	GB_decimel0(gb_time->gb_min);
	GB_printString0(":");
	GB_decimel0(gb_time->gb_sec);
	GB_printString0("\n");
	
}
void GB_displaydate (struct gb_rtc_date *gb_date)
{
	GB_decimel0(gb_date->gb_day);
	GB_printString0("/");
	GB_decimel0(gb_date->gb_month);
	GB_printString0("/");
	GB_decimel0(gb_date->gb_year);
	GB_printString0("   , ");
	GB_decimel0(gb_date->gb_wday);
	GB_printString0("   , ");
}
void GB_rtc3231_write_time(struct gb_rtc_time *gb_time)
{
	GB_TWI_start();
	GB_TWI_write_slave_address(gb_RTC_WADDR);
	GB_TWI_write_data(gb_Time_reg);
	GB_TWI_write_data(gb_time->gb_sec);
	GB_TWI_write_data(gb_time->gb_min);
	GB_TWI_write_data(gb_time->gb_hour);
	GB_TWI_stop();
}
void GB_rtc3231_write_date(struct gb_rtc_date *gb_date)
{
	GB_TWI_start();
	GB_TWI_write_slave_address(gb_RTC_WADDR);
	GB_TWI_write_data(gb_Date_reg);
	GB_TWI_write_data(gb_date->gb_wday);
	GB_TWI_write_data(gb_date->gb_day);
	GB_TWI_write_data(gb_date->gb_month);
	GB_TWI_write_data(gb_date->gb_year);
	GB_TWI_stop();
}
void GB_set_alarm1(struct gb_alarm1 *gb_AL1)
{
	GB_TWI_start();
	GB_TWI_write_slave_address(gb_RTC_WADDR);
	GB_TWI_write_data(gb_Alarm1_reg);
	GB_TWI_write_data(gb_AL1->gb_sec);
	GB_TWI_write_data(gb_AL1->gb_min);
	GB_TWI_write_data(gb_AL1->gb_hour);
	GB_TWI_write_data(gb_AL1->gb_wday);
	GB_TWI_write_data(gb_AL1->gb_day);
	GB_TWI_stop();
}
void GB_setdatetime(struct gb_rtc_time *gb_rt, struct gb_rtc_date *gb_rd)
{
	gb_rt->gb_sec=00;
	gb_rt->gb_min=0x37;
	gb_rt->gb_hour=0x23;
	gb_rd->gb_wday=07;
	gb_rd->gb_day=0x03;
	gb_rd->gb_month=0x01;
	gb_rd->gb_year=0x21;
	GB_rtc3231_write_date(gb_rd);
	GB_rtc3231_write_time(gb_rt);
}
uint8_t GB_DS3231_getTemperature(void)
{
	
	uint8_t gb_msb;
	uint8_t gb_lsb;
	GB_TWI_start();
	GB_TWI_write_slave_address(gb_RTC_WADDR);
	GB_TWI_write_data(gb_Temp_reg);
	GB_TWI_stop();

	GB_TWI_start();
	GB_TWI_read_slave_address(gb_RTC_RADDR);
	gb_msb= GB_TWI_read_dataAck();
	gb_lsb=GB_TWI_read_dataNack();
	GB_TWI_stop();
	
	return (float)gb_msb + ((gb_lsb >> 6) * 0.25f);
}
