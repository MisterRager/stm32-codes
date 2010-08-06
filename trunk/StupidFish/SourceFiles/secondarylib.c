/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : main.c
* Author             : Dean Sinaean
* Firm Ware Version  : V2.0.3
* Date               : 04/10/2010
* Description        : Main program body
********************************************************************************
* 
* 
* 
* 
* 
* 
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "secondarylib.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/*******************************************************************************
* Name  	: NVIC_Configuration
* Deion 	: Configures NVIC and Vector Table base location.
* Input 	: None
* Output	: None
* Return	: None
*******************************************************************************/
void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
#ifdef  VECT_TAB_RAM
    /* Set the Vector Table base location at 0x20000000 */
    NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#else  /* VECT_TAB_FLASH  */
    /* Set the Vector Table base location at 0x08000000 */
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
#endif
  
  /* Configure the NVIC Preemption Priority Bits */  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
  /* Enable the USART1 Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQChannel;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	/* Enable the USART2 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQChannel;
  NVIC_Init(&NVIC_InitStructure);

	/* Enable the USART3 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQChannel;
  NVIC_Init(&NVIC_InitStructure);

	/* Enable the UART4 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQChannel;
  NVIC_Init(&NVIC_InitStructure);

	/* Enable the UART5 Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQChannel;
  NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQChannel;
  NVIC_Init(&NVIC_InitStructure);
  
}






/* Rcc functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : RCC_Configuration
* Description    : Configures the different system clocks.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
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

  /* Enable GPIOA, GPIOC and USART1 clock  */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA 	\
											  |	RCC_APB2Periph_GPIOB	\
											 |	RCC_APB2Periph_GPIOC	\
											  |	RCC_APB2Periph_GPIOD	\
											 |	RCC_APB2Periph_TIM1 	\
											 |	RCC_APB2Periph_GPIOE	\
											 | RCC_APB2Periph_AFIO  \
                       | RCC_APB2Periph_USART1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);

}






/* Pwm functions */
/*******************************************************************************
* Function Name  : PWM_Set
* Description    : Set new PWM values
* Input          : Channel:integer:(0-7) ,Pulse:integer:(1200:6000)
* Output         : None
* Return         : 0-->mission complete; -1-->wrong Channel value;-2-->Wrong Pulse value
*******************************************************************************/
int PWM_Set(int Channel, int Pulse)
{
	TIM_OCInitTypeDef TIM_OCInitStructure;

	if(Pulse<1200 || Pulse>6000)
	return -2;

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState	 = TIM_OutputState_Enable ;
	TIM_OCInitStructure.TIM_Pulse = Pulse-1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	switch(Channel)
	{
		case 0:
			TIM_OC4Init(TIM4, &TIM_OCInitStructure);
			break;
		case 1:
			TIM_OC3Init(TIM4, &TIM_OCInitStructure);
			break;
		case 2:
			TIM_OC2Init(TIM4, &TIM_OCInitStructure);
			break;
		case 3:
			TIM_OC1Init(TIM4, &TIM_OCInitStructure);
			break;
		case 4:
			TIM_OC4Init(TIM3, &TIM_OCInitStructure);
			break;
		case 5:
			TIM_OC3Init(TIM3, &TIM_OCInitStructure);
			break;
		case 6:
			TIM_OC2Init(TIM3, &TIM_OCInitStructure);
			break;
		case 7:
			TIM_OC1Init(TIM3, &TIM_OCInitStructure);
			break;
		default:
			return -1;
	}
	return 0;
}
			

 
