#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "stm32f4xx_conf.h"

void RCC_Configuration(void);
void GPIO_Configuration(void);

int main(void)
{
	
	RCC_Configuration();
	GPIO_Configuration(); 
	while(1){
		GPIO_SetBits(GPIOD, GPIO_Pin_9);
		GPIO_SetBits(GPIOD, GPIO_Pin_12);
		vTaskDelay(200);
	//	GPIO_ResetBits(GPIOD,GPIO_Pin_9);
	//	GPIO_ResetBits(GPIOD,GPIO_Pin_12);
	//	vTaskDelay(1000);
	}
}

void RCC_Configuration(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_9 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
}


void vApplicationTickHook()
{
}
