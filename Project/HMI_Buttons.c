#include "stm32f4xx.h"
#include "Global_variables.h"

//Defines
#define PUSHED 1
#define RELEASED 0

//variable declerations
static uint8_t lastState = 0;


//Function delerations
void ButtonError(uint8_t*);

/*
Checks if button push is a new valid push

@Param button_state : global variable, 1 if pushed
											0 if not pushed.
@Retval 1 for valid push, 0 for invalid push.
*/
uint8_t newButtonPush(uint16_t button)
{
		uint8_t	*state;
	
	if(button & GPIO_Pin_7)
		{
		state = &start_button_pushed;
		}
		else if(button & GPIO_Pin_8)
		{
		state = &stop_button_pushed;
		}
	
	if(*state == PUSHED)
		{
			if(lastState == PUSHED)
			{
				return 0;
			}
			else if(lastState == RELEASED)
			{
				lastState = PUSHED;
				*state = 0;
				return 1;
			}else ButtonError(state);
		}
		else if(*state == RELEASED)
			{
				lastState = 0;
			}else ButtonError(state);
}

/*
Invalid state occoured.
Reset all variables.
*/
void ButtonError(uint8_t *state){
	*state = 0;
	lastState = 0;
}