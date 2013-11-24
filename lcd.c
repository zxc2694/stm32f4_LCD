#include "lcd.h"

#include "FreeRTOS.h"
#include "task.h"
#include "stm32f4xx_conf.h"

unsigned char table[10] = "0123456789"; 	

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
	vTaskDelay(5);		//delay 5m sec  
	}     			
	str=display;
}


void showCalendar(int hour, int min, int sec)
{
	vTaskDelay(5);
	LCD_CMD(0xC1);			//(row,column)=(2,2)
	vTaskDelay(5);
	LCD_DATA(table[hour/10]);	
	vTaskDelay(5);
	LCD_DATA(table[hour%10]);
	vTaskDelay(5);

	LCD_CMD(0xC6);			//(row,column)=(2,7)
	vTaskDelay(5);
	LCD_DATA(table[min/10]);	
	vTaskDelay(5);
	LCD_DATA(table[min%10]);
	vTaskDelay(5);

	LCD_CMD(0xCB);			//(row,column)=(2,12)
	vTaskDelay(5);		 
	LCD_DATA(table[sec/10]);	
	vTaskDelay(5);
	LCD_DATA(table[sec%10]);
	vTaskDelay(5);

	LCD_CMD(0xC4);			//(row,column)=(2,5)
	vTaskDelay(1);
	LCD_DATA(0x3A); 		//':'	
	vTaskDelay(1);
	LCD_CMD(0xC9);			//(row,column)=(2,8)	
	vTaskDelay(1);	
	LCD_DATA(0x3A);			//':'
	vTaskDelay(1);

}
