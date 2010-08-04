#include "stepmotor.h"

/*******************************************************************************
* Function Name  : Timer1_MotorSetFreq
* Description    : Initialize Timer1
* Input          : freq
* Output         : None
* Return         : None
*******************************************************************************/
void Timer1_MotorSetFreq(unsigned int freq)
{
	unsigned int value=2400000/freq;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	/*Timer Base Initialization for timer1 */
	TIM_TimeBaseInitStructure.TIM_Prescaler=15-1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseInitStructure.TIM_Period = value-1;
	TIM_TimeBaseInitStructure.TIM_ClockDivision	= 0;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseInitStructure);

	/*Auto-reload always */
	TIM_ARRPreloadConfig(TIM1, DISABLE);

	/*Channels initialization for timer1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState	 = TIM_OutputState_Enable ;
	TIM_OCInitStructure.TIM_Pulse = value/2-1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	/* Using Channel 1 ->PE9 */
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);

	/*CCRs auto-reload always */
	TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Disable);

	/*Start counter for timer1 */
	TIM_Cmd(TIM1, ENABLE);
}
/*End Timer1_MotorSetFreq()*/

/*******************************************************************************
* Function Name  : Timer1_MotorPrepare
* Description    : Initialize Timer1
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer1_MotorPrepare(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*Alternative function clock setup  for GPIO */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	/*Pin remap for timer1*/
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,ENABLE);

	/*PB11 setup for timer1*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_9 ;//|GPIO_Pin_1 |GPIO_Pin_2 |GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

	/* PE11,13,14 setup for GPIO */
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11 |GPIO_Pin_13 |GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStructure);
}
/* End Timer1_MotorPrepare */

/*******************************************************************************
* Function Name  : Timer2_MotorSetFreq
* Description    : Initialize Timer2
* Input          : freq
* Output         : None
* Return         : None
*******************************************************************************/
void Timer2_MotorSetFreq(unsigned int freq)
{
	unsigned int value=2400000/freq;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	/*Timer Base Initialization for timer2 */
	TIM_TimeBaseInitStructure.TIM_Prescaler=15-1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseInitStructure.TIM_Period = value-1;
	TIM_TimeBaseInitStructure.TIM_ClockDivision	= 0;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseInitStructure);

	/*Auto-reload always */
	TIM_ARRPreloadConfig(TIM2, DISABLE);

	/*Channels initialization for timer1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState	 = TIM_OutputState_Enable ;
	TIM_OCInitStructure.TIM_Pulse = value/2-1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	/* Using Channe4 1 ->PB11 */
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);

	/*CCRs auto-reload always */
	TIM_OC4PreloadConfig(TIM2,TIM_OCPreload_Disable);

	/*Start counter for timer2 */
	TIM_Cmd(TIM2, ENABLE);
}
/*End Timer2_MotorSetFreq()*/

/*******************************************************************************
* Function Name  : Timer2_MotorPrepare
* Description    : Initialize Timer2
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer2_MotorPrepare(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*Alternative function clock setup  for GPIO */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);

	/*Clock setup for timer2 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	/*Pin remap for timer2*/
	GPIO_PinRemapConfig(GPIO_FullRemap_TIM2,ENABLE);

	/*PB11 setup for timer2*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11 ;//|GPIO_Pin_1 |GPIO_Pin_2 |GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* PB10,PA5 setup for GPIO */
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
/* End Timer2_MotorPrepare */																

/*******************************************************************************
* Function Name  : Timer3_MotorSetFreq
* Description    : Initialize Timer3
* Input          : freq
* Output         : None
* Return         : None
*******************************************************************************/
void Timer3_MotorSetFreq(unsigned int freq)
{
	unsigned int value=2400000/freq;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;


	/*Timer Base Initialization for timer3 */
	TIM_TimeBaseInitStructure.TIM_Prescaler=15-1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseInitStructure.TIM_Period = value-1;
	TIM_TimeBaseInitStructure.TIM_ClockDivision	= 0;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseInitStructure);

	/*Auto-reload always */
	TIM_ARRPreloadConfig(TIM3, DISABLE);

	/*Channels initialization for timer3 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState	 = TIM_OutputState_Enable ;
	TIM_OCInitStructure.TIM_Pulse = value/2-1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);

	/*CCRs auto-reload always */
	TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Disable);

	/*Start counter for timer3 */
	TIM_Cmd(TIM3, ENABLE);

	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}
/*End Timer3_MotorSetFreq()*/

/*******************************************************************************
* Function Name  : Timer3_MotorPrepare
* Description    : Initialize Timer3
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer3_MotorPrepare(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*Alternative function clock setup  for GPIO */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	/*Clock setup for timer3 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

	/*PA6,7,PB0,1 setup for timer3*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6;// |GPIO_Pin_7 |GPIO_Pin_8 |GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* PA7 setup for GPIO */
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7 ;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	/* PB0,1 setup for GPIO */
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1 ;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}
/* End Timer3_MotorPrepare */

/*******************************************************************************
* Function Name  : Timer4_MotorSetFreq
* Description    : Initialize Timer4
* Input          : freq
* Output         : None
* Return         : None
*******************************************************************************/
void Timer4_MotorSetFreq(unsigned int freq)
{
	unsigned int value=2400000/freq;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;


	/*Timer Base Initialization for timer4 */
	TIM_TimeBaseInitStructure.TIM_Prescaler=15-1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseInitStructure.TIM_Period = value-1;
	TIM_TimeBaseInitStructure.TIM_ClockDivision	= 0;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseInitStructure);
	/*Auto-reload always */
	TIM_ARRPreloadConfig(TIM4, DISABLE);
	/*Channels initialization for timer4 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState	 = TIM_OutputState_Enable ;
	TIM_OCInitStructure.TIM_Pulse = value/2-1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);

	/*CCRs auto-reload always */
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);

	/*Start counter for timer4 */
	TIM_Cmd(TIM4, ENABLE);
}
/*End Timer4_Init()*/

/*******************************************************************************
* Function Name  : Timer4_MotorPrepare
* Description    : Initialize Timer4
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer4_MotorPrepare(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*Clock setup for timer4 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	/*PB6,7,8,9 setup for timer4*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 ;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* PA7,8,9 setup for GPIO */
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7 |GPIO_Pin_8 |GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
}
/* End Timer4_MotorPrepare */

/*******************************************************************************
* Function Name  : Timer5_MotorSetFreq
* Description    : Initialize Timer5
* Input          : freq
* Output         : None
* Return         : None
*******************************************************************************/
void Timer5_MotorSetFreq(unsigned int freq)
{
	unsigned int value=2400000/freq;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;


	/*Timer Base Initialization for timer5 */
	TIM_TimeBaseInitStructure.TIM_Prescaler=15-1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseInitStructure.TIM_Period = value-1;
	TIM_TimeBaseInitStructure.TIM_ClockDivision	= 0;
	TIM_TimeBaseInit(TIM5,&TIM_TimeBaseInitStructure);
	/*Auto-reload always */
	TIM_ARRPreloadConfig(TIM4, DISABLE);
	/*Channels initialization for timer5 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState	 = TIM_OutputState_Enable ;
	TIM_OCInitStructure.TIM_Pulse = value/2-1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC4Init(TIM5, &TIM_OCInitStructure);

	/*CCRs auto-reload always */
	TIM_OC4PreloadConfig(TIM5,TIM_OCPreload_Enable);

	/*Start counter for timer5 */
	TIM_Cmd(TIM5, ENABLE);
}
/*End Timer5_MotorSetFreq()*/

/*******************************************************************************
* Function Name  : Timer5_MotorPrepare
* Description    : Initialize Timer5
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer5_MotorPrepare(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*Clock setup for timer5 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);
	/*PB6,7,8,9 setup for timer5*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_3 ;//|GPIO_Pin_7 |GPIO_Pin_8 |GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* PA7,8,9 setup for GPIO */
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 |GPIO_Pin_1 |GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
}
/* End Timer5_MotorPrepare */

/*******************************************************************************
* Function Name  : Timer8_MotorSetFreq
* Description    : Initialize Timer8
* Input          : freq
* Output         : None
* Return         : None
*******************************************************************************/
void Timer8_MotorSetFreq(unsigned int freq)
{
	unsigned int value=2400000/freq;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;


	/*Timer Base Initialization for timer8 */
	TIM_TimeBaseInitStructure.TIM_Prescaler=15-1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseInitStructure.TIM_Period = value-1;
	TIM_TimeBaseInitStructure.TIM_ClockDivision	= 0;
	TIM_TimeBaseInit(TIM8,&TIM_TimeBaseInitStructure);
	/*Auto-reload always */
	TIM_ARRPreloadConfig(TIM8, DISABLE);
	/*Channels initialization for timer8 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState	 = TIM_OutputState_Enable ;
	TIM_OCInitStructure.TIM_Pulse = value/2-1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM8, &TIM_OCInitStructure);

	/*CCRs auto-reload always */
	TIM_OC1PreloadConfig(TIM8,TIM_OCPreload_Enable);

	/*Start counter for timer8 */
	TIM_Cmd(TIM8, ENABLE);

	TIM_CtrlPWMOutputs(TIM8, ENABLE);
}
/*End Timer8_MotorSetFreq()*/

/*******************************************************************************
* Function Name  : Timer8_MotorPrepare
* Description    : Initialize Timer8
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void Timer8_MotorPrepare(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/*Clock setup for timer8 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, ENABLE);

	GPIO_PinRemapConfig(GPIO_FullRemap_TIM1,ENABLE);
	/*PC6,7,8,9 setup for timer8*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 ;//|GPIO_Pin_7 |GPIO_Pin_8 |GPIO_Pin_9;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* PC7,8,9 setup for GPIO */
  GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
  GPIO_InitStructure.GPIO_Pin=GPIO_Pin_7 |GPIO_Pin_8 |GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC,&GPIO_InitStructure);
}
/* End Timer8_MotorPrepare */



