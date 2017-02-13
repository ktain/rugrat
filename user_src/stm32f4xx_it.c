/**
 * Filename: stm324xx_it.c
 *
 * Interrupt handlers and system time getter methods
 */

/* Peripheral includes */
#include "stm32f4xx_it.h"

/* User includes */
#include "main.h"
#include "delay.h"
#include "setup.h"

/* Static time variables */
volatile uint32_t g_millis;	// 49.7 days until overflow

/* Button flags */


/*
 * millis() - returns system time in milliseconds
 */
inline uint32_t millis(void) {
	return g_millis;
}

/*
 * micros() - returns system time in microseconds
 *
 * Return the sum of scaled current time and the remaining time
 * needed before the next systick reload cycle
 */
inline uint32_t micros(void) {
	return g_millis*1000 + (SystemCoreClock/1000 - SysTick->VAL)/TICKS_PER_US;
}

/*
 * Systick_Handler() - SysTick interrupt handler
 *
 * Runs periodically whenever the systick timer value reaches 0
 * Updates system time variable and calls the user systick() function
 */
void SysTick_Handler(void)
{
	g_millis++;
	systick();
}

/*
 * EXTI_9_5_IRQHandler() - Button 0 interrupt handler
 */
void EXTI9_5_IRQHandler(void) {
	if(EXTI_GetITStatus(EXTI_Line5) != RESET) {
		button0();
		EXTI_ClearITPendingBit(EXTI_Line5);
	}
}

/*
 * EXTI5_10_IRQHandler() - Button 1 interrupt handler
 */
void EXTI15_10_IRQHandler(void) {
	if(EXTI_GetITStatus(EXTI_Line10) != RESET) {
		button1();
		EXTI_ClearITPendingBit(EXTI_Line10);
	}
}


