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

static void Task_0(void *pdata);
static void Task_1(void *pdata);


void delay72M(void)
{
	int i,j;
	for(i=0;i<1000;i++)
		for(j=0;j<9000;j++);
}
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

    //  System clock configuration
    RCC_Configuration();    
    // Nested Vector Interrupt Controller configuration
    NVIC_Configuration();   
    // General Purpose I/O default configration
    GPIO_Configuration();
		SysTick_Configuration();
		SysTick_Start();
		OSInit();				/* 初始化OS 	  */

  
  	OSTaskCreateExt(Task_0, (void *)0, (OS_STK *)&InitTaskStk[OS_INIT_TASK_STACK_SIZE - 1],
					OS_TASK_INIT_PRIO,
					OS_TASK_INIT_PRIO,
					(OS_STK *)&InitTaskStk[0],
					OS_INIT_TASK_STACK_SIZE,
					(void *)0,
					OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR);	
		 OSTaskCreateExt(Task_1, (void *)0, (OS_STK *)&InitTaskStk1[OS_INIT_TASK_STACK_SIZE - 1],
					OS_TASK_INIT_PRIO+1,
					OS_TASK_INIT_PRIO+1,
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

static void Task_0(void *pdata)
{
		 
	pdata = pdata;				/* 防止编译器警告 				*/
	while(1)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_5);	//Task 0 light the led up for 1 second
		delay72M();												// and then suspend wait for 5 seconds.
		OSTimeDly(5000); 									// if Task 1 does not run, led won't be lit off at all.
	}	
}

static void Task_1(void *pdata)
{
		 
	pdata = pdata;				/* 防止编译器警告 				*/
	while(1)
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);	//While running the task, set led off always. 
		//delay72M();
		//OSTimeDly(1);
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

