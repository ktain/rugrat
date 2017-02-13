#include "stm32f4xx_it.h"
#include <stdio.h>

#include "main.h"
#include "setup.h"
#include "delay.h"

void systick(void) {
		
}

void button0(void) {
	GPIO_SetBits(GPIOA, GPIO_Pin_4|GPIO_Pin_6);
	GPIO_ResetBits(GPIOA, GPIO_Pin_5|GPIO_Pin_7);
}

void button1(void) {
	GPIO_SetBits(GPIOA, GPIO_Pin_5|GPIO_Pin_7);
	GPIO_ResetBits(GPIOA, GPIO_Pin_4|GPIO_Pin_6);
}

int main(void) {
	setup();
	delay_ms(10);	// Wait for transients to settle
	
	while(1) {
		
		button0();
		delay_us(1000000);
		button1();
		delay_us(1000000);
		
	}
}
