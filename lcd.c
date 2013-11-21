#include "lcd.h"

#include "FreeRTOS.h"
#include "task.h"
#include "stm32f4xx_conf.h"

void LCD_CMD(char cmd)		
{
	int i;	
	LCD_DBPORT=cmd ;         
	RS=0;RW=0;E=1;          
	for(i=0;i<4000;i++);      
	RS=0;RW=0;E=0;          
}

void LCD_DATA(char data1)	
{
	int i;
	LCD_DBPORT=data1;
	RS=1;RW=0;E=1;          
	for(i=0;i<4000;i++) ;      
	RS=1;RW=0;E=0;         
}

void delay10ms(int count) 
{
   int i,j;
   for(i=0;i<count;i++)    
	for(j=0;j<194000;j++);
}

void Init_LCD()		       
{
	delay10ms(2) ;          
	LCD_CMD(0x3f) ;        
	LCD_CMD(0xe) ;          
	LCD_CMD(0x1) ;          
	delay10ms(1) ; 
	LCD_CMD(0x80);          
} 
