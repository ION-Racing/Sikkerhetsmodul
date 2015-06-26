/* Macro list of all the Tx/Rx message ID's for this module
-----------------------------------------------------------
0x0 = unknown ID.
*/


/* Tx list 

Below is some information about the contents of the messages.
Example	: w1.1 = wheelsensor 1 part 1.
				: w1.2 = wheelsensor 1 part 2.
-------------------------------------
ID			D1		D2		D3		D4		D5
0x200		W1.1	w1.2	w2.1	w2.2	-
0x40		-			-			-			-			-
0x41		-			-			-			-			-
0x600		-			-			-			-			-

*/
#define TX_WHEELSENSOR	0x200
#define Tx_STOP					0x40
#define Tx_START				0x41
#define TX_IWD_TIMEOUT	0x600

/* Rx list */
#define RX_START_ACK 0x0
#define RX_STOP_ACK 0x0
#define	CRITICAL_ERROR 0x0
/* Temp macros, the safety module
will handle the CAN_watchdog on the 
dinished software.
*/
#define CAN_ECHO 0x30

/* Temp macros, the safety module
will handle the CAN_watchdog on the 
dinished software.
-----------------------------------
Safety module will "bark" on the CAN-
Bus and give out an ERROR if all the modules
doesn't "kick the can" in a timely fashion.
*/
#define ECU_KICKED_CAN 	0x31 		// Engine Control Unit
#define RPIU_KICKED_CAN 0x32 		// RPI Unit
#define DU_KICKED_CAN 	0x33		// Dashboard Unit
#define PU_KICKED_CAN 	0x34		// Pedalbox Unit

