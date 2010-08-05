#include "stm32f10x_type.h"
#include "stm32f10x_lib.h"

#ifndef __STEPMOTOR_H
#define __STEPMOTOR_H

#define	Timer1_MotorUp() 				GPIO_ResetBits(GPIOA,GPIO_Pin_11)
#define	Timer1_MotorDown() 			GPIO_SetBits(GPIOA,GPIO_Pin_11)
#define	Timer1_MotorEnable() 		GPIO_ResetBits(GPIOA,GPIO_Pin_13)
#define	Timer1_MotorDisable()  	GPIO_SetBits(GPIOA,GPIO_Pin_13)
void Timer1_MotorSetFreq(unsigned int freq);
void Timer1_MotorPrepare(void);
#define Timer1_MotorInit()			Timer1_MotorPrepare(); Timer1_MotorSetFreq(50)

#define	Timer2_MotorUp() 				GPIO_ResetBits(GPIOB,GPIO_Pin_10)
#define	Timer2_MotorDown() 			GPIO_SetBits(GPIOB,GPIO_Pin_10)
#define	Timer2_MotorEnable() 		GPIO_ResetBits(GPIOA,GPIO_Pin_5)
#define	Timer2_MotorDisable()  	GPIO_SetBits(GPIOA,GPIO_Pin_5)
void Timer2_MotorSetFreq(unsigned int freq);
void Timer2_MotorPrepare(void);
#define Timer2_MotorInit()			Timer2_MotorPrepare(); Timer2_MotorSetFreq(50)

#define	Timer3_MotorUp() 			GPIO_ResetBits(GPIOA,GPIO_Pin_7)
#define	Timer3_MotorDown() 		GPIO_SetBits(GPIOA,GPIO_Pin_7)
#define	Timer3_MotorEnable() 	GPIO_ResetBits(GPIOB,GPIO_Pin_0)
#define	Timer3_MotorDisable() GPIO_SetBits(GPIOB,GPIO_Pin_0)
void Timer3_MotorSetFreq(unsigned int freq);
void Timer3_MotorPrepare(void);
#define Timer3_MotorInit()			Timer3_MotorPrepare(); Timer3_MotorSetFreq(50)

#define	Timer4_MotorUp() 			GPIO_ResetBits(GPIOB,GPIO_Pin_7)
#define	Timer4_MotorDown() 		GPIO_SetBits(GPIOB,GPIO_Pin_7)
#define	Timer4_MotorEnable() 		GPIO_ResetBits(GPIOB,GPIO_Pin_8)
#define	Timer4_MotorDisable() 	GPIO_SetBits(GPIOB,GPIO_Pin_8)
void Timer4_MotorSetFreq(unsigned int freq);
void Timer4_MotorPrepare(void);
#define Timer4_MotorInit()			Timer4_MotorPrepare(); Timer4_MotorSetFreq(50)

#define	Timer5_MotorUp() 			GPIO_ResetBits(GPIOA,GPIO_Pin_2)
#define	Timer5_MotorDown() 		GPIO_SetBits(GPIOA,GPIO_Pin_2)
#define	Timer5_MotorEnable() 	GPIO_ResetBits(GPIOA,GPIO_Pin_1)
#define	Timer5_MotorDisable()  GPIO_SetBits(GPIOA,GPIO_Pin_1)
void Timer5_MotorSetFreq(unsigned int freq);
void Timer5_MotorPrepare(void);
#define Timer5_MotorInit()			Timer5_MotorPrepare(); Timer5_MotorSetFreq(50)

#define	Timer8_MotorUp() 			GPIO_ResetBits(GPIOC,GPIO_Pin_7)
#define	Timer8_MotorDown() 		GPIO_SetBits(GPIOC,GPIO_Pin_7)
#define	Timer8_MotorEnable() 	GPIO_ResetBits(GPIOC,GPIO_Pin_8)
#define	Timer8_MotorDisable() GPIO_SetBits(GPIOC,GPIO_Pin_8)
void Timer8_MotorSetFreq(unsigned int freq);
void Timer8_MotorPrepare(void);
#define Timer8_MotorInit()			Timer8_MotorPrepare(); Timer8_MotorSetFreq(50)

#endif 



