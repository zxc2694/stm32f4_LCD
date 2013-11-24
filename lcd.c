#include "lcd.h"

#include "FreeRTOS.h"
#include "task.h"
#include "stm32f4xx_conf.h"

unsigned char table[10] = "0123456789";

unsigned char wrdyear[]={0x04,0x0F,0x12,0x0F,0x0A,0x1F,0x02,0x02};	//display 'year' chinese word	
unsigned char wrdmonth[]={0x1F,0x11,0x1F,0x11,0x1F,0x11,0x11,0x13};	//display 'month'chinese word
unsigned char wrddata[]={0x1F,0x11,0x11,0x1F,0x11,0x11,0x11,0x1F};	//display 'day'  chinese word		

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
	LCD_CMD(0x000c); 
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


void showCalendar_time(int hour, int min, int sec)
{
	vTaskDelay(5);
	LCD_CMD(0xC1);			//(row,column)=(2,2)
	vTaskDelay(5);
	LCD_DATA(table[hour/10]);	
	vTaskDelay(5);
	LCD_DATA(table[hour%10]);
	vTaskDelay(5);

	LCD_CMD(0xC5);			//(row,column)=(2,6)
	vTaskDelay(5);
	LCD_DATA(table[min/10]);	
	vTaskDelay(5);
	LCD_DATA(table[min%10]);
	vTaskDelay(5);

	LCD_CMD(0xC9);			//(row,column)=(2,10)
	vTaskDelay(5);		 
	LCD_DATA(table[sec/10]);	
	vTaskDelay(5);
	LCD_DATA(table[sec%10]);
	vTaskDelay(5);

	LCD_CMD(0xC3);			//(row,column)=(2,4)
	vTaskDelay(5);
	LCD_DATA(0x3A); 		//':'	
	vTaskDelay(5);
	LCD_CMD(0xC7);			//(row,column)=(2,8)	
	vTaskDelay(5);	
	LCD_DATA(0x3A);			//':'
	vTaskDelay(5);

}
void showCalendar_day(int year, int month, int data)
{
	vTaskDelay(5);
        LCD_CMD(0x80);	
	vTaskDelay(5);		
	LCD_DATA(0x32);			//'2'		
	vTaskDelay(5);
	LCD_DATA(0x30);			//'0'
	vTaskDelay(5);

	LCD_CMD(0x82);			//(row,column)=(1,3)
	vTaskDelay(5);
	LCD_DATA(table[year/10]);	
	vTaskDelay(5);
	LCD_DATA(table[year%10]);
	vTaskDelay(5);

	LCD_CMD(0x85);			//(row,column)=(1,6)
	vTaskDelay(5);
	LCD_DATA(table[month/10]);	
	vTaskDelay(5);
	LCD_DATA(table[month%10]);
	vTaskDelay(5);

	LCD_CMD(0x88);			//(row,column)=(1,9)
	vTaskDelay(5);		 
	LCD_DATA(table[data/10]);	
	vTaskDelay(5);
	LCD_DATA(table[data%10]);
	vTaskDelay(5);
	
	char i;
        for(i=0;i<8;i++)		//make 'year' chinese word
	{
		LCD_CMD(0x40+i);	
		vTaskDelay(5);
		LCD_DATA(wrdyear[i]);
		vTaskDelay(5);
	}
	for(i=0;i<8;i++)		//make 'month' chinese word
	{
		LCD_CMD(0x48+i);	
		vTaskDelay(5);
		LCD_DATA(wrdmonth[i]);
		vTaskDelay(5);
	}
	for(i=0;i<8;i++)		//make 'data' chinese word
	{
		LCD_CMD(0x50+i);
		vTaskDelay(5);
		LCD_DATA(wrddata[i]);  
		vTaskDelay(5);
	}	
	for(i=0;i<3;i++)		//display all chinese word
	{
		LCD_CMD(0x84+i*3);
		vTaskDelay(5);	
		LCD_DATA(0x00+i);
		vTaskDelay(5);
	} 


}


