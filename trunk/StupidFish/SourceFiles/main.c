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
			unsigned int vEncoder=0;
	int Pulse[8]={3600,3600,3600,3600,3600,3600,3600,3600};
	u8 pre_received=255;
	u8 received[9];
	u8 receivedbyte;
	int i;
  	RCC_Configuration();
	NVIC_Configuration();
  	USART1_Init();
	//USART2_Init();															
	//USART3_Init();
	//UART4_Init();
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
	//Timer4_Init();
	//Serial_PutString("\r\n======================================================================");
	GPIO_SetBits(GPIOA,GPIO_Pin_2);

	while(1) 
	{


		unsigned int tmp=0;

		if(UART5_Data.Locked==FALSE)
		{	
			tmp=UART5_Data.Value;
			vEncoder=tmp*36000>>11;
				SerialPutChar(vEncoder/10000+'0');
				SerialPutChar(vEncoder%10000/1000+'0');
				SerialPutChar(vEncoder%1000/100+'0');
				SerialPutChar(vEncoder%100/10+'0');
				SerialPutChar(vEncoder%10+'0');
				Serial_PutString("    "); 

		}
		//limitations	
		if((vEncoder)<=9000)	
			Timer4_MotorUp();
		if((vEncoder)>=20000)
			Timer4_MotorDown();
			//1





			//6
			if((vEncoder)<=15000&&vEncoder>=14000)
				Timer4_MotorSetFreq(1200);



			//7
			if((vEncoder)<=16000&&vEncoder>=15000)
				Timer4_MotorSetFreq(1100);
			//5
			if((vEncoder)<=14000&&vEncoder>=13000)
				Timer4_MotorSetFreq(1100);
			//8
			if((vEncoder)<=17000&&vEncoder>=16000)
				Timer4_MotorSetFreq(900);
			//4
			if((vEncoder)<=13000&&vEncoder>=12000)
				Timer4_MotorSetFreq(900);
			//9
			if((vEncoder)<=18000&&vEncoder>=17000)
				Timer4_MotorSetFreq(700);
			//3
			if((vEncoder)<=12000&&vEncoder>=11000)
				Timer4_MotorSetFreq(700);				
			//10
			if((vEncoder)<=19000&&vEncoder>=18000)
				Timer4_MotorSetFreq(500);
			//2
			if((vEncoder)<=11000&&vEncoder>=10000)
				Timer4_MotorSetFreq(500);
			//11
			if((vEncoder)<=20000&&vEncoder>=19000)
				Timer4_MotorSetFreq(300);

			if((vEncoder)<=10000&&vEncoder>=9000)   			
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
