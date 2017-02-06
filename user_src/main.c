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

	while(1) {
		int32_t old_us = micros();
		int32_t old_ms = millis();
		delay_ms(1000);
		int32_t new_us = micros();
		int32_t new_ms = millis();
		printf("%d us per %d ms per 1 second\n\r", new_us - old_us , new_ms - old_ms);

	}
}
