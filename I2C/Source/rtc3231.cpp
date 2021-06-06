

void rtc3231_32khz_output()
{
	TWI_start();
	TWI_write_slave_address(RTC_WADDR);  // Slave address with Write mode
	TWI_write_data(Status_reg);   // Address of Status Register of RTC3231
	TWI_write_data(0b00000000);  //Data for Status register of RTC3231
	TWI_stop();
}
void rtc3231_init(void)
{
	printString0("Initialize \n");
	TWI_init_master();
	printString0("start  \n");
	TWI_start();
	printString0("write address \n");
	TWI_write_slave_address(RTC_WADDR);
	printString0(" address of control register \n");
	TWI_write_data(Control_reg);
	printString0(" data for control register \n");
	TWI_write_data(0b00101000);     //convert Temp, No alarm interrupt on INT pin
	printString0("data for status register \n");
	TWI_write_data(0x00001000);     //Enable 32K square signal
	printString0("stop \n");
	TWI_stop();
	printString0("Rtc initialized \n");
}
void rtc3231_read_time(struct rtc_time *time)
{
	TWI_start();
	TWI_read_slave_address(RTC_RADDR);
	time->sec = bcdToDec(TWI_read_dataAck());
	time->min = bcdToDec(TWI_read_dataAck());
	time->hour =bcdToDec(TWI_read_dataNack());
	TWI_stop();
}
void rtc3231_read_date(struct rtc_date *date)
{
	TWI_start();
	TWI_write_slave_address(RTC_WADDR);
	TWI_write_data(Date_reg);
	TWI_stop();
	
	TWI_start();
	TWI_read_slave_address(RTC_RADDR);
	date->wday = bcdToDec(TWI_read_dataAck());
	date->day = bcdToDec(TWI_read_dataAck());
	date->month = bcdToDec(TWI_read_dataAck());
	date->year = bcdToDec(TWI_read_dataNack());
	TWI_stop();

}
void rtc3231_read_datetime(struct rtc_time *time, struct rtc_date *date)
{
	TWI_start();
	TWI_read_slave_address(RTC_RADDR);
	time->sec = bcdToDec(TWI_read_dataAck());
	time->min = bcdToDec(TWI_read_dataAck());
	time->hour = bcdToDec(TWI_read_dataAck());
	date->wday = bcdToDec(TWI_read_dataAck());
	date->day = bcdToDec(TWI_read_dataAck());
	date->month = bcdToDec(TWI_read_dataAck());
	date->year = bcdToDec(TWI_read_dataNack());
	TWI_stop();
}
void dispalytimedate(struct rtc_time *time, struct rtc_date *date)
{
	decimel0(date->day);
	printString0("/");
	decimel0(date->month);
	printString0("/");
	decimel0(date->year);
	printString0("   , ");
	decimel0(date->wday);
	printString0("   , ");
	decimel0(time->hour);
	printString0(":");
	decimel0(time->min);
	printString0(":");
	decimel0(time->sec);
	printString0("\n");
	
}
void displaydate (struct rtc_date *date)
{
	decimel0(date->day);
	printString0("/");
	decimel0(date->month);
	printString0("/");
	decimel0(date->year);
	printString0("   , ");
	decimel0(date->wday);
	printString0("   , ");
}
void rtc3231_write_time(struct rtc_time *time)
{
	TWI_start();
	TWI_write_slave_address(RTC_WADDR);
	TWI_write_data(Time_reg);
	TWI_write_data(time->sec);
	TWI_write_data(time->min);
	TWI_write_data(time->hour);
	TWI_stop();
}
void rtc3231_write_date(struct rtc_date *date)
{
	TWI_start();
	TWI_write_slave_address(RTC_WADDR);
	TWI_write_data(Date_reg);
	TWI_write_data(date->wday);
	TWI_write_data(date->day);
	TWI_write_data(date->month);
	TWI_write_data(date->year);
	TWI_stop();
}
void set_alarm1(struct alarm1 *AL1)
{
	TWI_start();
	TWI_write_slave_address(RTC_WADDR);
	TWI_write_data(Alarm1_reg);
	TWI_write_data(AL1->sec);
	TWI_write_data(AL1->min);
	TWI_write_data(AL1->hour);
	TWI_write_data(AL1->wday);
	TWI_write_data(AL1->day);
	TWI_stop();
}
void setdatetime(struct rtc_time *rt, struct rtc_date *rd)
{
	rt->sec=00;
	rt->min=0x37;
	rt->hour=0x23;
	rd->wday=07;
	rd->day=0x03;
	rd->month=0x01;
	rd->year=0x21;
	rtc3231_write_date(rd);
	rtc3231_write_time(rt);
}
uint8_t DS3231_getTemperature(void)
{
	
	uint8_t msb;
	uint8_t lsb;
	TWI_start();
	TWI_write_slave_address(RTC_WADDR);
	TWI_write_data(Temp_reg);
	TWI_stop();

	TWI_start();
	TWI_read_slave_address(RTC_RADDR);
	msb= TWI_read_dataAck();
	lsb=TWI_read_dataNack();
	TWI_stop();
	
	return (float)msb + ((lsb >> 6) * 0.25f);
}
