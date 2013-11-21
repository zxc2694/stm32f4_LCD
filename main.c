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

int main(void)
{
	__IO unsigned long n=0xE00000;
	char display[]="0123456789";
	char *str;
	str=display;	

	RCC_Configuration();
	GPIO_Configuration();
/*	while(1)
	{
		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
		Delay(n);
		
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
		Delay(n);
	}*/
	Init_LCD();
	LCD_CMD(0x1) ;           		
	delay10ms(2) ;       
	LCD_CMD(0x80);       			
	while(*str!=0)
	LCD_DATA(*str++);     			
	str=display;
}

void RCC_Configuration(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef G;
	G.GPIO_Pin=0xffff;
	G.GPIO_Speed=GPIO_Speed_50MHz;
	G.GPIO_Mode=GPIO_Mode_OUT;
	G.GPIO_OType=GPIO_OType_PP;
	G.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOC,&G);

	G.GPIO_Pin=0xffff;
	G.GPIO_Speed=GPIO_Speed_50MHz;
	G.GPIO_Mode=GPIO_Mode_OUT;
	G.GPIO_OType=GPIO_OType_PP;
	G.GPIO_PuPd=GPIO_PuPd_UP;
	GPIO_Init(GPIOA,&G);
}


void vApplicationTickHook()
{
}
