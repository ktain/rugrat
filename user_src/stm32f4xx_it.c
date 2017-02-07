#include "stm32f4xx_it.h"

#include "main.h"
#include "delay.h"

/* Global time variables */
volatile uint32_t g_millis;	// 49.7 days until overflow

inline uint32_t millis(void) {
	return g_millis;
}

inline uint32_t micros(void) {
	return g_millis*1000 + 1000 - SysTick->VAL/100;
}

/* SysTick interrupt handler */
void SysTick_Handler(void)
{
	g_millis++;
	systick();
}

/* Button 0 interrupt handler */
void EXTI9_5_IRQHandler(void) {
	if(EXTI_GetITStatus(EXTI_Line5) != RESET) {
		button0();
		EXTI_ClearITPendingBit(EXTI_Line5);
	}
}

/* Button 1 interrupt handler */
void EXTI15_10_IRQHandler(void) {
	if(EXTI_GetITStatus(EXTI_Line10) != RESET) {
		button1();
		EXTI_ClearITPendingBit(EXTI_Line10);
	}
}


