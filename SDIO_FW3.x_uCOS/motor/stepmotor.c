#include "stepmotor.h"

/*******************************************************************************
* Function Name  : Timer1_Prepare
* Description    : Initialize Timer1
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer1_Prepare(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/*Alternative function clock setup  for GPIO */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOE | RCC_APB2Periph_USART1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	/*Pin remap for timer1*/
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,ENABLE);
	
	/*PB11 setup for timer1*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9 |GPIO_Pin_11 |GPIO_Pin_13 |GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE, &GPIO_InitStructure);

//	/* PE11,13,14 setup for GPIO */
//	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
//	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11 |GPIO_Pin_13 |GPIO_Pin_14;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_Init(GPIOE,&GPIO_InitStructure);
}
/* End Timer1_Prepare */

/*******************************************************************************
* Function Name  : Timer1_SetTimeBaseFreq
* Description    : Initialize Timer Base for Timer 1
* Input          : freq
* Output         : None
* Return         : None
*******************************************************************************/
void Timer1_SetTimeBaseCount(uint32_t count)
{
//	static uint32_t value;

	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//	value=freq;
//	if(value==2400000/freq)
//		return;
//	else value=2400000/freq;

	/*Timer Base Initialization for timer1 */
	TIM_TimeBaseInitStructure.TIM_Prescaler=30-1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseInitStructure.TIM_Period = count-1;
	TIM_TimeBaseInitStructure.TIM_ClockDivision	= 0;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);

	/*Auto-reload always */
	TIM_ARRPreloadConfig(TIM1, DISABLE);
}
/* END Timer1_SetTimeBaseFreq */

/*******************************************************************************
* Function Name  : Timer1_SetOutputPulseWidth
* Description    : 3rd Step->Set pulse width for each channal;
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer1_SetOutputPulseWidth( uint32_t width,PWM_CHANNEL CHn)
{
	TIM_OCInitTypeDef TIM_OCInitStructure;
	/*Channels initialization for timer1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState	 = TIM_OutputState_Enable ;
	TIM_OCInitStructure.TIM_Pulse = width;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	switch( CHn)
	{
		case CH1:
		TIM_OC1Init(TIM1, &TIM_OCInitStructure); //PE9
		break;

		case CH2:
		TIM_OC2Init(TIM1, &TIM_OCInitStructure);  //PE11
		break;

		case CH3:
		TIM_OC3Init(TIM1, &TIM_OCInitStructure); //PE13
		break;

		case CH4:
		TIM_OC4Init(TIM1, &TIM_OCInitStructure);  //PE14
		break;

		default:
		break;
	}
}
/* END Timer1_SetOutputPulseWidth */

/*******************************************************************************
* Function Name  : Timer1_StartStop
* Description    : 4th Step->Start or stop timer and output.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer1_StartStop(bool start)
{
//	/*CCRs auto-reload always */
//	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);
	/*Start counter for timer1 */
	if(start==TRUE)
	{
		TIM_Cmd(TIM1, ENABLE);
		TIM_CtrlPWMOutputs(TIM1, ENABLE);
	}
	else
	{
		TIM_Cmd(TIM1, DISABLE);
		TIM_CtrlPWMOutputs(TIM1, DISABLE);
	}
}
/* End Timer1_StartStop */


/*******************************************************************************
* Function Name  : Timer2_Prepare
* Description    : Initialize Timer2
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer2_Prepare(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*Alternative function clock setup  for GPIO */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
	/*Clock setup for timer2 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	/*Pin remap for timer2*/
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,ENABLE);

	/*PA5 setup for timer2*/
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
  	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	/*PB10/11/3 setup for timer2*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_InitStructure.GPIO_Pin =   GPIO_Pin_10| GPIO_Pin_11 |GPIO_Pin_3;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);
}
/* End Timer2_Prepare */	

/*******************************************************************************
* Function Name  : Timer2_SetTimeBaseFreq
* Description    : Initialize Timer2
* Input          : freq
* Output         : None
* Return         : None
*******************************************************************************/
void Timer2_SetTimeBaseCount(uint32_t count)
{
//	static unsigned int value;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

//	if(value==2400000/freq)
//		return;
//	else value=2400000/freq;
	/*Timer Base Initialization for timer2 */
	TIM_TimeBaseInitStructure.TIM_Prescaler=30-1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseInitStructure.TIM_Period = count-1;
	TIM_TimeBaseInitStructure.TIM_ClockDivision	= 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);

	/*Auto-reload always */
	TIM_ARRPreloadConfig(TIM2, DISABLE);
} 
/* End Timer2_SetTimeBaseCount */
void Timer2_SetOutputPulseWidth(uint32_t width,PWM_CHANNEL CHn)
{
	TIM_OCInitTypeDef TIM_OCInitStructure;
	/*Channels initialization for timer1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState	 = TIM_OutputState_Enable ;
	TIM_OCInitStructure.TIM_Pulse = width-1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	switch( CHn)
	{
		case CH1:
		TIM_OC1Init(TIM2, &TIM_OCInitStructure); //PA5
		break;

		case CH2:
		TIM_OC2Init(TIM2, &TIM_OCInitStructure);  //PB10
		break;

		case CH3:
		TIM_OC3Init(TIM2, &TIM_OCInitStructure); //PB11
		break;

		case CH4:
		TIM_OC4Init(TIM2, &TIM_OCInitStructure);  //PB3
		break;

		default:
		break;
	}
}
void Timer2_StartStop(bool start)
{
	if(start==TRUE)
	{
//		TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Disable);
		TIM_Cmd(TIM2, ENABLE);
	}
	else
	{
//		TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Disable);
		TIM_Cmd(TIM2, DISABLE);
	}
}
/*End Timer2_SetOutputPulseWidth*/

/*******************************************************************************
* Function Name  : Timer3_MotorPrepare
* Description    : Initialize Timer3
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer3_Prepare(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*Alternative function clock setup  for GPIO */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB, ENABLE);
	/*Clock setup for timer3 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	/*PA6,7,PB0,1 setup for timer3*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 |GPIO_Pin_7 ;//|GPIO_Pin_8 |GPIO_Pin_9;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* PB0,1 setup for GPIO */
  	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
  	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 |GPIO_Pin_1 ;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}
/* End Timer3_Prepare */															

/*******************************************************************************
* Function Name  : Timer3_SetTimeBaseCount
* Description    : Initialize Timer3
* Input          : freq
* Output         : None
* Return         : None
*******************************************************************************/
void Timer3_SetTimeBaseCount(uint32_t count)
{
//	static unsigned int value;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//	if(value==2400000/freq)
//		return;
//	else value=2400000/freq;
	/*Timer Base Initialization for timer3 */
	TIM_TimeBaseInitStructure.TIM_Prescaler=30-1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseInitStructure.TIM_Period = count-1;
	TIM_TimeBaseInitStructure.TIM_ClockDivision	= 0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);

	/*Auto-reload always */
	TIM_ARRPreloadConfig(TIM3, DISABLE);
}
/* End Timer3_SetTimeBaseCount */
void Timer3_SetOutputPulseWidth(uint32_t width,PWM_CHANNEL CHn)
{
	TIM_OCInitTypeDef TIM_OCInitStructure;
	/*Channels initialization for timer3 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState	 = TIM_OutputState_Enable ;
	TIM_OCInitStructure.TIM_Pulse = width-1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);

	switch( CHn)
	{
		case CH1:
		TIM_OC1Init(TIM3, &TIM_OCInitStructure); //PA5
		break;

		case CH2:
		TIM_OC2Init(TIM3, &TIM_OCInitStructure);  //PB10
		break;

		case CH3:
		TIM_OC3Init(TIM3, &TIM_OCInitStructure); //PB11
		break;

		case CH4:
		TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //PB3
		break;

		default:
		break;
	}
}
void Timer3_StartStop(bool start)
{
//	/*CCRs auto-reload always */
//	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Disable);
	if(start==TRUE)
	{
		TIM_Cmd(TIM3, ENABLE);
	}
	else
	{
		TIM_Cmd(TIM3, DISABLE);
	}	
}
/*End Timer3_StartStop */

/*******************************************************************************
* Function Name  : Timer4_Prepare
* Description    : Initialize Timer4
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer4_Prepare(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOB, ENABLE);
	/*Clock setup for timer4 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	/*PB6,7,8,9 setup for timer4*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 |GPIO_Pin_7 |GPIO_Pin_8 |GPIO_Pin_9 ;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);

//	/* PA7,8,9 setup for GPIO */
//  	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_OD;
//  	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7 |GPIO_Pin_8 |GPIO_Pin_9;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_Init(GPIOB,&GPIO_InitStructure);
}
/* End Timer4_Prepare */


/*******************************************************************************
* Function Name  : Timer4_SetTimeBaseCount
* Description    : Initialize Timer4
* Input          : freq
* Output         : None
* Return         : None
*******************************************************************************/
void Timer4_SetTimeBaseCount(uint32_t count)
{
//	static unsigned int value;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;

	/*Timer Base Initialization for timer4 */
	TIM_TimeBaseInitStructure.TIM_Prescaler=30-1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseInitStructure.TIM_Period = count-1;
	TIM_TimeBaseInitStructure.TIM_ClockDivision	= 0;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	/*Auto-reload always */
	TIM_ARRPreloadConfig(TIM4, DISABLE);
}

void Timer4_SetOutputPulseWidth(uint32_t width,PWM_CHANNEL CHn)
{
	TIM_OCInitTypeDef TIM_OCInitStructure;
	/*Channels initialization for timer4 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState	 = TIM_OutputState_Enable ;
	TIM_OCInitStructure.TIM_Pulse = width-1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	switch( CHn)
	{
		case CH1:
		TIM_OC1Init(TIM4, &TIM_OCInitStructure);
		break;
		 
		case CH2:
		TIM_OC2Init(TIM4, &TIM_OCInitStructure);
		break;

		case CH3:
		TIM_OC3Init(TIM4, &TIM_OCInitStructure);
		break;

		case CH4:
		TIM_OC4Init(TIM4, &TIM_OCInitStructure);
		break;
		
		default:
		break;
	}
}

void Timer4_StartStop(bool start)
{
//	/*CCRs auto-reload always */
//	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
   	if(start==TRUE)
	{
		/*Start counter for timer4 */
		TIM_Cmd(TIM4, ENABLE);
	}
	else
	{
		TIM_Cmd(TIM4, ENABLE);
	}
}
/*End Timer4_Init()*/



///*******************************************************************************
//* Function Name  : Timer5_MotorSetFreq
//* Description    : Initialize Timer5
//* Input          : freq
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void Timer5_SmallMotorLeftSetFreq(unsigned int freq)
//{
//	static unsigned int value;
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//	TIM_OCInitTypeDef TIM_OCInitStructure;
//
//	if(value==2400000/freq)
//		return;
//	else value=2400000/freq;
//	/*Timer Base Initialization for timer5 */
//	TIM_TimeBaseInitStructure.TIM_Prescaler=15-1;
//	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up ;
//	TIM_TimeBaseInitStructure.TIM_Period = value-1;
//	TIM_TimeBaseInitStructure.TIM_ClockDivision	= 0;
//	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);
//	/*Auto-reload always */
//	TIM_ARRPreloadConfig(TIM4, DISABLE);
//	/*Channels initialization for timer5 */
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
//	TIM_OCInitStructure.TIM_OutputState	 = TIM_OutputState_Enable ;
//	TIM_OCInitStructure.TIM_Pulse = value/2-1;
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
//	TIM_OC4Init(TIM5, &TIM_OCInitStructure);
//
//	/*CCRs auto-reload always */
//	TIM_OC4PreloadConfig(TIM5,TIM_OCPreload_Enable);
//
//	/*Start counter for timer5 */
//	TIM_Cmd(TIM5, ENABLE);
//}
///*End Timer5_MotorSetFreq()*/
//
///*******************************************************************************
//* Function Name  : Timer5_MotorPrepare
//* Description    : Initialize Timer5
//* Input          : None
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void Timer5_SmallMotorLeftPrepare(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//
//	/*Clock setup for timer5 */
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
//	/*PB6,7,8,9 setup for timer5*/
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3 ;//|GPIO_Pin_7 |GPIO_Pin_8 |GPIO_Pin_9;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIOA, &GPIO_InitStructure);
//
//	/* PA7,8,9 setup for GPIO */
//  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
//  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 |GPIO_Pin_1 |GPIO_Pin_2;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA,&GPIO_InitStructure);
//}
///* End Timer5_MotorPrepare */
//
///*******************************************************************************
//* Function Name  : Timer8_MotorSetFreq
//* Description    : Initialize Timer8
//* Input          : freq
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void Timer8_SmallMotorRightSetFreq(unsigned int freq)
//{
//	static unsigned int value;
//	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
//	TIM_OCInitTypeDef TIM_OCInitStructure;
//
//	if(value==2400000/freq)
//		return;
//	else value=2400000/freq;
//	/*Timer Base Initialization for timer8 */
//	TIM_TimeBaseInitStructure.TIM_Prescaler=15-1;
//	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up ;
//	TIM_TimeBaseInitStructure.TIM_Period = value-1;
//	TIM_TimeBaseInitStructure.TIM_ClockDivision	= 0;
//	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseInitStructure);
//	/*Auto-reload always */
//	TIM_ARRPreloadConfig(TIM8, DISABLE);
//	/*Channels initialization for timer8 */
//	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
//	TIM_OCInitStructure.TIM_OutputState	 = TIM_OutputState_Enable ;
//	TIM_OCInitStructure.TIM_Pulse = value/2-1;
//	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
//	TIM_OC1Init(TIM8, &TIM_OCInitStructure);
//
//	/*CCRs auto-reload always */
//	TIM_OC1PreloadConfig(TIM8,TIM_OCPreload_Enable);
//
//	/*Start counter for timer8 */
//	TIM_Cmd(TIM8, ENABLE);
//
//	TIM_CtrlPWMOutputs(TIM8, ENABLE);
//}
///*End Timer8_MotorSetFreq()*/
//
///*******************************************************************************
//* Function Name  : Timer8_MotorPrepare
//* Description    : Initialize Timer8
//* Input          : None
//* Output         : None
//* Return         : None
//*******************************************************************************/
//void Timer8_SmallMotorRightPrepare(void)
//{
//	GPIO_InitTypeDef GPIO_InitStructure;
//
//	/*Clock setup for timer8 */
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);
//
//	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,ENABLE);
//	/*PC6,7,8,9 setup for timer8*/
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
//  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 ;//|GPIO_Pin_7 |GPIO_Pin_8 |GPIO_Pin_9;
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//  GPIO_Init(GPIOC, &GPIO_InitStructure);
//
//	/* PC7,8,9 setup for GPIO */
//  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
//  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7 |GPIO_Pin_8 |GPIO_Pin_9;
//	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
//	GPIO_Init(GPIOC,&GPIO_InitStructure);
//}
///* End Timer8_MotorPrepare */
//
//
//
