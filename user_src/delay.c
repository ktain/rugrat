#include "stm32f4xx.h"
#include "stm32f4xx_it.h"

#include "delay.h"

void delay_ms(uint32_t duration_ms) {
	uint32_t start_time_ms = millis();
	while( (millis() - start_time_ms) < duration_ms ) {
		;	// busy wait
	}
}

void delay_us(uint32_t duration_us) {
	uint32_t start_time_us = micros();
	while( (micros() - start_time_us) < duration_us ) {
		;	// busy wait 
	}
}
