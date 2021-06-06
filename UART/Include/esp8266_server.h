//************ESP Server functions**********************//
#include <avr/pgmspace.h>

uint32_t flag=0;
int channelid;

//Function to wait for client to browse Ip address on Browser
uint32_t getstring_ESP8266FORSERVER(char* IP);
//function to find length of data to send
const char * esp8266_webpagedatacommand(int val);
//Function to send AT+CIPSEND command
void esp8266_serverdatatoclientcipsend();
void esp8266_serverdatatoclientcipsend(int  val);
void esp8266_webpagedata();
void esp8266_webpageclose();
void esp8266_iniserver();

#include "esp8266_server.cpp"