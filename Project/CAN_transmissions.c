#include "stm32f4xx.h"
#include "stm32f4xx_CAN.h"
#include "CAN_messages.h"

//Function prototypes
void CAN_Tx(uint16_t,uint8_t,uint16_t[]);
CanRxMsg CAN_Rx(void);
void Tx_setDefault_values(CanTxMsg*);
void Rx_setDefault_values(CanRxMsg*);


/*
CAN-Bus transmit function.
*/
void CAN_Tx(uint16_t ID, uint8_t DLC, uint16_t data[])
	{
		CanTxMsg TxMsg;	  
		TxMsg.RTR = CAN_RTR_DATA;
		TxMsg.IDE = CAN_ID_STD;
		TxMsg.DLC = DLC;
		if(DLC > 0)
		{
			uint8_t n;
			for(n=0; n < DLC; n+=2)
			{
					TxMsg.Data[n] 	= data[n];		//each datafield is 8 bit;
					TxMsg.Data[n+1] = data[n]<<8; //so split the data in two.
			}
			CAN_Transmit(CAN1,&TxMsg);
		}
	}
	
	uint8_t CAN_ECHO_SENT = 0;
	
	void sendEchoCAN()
	{
		CAN_Tx(CAN_ECHO,0,0);
		TIM_Cmd(TIM4,ENABLE); //ENABLE TIM4
		TIM4->CNT = 0;				//Reset TIM4
		CAN_ECHO_SENT = 1;		//set global flag
	}
	
	void ParseMessageCAN()
	{
		
	}

void Rx_setDefault_values(CanRxMsg* Rx)
	{
		
	}