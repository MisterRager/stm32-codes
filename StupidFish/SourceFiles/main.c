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
#include "stepmotor.h"
#include "usart.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
//#define VECT_TAB_RAM



/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
  void TIM_Configuration(void);
unsigned int vEncoder[4];
/* Private functions ---------------------------------------------------------*/
void vEncoder_Refresh(void)
{
	unsigned int tmp;
	if(UART5_Data.Locked==FALSE)
	{	
		tmp=UART5_Data.Value;
		vEncoder[3]=tmp*36000>>11;
		/*
		Serial_PutString("UART5:"); 
		SerialPutChar(vEncoder[3]/10000+'0');
		SerialPutChar(vEncoder[3]%10000/1000+'0');
		SerialPutChar(vEncoder[3]%1000/100+'0');
		SerialPutChar(vEncoder[3]%100/10+'0');
		SerialPutChar(vEncoder[3]%10+'0');
		Serial_PutString("\n\r"); 
		*/
	}
	if(UART4_Data.Locked==FALSE)
	{	
		tmp=UART4_Data.Value;
		vEncoder[2]=tmp*36000>>11;
		/*
		Serial_PutString("UART4:"); 
		SerialPutChar(vEncoder[2]/10000+'0');
		SerialPutChar(vEncoder[2]%10000/1000+'0');
		SerialPutChar(vEncoder[2]%1000/100+'0');
		SerialPutChar(vEncoder[2]%100/10+'0');
		SerialPutChar(vEncoder[2]%10+'0');
		Serial_PutString("\n\r"); 
		*/
	}
	if(USART3_Data.Locked==FALSE)
	{	
		tmp=USART3_Data.Value;
		vEncoder[1]=tmp*36000>>11;
		/*
		Serial_PutString("UART3:"); 
		SerialPutChar(vEncoder[1]/10000+'0');
		SerialPutChar(vEncoder[1]%10000/1000+'0');
		SerialPutChar(vEncoder[1]%1000/100+'0');
		SerialPutChar(vEncoder[1]%100/10+'0');
		SerialPutChar(vEncoder[1]%10+'0');
		Serial_PutString("\n\r"); 
		*/
	}
	if(USART2_Data.Locked==FALSE)
	{	
		tmp=USART2_Data.Value;
		vEncoder[0]=tmp*36000>>11;
		/*
		Serial_PutString("UART2:"); 
		SerialPutChar(vEncoder[0]/10000+'0');
		SerialPutChar(vEncoder[0]%10000/1000+'0');
		SerialPutChar(vEncoder[0]%1000/100+'0');
		SerialPutChar(vEncoder[0]%100/10+'0');
		SerialPutChar(vEncoder[0]%10+'0');
		Serial_PutString("\n\r"); 
		*/
	}
}
/*******************************************************************************
* Function Name  : Main
* Description    : Main Program
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main1(void)
{
	unsigned int vEncoder[5];
	int i;
  RCC_Configuration();
	NVIC_Configuration();
  USART1_Init();
	USART2_Init();															
	USART3_Init();
	UART4_Init();
	UART5_Init();
	Timer1_MotorInit();
	Timer1_MotorSetFreq(80);
	Timer2_MotorInit();
	Timer2_MotorSetFreq(800);
	Timer3_MotorInit();
	Timer3_MotorSetFreq(800);
	Timer4_MotorInit();
	Timer4_MotorSetFreq(800);
	Timer5_MotorInit();
	Timer5_MotorSetFreq(800);
	Timer8_MotorInit();
	Timer8_MotorSetFreq(800);

	while(1) 
	{
		vEncoder_Refresh();
		//limitations	
		if((vEncoder[3])<=9000)	
			Timer4_MotorUp();
		if((vEncoder[3])>=20000)
			Timer4_MotorDown();
			//1





			//6
			if((vEncoder[3])<=15000&&vEncoder[3]>=14000)
				Timer4_MotorSetFreq(1200);



			//7
			if((vEncoder[3])<=16000&&vEncoder[3]>=15000)
				Timer4_MotorSetFreq(1100);
			//5
			if((vEncoder[3])<=14000&&vEncoder[3]>=13000)
				Timer4_MotorSetFreq(1100);
			//8
			if((vEncoder[3])<=17000&&vEncoder[3]>=16000)
				Timer4_MotorSetFreq(900);
			//4
			if((vEncoder[3])<=13000&&vEncoder[3]>=12000)
				Timer4_MotorSetFreq(900);
			//9
			if((vEncoder[3])<=18000&&vEncoder[3]>=17000)
				Timer4_MotorSetFreq(700);
			//3
			if((vEncoder[3])<=12000&&vEncoder[3]>=11000)
				Timer4_MotorSetFreq(700);				
			//10
			if((vEncoder[3])<=19000&&vEncoder[3]>=18000)
				Timer4_MotorSetFreq(500);
			//2
			if((vEncoder[3])<=11000&&vEncoder[3]>=10000)
				Timer4_MotorSetFreq(500);
			//11
			if((vEncoder[3])<=20000&&vEncoder[3]>=19000)
				Timer4_MotorSetFreq(300);

			if((vEncoder[3])<=10000&&vEncoder[3]>=9000)   			
				Timer4_MotorSetFreq(300);																								
				
				
				
				/*

				SerialPutChar(vEncoder/10000+'0');
				SerialPutChar(vEncoder%10000/1000+'0');
				SerialPutChar(vEncoder%1000/100+'0');
				SerialPutChar(vEncoder%100/10+'0');
				SerialPutChar(vEncoder%10+'0');
				Serial_PutString("    ");*/
		/*
		if(SET==USART_GetFlagStatus(USART3,USART_FLAG_RXNE))
		{
			pre_received=received;
			received=(u8)USART_ReceiveData(USART3);	
			SerialPutChar(received);
			SerialPutChar('3');
		}
			
		if(SET==USART_GetFlagStatus(USART2,USART_FLAG_RXNE))
		{
			pre_received=received;
			received=(u8)USART_ReceiveData(USART2);	
			SerialPutChar(received);
			SerialPutChar('2');
		} */

		//if(SET==USART_GetFlagStatus(USART1,USART_FLAG_RXNE))
		//{
		//	received=(u8)USART_ReceiveData(USART1);

	/*	if(SET==USART_GetFlagStatus(USART1,USART_FLAG_RXNE))
		{
			tmp=(u8)USART_ReceiveData(USART1);
			if(tmp=='a')
				GPIO_SetBits(GPIOA,GPIO_Pin_2);
			else GPIO_ResetBits(GPIOA,GPIO_Pin_2);	 
		}	*/
		  



	}//end while

}//end main();
