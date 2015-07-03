#include "stm32f4xx.h"

void InitSystick(void);

#define COMPLETE 0
#define RESTART 1

extern volatile uint16_t clk1000ms;
extern volatile uint16_t clk100ms;
extern volatile uint8_t clk10msWheel;
extern volatile uint8_t clk10msButton;
extern volatile uint8_t clk10ms;
extern volatile uint16_t clk1000msHV;
extern volatile uint16_t clk1000msGLV;
extern volatile uint16_t clk100msCURRENT;

