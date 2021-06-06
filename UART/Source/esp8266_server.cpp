//Function to wait for client to browse Ip address on Browser
uint32_t getstring_ESP8266FORSERVER(char* IP)
{
	char * p;
	char * q;
	int ID=0;
	uint8_t x=0;
	memset(RX_DATA_UART1, '\0',RX_BUFFER_SIZE_UART1);
	printString0("***********Waiting For Client to connect********\n");
	printString0("Browse IP address on the local Web-Browser:");
	printString0(IP);
	printString0("\n");
	while (flag==0)
	{
		RX_DATA_UART1[x]= getchar_UART1();
		x++;
		p= strstr(RX_DATA_UART1,"Connection");
		if(p)    //IF Client is connected
		{
			printString0("*******Client Connected*******\n");
			q = strstr(RX_DATA_UART1,"+IPD");
			q += strlen("+IPD");
			channelid = *(q+1);
			// printString0(RX_DATA_UART1);
			// printString0("\n");
			printString0("Channel ID with Client is:");
			UART_TxChar0(channelid);
			flag=1;
			printString0("\n");
			decimel0(flag);
			printString0("\n");
			memset(Rx_Buffer_UART1, '\0',RX_BUFFER_SIZE_UART1);
			return 1;
		}
		
	}
	return 0;
}
char webpagedata[200];
const char signMessage[] PROGMEM = {"I AM PREDATOR,  UNSEEN COMBATANT. CREATED BY THE UNITED STATES DEPART"};
//function to find length of data to send
const char * esp8266_webpagedatacommand(int val)
{
	memset(webpagedata, '\0',sizeof(webpagedata));
	//sprintf(webpagedata,"<!DOCTYPE HTML><HTML><HEAD><TITLE>My first web pa</TITLE></HEAD><BODY><CENTER><B>Gettobyte......Temperature :%u</B></CENTER> </BODY>0</HTML>\r\n",val);
	sprintf(webpagedata,signMessage);
	printString0(webpage);
	printString0("\n");
	return (char * )webpage;
}

//Function to send AT+CIPSEND command
void esp8266_serverdatatoclientcipsend()
{
	printString0("\n****Sending details of data to be send (AT+CIPSEND)********\n");
	char send[15];
	//int get_command_length = strlen(webpage);
	int get_command_length = strlen(signMessage);
	sprintf(send,"AT+CIPSEND=%i,%u\r\n",channelid-48,get_command_length);
	printString0("Channel id is :");
	UART_TxChar0(channelid);
	printString0("\n");
	send_command(send);
	//printString0(send);
	int rsp = RFR_UART1(">",2000);
	//if (rsp==1) printString0(RX_DATA_UART1);
	printString0(RX_DATA_UART1);
	
}

void esp8266_serverdatatoclientcipsend(int  val)
{
	printString0("\n****Sending details of data to be send (AT+CIPSEND)********\n");
	char send[15];
	int get_command_length = strlen(esp8266_webpagedatacommand(val));
	sprintf(send,"AT+CIPSEND=%i,%u\r\n",channelid-48,get_command_length);
	printString0("Channel id is :");
	UART_TxChar0(channelid);
	printString0("\n");
	send_command(send);
	//printString0(send);
	int rsp = RFR_UART1(">",2000);
	if (rsp==1) printString0(RX_DATA_UART1);
	//printString0(RX_DATA_UART1);
}
void esp8266_webpagedata()
{
	printString0("\n************Sending Data to Client************\n");
	//send_command(webpage);
	send_command(signMessage);
	int rsp = RFR_UART1("SEND OK",2000);
	if (rsp==1) printString0(RX_DATA_UART1);
	//printString0(RX_DATA_UART1);
}
void esp8266_webpageclose()
{
	printString0("\n****************Closing the session with Client**************\n");
	char cipclose[20];
	sprintf(cipclose,"AT+CIPCLOSE=%u\r\n",channelid-48);
	send_command(cipclose);
	int rsp = RFR_UART1("OK",1000);
	if (rsp==1) printString0(RX_DATA_UART1);
	
}



void esp8266_iniserver()
{
	
	send_command("AT+CWMODE?\r\n");
	getstring_UART1();

	//Configure as Station
	send_command("AT+CWMODE=1\r\n");
	getstring_UART1();

	//Start Multiple connection
	send_command("AT+CIPMUX=1\r\n");
	getstring_UART1();


	send_command("AT+CWJAP?\r\n");
	getstring_UART1();


	//Connect To wifi
	//send_command("AT+CWJAP=\"JioFiber 2.4ghz\",\"Mansi5481\"\r\n");
	//RFR_UART1(16000);

	//Created A Server
	send_command("AT+CIPSERVER=1,80\r\n");
	RFR_UART1(1000);
}