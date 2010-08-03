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
	u8 received[9];
	u8 receivedbyte;
	int i;
  	RCC_Configuration();
  	USART1_Init();
	USART2_Init();															
	USART3_Init();
	//UART4_Init();
	UART5_Init();
	Timer2_Init(4800);
	Timer3_Init();
	Timer4_Init();
	//Serial_PutString("\r\n======================================================================");
	GPIO_SetBits(GPIOA,GPIO_Pin_2);

	while(1) 
	{


		unsigned char tmp=0;
		unsigned int vEncoder=0;
		u8 i;
		for(i=0;i<9;i++)
		{
			while(SET!=USART_GetFlagStatus(UART5,USART_FLAG_RXNE));//wait for another byte
        		received[i]=(u8)USART_ReceiveData(UART5);
        }

		for(i=0;i<9;i++)
		{
			if((received[i]==0xff)&&(received[i+1]==0x81)&&(received[i+2]==0x00))
			{	
				vEncoder=(received[i+3]<<8)|(received[i+4]);
				vEncoder=36000*vEncoder>>11;	
				Serial_PutString("Degree:");		
				SerialPutChar(vEncoder/10000+'0');
				SerialPutChar(vEncoder%10000/1000+'0');
				SerialPutChar(vEncoder%1000/100+'0');
				SerialPutChar('.');
				SerialPutChar(vEncoder%100/10+'0');
				SerialPutChar(vEncoder%10+'0');
				Serial_PutString("\n");	
			}
			//received[0]=0;	   	
		}
		//limitations	
			if((vEncoder)<=9000)	
				GPIO_ResetBits(GPIOA,GPIO_Pin_2);
			if((vEncoder)>=20000)
				GPIO_SetBits(GPIOA,GPIO_Pin_2);
			//1





			//6
			if((vEncoder)<=15000&&vEncoder>=14000)
				Timer2_Init(5000/5);



			//7
			if((vEncoder)<=16000&&vEncoder>=15000)
				Timer2_Init(6000/5);
			//5
			if((vEncoder)<=14000&&vEncoder>=13000)
				Timer2_Init(6000/5);
			//8
			if((vEncoder)<=17000&&vEncoder>=16000)
				Timer2_Init(7500/5);
			//4
			if((vEncoder)<=13000&&vEncoder>=12000)
				Timer2_Init(7500/5);
			//9
			if((vEncoder)<=18000&&vEncoder>=17000)
				Timer2_Init(9000/5);
			//3
			if((vEncoder)<=12000&&vEncoder>=11000)
				Timer2_Init(9000/5);				
			//10
			if((vEncoder)<=19000&&vEncoder>=18000)
				Timer2_Init(14000/5);
			//2
			if((vEncoder)<=11000&&vEncoder>=10000)
				Timer2_Init(14000/5);
			//11
			if((vEncoder)<=20000&&vEncoder>=19000)
				Timer2_Init(18000/5);

			if((vEncoder)<=10000&&vEncoder>=9000)   			
				Timer2_Init(18000/5);																								
				
				
				
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
