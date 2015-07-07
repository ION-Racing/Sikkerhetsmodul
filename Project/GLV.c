#include "stm32f4xx.h"
#include "systick.h"
#include "Global_variables.h"
#include "systick.h"
#include "CAN.h"
#include "ION_CAN.h"

/*
Max voltage is 15 volt, minimum allowed is 12 volt.
15 volt -> 3.05 volt on the input

Vbat = Vadc * vref * R1+R2
		----------	-------	
		(2^n)-1		  R2
		
---------------------------
Vadc		rawVoltage
Vref		3.3V
2^n -1		4095
(R1+R2)/R2	59/12 (4.923 measured)
*/

//Macros
#define GLV_MIN 2978
#define GLV_MAX 3722
#define V_DIVIDER 4.923 
#define GLV_MULT_FACTOR 10*3.3/4095*V_DIVIDER

//Function prototypes
uint8_t invalidValue(uint16_t value, uint16_t minValue, uint16_t maxValue);

//Variable declerations
uint16_t voltageGLV = 0;
static uint8_t counterLow = 0;

void processGLV(uint16_t rawVoltage)
{		
	if(rawVoltage<=GLV_MIN)
	{
		counterLow++;
		if(counterLow>10){
			GPIOD->ODR |= GPIO_Pin_14;
		}
	} 
	else
		counterLow = 0;

	if (clk1000msGLV == COMPLETE)
	{
		clk1000msGLV = RESET;
		voltageGLV = rawVoltage*GLV_MULT_FACTOR;	
		uint8_t LVBat[2] = {voltageGLV & 0xFF, voltageGLV>>8};
		CANTx(CAN_MSG_LV_SENSOR, 2, LVBat);
	}
}
