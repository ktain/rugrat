#include "stm32f4xx.h"

#include "setup.h"

#define SYSTICK_RELOAD (SystemCoreClock/1000)	// Number of ticks between interrupts
#define BAUDRATE 9600

void setup() {
	systick_setup();
	led_setup();
	emitter_setup();
	button_setup();
	usart_setup();
}


/*
 * SysTick setup
 * The SysTick timer is a 24-bit countdown timer.
 * SysTick_Handler is called when the timer reaches 0.
 * The RELOAD value should not exceed 0xFFFFFF (16,777,215). 
 */
void systick_setup(void) {
	/* Interrupt every X number of ticks */
	SysTick_Config(SYSTICK_RELOAD);
}


/*
 * LED setup
 * Setup the LEDs
 */
void led_setup(void) {
	/* Declare a GPIO struct to work with*/
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	/* 
	 * Connect the clock to the GPIO ports to be used.
	 * On the STM32F4XX, the GPIO ports are connected to the AHB1 bus.
	 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	/*
	 * GPIO_Pin - specify the pin to modify (specific, all)
	 * GPIO_Mode - pin-specific mode (digital out, digital in, analog, alternate)
	 * GPIO_OType - hardware configuration (push-pull, open-drain)
	 * GPIO_Speed - GPIO clock speed (2, 25, 50, 100MHz)
	 * GPIO_PuPd - internal configuration (pull-up, pull-down, neither)
	 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}



/*
 * Emitter setup
 * Setup the emitters
 */
void emitter_setup(void) {
	/* Declare a GPIO struct to work with*/
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	/* 
	 * Connect the clock to the GPIO ports to be used.
	 * On the STM32F4XX, the GPIO ports are connected to the AHB1 bus.
	 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
	
	/*
	 * GPIO_Pin - specify the pin to modify
	 * GPIO_Mode - pin-specific mode (digital out, digital in, analog, alternate)
	 * GPIO_OType - hardware configuration (push-pull, open-drain)
	 * GPIO_Speed - GPIO clock speed (2, 25, 50, 100MHz)
	 * GPIO_PuPd - internal configuration (pull-up, pull-down, neither)
	 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
}



void button_setup(void) {
	/* Declare EXTI, GPIO, and NVIC 32-bit structs to work with */
	EXTI_InitTypeDef EXTI_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* Connect the clock to the GPIO ports used by buttons */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	/* Connect the clock to SYSCFG used by EXTI line*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
	/* Configure GPIO settings for buttons*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	// Update registers
	
	/* Map EXTI line to button0 */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource5);
	
	/* Configure EXTI line for button 0 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line5;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	// Update registers
	
	/* Configure NVIC channel for button0 */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;	// Lowest priority = 0x0F
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;					// Highest priority = 0x00
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/* Map the EXTI line to button1 */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource10);

	/* Configure EXTI line for button 1 */
	EXTI_InitStructure.EXTI_Line = EXTI_Line10;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);	// Update registers
	
	/* Configure NVIC channel for button1 */
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;	// Lowest priority = 0x0F
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;					// Highest priority = 0x00
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}
 

void usart_setup(void) {
	/* Declare GPIO and USART 32-bit structs to work with */
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStructure;
	
	/* Connect the clock to the USART GPIO port used */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	/* Connect the Clock to USART1 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	/* Configure TX pin as alternate function */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
	
	/* Configure RX pin as alternate function */
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
	
	/* Configure GPIO pins for USART */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	// Update registers
	
	/* Configure USART */
	USART_InitStructure.USART_BaudRate = BAUDRATE;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);	// Update registers
	
	/* Configure USART clock */
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_High;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_1Edge;
	USART_ClockInit(USART1, &USART_ClockInitStructure);	// Update registers

	/* Enable USART */
	USART_Cmd(USART1, ENABLE);
}
