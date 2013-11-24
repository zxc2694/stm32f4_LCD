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

void LCD_display(char row,char column, char display[])
{
	char *str;
	uint16_t address;	
	str=display;
	address=0x0080+0x0040*(row-1)+(column-1);	
	LCD_CMD(address);
	vTaskDelay(10);		//delay 10m sec
	while(*str!=0){
	LCD_DATA(*str++);
	vTaskDelay(1);		//delay 1m sec  
	}     			
	str=display;
}
