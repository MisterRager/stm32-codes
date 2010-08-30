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
#include "../Config.h"
#include "stm32f10x_lib.h"

#if ( USE_LCD==1 && LCD_ILI9325==1 )
#include "../LCD/LCD_IOCFG.c"
#endif

#if	(USE_USART1==1 && TTY_AS_USART1==1)
#include "../STM32_Core/tty.h"
#endif

/******************************************************************************
 * Function Name  : GPIO_Configuration
 * Description    : General Purpose I/O configuration
 * Input          : None
 * Output         : None
 * Return         : None
 ******************************************************************************/
void GPIO_Configuration(void)
{
		/* Enabele GPIO Ports on APB2 */
    RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOA \
													| RCC_APB2Periph_GPIOB \
													|	RCC_APB2Periph_GPIOC \
													, ENABLE);
#if	(USE_USART1==1 &&TTY_AS_USART1==1)
		RCC_APB2PeriphClockCmd( RCC_APB2Periph_USART1,ENABLE);
		TTY_USART1_GPIO_Configuration();
		TTY_USART1_Init();
#endif	
    

#if ( USE_LCD==1 && LCD_ILI9325==1 )
		/* LCD GPIO Configuration 
		 * Want	:  	PD and PE enabled.
		 */
		RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOD \
													| RCC_APB2Periph_GPIOE \
													,ENABLE);
		LCD_GPIO_Configuration();
		LCD_FSMC_Configuration();
#endif
}	 

/******************* (C) COPYRIGHT 2010 WWW.USR.CC *****END OF FILE****/
