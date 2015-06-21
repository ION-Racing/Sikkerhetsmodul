#include "STM32f4xx.h"

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

void EXTI9_5_IRQHandler(void) {
    /* Make sure that interrupt flag is set */
     if (EXTI_GetITStatus(EXTI_Line9) != RESET) {
        /* Do your stuff when PD0 is changed */
        
        GPIOD->ODR ^= GPIO_Pin_14;
        /* Clear interrupt flag */
        EXTI_ClearITPendingBit(EXTI_Line9);
    } 
}
 
/* Handle PB12 interrupt */
void EXTI15_10_IRQHandler(void) {
       
        if (EXTI_GetITStatus(EXTI_Line10) != RESET) { //Is interrupt flag set?
        GPIOD->ODR ^= GPIO_Pin_15;       
        EXTI_ClearITPendingBit(EXTI_Line10);	//Clear interrupt flag.
    }    
}
