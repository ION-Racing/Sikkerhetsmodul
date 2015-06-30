#include "stm32f4xx.h"

/*
Configures USART1 in interrupt mode
*/

void InitUSART()
	{
		//Clock
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		/*
		GPIO USART
		----------
		PA9 	Tx
		PA10	Rx
		*/
		GPIO_InitTypeDef GPIO_initStruct;
		GPIO_initStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
		GPIO_initStruct.GPIO_Mode = GPIO_Mode_AF;
		GPIO_initStruct.GPIO_OType = GPIO_OType_PP;
		GPIO_initStruct.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_Init(GPIOA,&GPIO_initStruct);
		//Alternate function config.
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource9,GPIO_AF_USART1);
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource10,GPIO_AF_USART1);
		/*
		USART configuration
		*/
		USART_InitTypeDef USART_initStruct;
		USART_initStruct.USART_BaudRate = 9600;
		USART_initStruct.USART_WordLength = USART_WordLength_8b;
		USART_initStruct.USART_StopBits = USART_StopBits_1;
		USART_initStruct.USART_Parity = USART_Parity_No;
		USART_initStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_initStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_Init(USART1, &USART_initStruct);
		//Enable interrupt for empty transmit box
		USART_ITConfig(USART1,USART_IT_RXNE, ENABLE);
		USART_Cmd(USART1,ENABLE);
		
		/*
		NVIC configuration
		*/
		NVIC_InitTypeDef NVIC_initStruct;
		NVIC_initStruct.NVIC_IRQChannel = USART1_IRQn;
		NVIC_initStruct.NVIC_IRQChannelCmd = ENABLE;
		NVIC_initStruct.NVIC_IRQChannelPreemptionPriority = 0;
		NVIC_initStruct.NVIC_IRQChannelSubPriority = 1;
		NVIC_Init(&NVIC_initStruct);
		
		USART_SendData(USART1, 'U');
		
	}
	
void USART1_IRQHandler(void)
	{
		if(USART_GetITStatus(USART1,USART_IT_RXNE) != RESET)
		{
			USART_ClearITPendingBit(USART1,USART_IT_RXNE);
			//USART_ReceiveData();
			
		}
	}
