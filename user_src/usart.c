#include "stm32f4xx.h"
#include <stdio.h>

#include "usart.h"

struct __FILE {
	int32_t handle;
};

FILE	__stdout;
FILE	__stdin;

void _sys_exit(int32_t x) {
		x = x;
}


/*
 * fputc overloads printf to redirect output to serial port
 */
int32_t fputc(int32_t ch, FILE *f) {
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	USART_SendData(USART1, (uint8_t)ch);
	return ch;
}


int32_t fgetc(FILE *f) {
	uint16_t temp;
	while(!(USART1->SR & USART_SR_RXNE));
	temp = (uint16_t)(USART1->DR & (uint16_t)0x01FF);
	return temp;
}
