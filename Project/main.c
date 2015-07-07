//includes
#include "stm32f4xx.h"
#include "stm32f4xx_GPIO.h"
#include "GPIO.h"
#include "NVIC.h"
#include "CAN.h"
#include "EXTI.h"
#include "TIM.h"
#include "Global_variables.h"
#include "math.h"
#include "systick.h"
#include "watchdog.h"
#include "CAN_messages.h"
#include "CAN_functions.h"
#include "ADC.h"
#include "USART.h"

//Macros
#define ACK 1

//Variable declerations
RxCANd RxCAN;
CanTxMsg TxMsg;	  
CanRxMsg msgRx;

int main(void)
{
	// Configure the system clock.
	// The system clock is 168Mhz.
	RCC_HSEConfig(RCC_HSE_ON); // ENABLE HSE (HSE = 8Mhz)
	while(!RCC_WaitForHSEStartUp());  // Wait for HSE to stabilize
	
	SystemCoreClockUpdate();
	RCC_PCLK1Config(RCC_HCLK_Div4); // Set APB1=42Mhz (168/4)

	// Initialize peripheral modules
	InitCAN();
	InitGPIO();
	InitSystick();
	InitADC();
	
//	InitEXTI();
//	InitNVIC();
//	InitTim();
//	//initWatchdogCAN();
//	//InitWatchdog(); //Disable watchdog while debugging.
	
	
	// Check if the IWDG reset has occured
	if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST) == SET){
		RCC_ClearFlag();
	}
	
	int UARTmsg = 1;
	while(1){
		if(clk1000ms == COMPLETE)
		{
			GPIOD->ODR ^= GPIO_Pin_15;
			
			USART_SendData(USART1, UARTmsg);
			UARTmsg++;
			
			clk1000ms = RESTART;
		}	
	}
}
