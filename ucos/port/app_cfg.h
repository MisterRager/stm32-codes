/*
***************************************************************************************
*                                                                              
*                       �����Ƽ����޹�˾
*
*               (c) Copyright 2006-2008, hui lian. luo, china, zj
*                            All Rights Reserved
*
*                           http://www.bogodtech.com                         
*
*--------------�ļ���Ϣ-----------------------------------------------------------------
* �� �� ��: os_thread.c
* �� �� ��: �޻��� 	
* ��������: 2007��11��10��
* ��    ��: ͷ�ļ��ܻ�
* ��������: ¥����(������)  �㽭��ѧ�ŵ�ϵ
*
*---------- �汾��Ϣ-------------------------------------------------------------------
* ��    ��: V1.0
*
*--------------------------------------------------------------------------------------
****************************************************************************************
*/

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CONFIG_H
#define __CONFIG_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_lib.h"	

#include "ucos_ii.h"

//#include "create_task.h"
//#include "core_task.h"
//#include "windows.h"

//#include "uart.h"
//#include "cntl.h"
//#include "spi_led.h"
//#include "keyboard.h"


/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
#define LED1_RAY    (GPIO_WriteBit(GPIOC, GPIO_Pin_6, (BitAction)(1-GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_6))))
#define LED2_RAY    (GPIO_WriteBit(GPIOC, GPIO_Pin_7, (BitAction)(1-GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_7))))
#define LED3_RAY    (GPIO_WriteBit(GPIOC, GPIO_Pin_8, (BitAction)(1-GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_8))))
#define LED4_RAY    (GPIO_WriteBit(GPIOC, GPIO_Pin_9, (BitAction)(1-GPIO_ReadOutputDataBit(GPIOC, GPIO_Pin_9))))

#define OS_TASK_TMR_PRIO		 0


#endif /* __MAIN_H */

/*********************** http://www.bogodtech.com *******End of file **********************/
