#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "stm32f4xx_conf.h"


static void LCD_display_task(void *pvParameters);
xTaskHandle *pvLEDTask;

int main(void)
{
	/* Create a task to display something in the LCD. */
  	xTaskCreate(LCD_display_task,
             (signed portCHAR *) "Liquid Crystal Display",
             512 /* stack size */, NULL,
             tskIDLE_PRIORITY + 5, NULL);

 	 vTaskStartScheduler();
  	return 0;
}
static void LCD_display_task(void *pvParameters)
{
	RCC_Configuration();		//RCC  initialization
	GPIO_Configuration();		//GPIO initialization
	Init_LCD();			//LCD  initialization    		

	//LCD_display(1,1,"0123456789");	//(row,column,value)--> display form (1,1) to (1,10)
	showCalendar_day(year,month,data);
	showCalendar_time(hour,min,sec);		
	while(1);
}


void vApplicationTickHook()
{
}
