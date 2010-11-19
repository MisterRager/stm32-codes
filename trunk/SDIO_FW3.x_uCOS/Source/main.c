/**
******************************************************************************
* @file SDIO/main.c 
* @author  MCD Application Team
* @version  V3.0.0
* @date  04/06/2009
* @brief  Main program body
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "system.h"
#include "ucos_ii.h"

//for uC/OS-II
void InitTask(void *pdata);
void task0(void *pdata);
void task1(void *pdata);
#define OS_TASK_INIT_PRIO 			2 
#define OS_INIT_TASK_STACK_SIZE		64			/* 初始化任务堆栈大小 	*/ 
OS_STK	InitTaskStk[OS_INIT_TASK_STACK_SIZE];	/* 初始化任务堆栈 		*/

#define TASK_0_PRIO 	10
#define TASK_1_PRIO		11
#define	TASK_STACK_SIZE	64
OS_STK	Task0_Stack[TASK_STACK_SIZE];
OS_STK	Task1_Stack[TASK_STACK_SIZE];
	

int main(void)
{
	/* Clock Config */
	RCC_Configuration();
	/* Configure the GPIO ports */
	GPIO_Configuration_Main();
	/* Interrupt Config */
	NVIC_Configuration();
	///////////////// SDCARD Initialisation ////
	SDCard_Configuration();
//	res = f_open(&fsrc, "a.txt", FA_OPEN_ALWAYS | FA_WRITE |FA_READ);
//	if(res==FR_OK)
//		printf("File opened successfully.\n\r");
//	else 
//	{
//		printf("File open error.\n\r");
//		return 1;
//	}
//	printf("****************File Start***************\n\r");
//	while(f_read(&fsrc, fileBuff, buffsize,&br)==FR_OK)
//	{
//		printf("\n\r%s\n\r",fileBuff);
//		if(br!=buffsize)
//			break;
//	}
//	printf("****************File End*****************\n\r");
//	if(f_close(&fsrc)==FR_OK)
//		printf("\n\rFile closed.\n\r");

		 
// General Purpose I/O default configration
//	while(1);	
	OSInit();
	OSTaskCreate(InitTask, (void *)0, (OS_STK *)&InitTaskStk[OS_INIT_TASK_STACK_SIZE - 1],OS_TASK_INIT_PRIO);		 
	OSStart();
	return 0;
}

void InitTask(void *pdata)
{
		 
	pdata = pdata;				/* Avoid warnings from compiler	*/

	OSTaskCreate(task0, (void *)0, (OS_STK *)&Task0_Stack[TASK_STACK_SIZE - 1],	TASK_0_PRIO);
	OSTaskCreate(task1, (void *)0, (OS_STK *)&Task1_Stack[TASK_STACK_SIZE - 1], TASK_1_PRIO);


	SysTick_Config(SystemFrequency/72000);
	OSTaskDel(OS_PRIO_SELF);
	while(1)
	{
	}	
}

void task0(void *pdata)
{
		 
	pdata = pdata;				/* Avoid warnings from compiler	 				*/
	while(1)
	{
		printf("\n\r Task0 ");
		OSTimeDly(500); 									// if Task 1 does not run, led won't be lit off at all.
	}	
}

void task1(void *pdata)
{
		 
	pdata = pdata;				/* Avoid warnings from compiler	 				*/
	while(1)
	{
		printf("\n\r Task1................ ");
		OSTimeDly(300);
	}	
}




#ifdef  USE_FULL_ASSERT
/**
* @brief  Reports the name of the source file and the source line number
*   where the assert_param error has occurred.
* @param file: pointer to the source file name
* @param line: assert_param error line source number
* @retval : None
*/
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    
    /* Infinite loop */
    while (1)
    {}
}

#endif

/**
* @}
*/

/**
* @}
*/

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
