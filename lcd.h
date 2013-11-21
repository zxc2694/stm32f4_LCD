#ifndef __LCD_H__
#define __LCD_H__

#define LCD_DBPORT P0	

sbit RS=P2^7 ;		
sbit RW=P2^6 ;		
sbit E=P2^5 ;		

void LCD_CMD(char cmd);
void LCD_DATA(char data1);
void delay10ms(int count);
void Init_LCD();

#endif



