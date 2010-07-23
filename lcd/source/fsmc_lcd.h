#ifndef __FSMC_LCD_H
#define __FSMC_LCD_H

#include "stdint.h"
void FSMC_LCD_Init(void);
void LCD_GPIO_Configuration(void);
void LCD_Reset(void);
void Delay(volatile uint32_t nCount);

#endif 

