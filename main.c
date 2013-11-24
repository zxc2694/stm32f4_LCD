#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "stm32f4xx_conf.h"

static int hour=23;
static int min=45;
static int sec=50;
static int year=13;
static int month=11;
static int data=24;

static void LCD_display_task(void *pvParameters);
static void LED_task(void *pvParameters);
xTaskHandle *pvLEDTask;

int main(void)
{
	/* Create a task to display something in the LCD. */
  	xTaskCreate(LCD_display_task,
             (signed portCHAR *) "Liquid Crystal Display",
             512 /* stack size */, NULL,
             tskIDLE_PRIORITY + 5, NULL);

	/* Create a task to flash the LED. */
	xTaskCreate(LED_task,
             (signed portCHAR *) "LED Flash",
             512 /* stack size */, NULL,
             tskIDLE_PRIORITY + 5,  pvLEDTask );

 	/* Start running the tasks. */
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

static void LED_task(void *pvParameters)
{
  RCC_ClocksTypeDef RCC_Clocks;
  uint8_t togglecounter = 0x00;

  while(1)
  {    
      /* Toggle LED3 */
      STM_EVAL_LEDToggle(LED3);
      vTaskDelay(200);
      /* Toggle LED4 */
      STM_EVAL_LEDToggle(LED4);
      vTaskDelay(200);
      /* Toggle LED5 */
      STM_EVAL_LEDToggle(LED5);
      vTaskDelay(200);
      /* Toggle LED6 */
  }
}


void vApplicationTickHook()
{
}
