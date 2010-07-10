//******************************************************************************
//
//
//
//
//
//
//******************************************************************************


// *****************************************************************************
// Description: Includes
// *****************************************************************************
#include "stm32f10x_lib.h"
#include "app_cfg.h"
#define OS_TASK_INIT_PRIO 			2 
#define OS_INIT_TASK_STACK_SIZE		64			/* 初始化任务堆栈大小 	*/ 
OS_STK	InitTaskStk[OS_INIT_TASK_STACK_SIZE];	/* 初始化任务堆栈 		*/
OS_STK	InitTaskStk1[OS_INIT_TASK_STACK_SIZE];	



// *****************************************************************************
// Description: Private defines
// *****************************************************************************
#define VECT_TAB_RAM



// *****************************************************************************
// Description: Private variables
// *****************************************************************************

// *****************************************************************************
// Description: Private functions prototypes
// *****************************************************************************
extern void RCC_Configuration(void); 
extern void NVIC_Configuration(void);
extern void GPIO_Configuration(void);
extern void SysTick_Configuration(void);
extern void SysTick_Start(void);
unsigned int sig=0;

static void init_task_core(void *pdata);
static void init_task_core1(void *pdata);



// *****************************************************************************
// Function Name  : main
// Description    : Main program.
// Input          : None
// Output         : None
// Return         : None
// *****************************************************************************
int main(void)
{
#ifdef DEBUG
	debug();
#endif
		int led=0;
		led=0;
    //  System clock configuration
    RCC_Configuration();    
    // Nested Vector Interrupt Controller configuration
    NVIC_Configuration();   
    // General Purpose I/O default configration
    GPIO_Configuration();
		SysTick_Configuration();
		SysTick_Start();
		OSInit();				/* 初始化OS 	  */

  
  	OSTaskCreateExt(init_task_core, (void *)0, (OS_STK *)&InitTaskStk[OS_INIT_TASK_STACK_SIZE - 1],
					OS_TASK_INIT_PRIO,
					OS_TASK_INIT_PRIO,
					(OS_STK *)&InitTaskStk[0],
					OS_INIT_TASK_STACK_SIZE,
					(void *)0,
					OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);	
		  	OSTaskCreateExt(init_task_core1, (void *)0, (OS_STK *)&InitTaskStk1[OS_INIT_TASK_STACK_SIZE - 1],
					OS_TASK_INIT_PRIO-1,
					OS_TASK_INIT_PRIO-1,
					(OS_STK *)&InitTaskStk1[0],
					OS_INIT_TASK_STACK_SIZE,
					(void *)0,
					OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);	
					
	#if (OS_TASK_NAME_SIZE >= 16)
		OSTaskNameSet(OS_TASK_IDLE_PRIO, (INT8U *)"Idle task", &err);
		OSTaskNameSet(OS_TASK_INIT_PRIO, (INT8U *)"Init task", &err);
	#endif

	OSStart();				/* 启动多任务环境 */
	 
  	return(0);
}

static void init_task_core(void *pdata)
{
		 
	pdata = pdata;				/* 防止编译器警告 				*/
	GPIO_SetBits(GPIOB, GPIO_Pin_5);

	while(1)
	{
		//OSTaskSuspend(OS_PRIO_SELF);	/* 挂起初始化任务 		*/
	}	
}

static void init_task_core1(void *pdata)
{
		 
	pdata = pdata;				/* 防止编译器警告 				*/
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);

	while(1)
	{
		//OSTaskSuspend(OS_PRIO_SELF);	/* 挂起初始化任务 		*/
	}	
}

#ifdef  DEBUG
void assert_failed(u8* file, u32 line)
{ 
  	// User can add his own implementation to report the file name and line number,
  	//   ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line)

  	while (1)
  	{

  	}
}
#endif

// ******************************** END OF FILE ********************************

