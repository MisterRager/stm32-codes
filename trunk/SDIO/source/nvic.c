/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : nvic.c
* Author             : Dean Sinaean (Dean.Sinaean@gmail.com)
* Version            : V0
* Date               : 07/11/2008
* Description        : This file provides nvic functions.
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

/* *****************************************************************************
 *  Function Name  : NVIC_Configuration
 * Description    : Nested Vectored Interrupt Controller configuration
 * Input          : None
 * Output         : None
 * Return         : None
 * *****************************************************************************/
void NVIC_Configuration(void)
{
		NVIC_InitTypeDef NVIC_InitStructure;
#ifdef VECT_TAB_RAM
    /* Set the Vector Tab base at location at 0x20000000 */
    NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#else
    /* Set the Vector Tab base at location at 0x80000000 */
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
#endif
		  /* Configure the NVIC Preemption Priority Bits */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

/******************* (C) COPYRIGHT 2010 WWW.USR.CC *****END OF FILE****/
