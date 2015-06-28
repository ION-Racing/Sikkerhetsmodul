//#include "STM32f4xx.h"
//#include "Global_variables.h"

//struct wheel;

//void InitEXTI()
//{
//	/*Configure GPIOs as EXTI:
//	PD9		: Wheelsensor 1
//	PD10	: Wheelsensor 2
//	*/
//	
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
//	
//	//Configure syscfg
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource8);	//BMS
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource9);	//IMD
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource10);	//BSPD
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource11);	//Pre charge done
//	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource12);	//Hjelpekontakt
//	
//	EXTI_InitTypeDef EXTI_initstruct;
//	EXTI_initstruct.EXTI_Line = EXTI_Line8 | EXTI_Line9 | EXTI_Line10 | EXTI_Line11;
//	EXTI_initstruct.EXTI_LineCmd = ENABLE;
//	EXTI_initstruct.EXTI_Mode = EXTI_Mode_Interrupt;
//	EXTI_initstruct.EXTI_Trigger = EXTI_Trigger_Falling;
//	EXTI_Init(&EXTI_initstruct);
//	

//	EXTI_initstruct.EXTI_Line = EXTI_Line12;
//	EXTI_initstruct.EXTI_LineCmd = ENABLE;
//	EXTI_initstruct.EXTI_Mode = EXTI_Mode_Interrupt;
//	EXTI_initstruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
//	EXTI_Init(&EXTI_initstruct);
//}


//IOinterruptd IOinterrupt; //struct typedef.

//void EXTI9_5_IRQHandler(void) {
//	
//	__disable_irq();
//		
//	if(EXTI_GetITStatus(EXTI_Line8) != RESET){ //BMS fault
//		IOinterrupt.BMS.fault = 1;
//		IOinterrupt.BMS.timeStamp = TIM2->CNT;
//		EXTI_ClearITPendingBit(EXTI_Line8);			
//	}
//		
//	if(EXTI_GetITStatus(EXTI_Line9) != RESET){ //IMD fault
//		IOinterrupt.IMD.fault = 1;
//		IOinterrupt.IMD.timeStamp = TIM2->CNT;
//		EXTI_ClearITPendingBit(EXTI_Line9);			
//	}
//	__enable_irq();			
//}
// 
///* Handle PB12 interrupt */
//void EXTI15_10_IRQHandler(void) {
//	
//	__disable_irq();
//	
//	if(EXTI_GetITStatus(EXTI_Line10) != RESET){	//BSPD fault
//		IOinterrupt.BSPD.fault=1;
//		IOinterrupt.BSPD.timeStamp = TIM2->CNT;
//		EXTI_ClearITPendingBit(EXTI_Line10);			
//	}
//		
//	if(EXTI_GetITStatus(EXTI_Line11) != RESET){ //Pre charge done
//		IOinterrupt.PREd.done = 1;
//		EXTI_ClearITPendingBit(EXTI_Line11);			
//	}
//		
//	if(EXTI_GetITStatus(EXTI_Line12) != RESET){ //Hjelpekontakt lukket
//		IOinterrupt.shutdownCircuit.triggered = 1; 
//		EXTI_ClearITPendingBit(EXTI_Line12);			
//	}
//		
//	__enable_irq();			
//}
