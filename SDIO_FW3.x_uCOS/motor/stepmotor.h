#include "stm32f10x.h"


#ifndef __STEPMOTOR_H
#define __STEPMOTOR_H

typedef enum PWM_CHANNEL { CH1,CH2,CH3,CH4 } PWM_CHANNEL;
	 
void Timer1_Prepare(void);
void Timer1_SetTimeBaseCount(uint32_t freq);
void Timer1_SetOutputPulseWidth( uint32_t width,PWM_CHANNEL CHn);
void Timer1_StartStop(bool start);

void Timer2_Prepare(void);
void Timer2_SetTimeBaseCount(uint32_t count);
void Timer2_SetOutputPulseWidth( uint32_t width,PWM_CHANNEL CHn);
void Timer2_StartStop(bool start);

void Timer3_Prepare(void);
void Timer3_SetTimeBaseCount(uint32_t count);
void Timer3_SetOutputPulseWidth( uint32_t width,PWM_CHANNEL CHn);
void Timer3_StartStop(bool start);

void Timer4_Prepare(void);
void Timer4_SetTimeBaseCount(uint32_t count);
void Timer4_SetOutputPulseWidth( uint32_t width,PWM_CHANNEL CHn);
void Timer4_StartStop(bool start);
//#define	Timer1_MotorUp() 					GPIO_ResetBits(GPIOA,GPIO_Pin_11)
//#define	Timer1_MotorDown() 				GPIO_SetBits(GPIOA,GPIO_Pin_11)
//#define	Timer1_MotorEnable() 			GPIO_ResetBits(GPIOA,GPIO_Pin_13)
//#define	Timer1_MotorDisable()  		GPIO_SetBits(GPIOA,GPIO_Pin_13)
//void Timer1_MotorSetFreq(unsigned int freq);
//void Timer1_MotorPrepare(void);
//#define Timer1_MotorInit()					Timer1_MotorPrepare(); Timer1_MotorSetFreq(50)

//#define	Timer2_BigMotorLeftUp() 					GPIO_ResetBits(GPIOB,GPIO_Pin_10)
//#define	Timer2_BigMotorLeftDown() 				GPIO_SetBits(GPIOB,GPIO_Pin_10)
//#define	Timer2_BigMotorLeftEnable() 			GPIO_ResetBits(GPIOA,GPIO_Pin_5)
//#define	Timer2_BigMotorleftDisable()  		GPIO_SetBits(GPIOA,GPIO_Pin_5)
//#define Timer2_BigMotorLeftStop() 				TIM_Cmd(TIM2, DISABLE);
//#define Timer2_BigMotorLeftStart() 				TIM_Cmd(TIM2, ENABLE);
//void Timer2_BigMotorLeftSetFreq(unsigned int freq);
//void Timer2_BigMotorLeftPrepare(void);
//#define Timer2_BigMotorLeftInit()					Timer2_BigMotorLeftPrepare(); Timer2_BigMotorLeftSetFreq(50)
//
//#define	Timer3_BigMotorLeftUp() 					GPIO_ResetBits(GPIOA,GPIO_Pin_7)
//#define	Timer3_BigMotorLeftDown() 				GPIO_SetBits(GPIOA,GPIO_Pin_7)
//#define	Timer3_BigMotorLeftEnable() 			GPIO_ResetBits(GPIOB,GPIO_Pin_0)
//#define	Timer3_BigMotorLeftDisable() 		GPIO_SetBits(GPIOB,GPIO_Pin_0)
//#define Timer3_BigMotorLeftStop() 				TIM_Cmd(TIM3, DISABLE);
//#define Timer3_BigMotorLeftStart() 				TIM_Cmd(TIM3,ENABLE);
//void Timer3_BigMotorLeftSetFreq(unsigned int freq);
//void Timer3_BigMotorLeftPrepare(void);
//#define Timer3_BigMotorLeftInit()				Timer3_BigMotorLeftPrepare(); Timer3_BigMotorLeftSetFreq(50)
//
//#define	Timer4_BigMotorRightUp() 				GPIO_ResetBits(GPIOB,GPIO_Pin_7)
//#define	Timer4_BigMotorRightDown() 			GPIO_SetBits(GPIOB,GPIO_Pin_7)
//#define	Timer4_BigMotorRightEnable() 		GPIO_ResetBits(GPIOB,GPIO_Pin_8)
//#define	Timer4_BigMotorRightDisable() 		GPIO_SetBits(GPIOB,GPIO_Pin_8)
//#define Timer4_BigMotorRightStop() 				TIM_Cmd(TIM4, DISABLE);
//#define Timer4_BigMotorRightStart() 				TIM_Cmd(TIM4, ENABLE);
//void Timer4_BigMotorRightSetFreq(unsigned int freq);
//void Timer4_BigMotorRightPrepare(void);
//#define Timer4_BigMotorRightInit()				Timer4_BigMotorRightPrepare(); Timer4_BigMotorRightSetFreq(50)
//
//#define	Timer5_SmallMotorLeftUp() 				GPIO_ResetBits(GPIOA,GPIO_Pin_2)
//#define	Timer5_SmallMotorLeftDown() 			GPIO_SetBits(GPIOA,GPIO_Pin_2)
//#define	Timer5_SmallMotorLeftEnable() 		GPIO_ResetBits(GPIOA,GPIO_Pin_1)
//#define	Timer5_SmallMotorLeftDisable()  	GPIO_SetBits(GPIOA,GPIO_Pin_1)
//#define Timer5_SmallMotorLeftStop() 				TIM_Cmd(TIM5, DISABLE);
//#define Timer5_SmallMotorLeftStart() 				TIM_Cmd(TIM5, ENABLE);
//void Timer5_SmallMotorLeftSetFreq(unsigned int freq);
//void Timer5_SmallMotorLeftPrepare(void);
//#define Timer5_SmallMotorLeftInit()			Timer5_SmallMotorLeftPrepare(); Timer5_SmallMotorLeftSetFreq(50)
//
//#define	Timer8_SmallMotorRightUp() 									GPIO_ResetBits(GPIOC,GPIO_Pin_7)
//#define	Timer8_SmallMotorRightDown() 								GPIO_SetBits(GPIOC,GPIO_Pin_7)
//#define	Timer8_SmallMotorRightEnable() 							GPIO_ResetBits(GPIOC,GPIO_Pin_8)
//#define	Timer8_SmallMotorRightDisable() 						GPIO_SetBits(GPIOC,GPIO_Pin_8)
//void Timer8_SmallMotorRightSetFreq(unsigned int freq);
//void Timer8_SmallMotorRightPrepare(void);
//#define Timer8_SmallMotorRightStart() 				TIM_Cmd(TIM8, ENABLE);
//#define Timer8_SmallMotorRightInit()		Timer8_SmallMotorRightPrepare(); Timer8_SmallMotorRightSetFreq(50)

#endif 



