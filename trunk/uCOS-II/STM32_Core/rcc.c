/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : rcc.c
* Author             : Dean Sinaean (Dean.Sinaean@gmail.com)
* Version            : V0
* Date               : 07/11/2008
* Description        : This file provides rcc function.
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
#include "../Config.h"

/*****************************************************************************
 * Function Name  : RCC_Configuration
 * Description    : Reset and Clock Control configuration
 * Input          : None
 * Output         : None
 * Return         : None
 ******************************************************************************/
void RCC_Configuration(void)
{
    ErrorStatus HSEStartUpStatus;
    
    /* Reset the RCC clock configuration to default reset state */
    RCC_DeInit();
    
    /* Configure the High Speed External oscillator */
    RCC_HSEConfig(RCC_HSE_ON);
    
    /* Wait for HSE start-up */
    HSEStartUpStatus = RCC_WaitForHSEStartUp();
    
    if(HSEStartUpStatus == SUCCESS)
    {
        /* Enable Prefetch Buffer */
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
        
        /* Set the code latency value: FLASH Two Latency cycles */
        FLASH_SetLatency(FLASH_Latency_2);
        
        /* Configure the AHB clock(HCLK): HCLK = SYSCLK */
        RCC_HCLKConfig(RCC_SYSCLK_Div1);
        
        /* Configure the High Speed APB2 clcok(PCLK2): PCLK2 = HCLK */
        RCC_PCLK2Config(RCC_HCLK_Div1);
        
        /* Configure the Low Speed APB1 clock(PCLK1): PCLK1 = HCLK/2 */
        RCC_PCLK1Config(RCC_HCLK_Div2);
        
        /* Configure the PLL clock source and multiplication factor	*/
        /* PLLCLK = HSE*PLLMul = 8*9 = 72MHz */
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
        
        /* Enable PLL	*/
        RCC_PLLCmd(ENABLE);
        
        /* Check whether the specified RCC flag is set or not */
        /* Wait till PLL is ready	*/
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
        
        /* Select PLL as system clock source */
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
        
        /* Get System Clock Source */
        /* Wait till PLL is used as system clock source	*/
        while(RCC_GetSYSCLKSource() != 0x08);
    } 
#if ( USE_LCD==1 && LCD_ILI9325==1 )
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
#endif 
}

/******************* (C) COPYRIGHT 2010 WWW.USR.CC *****END OF FILE****/
