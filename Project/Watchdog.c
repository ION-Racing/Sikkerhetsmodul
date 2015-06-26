#include <stm32f4xx.h>
#include "watchdog.h"
#include "Global_variables.h"
#include "CAN_functions.h"
#include "CAN_messages.h"

/*
Configuration of the independent watchdog.
Counts down with the prescaled LSI clock from
setReload value. If it counts down to 0x000 
the microcontroller resets itself.
use IWDG_ReloadCounter() to reset the counter.

LSI = 32 Khz.
----------------------------------------
prescaler = 4, setReload=0xFFF -> 512ms
Prescaler = 8, setReload=0xFFF -> 1024ms
*/

void InitWatchdog(void){
	
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_4); 			
	IWDG_SetReload(0xFFF); 
	IWDG_Enable();
}

void initWatchdogCAN(){
		/*
		Timer for CAN-Watchdog
		*/
		//Enable clock
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
		//Ini ttypedefs
		NVIC_InitTypeDef  NVIC_InitStructure;
		TIM_TimeBaseInitTypeDef TIM_structinit;
	
		//TIM 4 interrupt
		NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x00;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		TIM_structinit.TIM_Prescaler = 8400-1; // TIM2 = 1 Mhz
		TIM_structinit.TIM_CounterMode = TIM_CounterMode_Up;
		TIM_structinit.TIM_Period = 5000-1; //
		TIM_structinit.TIM_ClockDivision = TIM_CKD_DIV1;
		TIM_TimeBaseInit(TIM4, &TIM_structinit);
		
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		TIM_Cmd(TIM4,DISABLE);
		TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE);
		/* Update flag gets set high on startup; so clear it to
		prevent instant fault... */

}

void CANwatchdogEnable()
{
		CANsendEcho();
		TIM_Cmd(TIM4,ENABLE);
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
		TIM4->CNT = 0;
}

void CANwatchdogDisable()
{
		TIM_Cmd(TIM4,DISABLE);
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		TIM_ITConfig(TIM4,TIM_IT_Update,DISABLE);
		CANecho.isSent = 0;
}
	
//watchdog interrupt handler for CAN
void	TIM4_IRQHandler(void)
{
		__disable_irq();
   if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)
	 {
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);
		GPIOA->ODR |= GPIO_Pin_4;
		 if(CANecho.DU == 0) CANTx(DU_FAILED_ECHO,0,0);
		 if(CANecho.ECU == 0) CANTx(ECU_FAILED_ECHO,0,0);
		 if(CANecho.PU == 0) CANTx(PU_FAILED_ECHO,0,0);
		 if(CANecho.RPIU == 0) CANTx(RPIU_FAILED_ECHO,0,0);	 
	 }
	 __enable_irq();
}
