/*
 *  lcd.h : Driver for Nokia3310/5110 LCD.
 *  Copyright (C) 2005-2009 Zhao Huabing
 *  www.ursastudio.com.cn
 *	History:	2005-11-20 Zhao Huabing created
 *				2009-03-12 Zhao Huabing modified 
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef _LCD_H
#define _LCD_H

/*  液晶分辨率定义  */
#define LCD_WIDTH 	84
#define LCD_HEIGHT	48

#define LCD_ROW		(LCD_HEIGHT/8)
#define LCD_COL		LCD_WIDTH

/*  液晶控制器端口定义  */
#define LCD_DDR		DDRA
#define LCD_PORT 	PORTA

/*  液晶控制器引脚定义  */

#define LCD_SCLK  	GPIO_Pin_7   	//PG9
#define LCD_SDIN 	GPIO_Pin_5   //PD7
#define LCD_DC   	GPIO_Pin_4		//PD5
#define LCD_SCE   	GPIO_Pin_1		//PD4
#define LCD_CTL		RCC_APB2Periph_GPIOD



#define LCD_RST						GPIO_Pin_0	/*PD0*/
#define LCD_RESET_CTL 				RCC_APB2Periph_GPIOD
#define LCD_Speed 			GPIO_Speed_50MHz

#define LCD_CTL_Pins	GPIOD
#define LCD_RESET_CTL_Pins GPIOD

/*  参数宏  */
#define COMMAND		(u8)0
#define DATA		(u8)1
#define LCDCMD		(u8)0
#define POWERDOWN	1
#define ACTIVE 		0

#define V_ADDR		1
#define H_ADDR		0

#define EXT_INS		1
#define BAS_INS		0

#define DISPLAY_BLANK		0x00//0b000
#define DISPLAY_ALL			0x01 //0b001
#define NORMAL_MODE		0x04 //0b100
#define INVERSE_MODE		0x05 //0b101

// 类型 、操作宏定义
typedef unsigned char uint8_t ;
//typedef uint8_t bool;
#define true		1
#define false		0
#define _BV(a)  	 (1<<a)


#define bit_get(sfr, bit) 			//((sfr>>(bit)) & 0x01)
#define bit_set(sfr, bit, val) 		//((val) ? (sfr |= _BV(bit)) : (sfr &= ~_BV(bit)))

void  LCD_SDIN_LOW(void) ;
void  LCD_SDIN_HIGH(void) ;/*read  lcm mode*/
void  LCD_SCLK_HIGH(void) ;
void  LCD_SCLK_LOW(void) ;/*write  lcm mode*/

/* 函数声明 */
void LcdInit(void);
void LcdClsScr(void);
void LcdWriteDC(u8 DC, uint8_t info);
void LcdDrawBitmap(uint8_t x, uint8_t y, uint8_t *pBmp, uint8_t row, uint8_t col);
void LcdPutString(uint8_t x, uint8_t y, const char *str);

#endif
