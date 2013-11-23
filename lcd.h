#ifndef __LCD_H__
#define __LCD_H__

#define LCD_DBPORT GPIOD	

#define RS_0  GPIO_ResetBits(GPIOD, GPIO_Pin_8)
#define RW_0  GPIO_ResetBits(GPIOD, GPIO_Pin_9)
#define E_0   GPIO_ResetBits(GPIOD, GPIO_Pin_10)


#define RS_1  GPIO_SetBits(GPIOD, GPIO_Pin_8)
#define RW_1  GPIO_SetBits(GPIOD, GPIO_Pin_9)
#define E_1   GPIO_SetBits(GPIOD, GPIO_Pin_10)

#include "FreeRTOS.h"
#include "task.h"
#include "stm32f4xx_conf.h"

void LCD_CMD(uint16_t cmd);
void LCD_DATA(uint16_t data1);
void delay10ms(int count);
void Init_LCD();

#endif



