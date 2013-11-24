#include "RTC.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "stm32f4xx_conf.h"
extern xTaskHandle *pvLEDTask;
void RTC_Alarm_IRQHandler()
{
  if(RTC_GetITStatus(RTC_IT_ALRA) != RESET)
  {
    vTaskSuspend( pvLEDTask );

    RTC_ClearITPendingBit(RTC_IT_ALRA);
    EXTI_ClearITPendingBit(EXTI_Line17);
    STM_EVAL_LEDOff(LED4);
    STM_EVAL_LEDOff(LED3);
    STM_EVAL_LEDOff(LED5);
    
  }
}
void RTC_WKUP_IRQHandler(void)
{
  RTC_TimeTypeDef RTC_TimeStruct;
  if(RTC_GetITStatus(RTC_IT_WUT) != RESET)
  {
    RTC_ClearITPendingBit(RTC_IT_WUT);
    EXTI_ClearITPendingBit(EXTI_Line22);
    STM_EVAL_LEDToggle(LED6);
    
    RTC_GetTime(RTC_Format_BIN, &RTC_TimeStruct);

    showCalendar_time(RTC_TimeStruct.RTC_Hours,
                      RTC_TimeStruct.RTC_Minutes,
                      RTC_TimeStruct.RTC_Seconds);
  }
}
static void initialize_RTC(void)
{
  RTC_InitTypeDef RTC_InitStructure;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);   /* Enable the PWR clock */
  PWR_BackupAccessCmd(ENABLE);                          /* Allow access to RTC */

  RCC_LSICmd(ENABLE);                                   /* Enable the LSI OSC */    
  while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET);   /* Wait till LSI is ready */  
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);               /* Select the RTC Clock Source */

  RCC_RTCCLKCmd(ENABLE);                                /* Enable the RTC Clock */
  RTC_WaitForSynchro();                                 /* Wait for RTC APB registers synchronisation */

  /* Configure the RTC data register and RTC prescaler 
  Make ck_spre 1Hz
  */
  RTC_InitStructure.RTC_AsynchPrediv = 127;
  RTC_InitStructure.RTC_SynchPrediv = 249;
  RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
  RTC_Init(&RTC_InitStructure);
}

static void setting_time(void)
{
  /* set 8:29:55 */
  RTC_TimeTypeDef RTC_TimeStruct;
  RTC_TimeStruct.RTC_Hours = 0x08;
  RTC_TimeStruct.RTC_Minutes = 0x29;
  RTC_TimeStruct.RTC_Seconds = 0x55;

  RTC_SetTime(RTC_Format_BCD, &RTC_TimeStruct);

}
static void initialize_RTC_alarm(void)
{
  EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /* EXTI configuration */
  EXTI_ClearITPendingBit(EXTI_Line17);
  EXTI_InitStructure.EXTI_Line = EXTI_Line17;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  /* Enable the RTC Alarm Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_Alarm_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
static void set_alarm_time(void)
{

  RTC_AlarmTypeDef RTC_AlarmStructure;

  RTC_AlarmCmd(RTC_Alarm_A, DISABLE);   /* disable before setting or cann't write */

  /* set alarm time 8:30:0 everyday */
  RTC_AlarmStructure.RTC_AlarmTime.RTC_H12     = RTC_H12_AM;
  RTC_AlarmStructure.RTC_AlarmTime.RTC_Hours   = 0x08;
  RTC_AlarmStructure.RTC_AlarmTime.RTC_Minutes = 0x30;
  RTC_AlarmStructure.RTC_AlarmTime.RTC_Seconds = 0x0;
  RTC_AlarmStructure.RTC_AlarmDateWeekDay = 0x31; // Nonspecific
  RTC_AlarmStructure.RTC_AlarmDateWeekDaySel = RTC_AlarmDateWeekDaySel_Date;
  RTC_AlarmStructure.RTC_AlarmMask = RTC_AlarmMask_DateWeekDay; // Everyday 
  RTC_SetAlarm(RTC_Format_BCD, RTC_Alarm_A, &RTC_AlarmStructure);

  /* Enable Alarm */
  RTC_ITConfig(RTC_IT_ALRA, ENABLE);
  RTC_AlarmCmd(RTC_Alarm_A, ENABLE);
  RTC_ClearFlag(RTC_FLAG_ALRAF);
}
void autowakeup_config()
{
  RTC_WakeUpCmd(DISABLE);
  RTC_WakeUpClockConfig(RTC_WakeUpClock_CK_SPRE_16bits);//configure 2
  RTC_SetWakeUpCounter(0x0000);//1 second 
  RTC_WakeUpCmd(ENABLE);
}
void enable_autowakeup_interrupt()
{
  NVIC_InitTypeDef NVIC_InitStructure;
  EXTI_InitTypeDef EXTI_InitStructure;
  /* Enable the RTC Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_WKUP_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  /* EXTI configuration */
  EXTI_ClearITPendingBit(EXTI_Line22);
  EXTI_InitStructure.EXTI_Line = EXTI_Line22;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
  
  RTC_ClearITPendingBit(RTC_IT_WUT);
  EXTI_ClearITPendingBit(EXTI_Line22);
  RTC_ITConfig(RTC_IT_WUT, ENABLE);
}


void RTC_setting()
{
    initialize_RTC();
    setting_time();
    initialize_RTC_alarm();
    set_alarm_time();
    autowakeup_config();
    enable_autowakeup_interrupt();
  
    

}
