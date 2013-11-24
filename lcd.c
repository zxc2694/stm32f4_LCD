#include "lcd.h"

#include "FreeRTOS.h"
#include "task.h"
#include "stm32f4xx_conf.h"


void LCD_CMD(uint16_t cmd)		
{
	int i;
	GPIO_SetBits(LCD_DBPORT, cmd);
	RS_0;
	RW_0;
	E_1;          
	vTaskDelay(1);      
	E_0;
	GPIO_ResetBits(LCD_DBPORT, cmd);          
}

void LCD_DATA(uint16_t data1)	
{
	int i;
	GPIO_SetBits(LCD_DBPORT, data1);
	RS_1;
	RW_0;
	E_1;          
	vTaskDelay(1);      
	E_0;     
	GPIO_ResetBits(LCD_DBPORT, data1);    
}

void Init_LCD()		       
{
	vTaskDelay(100);	         
	LCD_CMD(0x003f);       
	vTaskDelay(10);
	LCD_CMD(0x000e); 
	vTaskDelay(10);         
	LCD_CMD(0x0001);          
	vTaskDelay(10);
}
