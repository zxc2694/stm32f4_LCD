#include "lib.h"

#include "FreeRTOS.h"
#include "task.h"
#include "stm32f4xx_conf.h"

void RCC_Configuration(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef G;
	G.GPIO_Pin=0xffff;
	G.GPIO_Speed=GPIO_Speed_50MHz;
	G.GPIO_Mode=GPIO_Mode_OUT;
	G.GPIO_OType=GPIO_OType_PP;
	G.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOD,&G);
}

