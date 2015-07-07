#include "stm32f4xx.h"
#include "stm32f4xx_CAN.h"
#include "Global_variables.h"
#include "watchdog.h"
#include "CAN.h"

uint8_t CANparseEcho(CanRxMsg msg);

CANechod CANecho; //struct typedef for echo status.


/*
CAN Receive
*/
void Init_RxMes(CanRxMsg *RxMessage)
{
	uint8_t ubCounter = 0;

	RxMessage->StdId = 0x00;
	RxMessage->ExtId = 0x00;
	RxMessage->IDE = CAN_ID_STD;
	RxMessage->DLC = 0;
	RxMessage->FMI = 0;
	for (ubCounter = 0; ubCounter < 8; ubCounter++)
	{
		RxMessage->Data[ubCounter] = 0x00;
	}
}


/*
Echo function
*/
	void CANsendEcho()
	{
		//Reset Echo status struct
		CANecho.isSent = 1;
		CANecho.DU = 0;
		CANecho.ECU = 0;
		CANecho.PU = 0;
		CANecho.RPIU = 0;	
		CANTx(CAN_ECHO,0,0);
		
	}
	
	/*
	Function for parsing/filtering can messages.
	@Param CAN_FIFON : FIFO number that contains pending message.
	*/
	
	void CANparseMessage(uint8_t CAN_FIFON)
	{
		CanRxMsg msg;
		CAN_Receive(CAN1,CAN_FIFON,&msg);
		
		if(CANecho.isSent) //if an echo is sent; see if a echo is recived..
			{
			if(CANparseEcho(msg)) return; // if it was a echo message -> done.
			}
	}
	
	
	/*
	 checks if a echo was sent back and if so,
		sets the accompanying flag high.
	
	@param : msg; can message to parse.
	
	@retval 1 : if message matched a echo id.
	@retval 0	: if message did not match a echo id.
	*/
	
uint8_t CANparseEcho(CanRxMsg msg)
	{
			if( (msg.StdId>=ECU_KICKED_CAN) && (msg.StdId <= PU_KICKED_CAN) ){
			switch(msg.StdId){
				case(ECU_KICKED_CAN) 	: 
					return CANecho.ECU = 1;
				case(RPIU_KICKED_CAN) :
					return CANecho.RPIU = 1;
				case(DU_KICKED_CAN)		:
					return CANecho.DU = 1;
				case(PU_KICKED_CAN)		:
					return CANecho.PU = 1;
				default :
					return 0;
			}
		}
			return 0;
	}
	
	
	/*
	checks if all flags are set and if they are;
	reset the CANecho.issent flag to zero,
	resets the timer
	disables the timer
	
	@retval 1 : success
	@retval 0	: failure
	*/
uint8_t CANechoSuccess()
	{
	if(CANecho.ECU && CANecho.RPIU && CANecho.DU && CANecho.PU) //echo success.
		{
			return	1;
		} else return 0;
		
	}
