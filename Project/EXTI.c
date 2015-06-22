#include "STM32f4xx.h"
#include "Global_variables.h"

void InitEXTI()
{
	/*Configure GPIOs as EXTI:
	PE7		: Start button  
	PE8		: Stop button
	PD9		: Wheelsensor 1
	PD10	: Wheelsensor 2
	*/
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource7);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE, EXTI_PinSource8);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource9);
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOD, EXTI_PinSource10);
	
	EXTI_InitTypeDef EXTI_initstruct;
	EXTI_initstruct.EXTI_Line = EXTI_Line9 | EXTI_Line10;
	EXTI_initstruct.EXTI_LineCmd = ENABLE;
	EXTI_initstruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_initstruct.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_initstruct);
	
}


uint32_t time1IT=0; //wheel sensor 1 interrupt time/delay
uint32_t time2IT=0; //wheel sensor 1 interrupt time/delay
uint32_t Ws_deltat = 0; //delta time between trigger 1 and trigger 2
const uint8_t TRIGGER1=0; 
const uint8_t TRIGGER2=1; 
static uint8_t state = 0;
/*
Interrupt handlers for start-, stop- buttons, wheel sensor 1 and 2.
Could probably make the interrupt routine a lot quicker, or solve
the problem in a different manner.
*/

void EXTI9_5_IRQHandler(void) {
	
			__disable_irq();
     if (EXTI_GetITStatus(EXTI_Line9) != RESET) 		//Wheel sensor IT?
			 { 
				 if(state == TRIGGER1){																		
					TIM2->CNT = 0; 																					 
					state = TRIGGER2;
				 }else{																			//Second trigger..
					Ws_deltat = TIM2->CNT;
					state = TRIGGER1;
														//Reset counter
				 }
        EXTI_ClearITPendingBit(EXTI_Line9);
			 __enable_irq();
    } 
}
 
/* Handle PB12 interrupt */
void EXTI15_10_IRQHandler(void) {
       
        if (EXTI_GetITStatus(EXTI_Line10) != RESET) { //Is interrupt flag set?
        GPIOD->ODR ^= GPIO_Pin_15;       
        EXTI_ClearITPendingBit(EXTI_Line10);	//Clear interrupt flag.
    }    
}
