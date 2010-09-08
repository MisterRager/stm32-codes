#ifndef __LCD_H
#define __LCD_H

#include "stm32f10x_lib.h"
#include "stdint.h"
#define Bank1_LCD_D    ((uint32_t)0x60020000)    
#define Bank1_LCD_C    ((uint32_t)0x60000000)	

#define LCD_BackLightOn() GPIO_SetBits(GPIOD, GPIO_Pin_13) 

void ILI9325_Init(void);

void ILI9325_WriteIR(unsigned int index);
void ILI9325_SetRegister(unsigned int index,unsigned int val);
void ILI9325_WriteWDR(unsigned int val);
unsigned int ILI9325_ReadRDR(void);

#define ILI9325_GRAMOperation() ILI9325_WriteIR(0x22)
#define ILI9325_WritePixel(x) ILI9325_WriteWDR(x)

#define ILI9325_VerticalScreen() ILI9325_SetRegister(0x0003,0x1030)
#define ILI9325_HorizontalScreen() ILI9325_SetRegister(0x0003,0x1038)
#define ILI9325_ZoomInByTwo() ILI9325_SetRegister(0x0004, 0x0001)
#define ILI9325_ZoomInByFour() ILI9325_SetRegister(0x0004, 0x0003)

void ILI9325_DrawWindowArea(unsigned int startX,unsigned int startY,
														unsigned int width,unsigned int height,
													  unsigned int pixels[]);
void ILI9325_FillWindowArea(unsigned int startX,unsigned int startY,
                            unsigned int width,unsigned int height,unsigned int pixel);
#define ILI9325_Pix(x,y,pixel) ILI9325_FillWindowArea(x,y,1,1,pixel)
void ILI9325_SetCursorPos(unsigned int x ,unsigned int y);

#endif


