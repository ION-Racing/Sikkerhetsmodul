/* Structure for wheelsensor 1 and wheelsensor 2.
The values get set by the GPIO interrupt in EXTI.C
and is used in TxWheelsensor.c.
*/
#include "stdint.h"

/* Global variables for button push.
They get set in the IO interrupt handler
in EXTI.C. 
-----------------------------------------
1 for valid button push
0 for no button push
*/
extern uint8_t start_button_pushed;   
extern uint8_t stop_button_pushed;

/*
state of the can bus echo
1 Echo message on canbus sent.
0 echo recived or message not sent yet.
*/
extern	uint8_t CAN_ECHO_SENT;

/*
Typedef for global interrupt variables.
*/
typedef struct{
	
	struct{
		uint32_t timeStamp;
		uint8_t fault;
	}BMS;
	
	struct{
		uint32_t timeStamp;
		uint8_t fault;
	}IMD;
	
	struct{
		uint32_t timeStamp;
		uint8_t fault;
	}BSPD;

	struct{
		uint32_t done;
		uint8_t fault;
	}PREd;
	
	struct{
		uint8_t open;
		uint8_t closed;
		uint8_t triggered;
	}shutdownCircuit;
	
}IOinterruptd;

extern IOinterruptd IOinterrupt;
/*
struct for CAN ECHO/Watchdog state.
1 if echo recived.
*/
typedef struct{
	uint8_t ECU		;	// Engine control unit echo recived 
	uint8_t RPIU	; // Raspberry unit pi echo recived
	uint8_t DU		;	// Dashbord unit echo recived
	uint8_t PU		;	// Pedalbox unit echo recived
	uint8_t isSent;	// 1 : waiting for echo. 0 : not expecting echo.
}CANechod;

extern CANechod CANecho;


/*
Struct for recived can messages.
*/
typedef struct{
uint8_t FIFO0	; //Message pending in FIFO0
uint8_t FIFO1	; //Message pending in FIFO1
}RxCANd;

extern RxCANd RxCAN;



