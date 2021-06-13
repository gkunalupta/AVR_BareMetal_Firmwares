
#ifndef GB_RTC3231_H_
#define GB_RTC3231_H_

#include "GB_i2c master.h"

#include "GB_uarts.h"

// Convert normal decimal numbers to binary coded decimal
uint8_t GB_decimalToBcd(uint8_t gb_val){
	return( (gb_val/10*16) + (gb_val%10) );
}

// Convert binary coded decimal to normal decimal numbers
uint8_t GB_bcdToDec(uint8_t gb_val){
	return( (gb_val/16*10) + (gb_val%16) );
}
#define gb_RTC_WADDR 0b11010000   //Slave Write
#define gb_RTC_RADDR 0b11010001   //Slave Read

#define gb_Status_reg 0x0F
#define gb_Control_reg 0x0E
#define gb_Date_reg 0x03
#define gb_Time_reg 0x00
#define gb_Alarm1_reg 0x07
#define gb_Alarm2_reg 0x0B
#define gb_Temp_reg 0x11

#define gb_Enable_32khz_output 0b00001000    // byte to be send in status register for enabling 32K square wave
#define gb_disable_32khz_output 0b00000000   //byte to be send in status register for disabling 32K square wave
struct gb_rtc_time
{
	uint8_t gb_sec;
	uint8_t gb_min;
	uint8_t gb_hour;
};
struct gb_rtc_date
{
	uint8_t gb_wday;
	uint8_t gb_day;
	uint8_t gb_month;
	uint8_t gb_year;
};
struct gb_alarm1
{
	uint8_t gb_sec;
	uint8_t gb_min;
	uint8_t gb_hour;
	uint8_t gb_wday;
	uint8_t gb_day;
};
struct gb_alarm2
{
	uint8_t gb_sec;
	uint8_t gb_min;
	uint8_t gb_hour;
	uint8_t gb_wday;
	uint8_t gb_day;
};


void GB_rtc3231_32khz_output();
void GB_rtc3231_init(void);
void GB_rtc3231_read_time(struct gb_rtc_time *gb_time);
void GB_rtc3231_read_date(struct gb_rtc_date *gb_date);
void GB_rtc3231_read_datetime(struct gb_rtc_time *gb_time, struct gb_rtc_date *gb_date);
void GB_dispalytimedate(struct gb_rtc_time *gb_time, struct gb_rtc_date *gb_date);
void GB_displaydate (struct gb_rtc_date *gb_date);
void GB_rtc3231_write_time(struct gb_rtc_time *gb_time);
void GB_rtc3231_write_date(struct gb_rtc_date *gb_date);
void GB_set_alarm1(struct gb_alarm1 *gb_AL1);
void GB_setdatetime(struct gb_rtc_time *gb_rt, struct gb_rtc_date *gb_rd);
uint8_t GB_DS3231_getTemperature(void);

#include "GB_rtc3231.cpp"

#endif