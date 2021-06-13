//************ESP Server functions**********************//
#include <avr/pgmspace.h>

uint32_t gb_flag=0;
int gb_channelid;

//Function to wait for client to browse Ip address on Browser
uint32_t GB_getstring_ESP8266FORSERVER(char* gb_IP);
//function to find length of data to send
const char * GB_esp8266_webpagedatacommand(int gb_val);
//Function to send AT+CIPSEND command
void GB_esp8266_serverdatatoclientcipsend();
void GB_esp8266_serverdatatoclientcipsend(int  gb_val);
void GB_esp8266_webpagedata();
void GB_esp8266_webpageclose();
void GB_esp8266_iniserver();

#include "GB_esp8266_server.cpp"