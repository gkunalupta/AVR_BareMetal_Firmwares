//#ifndef GB_ESP8266_COMMAN_H_
//#define GB_ESP8266_COMMAN_H_

char gb_get_command[100];
int gb_senseval=0;


// USART Receiver buffer Ring buffer for UART0 port
#define gb_RX_BUFFER_SIZE_UART0 32
uint8_t gb_Rx_Buffer_UART0[gb_RX_BUFFER_SIZE_UART0+1]; // character array (buffer)
uint8_t gb_RX_Wr_Index_UART0; //index of next char to be put into the buffer  // head
uint8_t gb_RX_Rd_Index_UART0; //index of next char to be fetched from the buffer    //tail
uint8_t gb_RX_Counter_UART0; //a total count of characters in the buffer
bool gb_RX_Buffer_Overflow_UART0; // This flag is set on USART Receiver
// buffer overflow
ISR(USART0_RX_vect)
{
	char gb_rx_byte;
	
	// We only ever get here when an RXC interrupt has occurred;
	// Therefore, we know that there must be at least 1 byte in UDR

	// get the 1st byte
	gb_rx_byte = UDR0;
	GB_UART_TxChar0(gb_rx_byte);
	gb_Rx_Buffer_UART0[gb_RX_Wr_Index_UART0]= gb_rx_byte;   /* put received char in buffer */
	if(++gb_RX_Wr_Index_UART0 > gb_RX_BUFFER_SIZE_UART0)
	gb_RX_Wr_Index_UART0 = 0;
	if(++gb_RX_Counter_UART0 > gb_RX_BUFFER_SIZE_UART0) /* keep a character count */
	{ /* overflow check.. */
		gb_RX_Counter_UART0 = gb_RX_BUFFER_SIZE_UART0; /* if too many chars came */
		gb_RX_Buffer_Overflow_UART0 = 1; /* in before they could be used */
		} /* that could cause an error!! */

		
	}

	char GB_getchar_UART0()
	{
		char gb_c;
		while(gb_RX_Counter_UART0 == 0) /* wait for a character... */
		;
		gb_c = gb_Rx_Buffer_UART0[gb_RX_Rd_Index_UART0]; /* get one from the buffer..*/
		if(++gb_RX_Rd_Index_UART0 > gb_RX_BUFFER_SIZE_UART0) /* wrap the pointer */
		gb_RX_Rd_Index_UART0 = 0;
		if(gb_RX_Counter_UART0)
		gb_RX_Counter_UART0--; /* keep a count (buffer size) */
		return gb_c;
		
	}

    // USART Receiver buffer Ring buffer for UART1 port
	#define gb_RX_BUFFER_SIZE_UART1 255
	uint8_t gb_Rx_Buffer_UART1[gb_RX_BUFFER_SIZE_UART1]; // character array (buffer)
	uint8_t gb_RX_Wr_Index_UART1 =0; //index of next char to be put into the buffer  // head
	uint8_t gb_RX_Rd_Index_UART1=0; //index of next char to be fetched from the buffer    //tail
	uint8_t gb_RX_Counter_UART1=0; //a total count of characters in the buffer
	uint8_t gb_RX_No_of_byte_UART1=0;
	bool gb_RX_Buffer_Overflow_UART1; // This flag is set on USART Receiver // buffer overflow
	char gb_rx_byte;
	char gb_RX_DATA_UART1[gb_RX_BUFFER_SIZE_UART1];

	ISR(USART1_RX_vect)
	{
		
		gb_rx_byte = UDR1;
		gb_Rx_Buffer_UART1[gb_RX_Wr_Index_UART1]= gb_rx_byte;   /* put received char in buffer */
		if(++gb_RX_Wr_Index_UART1 > gb_RX_BUFFER_SIZE_UART1)
		gb_RX_Wr_Index_UART1 = 0;
		if(++gb_RX_Counter_UART1 > gb_RX_BUFFER_SIZE_UART1) /* keep a character count */
		{
			/* overflow check.. */
			gb_RX_Counter_UART1 = gb_RX_BUFFER_SIZE_UART1; /* if too many chars came */
			gb_RX_Buffer_Overflow_UART1 = 1;            /* in before they could be used */
			}                                          /* that could cause an error!! */
			gb_RX_No_of_byte_UART1=gb_RX_Counter_UART1 ;
			//GB_UART_TxChar0(gb_rx_byte);
			
		}
		/* reading from Interrupted Ring Buffer*/
		char  GB_getchar_UART1();            // <--->   Serial.read()
	
		void GB_getstring_UART1();

		char* GB_search_buffer(const char* gb_search);

		void GB_send_command(const char * gb_command);
		int GB_RFR_UART1(const char * gb_rsp, unsigned int gb_timeout);
		int GB_RFR_UART1( unsigned int gb_timeout);
		//Command ESP initialize functions in both client and web server
		int gb_CWMODE=0;
		void GB_esp8266_getmode();
		void GB_esp8266_connectiontype();
		void GB_esp8266_getAP();
		void GB_esp8266_setAP(const char * gb_ssid, const char * gb_pass);
		void GB_esp8266_disconnect();
		void GB_esp8266_IPadress();
		void GB_esp8266_listAP();
		void GB_esp8266_rst();
		
		
		
		
		#include "GB_esp8266_comman.cpp"
		
		//#endif