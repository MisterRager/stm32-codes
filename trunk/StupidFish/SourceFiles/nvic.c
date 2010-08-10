#include "stm32f10x_type.h"
#include "stm32f10x_lib.h"

/******************************************************************************

*        EXTI_Configuration

******************************************************************************/

void EXTI_Configuration(void)
{
	EXTI_InitTypeDef 	EXTI_InitStructure;
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource4);

	EXTI_InitStructure.EXTI_Line = EXTI_Line4;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
}

