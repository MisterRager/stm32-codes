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
#define OS_INIT_TASK_STACK_SIZE		64			/* ��ʼ�������ջ��С 	*/ 
OS_STK	InitTaskStk[OS_INIT_TASK_STACK_SIZE];	/* ��ʼ�������ջ 		*/
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
		OSInit();				/* ��ʼ��OS 	  */

  
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

	OSStart();				/* ���������񻷾� */
	 
  	return(0);
}

static void init_task_core(void *pdata)
{
		 
	pdata = pdata;				/* ��ֹ���������� 				*/
	GPIO_SetBits(GPIOB, GPIO_Pin_5);

	while(1)
	{
		//OSTaskSuspend(OS_PRIO_SELF);	/* �����ʼ������ 		*/
	}	
}

static void init_task_core1(void *pdata)
{
		 
	pdata = pdata;				/* ��ֹ���������� 				*/
	GPIO_ResetBits(GPIOB, GPIO_Pin_5);

	while(1)
	{
		//OSTaskSuspend(OS_PRIO_SELF);	/* �����ʼ������ 		*/
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

