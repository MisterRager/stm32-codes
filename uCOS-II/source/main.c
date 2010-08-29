//******************************************************************************
//
//
//
//
//
//
//******************************************************************************
#define VECT_TAB_FLASH



// *****************************************************************************
// Description: Includes
// *****************************************************************************
#include "stm32f10x_lib.h"
#include "stdio.h"
#include "usart.h"
#include "ucos_ii.h"
#include "app_cfg.h"





/*******************************************************************************
* Function Name  : fputc
* Description    : Retargets the C library printf function to the USART.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int fputc(int ch, FILE *f)
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
	SerialPutChar(ch);
	return ch;
}
//-----------------------------------------------------------------------------------------
#define OS_TASK_INIT_PRIO 			2 
#define OS_INIT_TASK_STACK_SIZE		64			/* ≥ı ºªØ»ŒŒÒ∂—’ª¥Û–° 	*/ 
OS_STK	InitTaskStk[OS_INIT_TASK_STACK_SIZE];	/* ≥ı ºªØ»ŒŒÒ∂—’ª 		*/

#define TASK_0_PRIO 	10
#define TASK_1_PRIO		11
#define	TASK_STACK_SIZE	64
OS_STK	Task0_Stack[TASK_STACK_SIZE];
OS_STK	Task1_Stack[TASK_STACK_SIZE];

void task0(void *pdata);
void task1(void *pdata);
void InitTask(void *pdata);


// *****************************************************************************
// Description: Private defines
// *****************************************************************************




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
		USART1_Init();
		SysTick_Configuration();
		SysTick_Start();
	//	while(1);
		
		OSInit();

		OSTaskCreate(InitTask, (void *)0, (OS_STK *)&InitTaskStk[OS_INIT_TASK_STACK_SIZE - 1],OS_TASK_INIT_PRIO);
		 SysTick_Start();
		OSStart();
			
		
		//GPIO_SetBits(GPIOE, GPIO_Pin_3);
		return 0;
}


#ifdef  DEBUG
void assert_failed(u8* file, u32 line)
{ 
  	while (1)
  	{

  	}
}
#endif

void InitTask(void *pdata)
{
		 
	pdata = pdata;				/* ∑¿÷π±‡“Î∆˜æØ∏Ê 				*/

	OSTaskCreate(task0, (void *)0, (OS_STK *)&Task0_Stack[TASK_STACK_SIZE - 1],	TASK_0_PRIO);
	OSTaskCreate(task1, (void *)0, (OS_STK *)&Task1_Stack[TASK_STACK_SIZE - 1], TASK_1_PRIO);


	
	OSTaskDel(OS_PRIO_SELF);
	while(1)
	{
	}	
}

void task0(void *pdata)
{
		 
	pdata = pdata;				/* ∑¿÷π±‡“Î∆˜æØ∏Ê 				*/
	while(1)
	{
	//	printf("\n\r Task0 ");
		OSTimeDly(5000); 									// if Task 1 does not run, led won't be lit off at all.
	}	
}

void task1(void *pdata)
{
		 
	pdata = pdata;				/* ∑¿÷π±‡“Î∆˜æØ∏Ê 				*/
	while(1)
	{
		//	printf("\n\r Task1................ ");
	}	
}

// ******************************** END OF FILE ********************************

