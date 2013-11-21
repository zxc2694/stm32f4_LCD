#ifndef __LCD_H__
#define __LCD_H__

#define LCD_DBPORT GPIOA	

#define RS_0  GPIO_ResetBits(GPIOC, GPIO_Pin_0);
#define RW_0  GPIO_ResetBits(GPIOC, GPIO_Pin_1);
#define E_0   GPIO_ResetBits(GPIOC, GPIO_Pin_2);


#define RS_1  GPIO_SetBits(GPIOC, GPIO_Pin_0);
#define RW_1  GPIO_SetBits(GPIOC, GPIO_Pin_1);
#define E_1   GPIO_SetBits(GPIOC, GPIO_Pin_2);

void LCD_CMD(char cmd);
void LCD_DATA(char data1);
void delay10ms(int count);
void Init_LCD();

#endif



