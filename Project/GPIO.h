#define LED_RED		GPIO_Pin_13
#define LED_GREEN	GPIO_Pin_14
#define LED_BLUE	GPIO_Pin_15

void InitGPIO(void);

void LED_SetState(uint32_t led, FunctionalState state);
