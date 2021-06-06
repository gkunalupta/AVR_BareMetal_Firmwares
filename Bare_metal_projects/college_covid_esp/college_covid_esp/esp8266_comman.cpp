
/* reading from Interrupted Ring Buffer*/
char  getchar_UART1()             // <--->   Serial.read()
{
	
	
	char c;

	c = Rx_Buffer_UART1[RX_Rd_Index_UART1]; /* get one from the buffer..*/
	
	if(++RX_Rd_Index_UART1 > RX_BUFFER_SIZE_UART1) /* wrap the pointer */
	RX_Rd_Index_UART1 = 0;
	if(RX_Counter_UART1)
	RX_Counter_UART1--; /* keep a count (buffer size) */
	return c ;//return char *
	//printString0("n \n ");
}
void getstring_UART1()
{
	printString0(" Number of characters received : ");
	decimel0(RX_No_of_byte_UART1);
	printString0("\n");
	uint8_t x=0;
	memset(RX_DATA_UART1, '\0',RX_BUFFER_SIZE_UART1);
	while (RX_Counter_UART1)
	{
		RX_DATA_UART1[x]= getchar_UART1();
		x++;
	}
	printString0(RX_DATA_UART1);
	//_delay_ms(1000);
	
}
char* search_buffer(const char* search)
{
	char* p;
	int bufferlen = strlen((const char * )RX_DATA_UART1);
	if(bufferlen < RX_BUFFER_SIZE_UART1)
	p= strstr ((const char *)RX_DATA_UART1,search);
	//printString0(p);
	return (p);
}
void send_command(const char * command)
{
	printString1(command);
	
}
int RFR_UART1( unsigned int timeout)
{
		unsigned long timeIn = millis();	// Timestamp coming into function
		uint8_t received = 0;
		memset(RX_DATA_UART1, '\0',RX_BUFFER_SIZE_UART1);
		
		while (millis() - timeIn < timeout) // While we haven't timed out
		{
			//printString0("k\n");
			if(RX_Counter_UART1)
			{
				RX_DATA_UART1[received]= getchar_UART1();
				received++;
				
				
			}
		}
		
		//printString0(RX_DATA_UART1);
		if (received > 0) // If we received any characters
		return 0; // Return unkown response error code
		else // If we haven't received any characters
		return 2; // Return the timeout error code
		
	}
int RFR_UART1(const char * rsp, unsigned int timeout)
{
	unsigned long timeIn = millis();	// Timestamp coming into function
	uint8_t received = 0;
	memset(RX_DATA_UART1, '\0',RX_BUFFER_SIZE_UART1);
	//printString0(" Number of characters received : ");
	//decimel0(RX_No_of_byte_UART1);
	//printString0("\n");
	
	while (millis() - timeIn < timeout) // While we haven't timed out
	{
		//printString0("k\n");
		if(RX_Counter_UART1)
		{
			RX_DATA_UART1[received]= getchar_UART1();
			//decimel0(received);
			//printString0(" ");
			//UART_TxChar0(RX_DATA_UART1[received]);
			//printString0("\n");
			received++;
			if(search_buffer(rsp)) return 1;
			
		}
	}
	
	//printString0(RX_DATA_UART1);
	if (received > 0) // If we received any characters
	return 0; // Return unkown response error code
	else // If we haven't received any characters
	return 2; // Return the timeout error code
	
}

//Command ESP initialise functions in both client and webserver
void esp8266_getmode()
{
	send_command("AT+CWMODE?\r\n");
	int rsp = RFR_UART1("OK", 1000);
	//printString0(RX_DATA_UART1);
	if(rsp==1)
	{
		//printString0(RX_DATA_UART1);
		//printString0("command is successfully send\n");
		char * p = strchr(RX_DATA_UART1, ':');
		if(p!=NULL)
		{
			char mode = *(p+1);
			CWMODE= mode-48;
			if(CWMODE==1) printString0("Station mode selected\n");
			if(CWMODE==2) printString0("SoftAP mode selected\n");
			if(CWMODE==3) printString0("SoftAP+Station mode selected\n");
		}
	}
	else
	{
		//printString0("Error in receiving command (check the command) or timeout has happened\n");
		//esp8266_rst();
		printString0(RX_DATA_UART1);
	}
}
void esp8266_connectiontype()
{
	send_command("AT+CIPMUX?\r\n");
	int rsp = RFR_UART1("OK", 1000);
	if(rsp==1)
	{
		// printString0("command is successfully send\n");
		char * p = strchr(RX_DATA_UART1, ':');
		if(p!=NULL)
		{
			char mode = *(p+1);
			int num = mode-48;
			if(num==0) printString0("Single connection - configured as client\n");
			if(num==1) printString0("multiple connection - configured as server\n");
		}
		
	}
	else
	{
		// printString0("Error in receiving response (check the command) or timeout has happened\n");
		printString0(RX_DATA_UART1);
	}
}
void esp8266_getAP()
{
	char ssid[20];
	send_command("AT+CWJAP?\r\n");
	int rsp = RFR_UART1("OK", 1000);
	if(rsp==1)
	{
		
		if (strstr(RX_DATA_UART1, "No AP") != NULL)   printString0("No AP is connected\n");
		char * p = strstr(RX_DATA_UART1,"+CWJAP:");
		if(p!=NULL)
		{
			p +=  strlen("+CWJAP") +2;
			char * q=strchr(p,'"');
			strncpy(ssid,p,q-p);
			printString0("Connected to Wifi:");
			printString0(ssid);
			printString0("\n");
		}
		
	}else
	{
		//printString0("Error in receiving response (check the command ) or timeout has happened\n");
		printString0(RX_DATA_UART1);
	}
	
}
void esp8266_setAP(const char * ssid, const char * pass)
{
	char setAP[40];
	sprintf(setAP,"AT+CWJAP=\"%s\",\"%s\"\r\n",ssid,pass);
	
	
	send_command(setAP);
	int rsp = RFR_UART1("OK",16000);
	

	if(rsp==1)
	{
		
		printString0("WiFi is  connected to :");
		printString0(ssid);
		printString0("\n");
		
	}
	else
	{
		printString0("Error in connecting to :");
		printString0(ssid);
		printString0("\n");
		char * p = strstr(RX_DATA_UART1,"+CWJAP:");
		if(p!=NULL)
		{
			p+= strlen("+CWJAP:");
			char error_code = *p;
			int num = error_code-48;
			if(num==1) printString0("Connection timeout \n");
			if(num==2) printString0("Wrong password \n");
			if(num==3) printString0("cannot find the target AP\n");
			if(num==4) printString0("connection failed \n");
		}
	}
}
void esp8266_disconnect()
{
	
	send_command("AT+CWQAP\r\n");
	//printString0("Sending \n");
	int rsp = RFR_UART1("WIFI DISCONNECT",1000);
	if(rsp==1) printString0("WIFI is  disconnected  \n");
	if(rsp==0) printString0("WIFI is already disconnected \n");
}
void esp8266_IPadress()
{
	
	send_command("AT+CIFSR\r\n");
	int rsp = RFR_UART1("OK",1000);
	char staip[20],stamac[20],apip[20],apmac[20];
	memset(staip, '\0',sizeof(staip));
	memset(stamac, '\0',sizeof(stamac));
	memset(apip, '\0',sizeof(apip));
	memset(apmac, '\0',sizeof(apmac));
	while(rsp==1)
	{
		printString0("IP address is \n");
		if(CWMODE==1)    //if station mode is selected
		{
			//Station IP
			char * p = strstr(RX_DATA_UART1,"+CIFSR:STAIP");
			p += strlen("+CWJAP:STAIP")+2;
			char * q=strchr(p,'"');
			strncpy(staip,p,q-p);
			printString0("IP address of Station is :");
			printString0(staip);
			
			// Station MAC
			char * r = strstr(RX_DATA_UART1,"+CIFSR:STAMAC");
			r += strlen("+CIFSR:STAMAC")+2;
			char * s =strchr(r,'"');
			strncpy(stamac,r,s-r);
			printString0("\n Mac address of Station is :");
			printString0(stamac);
			break;
		}
		if(CWMODE==2)
		{
			// Soft AP IP
			char * p = strstr(RX_DATA_UART1,"+CIFSR:APIP");
			p += strlen("+CIFSR:APIP")+2;
			char * q=strchr(p,'"');
			strncpy(apip,p,q-p);
			printString0("IP address of SoftAP is :");
			printString0(apip);
			
			// Soft AP MAC
			char * r = strstr(RX_DATA_UART1,"+CIFSR:APMAC");
			r += strlen("+CIFSR:APMAC")+2;
			char * s =strchr(r,'"');
			strncpy(apmac,r,s-r);
			printString0("\n Mac address of SoftAP is :");
			printString0(apmac);
			break;
		}
		if(CWMODE==3)
		{
			//Station IP
			char * p = strstr(RX_DATA_UART1,"+CIFSR:STAIP");
			p += strlen("+CWJAP:STAIP")+2;
			char * q=strchr(p,'"');
			strncpy(staip,p,q-p);
			printString0("IP address of Station is :");
			printString0(staip);
			printString0("\n");
			
			// Station MAC
			char * r = strstr(RX_DATA_UART1,"+CIFSR:STAMAC");
			r += strlen("+CIFSR:STAMAC")+2;
			char * s =strchr(r,'"');
			strncpy(stamac,r,s-r);
			printString0("Mac address of Station is :");
			printString0(stamac);
			printString0("\n");
			
			
			// Soft AP IP
			char * a = strstr(RX_DATA_UART1,"+CIFSR:APIP");
			a += strlen("+CIFSR:APIP")+2;
			char * b=strchr(a,'"');
			strncpy(apip,a,b-a);
			printString0("IP address of SoftAP is :");
			printString0(apip);
			printString0("\n");
			
			
			// Soft AP MAC
			char * c = strstr(RX_DATA_UART1,"+CIFSR:APMAC");
			c += strlen("+CIFSR:APMAC")+2;
			char * d =strchr(c,'"');
			strncpy(apmac,c,d-c);
			printString0("Mac address of SoftAP is :");
			printString0(apmac);
			printString0("\n");
			break;
		}
	}
}
void esp8266_listAP()
{
	
	send_command("AT+CWLAP\r\n");
	int rsp = RFR_UART1("OK",7000);
	//printString0(RX_DATA_UART1);
	//printString0("\n");
	if(rsp==0)
	{
		printString0("WiFi networks near are: \n");
		printString0(RX_DATA_UART1);
		printString0("\n");
	}else
	printString0(RX_DATA_UART1);
}
void esp8266_rst()
{
	
	send_command("AT+RST\r\n");
	int rsp = RFR_UART1("OK",4000);
	if(rsp==1) printString0(RX_DATA_UART1);
}
