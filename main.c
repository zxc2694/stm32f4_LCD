#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "stm32f4xx_conf.h"

void Delay(__IO unsigned long num)
{
	while(num--);
}
void RCC_Configuration(void);
void GPIO_Configuration(void);
void GPIO_Configuration2(void);

int main(void)
{
	__IO unsigned long n=0xAFFFFF;
	RCC_Configuration();
	GPIO_Configuration();
	while(1)
	{
		GPIO_ResetBits(GPIOD, GPIO_Pin_13);//for singal analyzer
		GPIO_ResetBits(GPIOC, GPIO_Pin_1);
		Delay(n);
		GPIO_SetBits(GPIOD, GPIO_Pin_13);//for singal analyzer
		GPIO_SetBits(GPIOC, GPIO_Pin_1);
		Delay(n);
	}
}

void RCC_Configuration(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef G;
	G.GPIO_Pin=GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	G.GPIO_Speed=GPIO_Speed_50MHz;
	G.GPIO_Mode=GPIO_Mode_OUT;
	G.GPIO_OType=GPIO_OType_PP;
	G.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOD,&G);

	G.GPIO_Pin=GPIO_Pin_1;
	G.GPIO_Speed=GPIO_Speed_50MHz;
	G.GPIO_Mode=GPIO_Mode_OUT;
	G.GPIO_OType=GPIO_OType_PP;
	G.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOC,&G);
}


void vApplicationTickHook()
{
}
