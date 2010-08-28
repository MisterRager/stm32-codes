/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : gpio.c
* Author             : Dean Sinaean (Dean.Sinaean@gmail.com)
* Version            : V0
* Date               : 07/11/2008
* Description        : This file provides gpio function.
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
 * Function Name  : GPIO_Configuration
 * Description    : General Purpose I/O configuration
 * Input          : None
 * Output         : None
 * Return         : None
 ******************************************************************************/
void GPIO_Configuration(void)
{
		GPIO_InitTypeDef    		GPIO_InitStructure;
		/* Enabele GPIO Ports on APB2 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB |
                           RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD |
                           RCC_APB2Periph_GPIOE, ENABLE);
    
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

    //GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    //GPIO_Init(GPIOC, &GPIO_InitStructure);
    //GPIO_Init(GPIOD, &GPIO_InitStructure);
    GPIO_Init(GPIOE, &GPIO_InitStructure); 
}	 

/******************* (C) COPYRIGHT 2010 WWW.USR.CC *****END OF FILE****/
