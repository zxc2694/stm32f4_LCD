#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "stm32f4xx_conf.h"

#define  Delay(n)  while((n)--)

void RCC_Configuration(void);
void GPIO_Configuration(void);
void GPIO_Configuration2(void);

int main(void)
{
	vu32 n=20000000;
	RCC_Configuration();
	GPIO_Configuration();

	GPIO_ResetBits(GPIOD, GPIO_Pin_9);
	GPIO_SetBits(GPIOD, GPIO_Pin_12);
	Delay(n);
	
	GPIO_SetBits(GPIOD,GPIO_Pin_9);
	GPIO_ResetBits(GPIOD,GPIO_Pin_12);
	Delay(n);
}

void RCC_Configuration(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef G;
	G.GPIO_Pin=GPIO_Pin_9 | GPIO_Pin_12;
	G.GPIO_Speed=GPIO_Speed_50MHz;
	G.GPIO_Mode=GPIO_Mode_OUT;
	G.GPIO_OType=GPIO_OType_PP;
	G.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD,&G);
}

void vApplicationTickHook()
{
}
