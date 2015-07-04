#include "stm32f4xx.h"
#include "systick.h"

/*
Functions for the HV sensor monitoring.
range 0.5 -> 3 ((0 to 2.5) +0.5). The sensor has an
adjustable offsett with a maximum offsett of 0.5 volt.
3 V ->615V
*/

#define VD_RATIO 205 //Voltage divider ratio R2/(R1+R2)
#define MULTIPLICATION_FACTOR 100
#define OFFSET 0.5*MULTIPLICATION_FACTOR


uint32_t vbat;
void processHV(uint16_t rawData)
{ 
	vbat = ((rawData/4095)-OFFSET)*VD_RATIO;
}
