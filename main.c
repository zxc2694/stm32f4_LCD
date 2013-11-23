#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "stm32f4xx_conf.h"



void RCC_Configuration(void);
void GPIO_Configuration(void);
void GPIO_Configuration2(void);

int main(void)
{
	__IO unsigned long n=0xAFFFFF;
	char display[]="0123456789";
	char *str;
	str=display;
	RCC_Configuration();
	GPIO_Configuration();
	
	Init_LCD();         		
	Delay(0x10000);
	LCD_CMD(0x0080);			
	Delay(0x2000);
	while(*str!=0){
	LCD_DATA(*str++);
	Delay(0x10000);
	}     			
	str=display;
	while(1);
}

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

void vApplicationTickHook()
{
}
