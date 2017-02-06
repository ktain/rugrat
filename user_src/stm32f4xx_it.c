#include "main.h"
#include "stm32f4xx_it.h"

/* SysTick interrupt handler */
void SysTick_Handler(void)
{
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
	if(EXTI_GetITStatus(EXTI_Line11) != RESET) {
		button1();
		EXTI_ClearITPendingBit(EXTI_Line11);
	}
}


