/******************** (C) COPYRIGHT 2008 STMicroelectronics ********************
* File Name          : main.c
* Author             : Dean Sinaean
* Firm Ware Version  : V2.0.3
* Date               : 04/10/2010
* Description        : Main program body
********************************************************************************
* This program aims to generate 8-channel pwm signals, which would be sent to 
* servo motors on a robot arm. 
* TIM3_CH1-->PC6; TIM3_CH2-->PC7; TIM3_CH3-->PC8; TIM4_CH4-->PC9;MOTOR 0,1,2,3
* TIM4_CH1-->PB6; TIM4_CH2-->PB7; TIM4_CH3-->PB8; TIM4_CH4-->PB9;MOTOR 4,5,6,7
* 
* 
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "secondarylib.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
//#define VECT_TAB_RAM


/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
  void TIM_Configuration(void);
/* Private functions ---------------------------------------------------------*/
/*******************************************************************************
* Function Name  : Main
* Description    : Main Program
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{
	int Pulse[8]={3600,3600,3600,3600,3600,3600,3600,3600};
	u8 pre_received=255;
	u8 received=255;
	int i;
  RCC_Configuration();
  USART1_Init();
	USART2_Init();															
	USART3_Init();
	//UART4_Init();
	UART5_Init();
	Timer2_Init();
	Timer3_Init();
	Timer4_Init();
	//Serial_PutString("\r\n======================================================================");
	//Serial_PutString("\r\n=              (C) COPYRIGHT 2008 STMicroelectronics                 =");
	//Serial_PutString("\r\n=                                                                    =");
	//Serial_PutString("\r\n=     In-Application Programming Application  (Version 2.0.2)        =");
	//Serial_PutString("\r\n=                                                                    =");
	//Serial_PutString("\r\n=                                   By MCD Application Team          =");
	//Serial_PutString("\r\n======================================================================");

	//Timer3_Init();
	//TIM_CtrlPWMOutputs(TIM3, ENABLE);
	//Timer4_Init();
	//TIM_CtrlPWMOutputs(TIM4, ENABLE);


  //for (i=0;i<8;i++)
	//PWM_Set(i,Pulse[i]);
	while(1) {
	//SerialPutChar('w');
		if(SET==USART_GetFlagStatus(UART5,USART_FLAG_RXNE))
	{
		pre_received=received;
		received=(u8)USART_ReceiveData(UART5);	
		SerialPutChar(received);
	}	


		if(SET==USART_GetFlagStatus(USART3,USART_FLAG_RXNE))
	{
		pre_received=received;
		received=(u8)USART_ReceiveData(USART3);	
		SerialPutChar(received);
	}
			if(SET==USART_GetFlagStatus(USART2,USART_FLAG_RXNE))
	{
		pre_received=received;
		received=(u8)USART_ReceiveData(USART2);	
		SerialPutChar(received);
	}	

															 

	}

}
