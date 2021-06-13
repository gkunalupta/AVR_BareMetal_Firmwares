


	//*************ESP Client Functions***********************
	void GB_esp8266_initialise_client()
	{
		
		GB_esp8266_getmode();
		GB_esp8266_connectiontype();
		GB_esp8266_setAP("JioFiber 2.4ghz","Mansi5481");
		GB_esp8266_getAP();
		
		GB_printString0("\nSETAP Command\n");
		//esp8266_setAP("JioFiber 2.4ghz","Mansi5481");
		// esp8266_setAP("KG","12345678");
		//esp8266_disconnect();
		//esp8266_listAP();
		//esp8266_IPadress();
		//esp8266_rst();
	}

		//AT+CIPSTART
		void GB_esp8266_connectTCPserver(const char * gb_url,int gb_port)
		{
			char gb_buff[100];
			sprintf(gb_buff,"AT+CIPSTART=\"TCP\",\"%s\",%u\r\n",gb_url,gb_port);
			GB_send_command(gb_buff);
			int gb_rsp = GB_RFR_UART1("OK", 2000);
			if(gb_rsp==1) GB_printString0("\n Successfully connected to server \n");
			if(gb_rsp==0) GB_printString0("\n Already connected to server \n");
		}
		//FOR CALCULATING LENGTH OF GET COMMAND
		char * GB_esp8266_command(const char * gb_urlpath)
		{
			//char get_command[100];
			memset(gb_get_command, '\0',sizeof(gb_get_command));
			sprintf(gb_get_command,"GET %s\r\n",gb_urlpath);
			//printString0(GET);
			//printString0("\n");
			return (char *) gb_get_command;
		}//FOR CALCULATING LENGTH OF GET COMMAND
		const char * GB_esp8266_command(const char * gb_urlpath, int gb_val)
		{
			//char get_command[100];
			memset(gb_get_command, '\0',sizeof(gb_get_command));
			sprintf(gb_get_command,"GET %s=%u\r\n",gb_urlpath,gb_val);
			GB_printString0(gb_get_command);
			GB_printString0("\n");
			return (char * )gb_get_command;
		}//FOR CALCULATING LENGTH OF GET COMMAND
		const char * GB_esp8266_command(const char * gb_urlpath, char * gb_val)
		{
			//char get_command[100];
			memset(gb_get_command, '\0',sizeof(gb_get_command));
			sprintf(gb_get_command,"GET %s=%s\r\n",gb_urlpath,gb_val);
			GB_printString0(gb_get_command);
			GB_printString0("\n");
			return (char * )gb_get_command;
		}
		//AT+CIPSEND
		void GB_esp8266_cipsend(int  gb_val, const char *  gb_urlpath)
		{
			
			char  gb_send[15];
			int  gb_get_command_length = strlen(GB_esp8266_command( gb_urlpath, gb_val));
			//decimel0(strlen(esp8266_command(urlpath,senseval)));
			//printString0("\n");
			//printString0(esp8266_command(urlpath));
			//printString0("\n");
			sprintf( gb_send,"AT+CIPSEND=%u\r\n", gb_get_command_length);
			GB_send_command( gb_send);
			//printString0(send);
			int  gb_rsp = GB_RFR_UART1(">",2000);
			//if (rsp==1) printString0(RX_DATA_UART1);
			GB_printString0( gb_RX_DATA_UART1);
			
		}
		//AT+CIPSEND
		void GB_esp8266_cipsend(char *  gb_val, const char *  gb_urlpath)
		{
			
			char  gb_send[15];
			int  gb_get_command_length = strlen(GB_esp8266_command( gb_urlpath, gb_val));
			//decimel0(strlen(esp8266_command(urlpath,senseval)));
			//printString0("\n");
			//printString0(esp8266_command(urlpath));
			//printString0("\n");
			sprintf( gb_send,"AT+CIPSEND=%u\r\n", gb_get_command_length);
			GB_send_command( gb_send);
			//printString0(send);
			int  gb_rsp = GB_RFR_UART1(">",2000);
			//if (rsp==1) printString0(RX_DATA_UART1);
			GB_printString0( gb_RX_DATA_UART1);
			
		}
				void GB_esp8266_cipsend(float  gb_val, const char *  gb_urlpath)
				{
					
					char  gb_send[15];
					int  gb_get_command_length = strlen(GB_esp8266_command( gb_urlpath,gb_val));
					//decimel0(strlen(esp8266_command(urlpath,senseval)));
					//printString0("\n");
					//printString0(esp8266_command(urlpath));
					//printString0("\n");
					sprintf(gb_send,"AT+CIPSEND=%u\r\n",gb_get_command_length);
					GB_send_command(gb_send);
					//printString0(send);
					int gb_rsp = GB_RFR_UART1(">",2000);
					//if (rsp==1) printString0(RX_DATA_UART1);
					GB_printString0(gb_RX_DATA_UART1);
					
				}
		//GET COMMAND
		void GB_esp8266_tcpgetcommand(const char * gb_urlpath)    //when no field value has to be updated like path for json file
		{
			char gb_buff[100];
			memset(gb_buff, '\0',sizeof(gb_buff));
			sprintf(gb_buff,"GET %s\r\n",gb_urlpath);
			GB_printString0(gb_buff);
			GB_send_command(gb_buff);
			GB_RFR_UART1("CLOSE", 2000);
			GB_printString0("\n");
			_delay_ms(100);
			GB_printString0(gb_RX_DATA_UART1);
		}//GET COMMAND
		void GB_esp8266_tcpgetcommand(const char * gb_urlpath, int gb_val)   //when field has to be updated like updating the sendor value.
		{    char gb_buff[100];
			memset(gb_buff, '\0',sizeof(gb_buff));
			sprintf(gb_buff,"GET %s=%u\r\n",gb_urlpath,gb_val);
			GB_printString0(gb_buff);
			GB_send_command(gb_buff);
			GB_RFR_UART1("CLOSE", 2000);
			GB_printString0("\n");
			_delay_ms(100);
			GB_printString0(gb_RX_DATA_UART1);
		}//GET COMMAND
		void GB_esp8266_tcpgetcommand(const char * gb_urlpath, char * gb_val)   //when field has to be updated like updating the sendor value.
		{    char gb_buff[100];
			memset(gb_buff, '\0',sizeof(gb_buff));
			sprintf(gb_buff,"GET %s=%s\r\n",gb_urlpath,gb_val);
			GB_printString0(gb_buff);
			GB_send_command(gb_buff);
			GB_RFR_UART1("CLOSE", 2000);
			GB_printString0("\n");
			_delay_ms(100);
			GB_printString0(gb_RX_DATA_UART1);
		}
		