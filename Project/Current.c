#include "stm32f4xx.h"
#include "systick.h"
#include "CAN.h"
#include "ION_CAN.h"

#define MAXPOWER 77000

#define VD_RATIO 205 //Voltage divider ratio R2/(R1+R2)
#define MULTIPLICATION_FACTOR 100
#define U_OFFSET 0.5*MULTIPLICATION_FACTOR

#define I_OFFSET 200 //set by calibrating current
#define CURRENT_DIVIDE_FACTOR 330/4095

void processPower(uint16_t I_pos, uint16_t I_neg, uint16_t rawData)
{
	uint8_t powerDirection;
	uint16_t vbat;
	uint16_t posCurrent, negCurrent, overCurrent;
	uint32_t power;
	
	//Voltage calc
	vbat = ((rawData/4095)-U_OFFSET)*VD_RATIO;	

	posCurrent = I_pos - I_OFFSET;
	negCurrent = I_neg + I_OFFSET;
	
	if (posCurrent > negCurrent) 
	{
		//Current calc
		posCurrent = posCurrent*CURRENT_DIVIDE_FACTOR;
		negCurrent = 0;
		power = posCurrent * vbat;
		powerDirection = 1; //positive (from battery to motors)
		
		if (power > MAXPOWER)
		{
			overCurrent = posCurrent - MAXPOWER/vbat;
		}			
	}
	else
	{
		negCurrent = negCurrent * CURRENT_DIVIDE_FACTOR;
		posCurrent = 0;
		power = negCurrent * vbat;
		powerDirection = 0; //negative (from motors to battery)
	}			

	
	if (clk100msCURRENT == COMPLETE)
	{
		clk100msCURRENT = RESET;
		
		// Send current sensor value
		uint8_t data[5] = {powerDirection, power>>16, power>>8, power&0xFF, negCurrent+posCurrent};
		CANTx(CAN_MSG_CURRENT_SENSOR, 5, data);
		
		// Overcurrent
		if(overCurrent > 0){
			data[0] = overCurrent & 0xFF;
			CANTx(CAN_ERR_OVERCURRENT, 1, data);
		}
	}

	
	if (clk1000msHV == COMPLETE) 
	{
		clk1000msHV = RESET;
		
		// Send HV sensor value
		uint8_t HVBat[2] = {vbat >> 8, vbat & 0xFF};
		CANTx(CAN_MSG_HV_SENSOR, 2, HVBat);
	}
	
	

}
