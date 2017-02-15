#include "stm32f4xx_it.h"
#include <stdio.h>

#include "main.h"
#include "setup.h"
#include "delay.h"

void systick(void) 
{
	readSensors(); // 70us
}

void button0(void) 
{
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	delay_ms(200);
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);
	delay_ms(200);
}

void button1(void) 
{
	GPIO_SetBits(GPIOA, GPIO_Pin_5|GPIO_Pin_7);
	delay_ms(200);
	GPIO_ResetBits(GPIOA, GPIO_Pin_5|GPIO_Pin_7);
	delay_ms(200);
}

int main(void) 
{
	setup();
	
	while(1) {
		printf("voltage %d s %d %d %d %d %d %d %d\r\n", rawVoltage,
			rawSensorVal[0], rawSensorVal[1], rawSensorVal[2],
			rawSensorVal[3], rawSensorVal[4], rawSensorVal[5],
			rawSensorVal[6]);
	}
}
