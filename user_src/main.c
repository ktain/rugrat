#include "main.h"
#include "setup.h"
#include "stm32f4xx_it.h"

int tog;

void systick(void) {
	if (tog)
		GPIO_SetBits(GPIOA, GPIO_Pin_4);
	else {
		tog = 1;
		GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	}
		
}

void button0(void) {
	
}

void button1(void) {
	
}

int main(void) {
	setup();
	
	
	while(1) {
		;
	}
}
