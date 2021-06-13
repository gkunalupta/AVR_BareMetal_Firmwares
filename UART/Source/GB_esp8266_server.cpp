//Function to wait for client to browse Ip address on Browser
uint32_t GB_getstring_ESP8266FORSERVER(char* gb_IP)
{
	char * gb_p;
	char * gb_q;
	int gb_ID=0;
	uint8_t gb_x=0;
	memset(gb_RX_DATA_UART1, '\0',gb_RX_BUFFER_SIZE_UART1);
	GB_printString0("***********Waiting For Client to connect********\n");
	GB_printString0("Browse IP address on the local Web-Browser:");
	GB_printString0(gb_IP);
	GB_printString0("\n");
	while (gb_flag==0)
	{
		gb_RX_DATA_UART1[gb_x]= GB_getchar_UART1();
		gb_x++;
		gb_p= strstr(gb_RX_DATA_UART1,"Connection");
		if(gb_p)    //IF Client is connected
		{
			GB_printString0("*******Client Connected*******\n");
			gb_q = strstr(gb_RX_DATA_UART1,"+IPD");
			gb_q += strlen("+IPD");
			gb_channelid = *(gb_q+1);
			// printString0(RX_DATA_UART1);
			// printString0("\n");
			GB_printString0("Channel ID with Client is:");
			GB_UART_TxChar0(gb_channelid);
			gb_flag=1;
			GB_printString0("\n");
			GB_decimel0(gb_flag);
			GB_printString0("\n");
			memset(gb_Rx_Buffer_UART1, '\0',gb_RX_BUFFER_SIZE_UART1);
			return 1;
		}
		
	}
	return 0;
}
char gb_webpagedata[200];
const char gb_signMessage[] PROGMEM = {"I AM PREDATOR,  UNSEEN COMBATANT. CREATED BY THE UNITED STATES DEPART"};
//function to find length of data to send
const char * GB_esp8266_webpagedatacommand(int gb_val)
{
	memset(gb_webpagedata, '\0',sizeof(gb_webpagedata));
	//sprintf(gb_webpagedata,"<!DOCTYPE HTML><HTML><HEAD><TITLE>My first web pa</TITLE></HEAD><BODY><CENTER><B>Gettobyte......Temperature :%u</B></CENTER> </BODY>0</HTML>\r\n",val);
	sprintf(gb_webpagedata,gb_signMessage);
	GB_printString0(gb_webpage);
	GB_printString0("\n");
	return (char * )gb_webpage;
}

//Function to send AT+CIPSEND command
void GB_esp8266_serverdatatoclientcipsend()
{
	GB_printString0("\n****Sending details of data to be send (AT+CIPSEND)********\n");
	char gb_send[15];
	//int get_command_length = strlen(webpage);
	int gb_get_command_length = strlen(gb_signMessage);
	sprintf(gb_send,"AT+CIPSEND=%i,%u\r\n",gb_channelid-48,gb_get_command_length);
	GB_printString0("Channel id is :");
	GB_UART_TxChar0(gb_channelid);
	GB_printString0("\n");
	GB_send_command(gb_send);
	//printString0(send);
	int gb_rsp = GB_RFR_UART1(">",2000);
	//if (rsp==1) printString0(RX_DATA_UART1);
	GB_printString0(gb_RX_DATA_UART1);
	
}

void GB_esp8266_serverdatatoclientcipsend(int  gb_val)
{
	GB_printString0("\n****Sending details of data to be send (AT+CIPSEND)********\n");
	char gb_send[15];
	int gb_get_command_length = strlen(GB_esp8266_webpagedatacommand(gb_val));
	sprintf(gb_send,"AT+CIPSEND=%i,%u\r\n",gb_channelid-48,gb_get_command_length);
	GB_printString0("Channel id is :");
	GB_UART_TxChar0(gb_channelid);
	GB_printString0("\n");
	GB_send_command(gb_send);
	//printString0(send);
	int gb_rsp = GB_RFR_UART1(">",2000);
	if (gb_rsp==1) GB_printString0(gb_RX_DATA_UART1);
	//printString0(RX_DATA_UART1);
}
void GB_esp8266_webpagedata()
{
	GB_printString0("\n************Sending Data to Client************\n");
	//send_command(webpage);
	GB_send_command(gb_signMessage);
	int gb_rsp = GB_RFR_UART1("SEND OK",2000);
	if (gb_rsp==1) GB_printString0(gb_RX_DATA_UART1);
	//printString0(RX_DATA_UART1);
}
void GB_esp8266_webpageclose()
{
	GB_printString0("\n****************Closing the session with Client**************\n");
	char gb_cipclose[20];
	sprintf(gb_cipclose,"AT+CIPCLOSE=%u\r\n",gb_channelid-48);
	GB_send_command(gb_cipclose);
	int gb_rsp = GB_RFR_UART1("OK",1000);
	if (gb_rsp==1) GB_printString0(gb_RX_DATA_UART1);
	
}



void GB_esp8266_iniserver()
{
	
	GB_send_command("AT+CWMODE?\r\n");
	GB_getstring_UART1();

	//Configure as Station
	GB_send_command("AT+CWMODE=1\r\n");
	GB_getstring_UART1();

	//Start Multiple connection
	GB_send_command("AT+CIPMUX=1\r\n");
	GB_getstring_UART1();


	GB_send_command("AT+CWJAP?\r\n");
	GB_getstring_UART1();


	//Connect To wifi
	//send_command("AT+CWJAP=\"JioFiber 2.4ghz\",\"Mansi5481\"\r\n");
	//RFR_UART1(16000);

	//Created A Server
	GB_send_command("AT+CIPSERVER=1,80\r\n");
	GB_RFR_UART1(1000);
}