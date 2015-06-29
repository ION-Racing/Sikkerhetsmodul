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
#include "Macros.h"

//Macros
#define ACK 1
//Function protoypes
void LEDtoggle(uint16_t LED);

//Variable declerations
RxCANd RxCAN;
CanTxMsg TxMsg;	  
CanRxMsg msgRx;

int main(void)
{	
	/*
	Initalize and configure periphermodules and system.
	*/
	// Configure the system clock.
	// The system clock is 168Mhz.
	RCC_HSEConfig(RCC_HSE_ON); // ENABLE HSE (HSE = 8Mhz)
	while(!RCC_WaitForHSEStartUp());  // Wait for HSE to stabilize
	
	SystemCoreClockUpdate();
	RCC_PCLK1Config(RCC_HCLK_Div4); // Set APB1=42Mhz (168/4)

	// Initialize peripheral modules
//	InitCAN();
	InitGPIO();
//	InitEXTI();
//	InitNVIC();
//	InitTim();
	InitSystick();
//	//initWatchdogCAN();
//	//InitWatchdog(); //Disable watchdog while debugging.
	
	/* 
	Check if the IWDG reset has occoured
	*/
	if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST) == SET){

		RCC_ClearFlag();
	}
	
	/*
	Main code
	*/
	while(1)
	{ 
		if(clk1000ms==COMPLETE){
		GPIOD->ODR ^= GPIO_Pin_15;
		clk1000ms = RESTART;
		}	
	} //END while1
}	//END Main



