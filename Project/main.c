#include "stm32f4xx.h"
#include "stm32f4xx_GPIO.h"
#include "GPIO.h"
#include "NVIC.h"
#include "CAN.h"
#include "EXTI.h"
#include "TIM.h"
#include "Global_variables.h"
#include "math.h"



static void Delay(__IO uint32_t);
void TxWheelrpm(uint32_t, uint8_t);


CanTxMsg TxMsg;	  
CanRxMsg msgRx;
//float Ws_freq;
uint32_t freq1;
uint32_t freq2;

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
	InitEXTI();
	InitNVIC();
	InitTim();
	
	GPIOA->ODR |= GPIO_Pin_4;
	
	//Enable a LED to show on status.
	//GPIOC->ODR |= GPIO_Pin_8;
	//GPIOD->ODR |= GPIO_Pin_14;
	/* Main code */
	while(1)
	{
		TxWheelrpm(wheel1_Dt,0x1);
		TxWheelrpm(wheel2_Dt,0x2);
	}
}

//--------------------------------------------------------------------
/**
  * @brief  Delay
  * @param  None
  * @retval None
  */
void Delay(__IO uint32_t nCount){
  while(nCount--){}
}

/*
@Param 
period : Periode of the wheel-sensor input
wheelN : wheel number; wheel1 or wheel2.
*/
void TxWheelrpm(uint32_t period, uint8_t wheelN){
	uint32_t frequency;
	if(period != 0)
			{
				freq1 = (uint32_t)round(1000000/period); // f*1000 = (1/t[us])*1000
				TxMsg.StdId = wheelN;
				TxMsg.RTR = CAN_RTR_DATA;
				TxMsg.IDE = CAN_ID_STD;
				TxMsg.DLC = 2;
				TxMsg.Data[0] = freq1;
				TxMsg.Data[1] = freq1>>8;
				CAN_Transmit(CAN1, &TxMsg);
			}
}