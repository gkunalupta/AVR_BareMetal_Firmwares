

void GB_MFRC522_WriteRegister(PCD_Register GB_reg, uint8_t value)
{
	gb_MFRC522_CE_pin_low;
	GB_MA_SPI0_send_byte_conti(GB_reg);
	GB_MA_SPI0_send_byte_conti(value);
	gb_MFRC522_CE_pin_high;
}

void GB_MFRC522_WriteRegister(PCD_Register GB_reg, uint8_t count, uint8_t *value)
{
	gb_MFRC522_CE_pin_low;
	GB_MA_SPI0_send_byte_conti(GB_reg);
	for (uint8_t i =0;i<count;i++){
		GB_MA_SPI0_send_byte_conti(value[i]);
	}
	gb_MFRC522_CE_pin_high;
}


uint8_t GB_MFRC522_ReadRegister(PCD_Register GB_reg)
{
	uint8_t gb_x = 0;
	gb_MFRC522_CE_pin_low;
	
	GB_MA_SPI0_exchange_byte((0x80 | GB_reg));
//	GB_MA_SPI0_send_byte_conti(0x80 | GB_reg);
    gb_x = GB_MA_SPI0_exchange_byte(0);
//	gb_x = GB_MA_SPI0_read_byte();
	gb_MFRC522_CE_pin_high;
	return gb_x;
}

void GB_MFRC522_ReadRegister(PCD_Register reg, byte count, byte *values, byte rxalign)
{
	
}

void GB_MFRC522_ClearRegisterBitMask(PCD_Register gb_reg, byte mask)
{
	byte tmp;
	tmp = GB_MFRC522_ReadRegister(gb_reg);
	GB_MFRC522_WriteRegister(gb_reg, tmp & (~mask));     //clear bit mask
}

void GB_MFRC522_SetRegisterBitmask( PCD_Register gb_reg, byte mask)
{
	byte tmp;
	tmp = GB_MFRC522_ReadRegister(gb_reg);
	GB_MFRC522_WriteRegister(gb_reg, tmp | (mask));     //clear bit mask
}
void GB_MFRC522Version()
{
	uint8_t v =  GB_MFRC522_ReadRegister(VersionReg);
	GB_printString0("Firmware Version: 0d");
	GB_decimel0(v);
	switch(v) 
   {
		case 0x88: GB_printString0(" = (clone)\n"); break;
		case 0x90: GB_printString0(" = v0.0\n"); break;
		case 0x91: GB_printString0(" = v1.0\n"); break;
		case 0x92: GB_printString0(" = v2.0\n"); break;
		case 0x12: GB_printString0(" = counterfeit chip\n"); break;
		default: GB_printString0(" = (unknown)\n");
	}	   						   
}

void MFRC522_init()
{
	GB_MFRC522_WriteRegister(TxModeReg, 0x00);
	GB_MFRC522_WriteRegister(RxModeReg, 0x00);
	
	GB_MFRC522_WriteRegister(ModWidthReg, 0x26);
	
	// When communicating with a PICC we need a timeout if something goes wrong.
	// f_timer = 13.56 MHz / (2*TPreScaler+1) where TPreScaler = [TPrescaler_Hi:TPrescaler_Lo].
	// TPrescaler_Hi are the four low bits in TModeReg. TPrescaler_Lo is TPrescalerReg.
	GB_MFRC522_WriteRegister(TModeReg, 0x80);          // TAuto=1; timer starts automatically at the end of the transmission in all communication modes at all speeds
	GB_MFRC522_WriteRegister(TPrescalerReg, 0xA9);     // TPreScaler = TModeReg[3..0]:TPrescalerReg, ie 0x0A9 = 169 => f_timer=40kHz, ie a timer period of 25μs.
	GB_MFRC522_WriteRegister(TReloadRegH, 0x03);       // Reload timer with 0x3E8 = 1000, ie 25ms before timeout.
	GB_MFRC522_WriteRegister(TReloadRegL, 0xE8);
	
	
	GB_MFRC522_WriteRegister(TxASKReg, 0x40);// Default 0x00. Force a 100 % ASK modulation independent of the ModGsPReg register setting
	GB_MFRC522_WriteRegister(ModeReg, 0x3D); // Default 0x3F. Set the preset value for the CRC co processor for the CalcCRC command to 0x6363 (ISO 14443-3 part 6.2.4)		// Enable the antenna driver pins TX1 and TX2 (they were disabled by the reset)
	
	GB_MFRC522_AnteenaOn();                  //Enable the Antenna Driver pins TX1 & TX2(They are disabled by reset)
	
}

void GB_MFRC522_AnteenaOn()
{
	uint8_t gb_x = GB_MFRC522_ReadRegister(TxControlReg);
	if((gb_x & 0x03) != 0x03)
	{
		GB_MFRC522_WriteRegister(TxControlReg, (gb_x | 0x03));
	}
}

gb_MFRC522_statusCodes GB_MFRC522_CommunicateWithPICC(byte command,   //The command to execute
                                                      byte waitIRQ,
													  byte *sendData,
													  byte sendLen,
													  byte *backdata,
													  byte *backlen,
													  byte *validbits,
													  byte rxalign,
													bool checkCRC
													)
{
	byte txLastBits = validbits ? *validbits :0;
	byte bitFraming = (rxalign <<4) + txLastBits;    //RxAlign = BitFramingReg[6..4]. TxLastBits = BitFramingReg[2..0]
// 	GB_printString0("bitFraming");
// 	GB_decimel0(bitFraming);
// 	GB_printString0("\n");
	
	GB_MFRC522_WriteRegister(CommandReg, PCD_Idle);			// Stop any active command.
	GB_MFRC522_WriteRegister(ComIrqReg, 0x7F);					// Clear all seven interrupt request bits
	
	// For PCD to PICC Communication!!
	GB_MFRC522_WriteRegister(FIFOLevelReg, 0x80);				// FlushBuffer = 1, FIFO initialization
	GB_MFRC522_WriteRegister(FIFODataReg, sendLen, sendData);	// Write sendData to the FIFO
	GB_MFRC522_WriteRegister(BitFramingReg, bitFraming);		// Bit adjustments
	GB_MFRC522_WriteRegister(CommandReg, command);				// Execute the command
	if(command = PCD_Transceive){
		GB_MFRC522_SetRegisterBitmask(BitFramingReg, 0x80);     //StartSend=1, transmission of data starts
	}
	
	const uint32_t deadline = GB_millis()+36;
// 	GB_decimel0(deadline);
// 	GB_printString0("\n");
	bool completed = false;
	
	  // _delay_ms(300);
	do {
		byte n = GB_MFRC522_ReadRegister(ComIrqReg);	// ComIrqReg[7..0] bits are: Set1 TxIRq RxIRq IdleIRq HiAlertIRq LoAlertIRq ErrIRq TimerIRq
		//GB_printString0("3\n");
// 		GB_printString0("comirq\n");
  		//GB_decimel0(n);
 	//	GB_printString0("\n");
		if (n & waitIRQ) {					// One of the interrupts that signal success has been set.
			GB_printString0("signal success\n");
		//	GB_printString0("2\n");
			completed = true;
			break;
		}
		if (n & 0x01) {						// Timer interrupt - nothing received in 25ms
			GB_printString0("Timeout\n");
			return STATUS_TIMEOUT;
		}
	//yield();
	//GB_decimel0(GB_millis());
//	GB_printString0("\n");
	}
	while (static_cast<uint32_t> (GB_millis()) < deadline);

	   _delay_ms(30);
//36ms and nothing happened. Communication with the MFRC522 might be down.
if (!completed) {
	return STATUS_TIMEOUT;
}

//Stop now if any errors except collisions were detected.
byte errorRegValue = GB_MFRC522_ReadRegister(ErrorReg); // ErrorReg[7..0] bits are: WrErr TempErr reserved BufferOvfl CollErr CRCErr ParityErr ProtocolErr
if (errorRegValue & 0x13) {	 // BufferOvfl ParityErr ProtocolErr
	GB_printString0("Some error \n");
	return STATUS_ERROR;
}

byte _validbits = 0;
//If the caller wants data back, get it from the MFRC522.
if(backdata && backlen) {
	byte n = GB_MFRC522_ReadRegister(FIFOLevelReg);
// 	GB_printString0("FIFO len");
// 	GB_decimel0(n);
	//GB_printString0("\n");
	if(n > *backlen){
		return STATUS_NO_ROOM;
	}
	
	*backlen = n;
	GB_MFRC522_ReadRegister(FIFODataReg, n, backdata, rxalign);
// 	GB_printString0("FIFO len");
// 	GB_decimel0(*backdata);
//	GB_printString0("\n");
	_validbits = GB_MFRC522_ReadRegister(ControlReg) & 0x07;
	if(validbits){
		*validbits = _validbits;
			}
			return STATUS_OK;
}
	//return STATUS_OK;
}
gb_MFRC522_statusCodes GB_MFRC522_TransceiveData( byte *senddata,  //Pointer to the data to transfer to the FIFO
                                                  byte sendlen,       //Number of bytes to transfer to FIFO
												  byte *backdata,     //nullptr or pointer to buffer if data should be read back after executing the command
												  byte *backlen,      //In: Max no of bytes to write to *backdata. Out: The no of bytes returned.
												  byte *validbits,    //In/Out: The number of valid bits in the last byte
												  byte rxalign,
												  bool checkCRC       //In: True => The last 2 bytes of the response is assumed to be a CRC_A that must be validated
												  )
{
	byte waitIRQ = 0x30;
	return GB_MFRC522_CommunicateWithPICC(PCD_Transceive, waitIRQ, senddata, sendlen, backdata, backlen, validbits, rxalign, checkCRC);
}


gb_MFRC522_statusCodes GB_PICC_REQA_OR_WUPA(byte command, byte *gb_bufferATQA, byte *gb_buffersize)
{
	gb_MFRC522_statusCodes status;
	byte gb_validbits;
	if(gb_bufferATQA == 0 || *gb_buffersize < 2) { // As gb_bufferATQA is a buffer to store the Answer to request, when command REQ is send by PCD.
	 return STATUS_NO_ROOM;                                                   //So this buffer should be pointing to some valid pointer and not to null pointer. And buffer 
	}												   //size should be greater then 2 bytes, ATQA is of 2 bytes.
	
	GB_MFRC522_ClearRegisterBitMask(CollReg,0x80);
	gb_validbits = 7;
	
	status = GB_MFRC522_TransceiveData(&command, 1, gb_bufferATQA, gb_buffersize, &gb_validbits, 0, 0);
	GB_printString0("status -->");
	GB_decimel0(status);
	GB_printString0("\n");
	if( status != STATUS_OK);
	return status;
	
	if(*gb_buffersize !=2 || gb_validbits != 0){
		return STATUS_ERROR;
	}
	
	return STATUS_OK;
	
}

gb_MFRC522_statusCodes GB_PICC_RequestA(byte * bufferATQ, byte *buffersize)
{
	return GB_PICC_REQA_OR_WUPA(PICC_CMD_REQA, bufferATQ, buffersize);
}
bool GB_PICC_IsNewCardPresent()
{
	byte gb_bufferATQ[2]; // We will be sending the Request command. That is in order to detect the PICCs which are in the operating field 
	                     // PCD shall send repeated request commands. PCD will send REQ or WUP in any sequence to detect the PICCs.
						 //REQ commands are transmitted via short frame If PICC is in energizing field for PCD and gets powered up,
						 //it will start listening for valid REQ command. And transmits its ATQ(Answer to request). 
						 //This answer to Request is stored in this buffer. ATQA is a 2 byte number that is returned by PICC.
	byte gb_buffersize = sizeof(gb_bufferATQ);
	// Reset baud rates
	GB_MFRC522_WriteRegister(TxModeReg, 0x00);
	GB_MFRC522_WriteRegister(RxModeReg, 0x00);
	// Reset ModWidthReg
	GB_MFRC522_WriteRegister(ModWidthReg, 0x26);//38 in decimal
	
   gb_MFRC522_statusCodes result = GB_PICC_RequestA(gb_bufferATQ, &gb_buffersize);
 	return (result == STATUS_OK || result == STATUS_COLLISION);
	
	
}