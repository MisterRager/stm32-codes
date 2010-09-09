/*****************************************************************************
 *  Module for Microchip Graphics Library
 *  Solomon Systech. SSD1289 TCON  driver
 *****************************************************************************
 * FileName:        TCON_SSD1289.c
 * Dependencies:    Graphics.h
 * Processor:       PIC24, PIC32
 * Compiler:       	MPLAB C30, MPLAB C32
 * Linker:          MPLAB LINK30, MPLAB LINK32
 * Company:         Microchip Technology Incorporated
 *
 * Software License Agreement
 *
 * Copyright © 2008 Microchip Technology Inc.  All rights reserved.
 * Microchip licenses to you the right to use, modify, copy and distribute
 * Software only when embedded on a Microchip microcontroller or digital
 * signal controller, which is integrated into your product or third party
 * product (pursuant to the sublicense terms in the accompanying license
 * agreement).  
 *
 * You should refer to the license agreement accompanying this Software
 * for additional information regarding your rights and obligations.
 *
 * SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY
 * OF MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR
 * PURPOSE. IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR
 * OBLIGATED UNDER CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION,
 * BREACH OF WARRANTY, OR OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT
 * DAMAGES OR EXPENSES INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL,
 * INDIRECT, PUNITIVE OR CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA,
 * COST OF PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY
 * CLAIMS BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF),
 * OR OTHER SIMILAR COSTS.
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Anton Alkhimenok     11/17/08
 * PAT					04/05/10	Modified initialization to reduce flicker.
 *****************************************************************************/
#include "Graphics\Graphics.h"

#define CS  0x01
#define SCL 0x02
#define SDO 0x04
#define DC  0x08
#define BL  0x10

BYTE    value;

/* */

void TCON_Delay(void)
{
    WORD    timeOut;
    timeOut = 200;
    while(timeOut--);
}

/* */
void TCON_CTRL(BYTE mask, BYTE level)
{
  #if (DISPLAY_CONTROLLER == MCHP_DA210)

    switch(mask)
    {
        case CS:    CS_PORT  = level;
                    break;

        case SCL:   SCL_PORT = level;
                    break;

        case SDO:   SDO_PORT = level;
                    break;

        case DC:    DC_PORT  = level;
                    break;
    }
    
    Nop();
    
  #else

    if(level == 0)
    {
        value &= ~mask;
    }
    else
    {
        value |= mask;
    }

    SetReg(0xAC, value);

  #endif
}

/* */
void TCONWriteByte(BYTE value)
{
    BYTE    mask;

    mask = 0x80;
    while(mask)
    {
        TCON_CTRL(SCL, 0);
        TCON_Delay();
        if(mask & value)
        {
            TCON_CTRL(SDO, 1);
        }
        else
        {
            TCON_CTRL(SDO, 0);
        }

        TCON_CTRL(SCL, 1);
        mask >>= 1;
    }
}

/* */
void GPIO_TCON(WORD index, WORD value)
{
    TCON_CTRL(CS, 0);

    // Index
    TCON_CTRL(DC, 0);
    TCONWriteByte(((WORD_VAL) index).v[1]);
    TCONWriteByte(((WORD_VAL) index).v[0]);

    TCON_CTRL(CS, 1);
    TCON_Delay();
    TCON_CTRL(CS, 0);

    // Data
    TCON_CTRL(DC, 1);
    TCONWriteByte(((WORD_VAL) value).v[1]);
    TCONWriteByte(((WORD_VAL) value).v[0]);
    TCON_CTRL(CS, 1);
    TCON_Delay();
}

/* */
void TCON_Init(void)
{
    #if (DISPLAY_CONTROLLER == MCHP_DA210)
	
		WORD CS_TRIS_temp = CS_TRIS;	
		WORD SCL_TRIS_temp = SCL_TRIS;
        WORD SDO_TRIS_temp = SDO_TRIS;
        WORD DC_TRIS_temp = DC_TRIS;

        CS_DIG();
        CS_PORT  = 1;
        CS_TRIS  = 0;

        SCL_DIG();
        SCL_PORT = 1;
        SCL_TRIS = 0;

        SDO_DIG();
        SDO_PORT = 1;
        SDO_TRIS = 0;

        DC_DIG();
        DC_PORT  = 1;
        DC_TRIS  = 0;

    #else

        SetReg(0xA8, BL| DC | CS | SDO | SCL);
        TCON_CTRL(DC, 1);
        TCON_CTRL(CS, 1);
        TCON_CTRL(SDO, 1);
        TCON_CTRL(SCL, 1);
        TCON_CTRL(BL, 1);
       
    #endif
    
	GPIO_TCON(0x0028, 0x0006);
	GPIO_TCON(0x0000, 0x0001);
	DelayMs(15);

	GPIO_TCON(0x002B, 0x9532);
	GPIO_TCON(0x0003, 0xAAAC);
	GPIO_TCON(0x000C, 0x0002);
	GPIO_TCON(0x000D, 0x000A);
	GPIO_TCON(0x000E, 0x2C00);
	GPIO_TCON(0x001E, 0x00AA);
	GPIO_TCON(0x0025, 0x8000);
	DelayMs(15);

	GPIO_TCON(0x0001, 0x2B3F);
	GPIO_TCON(0x0002, 0x0600);
	GPIO_TCON(0x0010, 0x0000);
	DelayMs(20);

	GPIO_TCON(0x0005, 0x0000);
	GPIO_TCON(0x0006, 0x0000);
	
	
	GPIO_TCON(0x0016, 0xEF1C);
	GPIO_TCON(0x0017, 0x0003);
	GPIO_TCON(0x0007, 0x0233);
	GPIO_TCON(0x000B, 0x5312);
	GPIO_TCON(0x000F, 0x0000);
	DelayMs(20);

	GPIO_TCON(0x0041, 0x0000);
	GPIO_TCON(0x0042, 0x0000);
	GPIO_TCON(0x0048, 0x0000);
	GPIO_TCON(0x0049, 0x013F);
	GPIO_TCON(0x0044, 0xEF00);
	GPIO_TCON(0x0045, 0x0000);
	GPIO_TCON(0x0046, 0x013F);
	GPIO_TCON(0x004A, 0x0000);
	GPIO_TCON(0x004B, 0x0000);
	DelayMs(20);

	GPIO_TCON(0x0030, 0x0707);
	GPIO_TCON(0x0031, 0x0704);
	GPIO_TCON(0x0032, 0x0204);
	GPIO_TCON(0x0033, 0x0201);
	GPIO_TCON(0x0034, 0x0203);
	GPIO_TCON(0x0035, 0x0204);
	GPIO_TCON(0x0036, 0x0204);
	GPIO_TCON(0x0037, 0x0502);
	GPIO_TCON(0x003A, 0x0302);
	GPIO_TCON(0x003B, 0x0500);
	DelayMs(20);

  #if (DISPLAY_CONTROLLER == MCHP_DA210)
		CS_TRIS = CS_TRIS_temp;	
		SCL_TRIS = SCL_TRIS_temp;
        SDO_TRIS = SDO_TRIS_temp;
        DC_TRIS = DC_TRIS_temp;
   #endif

}
