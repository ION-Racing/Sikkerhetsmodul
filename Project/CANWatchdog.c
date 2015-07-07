#include "stm32f4xx.h"
#include "ION_CAN.h"
#include "CAN.h"

uint32_t watchdogTimer = 0;

void CANWatchdog_Request(void){
	uint8_t data[1] = {0x00};
	CANTx(CAN_MSG_WATCHDOG_REQUEST, 1, data);
}