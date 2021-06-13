
/* reading from Interrupted Ring Buffer*/
char  GB_getchar_UART1()             // <--->   Serial.read()
{
	
	
	char gb_c;

	gb_c = gb_Rx_Buffer_UART1[gb_RX_Rd_Index_UART1]; /* get one from the buffer..*/
	
	if(++gb_RX_Rd_Index_UART1 > gb_RX_BUFFER_SIZE_UART1) /* wrap the pointer */
	gb_RX_Rd_Index_UART1 = 0;
	if(gb_RX_Counter_UART1)
	gb_RX_Counter_UART1--; /* keep a count (buffer size) */
	return gb_c ;//return char *
	//printString0("n \n ");
}
void GB_getstring_UART1()
{
	GB_printString0(" Number of characters received : ");
	GB_decimel0(gb_RX_No_of_byte_UART1);
	GB_printString0("\n");
	uint8_t gb_x=0;
	memset(gb_RX_DATA_UART1, '\0',gb_RX_BUFFER_SIZE_UART1);
	while (gb_RX_Counter_UART1)
	{
		gb_RX_DATA_UART1[gb_x]= GB_getchar_UART1();
		gb_x++;
	}
	GB_printString0(gb_RX_DATA_UART1);
	//_delay_ms(1000);
	
}
char* GB_search_buffer(const char* gb_search)
{
	char* gb_p;
	int gb_bufferlen = strlen((const char * )gb_RX_DATA_UART1);
	if(gb_bufferlen < gb_RX_BUFFER_SIZE_UART1)
	gb_p= strstr ((const char *)gb_RX_DATA_UART1,gb_search);
	//printString0(p);
	return (gb_p);
}
void GB_send_command(const char * gb_command)
{
	GB_printString1(gb_command);
	
}
int GB_RFR_UART1( unsigned int gb_timeout)
{
		unsigned long gb_timeIn = GB_millis();	// Timestamp coming into function
		uint8_t gb_received = 0;
		memset(gb_RX_DATA_UART1, '\0',gb_RX_BUFFER_SIZE_UART1);
		
		while (GB_millis() - gb_timeIn < gb_timeout) // While we haven't timed out
		{
			//printString0("k\n");
			if(gb_RX_Counter_UART1)
			{
				gb_RX_DATA_UART1[gb_received]= GB_getchar_UART1();
				gb_received++;
				
				
			}
		}
		
		//printString0(RX_DATA_UART1);
		if (gb_received > 0) // If we received any characters
		return 0; // Return unkown response error code
		else // If we haven't received any characters
		return 2; // Return the timeout error code
		
	}
int GB_RFR_UART1(const char * gb_rsp, unsigned int gb_timeout)
{
	unsigned long gb_timeIn = GB_millis();	// Timestamp coming into function
	uint8_t gb_received = 0;
	memset(gb_RX_DATA_UART1, '\0',gb_RX_BUFFER_SIZE_UART1);
	//printString0(" Number of characters received : ");
	//decimel0(RX_No_of_byte_UART1);
	//printString0("\n");
	
	while (GB_millis() - gb_timeIn < gb_timeout) // While we haven't timed out
	{
		//printString0("k\n");
		if(gb_RX_Counter_UART1)
		{
			gb_RX_DATA_UART1[gb_received]= GB_getchar_UART1();
			//decimel0(received);
			//printString0(" ");
			//UART_TxChar0(RX_DATA_UART1[received]);
			//printString0("\n");
			gb_received++;
			if(GB_search_buffer(gb_rsp)) return 1;
			
		}
	}
	
	//printString0(RX_DATA_UART1);
	if (gb_received > 0) // If we received any characters
	return 0; // Return unkown response error code
	else // If we haven't received any characters
	return 2; // Return the timeout error code
	
}

//Command ESP initialise functions in both client and webserver
void GB_esp8266_getmode()
{
	GB_send_command("AT+CWMODE?\r\n");
	int gb_rsp = GB_RFR_UART1("OK", 1000);
	//printString0(RX_DATA_UART1);
	if(gb_rsp==1)
	{
		//printString0(RX_DATA_UART1);
		//printString0("command is successfully send\n");
		char * gb_p = strchr(gb_RX_DATA_UART1, ':');
		if(gb_p!=NULL)
		{
			char gb_mode = *(gb_p+1);
			gb_CWMODE= gb_mode-48;
			if(gb_CWMODE==1) GB_printString0("Station mode selected\n");
			if(gb_CWMODE==2) GB_printString0("SoftAP mode selected\n");
			if(gb_CWMODE==3) GB_printString0("SoftAP+Station mode selected\n");
		}
	}
	else
	{
		//printString0("Error in receiving command (check the command) or timeout has happened\n");
		//esp8266_rst();
		GB_printString0(gb_RX_DATA_UART1);
	}
}
void GB_esp8266_connectiontype()
{
	GB_send_command("AT+CIPMUX?\r\n");
	int gb_rsp = GB_RFR_UART1("OK", 1000);
	if(gb_rsp==1)
	{
		// printString0("command is successfully send\n");
		char * gb_p = strchr(gb_RX_DATA_UART1, ':');
		if(gb_p!=NULL)
		{
			char gb_mode = *(gb_p+1);
			int gb_num = gb_mode-48;
			if(gb_num==0) GB_printString0("Single connection - configured as client\n");
			if(gb_num==1) GB_printString0("multiple connection - configured as server\n");
		}
		
	}
	else
	{
		// printString0("Error in receiving response (check the command) or timeout has happened\n");
		GB_printString0(gb_RX_DATA_UART1);
	}
}
void GB_esp8266_getAP()
{
	char gb_ssid[20];
	GB_send_command("AT+CWJAP?\r\n");
	int gb_rsp = GB_RFR_UART1("OK", 1000);
	if(gb_rsp==1)
	{
		
		if (strstr(gb_RX_DATA_UART1, "No AP") != NULL)   GB_printString0("No AP is connected\n");
		char * gb_p = strstr(gb_RX_DATA_UART1,"+CWJAP:");
		if(gb_p!=NULL)
		{
			gb_p +=  strlen("+CWJAP") +2;
			char * gb_q=strchr(gb_p,'"');
			strncpy(gb_ssid,gb_p,gb_q-gb_p);
			GB_printString0("Connected to Wifi:");
			GB_printString0(gb_ssid);
			GB_printString0("\n");
		}
		
	}else
	{
		//printString0("Error in receiving response (check the command ) or timeout has happened\n");
		GB_printString0(gb_RX_DATA_UART1);
	}
	
}
void GB_esp8266_setAP(const char * gb_ssid, const char * gb_pass)
{
	char gb_setAP[40];
	sprintf(gb_setAP,"AT+CWJAP=\"%s\",\"%s\"\r\n",gb_ssid,gb_pass);
	
	
	GB_send_command(gb_setAP);
	int gb_rsp = GB_RFR_UART1("OK",16000);
	

	if(gb_rsp==1)
	{
		
		GB_printString0("WiFi is  connected to :");
		GB_printString0(gb_ssid);
		GB_printString0("\n");
		
	}
	else
	{
		GB_printString0("Error in connecting to :");
		GB_printString0(gb_ssid);
		GB_printString0("\n");
		char * gb_p = strstr(gb_RX_DATA_UART1,"+CWJAP:");
		if(gb_p!=NULL)
		{
			gb_p+= strlen("+CWJAP:");
			char gb_error_code = *gb_p;
			int gb_num = gb_error_code-48;
			if(gb_num==1) GB_printString0("Connection timeout \n");
			if(gb_num==2) GB_printString0("Wrong password \n");
			if(gb_num==3) GB_printString0("cannot find the target AP\n");
			if(gb_num==4) GB_printString0("connection failed \n");
		}
	}
}
void GB_esp8266_disconnect()
{
	
	GB_send_command("AT+CWQAP\r\n");
	//printString0("Sending \n");
	int gb_rsp = GB_RFR_UART1("WIFI DISCONNECT",1000);
	if(gb_rsp==1) GB_printString0("WIFI is  disconnected  \n");
	if(gb_rsp==0) GB_printString0("WIFI is already disconnected \n");
}
void GB_esp8266_IPadress()
{
	
	GB_send_command("AT+CIFSR\r\n");
	int gb_rsp = GB_RFR_UART1("OK",1000);
	char gb_staip[20],gb_stamac[20],gb_apip[20],gb_apmac[20];
	memset(gb_staip, '\0',sizeof(gb_staip));
	memset(gb_stamac, '\0',sizeof(gb_stamac));
	memset(gb_apip, '\0',sizeof(gb_apip));
	memset(gb_apmac, '\0',sizeof(gb_apmac));
	while(gb_rsp==1)
	{
		GB_printString0("IP address is \n");
		if(gb_CWMODE==1)    //if station mode is selected
		{
			//Station IP
			char * gb_p = strstr(gb_RX_DATA_UART1,"+CIFSR:STAIP");
			gb_p += strlen("+CWJAP:STAIP")+2;
			char * gb_q=strchr(gb_p,'"');
			strncpy(gb_staip,gb_p,gb_q-gb_p);
			GB_printString0("IP address of Station is :");
			GB_printString0(gb_staip);
			
			// Station MAC
			char * gb_r = strstr(gb_RX_DATA_UART1,"+CIFSR:STAMAC");
			gb_r += strlen("+CIFSR:STAMAC")+2;
			char * gb_s =strchr(gb_r,'"');
			strncpy(gb_stamac,gb_r,gb_s-gb_r);
			GB_printString0("\n Mac address of Station is :");
			GB_printString0(gb_stamac);
			break;
		}
		if(gb_CWMODE==2)
		{
			// Soft AP IP
			char * gb_p = strstr(gb_RX_DATA_UART1,"+CIFSR:APIP");
			gb_p += strlen("+CIFSR:APIP")+2;
			char * gb_q=strchr(gb_p,'"');
			strncpy(gb_apip,gb_p,gb_q-gb_p);
			GB_printString0("IP address of SoftAP is :");
			GB_printString0(gb_apip);
			
			// Soft AP MAC
			char * gb_r = strstr(gb_RX_DATA_UART1,"+CIFSR:APMAC");
			gb_r += strlen("+CIFSR:APMAC")+2;
			char * gb_s =strchr(gb_r,'"');
			strncpy(gb_apmac,gb_r,gb_s-gb_r);
			GB_printString0("\n Mac address of SoftAP is :");
			GB_printString0(gb_apmac);
			break;
		}
		if(gb_CWMODE==3)
		{
			//Station IP
			char * gb_p = strstr(gb_RX_DATA_UART1,"+CIFSR:STAIP");
			gb_p += strlen("+CWJAP:STAIP")+2;
			char * gb_q=strchr(gb_p,'"');
			strncpy(gb_staip,gb_p,gb_q-gb_p);
			GB_printString0("IP address of Station is :");
			GB_printString0(gb_staip);
			GB_printString0("\n");
			
			// Station MAC
			char * gb_r = strstr(gb_RX_DATA_UART1,"+CIFSR:STAMAC");
			gb_r += strlen("+CIFSR:STAMAC")+2;
			char * gb_s =strchr(gb_r,'"');
			strncpy(gb_stamac,gb_r,gb_s-gb_r);
			GB_printString0("Mac address of Station is :");
			GB_printString0(gb_stamac);
			GB_printString0("\n");
			
			
			// Soft AP IP
			char * gb_a = strstr(gb_RX_DATA_UART1,"+CIFSR:APIP");
			gb_a += strlen("+CIFSR:APIP")+2;
			char * gb_b=strchr(gb_a,'"');
			strncpy(gb_apip,gb_a,gb_b-gb_a);
			GB_printString0("IP address of SoftAP is :");
			GB_printString0(gb_apip);
			GB_printString0("\n");
			
			
			// Soft AP MAC
			char * gb_c = strstr(gb_RX_DATA_UART1,"+CIFSR:APMAC");
			gb_c += strlen("+CIFSR:APMAC")+2;
			char * gb_d =strchr(gb_c,'"');
			strncpy(gb_apmac,gb_c,gb_d-gb_c);
			GB_printString0("Mac address of SoftAP is :");
			GB_printString0(gb_apmac);
			GB_printString0("\n");
			break;
		}
	}
}
void GB_esp8266_listAP()
{
	
	GB_send_command("AT+CWLAP\r\n");
	int gb_rsp = GB_RFR_UART1("OK",7000);
	//printString0(RX_DATA_UART1);
	//printString0("\n");
	if(gb_rsp==0)
	{
		GB_printString0("WiFi networks near are: \n");
		GB_printString0(gb_RX_DATA_UART1);
		GB_printString0("\n");
	}else
	GB_printString0(gb_RX_DATA_UART1);
}
void GB_esp8266_rst()
{
	
	GB_send_command("AT+RST\r\n");
	int gb_rsp = GB_RFR_UART1("OK",4000);
	if(gb_rsp==1) GB_printString0(gb_RX_DATA_UART1);
}
