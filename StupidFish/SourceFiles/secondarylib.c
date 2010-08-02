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
/* Usart functions ---------------------------------  ------------------------*/
/*******************************************************************************
* Function Name  : SerialPutChar
* Description    : Print a character on the HyperTerminal
* Input          : - c: The character to be printed
* Output         : None
* Return         : None
*******************************************************************************/
void SerialPutChar(u8 c)
{
  USART_SendData(USART1, c);
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}

/*******************************************************************************
* Function Name  : Serial_PutString
* Description    : Print a string on the HyperTerminal
* Input          : - s: The string to be printed
* Output         : None
* Return         : None
*******************************************************************************/
void Serial_PutString(u8 *s)
{
  while (*s != '\0')
  {
    SerialPutChar(*s);
    s ++;
  }
}

/*******************************************************************************
* Function Name  : IAP_Init
* Description    : Initialize the IAP: Configure RCC, USART and GPIOs.
* Input          : None
* Output         : None
* Return         : None
* Note			 : You have to run RCC_Configuration() before calling this function
*******************************************************************************/
void USART1_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;

  /* Clock configuration -------------------------------------------------------*/

  /* Configure the GPIO ports( USART1 Transmit and Receive Lines) */
  /* Configure the USART1_Tx as Alternate function Push-Pull */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Configure the USART1_Rx as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* USART1 configuration ------------------------------------------------------*/
  /* USART1 configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  /* Configure the USART1 */
  USART_Init(USART1, &USART_InitStructure);

  /* Enable the USART1 */
  USART_Cmd(USART1, ENABLE);
}

void USART2_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;

  /* Clock configuration -------------------------------------------------------*/

  /* Configure the GPIO ports( USART1 Transmit and Receive Lines) */
  /* Configure the USART1_Tx as Alternate function Push-Pull */
  /* Configure USART4_Tx(PC10) as alternate function push-pull */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO,ENABLE);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  // Configure USART4_Rx(PC11) as input floating 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOD, &GPIO_InitStructure);  


  /* USART1 configuration ------------------------------------------------------*/
  /* USART1 configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  /* Configure the USART1 */
  USART_Init(USART2, &USART_InitStructure);

  /* Enable the USART1 */
  USART_Cmd(USART2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO,ENABLE);
}

void USART3_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;

  /* Clock configuration -------------------------------------------------------*/

  /* Configure the GPIO ports( USART1 Transmit and Receive Lines) */
  /* Configure the USART1_Tx as Alternate function Push-Pull */
  /* Configure USART4_Tx(PC10) as alternate function push-pull */
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_PinRemapConfig(GPIO_FullRemap_USART3,ENABLE);


  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);

  // Configure USART4_Rx(PC11) as input floating 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOD, &GPIO_InitStructure);  


  /* USART1 configuration ------------------------------------------------------*/
  /* USART1 configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  /* Configure the USART1 */
  USART_Init(USART3, &USART_InitStructure);

  /* Enable the USART1 */
  USART_Cmd(USART3, ENABLE);
}

void UART4_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;

  /* Clock configuration -------------------------------------------------------*/

  /* Configure the GPIO ports( USART1 Transmit and Receive Lines) */
  /* Configure the USART1_Tx as Alternate function Push-Pull */
  /* Configure USART4_Tx(PC10) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  // Configure USART4_Rx(PC11) as input floating 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOC, &GPIO_InitStructure);  


  /* USART1 configuration ------------------------------------------------------*/
  /* USART1 configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  /* Configure the USART1 */
  USART_Init(UART4, &USART_InitStructure);

  /* Enable the USART1 */
  USART_Cmd(UART4, ENABLE);
}

void UART5_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;

  /* Clock configuration -------------------------------------------------------*/

  /* Configure the GPIO ports( USART1 Transmit and Receive Lines) */
  /* Configure the USART1_Tx as Alternate function Push-Pull */
  /* Configure USART4_Tx(PC10) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  // Configure USART4_Rx(PC11) as input floating 
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_Init(GPIOD, &GPIO_InitStructure);  


  /* USART1 configuration ------------------------------------------------------*/
  /* USART1 configured as follow:
        - BaudRate = 115200 baud  
        - Word Length = 8 Bits
        - One Stop Bit
        - No parity
        - Hardware flow control disabled (RTS and CTS signals)
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  /* Configure the USART1 */
  USART_Init(UART5, &USART_InitStructure);

  /* Enable the USART1 */
  USART_Cmd(UART5, ENABLE);
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
	/* RCC system reset(for debug purpose) */
	RCC_DeInit();

	/* Enable HSI */
	RCC_HSICmd(ENABLE);	

  if (1)
	{
    /* Enable Prefetch Buffer */
  	FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);

    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1);

    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1);

    /* PCLK1 = HCLK/2 */
    RCC_PCLK1Config(RCC_HCLK_Div2);

    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSI_Div2, RCC_PLLMul_9);

    /* Enable PLL */
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {}

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while (RCC_GetSYSCLKSource() != 0x08)
    {}
  }

  /* Enable GPIOA, GPIOC and USART1 clock  */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA 	\
											 |	RCC_APB2Periph_GPIOC	\
											  |	RCC_APB2Periph_GPIOD	\
											 |	RCC_APB2Periph_TIM1 	\
											 |	RCC_APB2Periph_GPIOB	\
											 |	RCC_APB2Periph_GPIOE	\
											 | RCC_APB2Periph_AFIO  \
                       | RCC_APB2Periph_USART1, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5,ENABLE);

}

/* Timer functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : Timer2_Init
* Description    : Initialize Timer2
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer2_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	/*Alternative function clock setup  for GPIO */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	/*Clock setup for timer2 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	/*Pin remap for timer2*/
	//GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,ENABLE);
	/*PA0,1,2,3 setup for timer2*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 |GPIO_Pin_1 |GPIO_Pin_2 |GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	/*Timer Base Initialization for timer3 */
	TIM_TimeBaseInitStructure.TIM_Prescaler=15-1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseInitStructure.TIM_Period = 48000-1;
	TIM_TimeBaseInitStructure.TIM_ClockDivision	= 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);
	/*Auto-reload always */
	TIM_ARRPreloadConfig(TIM2, DISABLE);
	/*Channels initialization for timer3 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState	 = TIM_OutputState_Enable ;
	TIM_OCInitStructure.TIM_Pulse = 3600-1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);
	/*CCRs auto-reload always */
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Disable);
	TIM_OC2PreloadConfig(TIM2,TIM_OCPreload_Disable);
	TIM_OC3PreloadConfig(TIM2,TIM_OCPreload_Disable);
	TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Disable);
	/*Start counter for timer2 */
	TIM_Cmd(TIM2, ENABLE);
}
/*End Timer2_Init()*/

/*******************************************************************************
* Function Name  : Timer3_Init
* Description    : Initialize Timer3
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer3_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	/*Alternative function clock setup  for GPIO */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	/*Clock setup for timer3 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	/*Pin remap for timer3*/
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM3,ENABLE);
	/*PC6,7,8,9 setup for timer3*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 |GPIO_Pin_7 |GPIO_Pin_8 |GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
	/*Timer Base Initialization for timer3 */
	TIM_TimeBaseInitStructure.TIM_Prescaler=15-1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseInitStructure.TIM_Period = 48000-1;
	TIM_TimeBaseInitStructure.TIM_ClockDivision	= 0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);
	/*Auto-reload always */
	TIM_ARRPreloadConfig(TIM3, DISABLE);
	/*Channels initialization for timer3 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState	 = TIM_OutputState_Enable ;
	TIM_OCInitStructure.TIM_Pulse = 3600-1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	/*CCRs auto-reload always */
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Disable);
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Disable);
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Disable);
	TIM_OC4PreloadConfig(TIM3,TIM_OCPreload_Disable);
	/*Start counter for timer3 */
	TIM_Cmd(TIM3, ENABLE);
}
/*End Timer3_Init()*/

/*******************************************************************************
* Function Name  : Timer4_Init
* Description    : Initialize Timer4
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer4_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;

	/*Clock setup for timer4 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	/*PB6,7,8,9 setup for timer4*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 |GPIO_Pin_7 |GPIO_Pin_8 |GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
	/*Timer Base Initialization for timer4 */
	TIM_TimeBaseInitStructure.TIM_Prescaler=15-1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseInitStructure.TIM_Period = 48000-1;
	TIM_TimeBaseInitStructure.TIM_ClockDivision	= 0;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	/*Auto-reload always */
	TIM_ARRPreloadConfig(TIM4, DISABLE);
	/*Channels initialization for timer4 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState	 = TIM_OutputState_Enable ;
	TIM_OCInitStructure.TIM_Pulse = 3600-1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	TIM_OC3Init(TIM4, &TIM_OCInitStructure);
	TIM_OC4Init(TIM4, &TIM_OCInitStructure);
	/*CCRs auto-reload always */
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_OC2PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM4,TIM_OCPreload_Enable);
	/*Start counter for timer4 */
	TIM_Cmd(TIM4, ENABLE);
}
/*End Timer4_Init()*/

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
			

 
