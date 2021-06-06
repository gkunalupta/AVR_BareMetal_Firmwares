
#ifndef RTC3231_H_
#define RTC3231_H_

#include "i2c master.h"

#include "uarts.h"

// Convert normal decimal numbers to binary coded decimal
uint8_t decimalToBcd(uint8_t val){
	return( (val/10*16) + (val%10) );
}

// Convert binary coded decimal to normal decimal numbers
uint8_t bcdToDec(uint8_t val){
	return( (val/16*10) + (val%16) );
}
#define RTC_WADDR 0b11010000   //Slave Write
#define RTC_RADDR 0b11010001   //Slave Read

#define Status_reg 0x0F
#define Control_reg 0x0E
#define Date_reg 0x03
#define Time_reg 0x00
#define Alarm1_reg 0x07
#define Alarm2_reg 0x0B
#define Temp_reg 0x11

#define Enable_32khz_output 0b00001000    // byte to be send in status register for enabling 32K square wave
#define disable_32khz_output 0b00000000   //byte to be send in status register for disabling 32K square wave
struct rtc_time
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
};
struct rtc_date
{
	uint8_t wday;
	uint8_t day;
	uint8_t month;
	uint8_t year;
};
struct alarm1
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t wday;
	uint8_t day;
};
struct alarm2
{
	uint8_t sec;
	uint8_t min;
	uint8_t hour;
	uint8_t wday;
	uint8_t day;
};


void rtc3231_32khz_output();
void rtc3231_init(void);
void rtc3231_read_time(struct rtc_time *time);
void rtc3231_read_date(struct rtc_date *date);
void rtc3231_read_datetime(struct rtc_time *time, struct rtc_date *date);
void dispalytimedate(struct rtc_time *time, struct rtc_date *date);
void displaydate (struct rtc_date *date);
void rtc3231_write_time(struct rtc_time *time);
void rtc3231_write_date(struct rtc_date *date);
void set_alarm1(struct alarm1 *AL1);
void setdatetime(struct rtc_time *rt, struct rtc_date *rd);
uint8_t DS3231_getTemperature(void);

#include "rtc3231.cpp"

#endif