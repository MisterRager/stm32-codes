/*****************************************************************************
 *  Module for Microchip Graphics Library
 *  Custom display controller driver template
 *****************************************************************************
 * FileName:            MicrochipGraphicsModule.h
 * Dependencies:    p24Fxxxx.h or plib.h
 * Processor:           PIC24F
 * Compiler:       	MPLAB C30
 * Linker:                MPLAB LINK30
 * Company:            Microchip Technology Incorporated
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
 * Author                                    Date                               Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Pradeep Budagutta                20 Aug 2009                 Initial Version
 * Pradeep Budagutta                03 Dec 2009                 Added Double Buffering Support
 *****************************************************************************/
#ifndef _CUSTOM_DISPLAY_DRIVER_H
#define _CUSTOM_DISPLAY_DRIVER_H

#ifdef __PIC32MX
#include <plib.h>
#define PMDIN1   PMDIN
#else
#ifdef __PIC24F__
#include <p24Fxxxx.h>
#else
#error CONTROLLER IS NOT SUPPORTED
#endif
#endif

#include "GraphicsConfig.h"
#include "GenericTypeDefs.h"

/*********************************************************************
* Overview: Additional hardware-accelerated functions can be implemented
*           in the driver. These definitions exclude the PutPixel()-based
*           functions in the primitives layer (Primitive.c file) from compilation.
*********************************************************************/

// Define this to implement Font related functions in the driver.
#if (DISP_ORIENTATION == 0) 
//    #define USE_DRV_FONT
#endif

// Define this to implement Line function in the driver.
#define USE_DRV_LINE

// Define this to implement Circle function in the driver.
//#define USE_DRV_CIRCLE

// Define this to implement FillCircle function in the driver.
//#define USE_DRV_FILLCIRCLE

// Define this to implement Bar function in the driver.
#define USE_DRV_BAR

// Define this to implement ClearDevice function in the driver.
#define USE_DRV_CLEARDEVICE

// Define this to implement PutImage function in the driver.
#define USE_DRV_PUTIMAGE

#ifndef DISP_HOR_RESOLUTION
    #error  DISP_HOR_RESOLUTION must be defined in GraphicsConfig.h
#endif

#ifndef DISP_VER_RESOLUTION
    #error  DISP_VER_RESOLUTION must be defined in GraphicsConfig.h
#endif

#ifndef COLOR_DEPTH
    #error  COLOR_DEPTH must be defined in GraphicsConfig.h
#endif

#ifndef DISP_ORIENTATION
    #error  DISP_ORIENTATION must be defined in GraphicsConfig.h
#endif

/*********************************************************************
* Overview: Clipping region control codes to be used with SetClip(...)
*           function. 
*********************************************************************/
#define CLIP_DISABLE       0 	// Disables clipping.
#define CLIP_ENABLE        1	// Enables clipping.

/*********************************************************************
* Overview: Some basic colors definitions.
*********************************************************************/
#ifdef USE_PALETTE

    #include "PaletteColorDefines.h"
    
#elif (COLOR_DEPTH == 16)

    #define BLACK               RGB565CONVERT(0,    0,      0)
    #define BRIGHTBLUE          RGB565CONVERT(0,    0,      255)
    #define BRIGHTGREEN         RGB565CONVERT(0,    255,    0)
    #define BRIGHTCYAN          RGB565CONVERT(0,    255,    255)
    #define BRIGHTRED           RGB565CONVERT(255,  0,      0)
    #define BRIGHTMAGENTA       RGB565CONVERT(255,  0,      255)
    #define BRIGHTYELLOW        RGB565CONVERT(255,  255,    0)
    #define BLUE                RGB565CONVERT(0,    0,      128)
    #define GREEN               RGB565CONVERT(0,    128,    0)
    #define CYAN                RGB565CONVERT(0,    128,    128)
    #define RED                 RGB565CONVERT(128,  0,      0)
    #define MAGENTA             RGB565CONVERT(128,  0,      128)
    #define BROWN               RGB565CONVERT(255,  128,    0)
    #define LIGHTGRAY           RGB565CONVERT(128,  128,    128)
    #define DARKGRAY            RGB565CONVERT(64,   64,     64)
    #define LIGHTBLUE           RGB565CONVERT(128,  128,    255)
    #define LIGHTGREEN          RGB565CONVERT(128,  255,    128)
    #define LIGHTCYAN           RGB565CONVERT(128,  255,    255)
    #define LIGHTRED            RGB565CONVERT(255,  128,    128)
    #define LIGHTMAGENTA        RGB565CONVERT(255,  128,    255)
    #define YELLOW              RGB565CONVERT(255,  255,    128)
    #define WHITE               RGB565CONVERT(255,  255,    255)
    
    #define GRAY0       	    RGB565CONVERT(224,  224,    224)
    #define GRAY1         	    RGB565CONVERT(192,  192,    192)
    #define GRAY2               RGB565CONVERT(160,  160,    160)
    #define GRAY3               RGB565CONVERT(128,  128,    128)
    #define GRAY4               RGB565CONVERT(96,   96,     96)
    #define GRAY5               RGB565CONVERT(64,   64,     64)
    #define GRAY6	            RGB565CONVERT(32,   32,     32)

#elif (COLOR_DEPTH == 8)

    #define BLACK               RGB332CONVERT(0,    0,      0)
    #define BRIGHTBLUE          RGB332CONVERT(0,    0,      255)
    #define BRIGHTGREEN         RGB332CONVERT(0,    255,    0)
    #define BRIGHTCYAN          RGB332CONVERT(0,    255,    255)
    #define BRIGHTRED           RGB332CONVERT(255,  0,      0)
    #define BRIGHTMAGENTA       RGB332CONVERT(255,  0,      255)
    #define BRIGHTYELLOW        RGB332CONVERT(255,  255,    0)
    #define BLUE                RGB332CONVERT(0,    0,      128)
    #define GREEN               RGB332CONVERT(0,    128,    0)
    #define CYAN                RGB332CONVERT(0,    128,    128)
    #define RED                 RGB332CONVERT(128,  0,      0)
    #define MAGENTA             RGB332CONVERT(128,  0,      128)
    #define BROWN               RGB332CONVERT(255,  128,    0)
    #define LIGHTGRAY           RGB332CONVERT(128,  128,    128)
    #define DARKGRAY            RGB332CONVERT(64,   64,     64)
    #define LIGHTBLUE           RGB332CONVERT(128,  128,    255)
    #define LIGHTGREEN          RGB332CONVERT(128,  255,    128)
    #define LIGHTCYAN           RGB332CONVERT(128,  255,    255)
    #define LIGHTRED            RGB332CONVERT(255,  128,    128)
    #define LIGHTMAGENTA        RGB332CONVERT(255,  128,    255)
    #define YELLOW              RGB332CONVERT(255,  255,    128)
    #define WHITE               RGB332CONVERT(255,  255,    255)
    
    #define GRAY0       	    RGB332CONVERT(224,  224,    224)
    #define GRAY1         	    RGB332CONVERT(192,  192,    192)
    #define GRAY2               RGB332CONVERT(160,  160,    160)
    #define GRAY3               RGB332CONVERT(128,  128,    128)
    #define GRAY4               RGB332CONVERT(96,   96,     96)
    #define GRAY5               RGB332CONVERT(64,   64,     64)
    #define GRAY6	            RGB332CONVERT(32,   32,     32)

#elif (COLOR_DEPTH == 4)

    #define BLACK               0x00
    #define BRIGHTBLUE          0x09
    #define BRIGHTGREEN         0x0C
    #define BRIGHTCYAN          0x0D
    #define BRIGHTRED           0x0A
    #define BRIGHTMAGENTA       0x0B
    #define BRIGHTYELLOW        0x0E
    #define BLUE                0x09
    #define GREEN               0x0C
    #define CYAN                0x0D
    #define RED                 0x0A
    #define MAGENTA             0x0B
    #define BROWN               0x02
    #define LIGHTGRAY           0x07
    #define DARKGRAY            0x07
    #define LIGHTBLUE           0x01
    #define LIGHTGREEN          0x04
    #define LIGHTCYAN           0x05
    #define LIGHTRED            0x02
    #define LIGHTMAGENTA        0x03
    #define YELLOW              0x06
    #define WHITE               0x0F
    
    #define GRAY0       	    0x07
    #define GRAY1         	    0x07
    #define GRAY2               0x07
    #define GRAY3               0x07
    #define GRAY4               0x07
    #define GRAY5               0x07
    #define GRAY6	            0x07

#elif (COLOR_DEPTH == 2)

    #define BLACK               0x00
    #define BRIGHTBLUE          0x03
    #define BRIGHTGREEN         0x03
    #define BRIGHTCYAN          0x03
    #define BRIGHTRED           0x03
    #define BRIGHTMAGENTA       0x03
    #define BRIGHTYELLOW        0x03
    #define BLUE                0x02
    #define GREEN               0x02
    #define CYAN                0x02
    #define RED                 0x02
    #define MAGENTA             0x02
    #define BROWN               0x02
    #define LIGHTGRAY           0x02
    #define DARKGRAY            0x01
    #define LIGHTBLUE           0x01
    #define LIGHTGREEN          0x01
    #define LIGHTCYAN           0x01
    #define LIGHTRED            0x01
    #define LIGHTMAGENTA        0x01
    #define YELLOW              0x01
    #define WHITE               0x03
    
    #define GRAY0       	    0x02
    #define GRAY1         	    0x02
    #define GRAY2               0x02
    #define GRAY3               0x01
    #define GRAY4               0x01
    #define GRAY5               0x01
    #define GRAY6	            0x01

#elif (COLOR_DEPTH == 1)

    #define BLACK               0x00
    #define BRIGHTBLUE          0x01
    #define BRIGHTGREEN         0x01
    #define BRIGHTCYAN          0x01
    #define BRIGHTRED           0x01
    #define BRIGHTMAGENTA       0x01
    #define BRIGHTYELLOW        0x01
    #define BLUE                0x01
    #define GREEN               0x01
    #define CYAN                0x01
    #define RED                 0x01
    #define MAGENTA             0x01
    #define BROWN               0x01
    #define LIGHTGRAY           0x00
    #define DARKGRAY            0x00
    #define LIGHTBLUE           0x00
    #define LIGHTGREEN          0x00
    #define LIGHTCYAN           0x00
    #define LIGHTRED            0x00
    #define LIGHTMAGENTA        0x00
    #define YELLOW              0x00
    #define WHITE               0x00
    
    #define GRAY0       	    0x01
    #define GRAY1         	    0x01
    #define GRAY2               0x01
    #define GRAY3               0x01
    #define GRAY4               0x00
    #define GRAY5               0x00
    #define GRAY6	            0x00

#endif // Color

extern WORD_VAL _color;
extern WORD_VAL _chrcolor;

/*********************************************************************
* Overview: Clipping region control and border settings.
*
*********************************************************************/
// Clipping region enable control
extern SHORT _clipRgn;
// Left clipping region border
extern SHORT _clipLeft;
// Top clipping region border
extern SHORT _clipTop;
// Right clipping region border
extern SHORT _clipRight;
// Bottom clipping region border
extern SHORT _clipBottom;

#define GFX_LCD_TFT  0x01
#define GFX_LCD_MSTN 0x02
#define GFX_LCD_CSTN 0x03
#define GFX_LCD_OFF  0x00

#define STN_DISPLAY_WIDTH_4  0x00
#define STN_DISPLAY_WIDTH_8  0x01
#define STN_DISPLAY_WIDTH_16 0x02

#define GFX_1_BPP  0x00
#define GFX_2_BPP  0x01
#define GFX_4_BPP  0x02
#define GFX_8_BPP  0x03
#define GFX_16_BPP 0x04

#if (COLOR_DEPTH == 1)
    #define GFX_BITS_PER_PIXEL                  GFX_1_BPP
    #define GFX_COLOR_MASK                      0x0001
#elif (COLOR_DEPTH == 2)
    #define GFX_BITS_PER_PIXEL                  GFX_2_BPP
    #define GFX_COLOR_MASK                      0x0003
#elif (COLOR_DEPTH == 4)
    #define GFX_BITS_PER_PIXEL                  GFX_4_BPP
    #define GFX_COLOR_MASK                      0x000F
#elif (COLOR_DEPTH == 8)
    #define GFX_BITS_PER_PIXEL                  GFX_8_BPP
    #define GFX_COLOR_MASK                      0x00FF
#else
    #define GFX_BITS_PER_PIXEL                  GFX_16_BPP
    #define GFX_COLOR_MASK                      0xFFFF
#endif

#define GFX_COMMAND_QUEUE_LENGTH            16

#define GFX_ACTIVE_HIGH                     1
#define GFX_ACTIVE_LOW                      0

/* RCC GPU Commands */
#define RCC_SRCADDR                         0x62000000ul
#define RCC_DESTADDR                        0x63000000ul
#define RCC_RECTSIZE                        0x64000000ul
#define RCC_COLOR                           0x66000000ul
#define RCC_STARTCOPY                       0x67000000ul

#define RCC_SOLID_FILL                      0x00000000ul
#define RCC_COPY                            0x00000080ul
#define RCC_TRANSPARENT_COPY                0x00000300ul

#define RCC_ROP_0                           0x00000000ul
#define RCC_ROP_1                           0x00000008ul
#define RCC_ROP_2                           0x00000010ul
#define RCC_ROP_3                           0x00000018ul
#define RCC_ROP_4                           0x00000020ul
#define RCC_ROP_5                           0x00000028ul
#define RCC_ROP_6                           0x00000030ul
#define RCC_ROP_7                           0x00000038ul
#define RCC_ROP_8                           0x00000040ul
#define RCC_ROP_9                           0x00000048ul
#define RCC_ROP_A                           0x00000050ul
#define RCC_ROP_B                           0x00000058ul
#define RCC_ROP_C                           0x00000060ul
#define RCC_ROP_D                           0x00000068ul
#define RCC_ROP_E                           0x00000070ul
#define RCC_ROP_F                           0x00000078ul

#define RCC_SRC_ADDR_CONTINUOUS             0x00000002ul
#define RCC_SRC_ADDR_DISCONTINUOUS          0x00000000ul
#define RCC_DEST_ADDR_CONTINUOUS            0x00000004ul
#define RCC_DEST_ADDR_DISCONTINUOUS         0x00000000ul

#define GFX_SetCommand(c)                   { DWORD command = c; G1CMDL = ((DWORD_VAL)(command)).word.LW; G1CMDH = ((DWORD_VAL)(command)).word.HW; Nop(); }

#define GFX_SetDisplayArea(a)               { DWORD address = a; G1DPADRL = ((DWORD_VAL)(address)).word.LW; G1DPADRH = ((DWORD_VAL)(address)).word.HW; }
#define GFX_SetWorkArea1(a)                 { DWORD address = a; G1W1ADRL = ((DWORD_VAL)(address)).word.LW; G1W1ADRH = ((DWORD_VAL)(address)).word.HW; }
#define GFX_SetWorkArea2(a)                 { DWORD address = a; G1W2ADRL = ((DWORD_VAL)(address)).word.LW; G1W2ADRH = ((DWORD_VAL)(address)).word.HW; }

#define GFX_SetSrcAddress(s)                GFX_SetCommand(RCC_SRCADDR | (s));      /* Don't do error checking or error corrections */
#define GFX_SetDestAddress(d)               GFX_SetCommand(RCC_DESTADDR | (d));     /* Don't do error checking or error corrections */
#define GFX_SetRectSize(width, height)      GFX_SetCommand(RCC_RECTSIZE | (((DWORD)(width)) << 12) | (DWORD)height)     /* Don't do error checking or error corrections */
#define GFX_SetColor(color)                 GFX_SetCommand(RCC_COLOR | (color & GFX_COLOR_MASK))       /* Don't do error checking or error corrections */
#define GFX_StartCopy(type_of_copy, rop, src_addr_type, dest_addr_type)     GFX_SetCommand(RCC_STARTCOPY | type_of_copy | rop | src_addr_type | dest_addr_type)     /* Don't do error checking or error corrections */

#define CHR_FGCOLOR                         0x50000000ul
#define CHR_BGCOLOR                         0x51000000ul
#define CHR_FONTBASE                        0x52000000ul
#define CHR_PRINTCHAR                       0x53000000ul
#define CHR_TEXTAREASTART                   0x58000000ul
#define CHR_TEXTAREAEND                     0x59000000ul
#define CHR_PRINTPOS                        0x5A000000ul

#define CHR_TRANSPARENT                     0x00800000ul
#define CHR_OPAQUE                          0x00000000ul

#define GFX_SetCharFgColor(color)           { _chrcolor.Val = color; GFX_SetCommand(CHR_FGCOLOR | color); }
#define GFX_SetCharBgColor(color)           GFX_SetCommand(CHR_BGCOLOR | color)
#define GFX_SetFont(fontaddress)            GFX_SetCommand(CHR_FONTBASE | fontaddress)
#define GFX_SetStartXY(x, y)                GFX_SetCommand(CHR_TEXTAREASTART | ((DWORD)x) << 12 | y)
#define GFX_SetEndXY(x, y)                  GFX_SetCommand(CHR_TEXTAREAEND | ((DWORD)x) << 12 | y)
#define GFX_SetPrintXY(x, y)                GFX_SetCommand(CHR_PRINTPOS | ((DWORD)x) << 12 | y)
#define GFX_PrintChar(character, transparency)      GFX_SetCommand(CHR_PRINTCHAR | transparency | character)

#define IPU_SRCOFFSET                       0x71000000ul
#define IPU_DSTOFFSET                       0x72000000ul
#define IPU_DSTSIZE                         0x74000000ul

#define GFX_SetCompressedSource(address)    GFX_SetCommand(IPU_SRCOFFSET | address)
#define GFX_SetDecompressionDest(address)   GFX_SetCommand(IPU_DSTOFFSET | address)
#define GFX_SetDecompressSize(bytes)        GFX_SetCommand(IPU_DSTSIZE | bytes)
#define GFX_FinalBlock()                    (G1IPU & 0x0001)
#define GFX_DecomperssionDone()             (G1IPU & 0x0002)
#define GFX_DecompressionError()            (G1IPU & 0x003C)
#define GFX_WrapAroundError()               (G1IPU & 0x0004)
#define GFX_BlockLengthError()              (G1IPU & 0x0008)
#define GFX_UndefinedBlockError()           (G1IPU & 0x0010)
#define GFX_HuffmannError()                 (G1IPU & 0x0020)

#define GFX_GetFreeCommandSpace()       	(GFX_COMMAND_QUEUE_LENGTH - _GCMDCNT)
#define GFX_WaitForCommandQueue(n)      	while(GFX_GetFreeCommandSpace() < (n));
#define GFX_IsRccGpuBusy()              	(_RCCBUSY)
#define GFX_IsIpuGpuBusy()              	(_IPUBUSY)
#define GFX_IsChrGpuBusy()              	(_CHRBUSY)
#define GFX_IsPuGpuBusy()               	(_PUBUSY)
#define GFX_WaitForRccGpu()             	while(_RCCBUSY);
#define GFX_WaitForIpuGpu()             	while(_IPUBUSY);
#define GFX_WaitForChrGpu()             	while(_CHRBUSY);
#define GFX_WaitForGpu()                	while(_PUBUSY);

/*********************************************************************
* Function:  void ResetDevice()
*
* Overview: Initializes LCD module.
*
* PreCondition: none
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
void ResetDevice(void);

/*********************************************************************
* Macros:  GetMaxX()
*
* Overview: Returns maximum horizontal coordinate.
*
* PreCondition: none
*
* Input: none
*
* Output: Maximum horizontal coordinate.
*
* Side Effects: none
*
********************************************************************/
#if (DISP_ORIENTATION == 90) || (DISP_ORIENTATION == 270)

#define	GetMaxX() (DISP_VER_RESOLUTION-1)

#elif (DISP_ORIENTATION == 0) || (DISP_ORIENTATION == 180)

#define	GetMaxX() (DISP_HOR_RESOLUTION-1)

#endif

/*********************************************************************
* Macros:  GetMaxY()
*
* Overview: Returns maximum vertical coordinate.
*
* PreCondition: none
*
* Input: none
*
* Output: Maximum vertical coordinate.
*
* Side Effects: none
*
********************************************************************/
#if (DISP_ORIENTATION == 90) || (DISP_ORIENTATION == 270)

#define	GetMaxY() (DISP_HOR_RESOLUTION-1)

#elif (DISP_ORIENTATION == 0) || (DISP_ORIENTATION == 180)

#define	GetMaxY() (DISP_VER_RESOLUTION-1)

#endif

/*********************************************************************
* Macros:  SetColor(color)
*
* Overview: Sets current drawing color.
*
* PreCondition: none
*
* Input: color - Color coded in 5:6:5 RGB format.
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
#define SetColor(color) _color.Val = color;

/*********************************************************************
* Macros:  GetColor()
*
* Overview: Returns current drawing color.
*
* PreCondition: none
*
* Input: none
*
* Output: Color coded in 5:6:5 RGB format.
*
* Side Effects: none
*
********************************************************************/
#define GetColor() _color.Val

/*********************************************************************
* Macros:  SetActivePage(page)
*
* Overview: Sets active graphic page.
*
* PreCondition: none
*
* Input: page - Graphic page number.
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
#define SetActivePage(page)

/*********************************************************************
* Macros: SetVisualPage(page)
*
* Overview: Sets graphic page to display.
*
* PreCondition: none
*
* Input: page - Graphic page number
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
#define SetVisualPage(page)

/*********************************************************************
* Function: WORD MoveBlock(DWORD srcAddr, DWORD dstAddr, 
*						   DWORD srcOffset, DWORD dstOffset, 
*			               WORD srcType, WORD dstType, 
*                          WORD width, WORD height)
*
* PreCondition: none
*
* Input: srcAddr - the base address of the data to be moved
*        dstAddr - the base address of the new location of the moved data 
*        srcOffset - offset of the data to be moved with respect to the 
*					 source base address.
*        dstOffset - offset of the new location of the moved data respect 
*					 to the source base address.
*        srcType - sets the source type (continuous or discontinuous)
*        dstType - sets the source type (continuous or discontinuous) 
*        width - width of the block of data to be moved
*        height - height of the block of data to be moved
*
* Output: none
*
* Side Effects: none
*
* Overview: puts pixel
*
* Note: none
*
********************************************************************/
WORD MoveBlock(DWORD srcAddr, DWORD dstAddr, DWORD srcOffset, DWORD dstOffset, 
			   WORD srcType, WORD dstType, WORD width, WORD height);

/*********************************************************************
* Function: WORD ScrollLeft(SHORT left, SHORT top,  
*							SHORT right, SHORT bottom, SHORT delta)
*
* PreCondition: none
*
* Input: left - left position of the scrolled rectangle
*        top - top position of the scrolled rectangle
*        right - right position of the scrolled rectangle
*        bottom - bottom position of the scrolled rectangle
*        delta - defines the scroll delta
*
* Output: none
*
* Side Effects: none
*
* Overview: Scrolls the rectangular area defined by left, top, right, bottom by delta pixels.
*
* Note: none
*
********************************************************************/
WORD ScrollLeft(SHORT left, SHORT top, SHORT right, SHORT bottom, SHORT delta);
			   				
/*********************************************************************
* Function: void PutPixel(SHORT x, SHORT y)
*
* Overview: Puts pixel with the given x,y coordinate position.
*
* PreCondition: none
*
* Input: x - x position of the pixel.
*		 y - y position of the pixel.
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
void PutPixel(SHORT x, SHORT y);

/*********************************************************************
* Function: WORD GetPixel(SHORT x, SHORT y)
*
* Overview: Returns pixel color at the given x,y coordinate position.
*
* PreCondition: none
*
* Input: x - x position of the pixel.
*		 y - y position of the pixel.
*
* Output: pixel color
*
* Side Effects: none
*
********************************************************************/
WORD GetPixel(SHORT x, SHORT y);

/*********************************************************************
* Function: SetClipRgn(left, top, right, bottom)
*
* Overview: Sets clipping region.
*
* PreCondition: none
*
* Input: left - Defines the left clipping region border.
*		 top - Defines the top clipping region border.
*		 right - Defines the right clipping region border.
*	     bottom - Defines the bottom clipping region border.
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
void SetClipRgn(SHORT left, SHORT top, SHORT right, SHORT bottom);

/*********************************************************************
* Macros: GetClipLeft()
*
* Overview: Returns left clipping border.
*
* PreCondition: none
*
* Input: none
*
* Output: Left clipping border.
*
* Side Effects: none
*
********************************************************************/
#define GetClipLeft() _clipLeft

/*********************************************************************
* Macros: GetClipRight()
*
* Overview: Returns right clipping border.
*
* PreCondition: none
*
* Input: none
*
* Output: Right clipping border.
*
* Side Effects: none
*
********************************************************************/
#define GetClipRight() _clipRight

/*********************************************************************
* Macros: GetClipTop()
*
* Overview: Returns top clipping border.
*
* PreCondition: none
*
* Input: none
*
* Output: Top clipping border.
*
* Side Effects: none
*
********************************************************************/
#define GetClipTop() _clipTop

/*********************************************************************
* Macros: GetClipBottom()
*
* Overview: Returns bottom clipping border.
*
* PreCondition: none
*
* Input: none
*
* Output: Bottom clipping border.
*
* Side Effects: none
*
********************************************************************/
#define GetClipBottom() _clipBottom

/*********************************************************************
* Function: SetClip(control)
*
* Overview: Enables/disables clipping.
*
* PreCondition: none
*
* Input: control - Enables or disables the clipping.
*			- 0: Disable clipping
*			- 1: Enable clipping
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
void SetClip(BYTE control);

/*********************************************************************
* Macros: IsDeviceBusy()
*
* Overview: Returns non-zero if LCD controller is busy 
*           (previous drawing operation is not completed).
*
* PreCondition: none
*
* Input: none
*
* Output: Busy status.
*
* Side Effects: none
*
********************************************************************/
#define IsDeviceBusy()  (GFX_GetFreeCommandSpace() < 4)

/*********************************************************************
* Function:  BYTE Decompress(DWORD SrcAddress, DWORD DestAddress, DWORD nbytes);
*
* Overview: Decompresses the nbytes number of data at SrcAddress and
*           places starting from DestAddress. (Blocking)
*
* PreCondition: SrcAddress must point to the start of a compressed block.
*
* Input: SrcAddress  - Source address
*        DestAddress - Destination address
*        nbytes      - Number of bytes to be decompressed
*
* Output: error flag
*
* Side Effects: Modifies workarea_1 & workarea_2 registers.
*
********************************************************************/
BYTE Decompress(DWORD SrcAddress, DWORD DestAddress, DWORD nbytes);

typedef struct
{
    WORD X;
    WORD Y;
    WORD W;
    WORD H;
} RectangleArea;

#ifdef USE_DOUBLE_BUFFERING

    #define GFX_MAX_INVALIDATE_AREAS 5

extern BYTE blInvalidateAll;
extern BYTE blEnableDoubleBuffering;
extern volatile BYTE blDisplayUpdatePending;
extern BYTE NoOfInvalidatedRectangleAreas;
extern RectangleArea InvalidatedArea[GFX_MAX_INVALIDATE_AREAS];

/*********************************************************************
* Macros:  SwitchOnDoubleBuffering()
*
* Overview: Switches on the double buffering.
*           The drawing is done on the draw buffer.
*           This also causes copying of the frame buffer to draw buffer once.
*
* PreCondition: none
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
#define SwitchOnDoubleBuffering()       if(blEnableDoubleBuffering == 0) \
                                        { blEnableDoubleBuffering = 1; InvalidateAll(); }

/*********************************************************************
* Macros:  SwitchOffDoubleBuffering()
*
* Overview: Switches off the double buffering.
*           The drawing is done on the display buffer.
*
* PreCondition: none
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
#define SwitchOffDoubleBuffering()      if(blEnableDoubleBuffering == 1) \
                                        { UpdateDisplayNow(); \
                                          _drawbuffer = (_drawbuffer == GFX_BUFFER1)? GFX_BUFFER2: GFX_BUFFER1; \
                                          blEnableDoubleBuffering = 0; }

/*********************************************************************
* Macros:  IsDisplayUpdatePending()
*
* Overview: Returns id the display updation is pending.
*
* PreCondition: none
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
#define IsDisplayUpdatePending()    blDisplayUpdatePending

/*********************************************************************
* Macros:  InvalidateAll()
*
* Overview: Invalidates the whole screen
*
* PreCondition: none
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
#define InvalidateAll()                 blInvalidateAll = 1;

/*********************************************************************
* Function:  void InvalidateRectangle(WORD left, WORD top, WORD right, WORD bottom)
*
* Overview: Invalidates the specified rectangular area and if the
*           invalidated areas exceed the GFX_MAX_INVALIDATE_AREAS,
*           whole area is marked as invalidate
*
* PreCondition: None
*
* Input: left,top - top left corner coordinates,
*        right,bottom - bottom right corner coordinates
*
* Output: None
*
* Side Effects: Only copies back the invalidated areas to the draw -
*               buffer after the exchange of draw and frame buffers
*
********************************************************************/
void InvalidateRectangle(WORD x, WORD y, WORD w, WORD h);

/*********************************************************************
* Function:  void UpdateDisplayNow(void)
*
* Overview: Synchronizes the draw and frame buffers immediately
*
* PreCondition: none
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
void UpdateDisplayNow(void);

/*********************************************************************
* Function:  void RequestDisplayUpdate(void)
*
* Overview: Synchronizes the draw and frame buffers at next VBlank
*
* PreCondition: none
*
* Input: none
*
* Output: none
*
* Side Effects: none
*
********************************************************************/
void RequestDisplayUpdate(void);

#else

#define SwitchOnDoubleBuffering()
#define SwitchOffDoubleBuffering()
#define IsDisplayUpdatePending() 0
#define InvalidateAll()
#define InvalidateRectangle(x, y, w, h)
#define ExchangeDrawAndFrameBuffers()
#define UpdateDisplayNow()
#define RequestDisplayUpdate()

#endif //USE_DOUBLE_BUFFERING

#ifdef USE_PALETTE
    #include "Graphics\Palette.h"
#endif

#endif // _CUSTOM_DISPLAY_DRIVER_H
