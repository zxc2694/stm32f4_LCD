#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "stm32f4xx_conf.h"

static int delaytime = 30000;

static void LCD_display_task(void *pvParameters);


int main(void)
{
	/* Create a task to display something in the LCD. */
  	xTaskCreate(LCD_display_task,
             (signed portCHAR *) "Liquid Crystal Display",
             512 /* stack size */, NULL,
             tskIDLE_PRIORITY + 5, NULL);

 	/* Start running the tasks. */
 	 vTaskStartScheduler();
  	return 0;
}
static void LCD_display_task(void *pvParameters)
{
	char display[]="0123456789";
	char *str;
	str=display;	

	RCC_Configuration();
	GPIO_Configuration();
	
	Init_LCD();         		
	Delay(delaytime);
	LCD_CMD(0x0080);			
	Delay(delaytime);
	while(*str!=0){
	LCD_DATA(*str++);
	Delay(delaytime);
	}     			
	str=display;
	while(1);
}




void vApplicationTickHook()
{
}
