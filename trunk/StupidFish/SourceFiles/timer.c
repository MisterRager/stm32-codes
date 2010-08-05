#include "stm32f10x_type.h"
#include "stm32f10x_lib.h"
#include "timer.h"

unsigned int gTimer_1ms;
void SysTick_Init(void)
{
  
  /* SysTick end of count event each 1ms with input clock equal to 9MHz (HCLK/8, default) */
  SysTick_SetReload(9000);
  /* Enable SysTick interrupt */
  SysTick_ITConfig(ENABLE);
  /* Enable the SysTick Counter */
  SysTick_CounterCmd(SysTick_Counter_Enable);
}


/*******************************************************************************
* Function Name  : Delay
* Description    : Inserts a delay time.
* Input          : nTime: specifies the delay time length, in milliseconds.
* Output         : None
* Return         : None
*******************************************************************************/
void Delayms(u32 nTime)
{
	unsigned int  counter;
  
  counter=gTimer_1ms;
  while( gTimer_1ms-counter < nTime);
  
}

/*******************************************************************************
* Function Name  : TimingDelay_Decrement
* Description    : Decrements the TimingDelay variable.
* Input          : None
* Output         : TimingDelay
* Return         : None
*******************************************************************************/
void TimingDelay_Decrement(void)
{
  gTimer_1ms++;
}


