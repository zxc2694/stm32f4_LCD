#include "lcd.h"

#include "FreeRTOS.h"
#include "task.h"
#include "stm32f4xx_conf.h"


static __IO unsigned long n=0xE00000;

void Delay(__IO unsigned long num)
{
	while(num--);
}

void LCD_CMD(uint16_t cmd)		
{
	int i;
	GPIO_SetBits(LCD_DBPORT, cmd);
//	LCD_DBPORT=cmd ;       
	RS_0;RW_0;E_1;          
	for(i=0;i<10000;i++);      
	RS_0;RW_0;E_0;          
}

void LCD_DATA(uint16_t data1)	
{
	int i;
	GPIO_SetBits(LCD_DBPORT, data1);
//	LCD_DBPORT=data1;
	RS_1;RW_0;E_1;          
	for(i=0;i<10000;i++) ;      
	RS_1;RW_0;E_0;         
}

void Init_LCD()		       
{
	Delay(n) ;          
	LCD_CMD(0x003f) ;       
	Delay(0x10000);
	LCD_CMD(0x000e) ; 
	Delay(0x10000);         
	LCD_CMD(0x0001) ;          
	Delay(0x50000) ;
}

