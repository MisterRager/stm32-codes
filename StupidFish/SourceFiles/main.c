/* Using Timer2\3\4\5 and UART 2\3\4\5 for 4 motors */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"
#include "secondarylib.h"
#include "stepmotor.h"
#include "usart.h"
#include "timer.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
//#define VECT_TAB_RAM
extern void Delayms(u32 nTime);
extern void Delay_us(unsigned int  n);
extern void clearFlag(void);
extern void TX_Mode(unsigned char * BUF);
extern void RX_Mode(void);
extern void EXTI_Configuration(void);
extern void SPI2_Init(void);

struct RespondToken
{
	unsigned char token[7];
	bool valid=FALSE;
}respondToken;

unsigned int A=4500,qT=1000; // %degree: ms.
#define divNum 1275  //1~50
#define MotorId 2
#define AH		3
#define AL		4
#define TH		5
#define TL		6


struct Motor 
{
	//motor Identification
	unsigned char motorId;
	//Changed only when receive commands
	unsigned int A;//amplitude
	unsigned int T;//Period
	unsigned int speedTable[50];
	unsigned int positionTable[50];
	unsigned int centralPosition;
	unsigned int positionUpperLimit;
	unsigned int positionLowerLimit;
	//always changing
	unsigned int currentPosition;
	unsigned int currentIndex;
};
struct Motor BigMotorAleft,BigMotorARight,SmallMotorALeft,SmallMotorARight;


#define BigMotorALeftId 		0xa1
#define BigMotorARightId 		0xa2
#define SmallMotorALeftId 	0xa3
#define SmallMotorARightId 	0xa4

#define BigMotorBLeftId 		0xb1
#define BigMotorBRightId 		0xb2
#define SmallMotorBLeftId 	0xb3
#define SmallMotorBRightId 	0xb4

#define BigMotorCLeftId 		0xc1
#define BigMotorCRightId 		0xc2
#define SmallMotorCLeftId 	0xc3
#define SmallMotorCRightId 	0xc4

#define IsMotorOnBoardA(motorId) (motorId==0xa0)
#define IsMotorOnBoardB(motorId) (motorId==0xb0)
#define IsMotorOnBoardC(motorId) (motorId==0xc0)

#define BigMotorALeftPositionUpperLimit  20000
#define BigMotorALeftPositionLowerLimit		9000

#define BigMotorARightPositionUpperLimit 	20000
#define BigMotorARightPositionLowerLimit 	9000
 
#define SmallMotorALeftPositionUpperLimit	20000
#define SmallMotorALeftPositionLowerLimit	9000

#define SmallMotorARightPositionUpperLimit 20000
#define SmallMotorARightPositionLowerLimit 9000

#define BigMotorLeftActualPositiion vEncoder[0]
#define BigMotorRightcurrentPosition vEncoder[1]
#define SmallMotorLeftcurrentPosition vEncoder[2]
#define SmallMotorLeftcurrentPosition vEncoder[3]

void motorInit(void)
{

	BigMotorALeft.motorId=0xa1;
	BigMotorALeft.A=4500;
	BigMotorALeft.T=1000;
	BigMotorALeft.centralPosition=14000;
	BigMotorALeft.positionUpperLimit=20000;
	BigMotorALeft.positionLowerLimit=9000;
		
	BigMotorARight.motorId=0xa2;
	BigMotorARight.A=4500;
	BigMotorARight.T=1000;
	BigMotorARight.centralPosition=14000;
	BigMotorARight.positionUpperLimit=20000;
	BigMotorARight.positionLowerLimit=9000;
	
	SmallMotorALeft.motorId=0xa3;
	SmallMotorARight.A=4500;
	SmallMotorARight.T=1000;
	SmallMotorALeft.centralPosition=14000;
	SmallMotorALeft.positionUpperLimit=20000;
	SmallMotorALeft.positionLowerLimit=9000;
	
	SmallMotorARight.motorId=0xa4;
	SmallMotorARight.A=4500;
	SmallMotorARight.T=1000;
	SmallMotorARight.centralPosition=14000;
	SmallMotorARight.positionUpperLimit=20000;
	SmallMotorARight.positionLowerLimit=9000;
	
	refreshPosition();
}

void motorReset(void)
{
	int i,temp;
	if(BigMotorALeft.currentPosition<BigMotorALeft.centralPosition)
		Timer2_BigMotorLeftUp();
	else Timer2_BigMotorLeftDown();

	if(BigMotorARight.currentPosition<BigMotorARight.centralPosition)
		Timer3_BigMotorRightUp();
	else Timer3_BigMotorRightDown();

	if(SmallMotorALeft.currentPosition<SmallMotorALeft.centralPosition)
		Timer4_SmallMotorLeftUp();
	else Timer4_SmallMotorLeftDown();

	if(SmallMotorARight.currentPosition<SmallMotorARight.centralPosition)
		Timer5_SmallMotorRightUp();
	else Timer5_SmallMotorRightDown();

	Timer2_MotorInit();
	Timer2_MotorSetFreq(80);
	Timer3_MotorInit();
	Timer3_MotorSetFreq(80);
	Timer4_MotorInit();
	Timer4_MotorSetFreq(80);
	Timer5_MotorInit();
	Timer5_MotorSetFreq(80);
	while(1)
	{
		temp=BigMotorALeft.currentPosition-BigMotorALeft.centralPosition;
		if((temp>-50)&&(temp<=50))
			Timer2_BigMotorLeftStop();

		temp=BigMotorARight.currentPosition-BigMotorARight.centralPosition;
		if((temp>-50)&&(temp<=50))
			Timer3_BigMotorRightStop();

		temp=SmaillMotorALeft.currentPosition-SmallMotorALeft.centralPosition;
		if((temp>-50)&&(temp<=50))
			Timer4_SmallMotorLeftStop();

		temp=SmaillMotorARight.currentPosition-SmallMotorARight.centralPosition;
		if((temp>-50)&&(temp<=50))
			Timer4_SmallMotorRightStop();
	}
	refreshPosition();
	BigMotorALeft.centralPosition=BigMotorALeft.currentPosition;
	BigMotorARight.centralPosition=BigMotorARight.currentPosition;
	SmallMotorALeft.centralPosition=SmallMotorALeft.currentPosition;
	SmallMotorARight.centralPosition=SmallMotorARight.currentPosition;

	refreshTable(BigMotorALeft);
	refreshTable(BigMotorARight);
	refreshTable(SmallMotorALeft);
	refreshTable(SmallMotorARight);

	BigMotorALeft.currentIndex=49;
	BigMotorARight.currentIndex=49;
	SmallMotorALeft.currentIndex=49;
	SmallMotorARight.currentIndex=49;

	Timer2_BigMotorLeftUp();
	Timer3_BigMotorRightUp();
	Timer4_SmallMotorLeftUp();
	Timer5_SmallMotorRightUp();
}


			









void Wireless_Send(unsigned char * token)
{
	Enter_Critical();
	TX_Mode(token);
	Delay_us(1000);
	clearFlag();
	RX_Mode();
	Exit_Critical();
}

void Wireless_Received(unsigned char * token)
{
	unsigned int i;
	unsigned short A,T;
	//Set Parameters
	if(token[0]=='s'&&token[1]=='p')
	{	//Serial_PutString("cmd rd");
		A=token[AH]<<8+token[AL];
		T=token[TH]<<8+token[TL];
		if(token[MotorId]==BigMotorALeftId)
		{
			refreshTable(BigMotorALeft,A,T);
		}
		if(token[MotorId]==BigMotorARightId)
		{
			refreshTable(BigMotorARight,A,T);
		}
		if(token[MotorId]==SmallMotorALeftId)
		{
			refreshTable(SmallMotorALeft,A,T);
		}
		if(token[MotorId]==SmallMotorARightId)
		{
			refreshTable(SmallMotorARight,A,T);
		}
	}//Set Parameters end	
	//Program Control
	if(token[0]=='p' &&token[1]=='c')
	{
		
	}//Program Control end
	//Respond Token
	if(token[0]=='r'&&token[1]=='e')
	{
		unsigned int i;
		for(i=0;i<7;i++)
		{
			respondToken.token[i]=token[i];
		}
		respondToken.valid=TRUE;
	}//respond Token end
	
	//System_Init
		
}//Wireless_Received End





/* Private functions ---------------------------------------------------------*/
void refreshTable(struct Motor motor)
{
	unsigned int deltaSpeed,deltaT,i;
	A=motor.A;
	qT=motor.T/4;
	deltaT=qT/50;
	deltaSpeed=A/divNum;
	motor.speedTable[0]=deltaSpeed;
	motor.positionTable[0]=deltaSpeed*deltaT;
	for(i=1;i<50;i++)
	{
		motor.speedTable[i]=motor.speedTable[i-1]+deltaSpeed;
		motor.positionTable[i]=motor.currentPosition+motor.positionTable[i-1]+motor.speedTable[i]*deltaT;
	}
}
	
	

void refreshPosition(void)
{
	unsigned int tmp;
	if(UART5_Data.Locked==FALSE)
	{	
		tmp=UART5_Data.Value;
		SmallMotorARight.currentPosition=tmp*36000>>11;
	}
	if(UART4_Data.Locked==FALSE)
	{	
		tmp=UART4_Data.Value;
		SmallMotorALeft.currentPosition=tmp*36000>>11;
	}
	if(USART3_Data.Locked==FALSE)
	{	
		tmp=USART3_Data.Value;
		BigMotorARight.currentPosition=tmp*36000>>11;
	}
	if(USART2_Data.Locked==FALSE)
	{	
		tmp=USART2_Data.Value;
		BigMotorALeft.currentPosition=tmp*36000>>11;
	}
}

void positionReport(void)
{
	unsigned int i,tmp;
	unsigned token[7];
	while(UART5_Data.Locked==FALSE);
	tmp=UART5_Data.Value;
	SmallMotorARight.currentPosition=tmp*36000>>11;
	token[0]='R';
	token[1]=0xa4;
	token[2]=SmallMotorARight.currentPosition/10000+'0';
	token[3]=SmallMotorARight.currentPosition%10000/1000+'0';
	token[4]=SmallMotorARight.currentPosition%1000/100+'0';
	token[5]=SmallMotorARight.currentPosition%100/10+'0';
	token[6]=SmallMotorARight.currentPosition%10+'0';
	Wireless_Send(token);
	//while(respondToken.valid==FALSE);

	while(UART4_Data.Locked==FALSE);
	tmp=UART4_Data.Value;
	SmallMotorALeft.currentPosition=tmp*36000>>11;
	token[0]='R';
	token[1]=0xa3;
	token[2]=SmallMotorALeft.currentPosition/10000+'0';
	token[3]=SmallMotorALeft.currentPosition%10000/1000+'0';
	token[4]=SmallMotorALeft.currentPosition%1000/100+'0';
	token[5]=SmallMotorALeft.currentPosition%100/10+'0';
	token[6]=SmallMotorALeft.currentPosition%10+'0';
	Wireless_Send(token);

	while(USART3_Data.Locked==FALSE);
	tmp=USART3_Data.Value;
	BigMotorARight.currentPosition=tmp*36000>>11;
	token[0]='R';
	token[1]=0xa2;
	token[2]=BigMotorARight.currentPosition/10000+'0';
	token[3]=BigMotorARight.currentPosition%10000/1000+'0';
	token[4]=BigMotorARight.currentPosition%1000/100+'0';
	token[5]=BigMotorARight.currentPosition%100/10+'0';
	token[6]=BigMotorARight.currentPosition%10+'0';
	Wireless_Send(token);

	while(USART2_Data.Locked==FALSE);
	tmp=USART2_Data.Value;
	BigMotorALeft.currentPosition=tmp*36000>>11;
	token[0]='R';
	token[1]=0xa1;
	token[2]=BigMotorALeft.currentPosition/10000+'0';
	token[3]=BigMotorALeft.currentPosition%10000/1000+'0';
	token[4]=BigMotorALeft.currentPosition%1000/100+'0';
	token[5]=BigMotorALeft.currentPosition%100/10+'0';
	token[6]=BigMotorALeft.currentPosition%10+'0';
	Wireless_Send(token);
}

void System_Loop(void)
{
	int i;
	Timer2_BigMotorLeftStart();
	Timer3_BigMotorRightStart();
	Timer4_SmallMotorLeftStart();
	Timer4_SmallMotorRightStart();
	while(1)
	{
		for(i=0;i<=5;i++)
		{
			if(BigMotorALeft.currentPosition>=BigMotorALeft.positionTable[BigMotorALeft.currentIndex+i-1]
				&&BigMotorALeft.currentPosition<=BigMotorALeft.positionTable[BigMotorALeft.currentIndex+i])
			{
				if(i==0)
					set

					
			}

					
	}
}
	
 

void System_Init(void)
{
/* Principles to follow :
1.Motor positon detection and report.


*/
	positionReport();
	motorInit();
	motorReset();
	positionReport();

}
/*******************************************************************************
* Function Name  : Main
* Description    : Main Program
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
int main(void)
{
	unsigned int vEncoder[4];
	int i;
  RCC_Configuration();
	NVIC_Configuration();
	EXTI_Configuration();
  USART1_Init();
	USART2_Init();															
	USART3_Init();
	UART4_Init();
	UART5_Init();
	SPI2_Init();
	SysTick_Init();
	RX_Mode();

	System_Init();



	while(1) 
	{
		vEncoder_Refresh();
		//////////////////////////////////////////////////////////////////////////////	
		if( (BigMotorLeftcurrentPosition) <= BigMotorALeftPositionLowerLimit )	
			Timer2_BigMotorLeftUp();
		if( (BigMotorLeftcurrentPosition) >=BigMotorALeftPositionUpperLimit )
			Timer2_BigMotorLeftDown();
		if( (BigMotorRightcurrentPosition) <= BigMotorARightPositionLowerLimit )	
			Timer3_BigMotorRightUp();
		if( (BigMotorRightcurrentPosition) >=BigMotorARightPositionUpperLimit )
			Timer3_BigMotorRightDown();
		if( (SmallMotorLeftcurrentPosition) <= SmallMotorALeftPositionLowerLimit )	
			Timer4_SmallMotorLeftUp();
		if( (BigMotorLeftcurrentPosition) >=SmallMotorALeftPositionUpperLimit )
			Timer4_SmallMotorLeftDown();
		if( (SmallMotorRightcurrentPosition) <= SmallMotorARightPositionLowerLimit )	
			Timer5_SmallMotorRightUp();
		if( (SmallMotorRightcurrentPosition) >=SmallMotorARightPositionUpperLimit )
			Timer5_SmallMotorRightDown();
		////////////////////////////////////////////////////////////////////////////
		//6
		for(i=0;i<50;i++)
		{
			if(BigMotorLeftcurrentPosition>




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
		  



	}//end while

}//end main();
