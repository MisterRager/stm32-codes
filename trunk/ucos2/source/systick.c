/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : systick.c
* Author             : Dean Sinaean (Dean.Sinaean@gmail.com)
* Version            : V0
* Date               : 07/11/2008
* Description        : This file provides systick function.
********************************************************************************
* THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
* WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE TIME.
* AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY DIRECT,
* INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING FROM THE
* CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE CODING
* INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
*******************************************************************************/
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"

/******************************************************************************
 * Function Name  : SysTick_Configuration
 * Description    : None
 * Input          : None
 * Output         : None
 * Return         : None
 ******************************************************************************/
void SysTick_Configuration(void)
{
	SysTick_CLKSourceConfig(SysTick_CLKSource_HCLK);
	SysTick_SetReload(72000);
	SysTick_ITConfig(ENABLE);
}
/******************************************************************************
 * Function Name  : SysTick_Start
 * Description    : None
 * Input          : None
 * Output         : None
 * Return         : None
 ******************************************************************************/
void SysTick_Start(void)
{
	SysTick_CounterCmd(SysTick_Counter_Clear);
	SysTick_CounterCmd(SysTick_Counter_Enable);
}
/******************* (C) COPYRIGHT 2010 WWW.USR.CC *****END OF FILE****/
