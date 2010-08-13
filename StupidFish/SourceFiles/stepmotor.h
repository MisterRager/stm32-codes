#include "stm32f10x_type.h"
#include "stm32f10x_lib.h"


#ifndef __STEPMOTOR_H
#define __STEPMOTOR_H

#define	Timer1_MotorUp() 					GPIO_ResetBits(GPIOA,GPIO_Pin_11)
#define	Timer1_MotorDown() 				GPIO_SetBits(GPIOA,GPIO_Pin_11)
#define	Timer1_MotorEnable() 			GPIO_ResetBits(GPIOA,GPIO_Pin_13)
#define	Timer1_MotorDisable()  		GPIO_SetBits(GPIOA,GPIO_Pin_13)
void Timer1_MotorSetFreq(unsigned int freq);
void Timer1_MotorPrepare(void);
#define Timer1_MotorInit()					Timer1_MotorPrepare(); Timer1_MotorSetFreq(50)

#define	Timer2_BigMotorLeftUp() 					GPIO_ResetBits(GPIOB,GPIO_Pin_10)
#define	Timer2_BigMotorLeftDown() 				GPIO_SetBits(GPIOB,GPIO_Pin_10)
#define	Timer2_BigMotorLeftEnable() 			GPIO_ResetBits(GPIOA,GPIO_Pin_5)
#define	Timer2_BigMotorleftDisable()  		GPIO_SetBits(GPIOA,GPIO_Pin_5)
#define Timer2_BigMotorLeftStop() 				TIM_Cmd(TIM2, DISABLE);
#define Timer2_BigMotorLeftStart() 				TIM_Cmd(TIM2, ENABLE);
void Timer2_BigMotorLeftSetFreq(unsigned int freq);
void Timer2_BigMotorLeftPrepare(void);
#define Timer2_BigMotorLeftInit()					Timer2_BigMotorLeftPrepare(); Timer2_BigMotorLeftSetFreq(50)

#define	Timer3_BigMotorRightUp() 					GPIO_ResetBits(GPIOA,GPIO_Pin_7)
#define	Timer3_BigMotorRightDown() 				GPIO_SetBits(GPIOA,GPIO_Pin_7)
#define	Timer3_BigMotorRightEnable() 			GPIO_ResetBits(GPIOB,GPIO_Pin_0)
#define	Timer3_BigMotorRightDisable() 		GPIO_SetBits(GPIOB,GPIO_Pin_0)
#define Timer3_BigMotorRightStop() 				TIM_Cmd(TIM3, DISABLE);
#define Timer3_BigMotorRightStart() 				TIM_Cmd(TIM3,ENABLE);
void Timer3_BigMotorRightSetFreq(unsigned int freq);
void Timer3_BigMotorRightPrepare(void);
#define Timer3_BigMotorRightInit()				Timer3_BigMotorRightPrepare(); Timer3_BigMotorRightSetFreq(50)

#define	Timer4_SmallMotorLeftUp() 				GPIO_ResetBits(GPIOB,GPIO_Pin_7)
#define	Timer4_SmallMotorleftDown() 			GPIO_SetBits(GPIOB,GPIO_Pin_7)
#define	Timer4_SmallMotorLeftEnable() 		GPIO_ResetBits(GPIOB,GPIO_Pin_8)
#define	Timer4_SmallMotorLeftDisable() 		GPIO_SetBits(GPIOB,GPIO_Pin_8)
#define Timer4_SmallMotorLeftStop() 				TIM_Cmd(TIM4, DISABLE);
#define Timer4_SmallMotorLeftStart() 				TIM_Cmd(TIM4, ENABLE);
void Timer4_SmallMotorLeftSetFreq(unsigned int freq);
void Timer4_SmallMotorLeftPrepare(void);
#define Timer4_SmallMotorLeftInit()				Timer4_SmallMotorLeftPrepare(); Timer4_SmallMotorLeftSetFreq(50)

#define	Timer5_SmallMotorRightUp() 				GPIO_ResetBits(GPIOA,GPIO_Pin_2)
#define	Timer5_SmallMotorRightDown() 			GPIO_SetBits(GPIOA,GPIO_Pin_2)
#define	Timer5_SmallMotorRightEnable() 		GPIO_ResetBits(GPIOA,GPIO_Pin_1)
#define	Timer5_SmallMotorRightDisable()  	GPIO_SetBits(GPIOA,GPIO_Pin_1)
#define Timer5_SmallMotorRightStop() 				TIM_Cmd(TIM5, DISABLE);
#define Timer5_SmallMotorRightStart() 				TIM_Cmd(TIM5, ENABLE);
void Timer5_SmallMotorRightSetFreq(unsigned int freq);
void Timer5_SmallMotorRightPrepare(void);
#define Timer5_SmallMotorRightInit()			Timer5_SmallMotorRightPrepare(); Timer5_SmallMotorRightSetFreq(50)

#define	Timer8_MotorUp() 									GPIO_ResetBits(GPIOC,GPIO_Pin_7)
#define	Timer8_MotorDown() 								GPIO_SetBits(GPIOC,GPIO_Pin_7)
#define	Timer8_MotorEnable() 							GPIO_ResetBits(GPIOC,GPIO_Pin_8)
#define	Timer8_MotorDisable() 						GPIO_SetBits(GPIOC,GPIO_Pin_8)
void Timer8_MotorSetFreq(unsigned int freq);
void Timer8_MotorPrepare(void);
#define Timer8_MotorInit()								Timer8_MotorPrepare(); Timer8_MotorSetFreq(50)

#endif 



