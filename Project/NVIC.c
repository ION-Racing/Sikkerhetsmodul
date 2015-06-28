#include "stm32f4xx.h"

/**
  * @brief  Configures the NVIC
  * @param  None
  * @retval None
  */
	
	NVIC_InitTypeDef  NVIC_InitStructure;
	
void InitNVIC(void)
{

	// CAN1 Receive Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = CAN1_RX0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/*
	FLT inputs, all of the faults are active high. i.e. if a
	fault occours the signal goes low. If a fault occours the 
	microcontroller should respons by opening the shutdown circuit;
	see shutdown.c
	----------------------------------------------------------------
	PD8		:	BMS FLT
	PD9 	:	IMD FLT
	PD10	:	BSPD FLT
	*/
 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/*Wheelsensor1 (PD9), Start button (PE7)
	and stop button (PE8)
	*/

	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	
}
