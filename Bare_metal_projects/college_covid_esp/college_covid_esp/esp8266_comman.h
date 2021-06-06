//#ifndef ESP8266_COMMAN_H_
//#define ESP8266_COMMAN_H_

char get_command[100];
int senseval=0;


// USART Receiver buffer Ring buffer for UART0 port
#define RX_BUFFER_SIZE_UART0 32
uint8_t Rx_Buffer_UART0[RX_BUFFER_SIZE_UART0+1]; // character array (buffer)
uint8_t RX_Wr_Index_UART0; //index of next char to be put into the buffer  // head
uint8_t RX_Rd_Index_UART0; //index of next char to be fetched from the buffer    //tail
uint8_t RX_Counter_UART0; //a total count of characters in the buffer
bool RX_Buffer_Overflow_UART0; // This flag is set on USART Receiver
// buffer overflow
ISR(USART0_RX_vect)
{
	char rx_byte;
	
	// We only ever get here when an RXC interrupt has occurred;
	// Therefore, we know that there must be at least 1 byte in UDR

	// get the 1st byte
	rx_byte = UDR0;
	UART_TxChar0(rx_byte);
	Rx_Buffer_UART0[RX_Wr_Index_UART0]= rx_byte;   /* put received char in buffer */
	if(++RX_Wr_Index_UART0 > RX_BUFFER_SIZE_UART0)
	RX_Wr_Index_UART0 = 0;
	if(++RX_Counter_UART0 > RX_BUFFER_SIZE_UART0) /* keep a character count */
	{ /* overflow check.. */
		RX_Counter_UART0 = RX_BUFFER_SIZE_UART0; /* if too many chars came */
		RX_Buffer_Overflow_UART0 = 1; /* in before they could be used */
		} /* that could cause an error!! */

		
	}

	char getchar_UART0()
	{
		char c;
		while(RX_Counter_UART0 == 0) /* wait for a character... */
		;
		c = Rx_Buffer_UART0[RX_Rd_Index_UART0]; /* get one from the buffer..*/
		if(++RX_Rd_Index_UART0 > RX_BUFFER_SIZE_UART0) /* wrap the pointer */
		RX_Rd_Index_UART0 = 0;
		if(RX_Counter_UART0)
		RX_Counter_UART0--; /* keep a count (buffer size) */
		return c;
		
	}

    // USART Receiver buffer Ring buffer for UART1 port
	#define RX_BUFFER_SIZE_UART1 255
	uint8_t Rx_Buffer_UART1[RX_BUFFER_SIZE_UART1]; // character array (buffer)
	uint8_t RX_Wr_Index_UART1 =0; //index of next char to be put into the buffer  // head
	uint8_t RX_Rd_Index_UART1=0; //index of next char to be fetched from the buffer    //tail
	uint8_t RX_Counter_UART1=0; //a total count of characters in the buffer
	uint8_t RX_No_of_byte_UART1=0;
	bool RX_Buffer_Overflow_UART1; // This flag is set on USART Receiver // buffer overflow
	char rx_byte;
	char RX_DATA_UART1[RX_BUFFER_SIZE_UART1];

	ISR(USART1_RX_vect)
	{
		
		rx_byte = UDR1;
		Rx_Buffer_UART1[RX_Wr_Index_UART1]= rx_byte;   /* put received char in buffer */
		if(++RX_Wr_Index_UART1 > RX_BUFFER_SIZE_UART1)
		RX_Wr_Index_UART1 = 0;
		if(++RX_Counter_UART1 > RX_BUFFER_SIZE_UART1) /* keep a character count */
		{
			/* overflow check.. */
			RX_Counter_UART1 = RX_BUFFER_SIZE_UART1; /* if too many chars came */
			RX_Buffer_Overflow_UART1 = 1;            /* in before they could be used */
			}                                          /* that could cause an error!! */
			RX_No_of_byte_UART1=RX_Counter_UART1 ;
			//UART_TxChar0(rx_byte);
			
		}
		/* reading from Interrupted Ring Buffer*/
		char  getchar_UART1();            // <--->   Serial.read()
	
		void getstring_UART1();

		char* search_buffer(const char* search);

		void send_command(const char * command);
		int RFR_UART1(const char * rsp, unsigned int timeout);
		int RFR_UART1( unsigned int timeout);
		//Command ESP initialize functions in both client and web server
		int CWMODE=0;
		void esp8266_getmode();
		void esp8266_connectiontype();
		void esp8266_getAP();
		void esp8266_setAP(const char * ssid, const char * pass);
		void esp8266_disconnect();
		void esp8266_IPadress();
		void esp8266_listAP();
		void esp8266_rst();
		
		
		
		
		#include "esp8266_comman.cpp"
		
		//#endif