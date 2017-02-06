#include "stm32f4xx_it.h"
#include <stdio.h>

#include "main.h"
#include "setup.h"

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
	
	while(1) {
		printf("I am Rugrat.\n\r");
	}
}
