


	//*************ESP Client Functions***********************
	void esp8266_initialise_client()
	{
		
		esp8266_getmode();
		esp8266_connectiontype();
		esp8266_setAP("JioFiber 2.4ghz","Mansi5481");
		esp8266_getAP();
		
		printString0("\nSETAP Command\n");
		//esp8266_setAP("JioFiber 2.4ghz","Mansi5481");
		// esp8266_setAP("KG","12345678");
		//esp8266_disconnect();
		//esp8266_listAP();
		//esp8266_IPadress();
		//esp8266_rst();
	}

		//AT+CIPSTART
		void esp8266_connectTCPserver(const char * url,int port)
		{
			char buff[100];
			sprintf(buff,"AT+CIPSTART=\"TCP\",\"%s\",%u\r\n",url,port);
			send_command(buff);
			int rsp = RFR_UART1("OK", 2000);
			if(rsp==1) printString0("\n Successfully connected to server \n");
			if(rsp==0) printString0("\n Already connected to server \n");
		}
		//FOR CALCULATING LENGTH OF GET COMMAND
		char * esp8266_command(const char * urlpath)
		{
			//char get_command[100];
			memset(get_command, '\0',sizeof(get_command));
			sprintf(get_command,"GET %s\r\n",urlpath);
			//printString0(GET);
			//printString0("\n");
			return (char *) get_command;
		}//FOR CALCULATING LENGTH OF GET COMMAND
		const char * esp8266_command(const char * urlpath, int val)
		{
			//char get_command[100];
			memset(get_command, '\0',sizeof(get_command));
			sprintf(get_command,"GET %s=%u\r\n",urlpath,val);
			printString0(get_command);
			printString0("\n");
			return (char * )get_command;
		}//FOR CALCULATING LENGTH OF GET COMMAND
		const char * esp8266_command(const char * urlpath, char * val)
		{
			//char get_command[100];
			memset(get_command, '\0',sizeof(get_command));
			sprintf(get_command,"GET %s=%s\r\n",urlpath,val);
			printString0(get_command);
			printString0("\n");
			return (char * )get_command;
		}
		//AT+CIPSEND
		void esp8266_cipsend(int val, const char * urlpath)
		{
			
			char send[15];
			int get_command_length = strlen(esp8266_command(urlpath,val));
			//decimel0(strlen(esp8266_command(urlpath,senseval)));
			//printString0("\n");
			//printString0(esp8266_command(urlpath));
			//printString0("\n");
			sprintf(send,"AT+CIPSEND=%u\r\n",get_command_length);
			send_command(send);
			//printString0(send);
			int rsp = RFR_UART1(">",2000);
			//if (rsp==1) printString0(RX_DATA_UART1);
			printString0(RX_DATA_UART1);
			
		}
		//AT+CIPSEND
		void esp8266_cipsend(char * val, const char * urlpath)
		{
			
			char send[15];
			int get_command_length = strlen(esp8266_command(urlpath,val));
			//decimel0(strlen(esp8266_command(urlpath,senseval)));
			//printString0("\n");
			//printString0(esp8266_command(urlpath));
			//printString0("\n");
			sprintf(send,"AT+CIPSEND=%u\r\n",get_command_length);
			send_command(send);
			//printString0(send);
			int rsp = RFR_UART1(">",2000);
			//if (rsp==1) printString0(RX_DATA_UART1);
			printString0(RX_DATA_UART1);
			
		}
				void esp8266_cipsend(float val, const char * urlpath)
				{
					
					char send[15];
					int get_command_length = strlen(esp8266_command(urlpath,val));
					//decimel0(strlen(esp8266_command(urlpath,senseval)));
					//printString0("\n");
					//printString0(esp8266_command(urlpath));
					//printString0("\n");
					sprintf(send,"AT+CIPSEND=%u\r\n",get_command_length);
					send_command(send);
					//printString0(send);
					int rsp = RFR_UART1(">",2000);
					//if (rsp==1) printString0(RX_DATA_UART1);
					printString0(RX_DATA_UART1);
					
				}
		//GET COMMAND
		void esp8266_tcpgetcommand(const char * urlpath)    //when no field value has to be updated like path for json file
		{
			char buff[100];
			memset(buff, '\0',sizeof(buff));
			sprintf(buff,"GET %s\r\n",urlpath);
			printString0(buff);
			send_command(buff);
			RFR_UART1("CLOSE", 2000);
			printString0("\n");
			_delay_ms(100);
			printString0(RX_DATA_UART1);
		}//GET COMMAND
		void esp8266_tcpgetcommand(const char * urlpath, int val)   //when field has to be updated like updating the sendor value.
		{    char buff[100];
			memset(buff, '\0',sizeof(buff));
			sprintf(buff,"GET %s=%u\r\n",urlpath,val);
			printString0(buff);
			send_command(buff);
			RFR_UART1("CLOSE", 2000);
			printString0("\n");
			_delay_ms(100);
			printString0(RX_DATA_UART1);
		}//GET COMMAND
		void esp8266_tcpgetcommand(const char * urlpath, char * val)   //when field has to be updated like updating the sendor value.
		{    char buff[100];
			memset(buff, '\0',sizeof(buff));
			sprintf(buff,"GET %s=%s\r\n",urlpath,val);
			printString0(buff);
			send_command(buff);
			RFR_UART1("CLOSE", 2000);
			printString0("\n");
			_delay_ms(100);
			printString0(RX_DATA_UART1);
		}
		