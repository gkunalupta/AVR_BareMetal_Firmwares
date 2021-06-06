	
	//#include "esp8266_comman.h"
	
	//*************ESP Client Functions***********************
			void esp8266_initialise_client();
		//AT+CIPSTART
		void esp8266_connectTCPserver(const char * url,int port);
		//FOR CALCULATING LENGTH OF GET COMMAND
		char * esp8266_command(const char * urlpath);
		//FOR CALCULATING LENGTH OF GET COMMAND
		const char * esp8266_command(const char * urlpath, int val);
		//FOR CALCULATING LENGTH OF GET COMMAND
		const char * esp8266_command(const char * urlpath, char * val);
		//AT+CIPSEND
		void esp8266_cipsend(int val, const char * urlpath);
		//AT+CIPSEND
		void esp8266_cipsend(char * val, const char * urlpath);
		void esp8266_cipsend(float val, const char * urlpath);
		//GET COMMAND
		void esp8266_tcpgetcommand(const char * urlpath);    //when no field value has to be updated like path for json file
		//GET COMMAND
		void esp8266_tcpgetcommand(const char * urlpath, int val); //  //when field has to be updated like updating the sendor value.
	    //GET COMMAND
		void esp8266_tcpgetcommand(const char * urlpath, char * val);   //when field has to be updated like updating the sendor value.

		
		#include "esp8266_client.cpp"