/*********************************************************************
 *
 *	Hardware specific definitions
 *
 *********************************************************************
 * FileName:        HardwareProfile.h
 * Dependencies:    None
 * Processor:       PIC24F, PIC24H, dsPIC, PIC32
 * Compiler:        Microchip C32 v1.00 or higher
 *					Microchip C30 v3.01 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 *
 * Copyright © 2002-2008 Microchip Technology Inc.  All rights 
 * reserved.
 *
 * Microchip licenses to you the right to use, modify, copy, and 
 * distribute: 
 * (i)  the Software when embedded on a Microchip microcontroller or 
 *      digital signal controller product (“Device”) which is 
 *      integrated into Licensee’s product; or
 * (ii) ONLY the Software driver source files ENC28J60.c and 
 *      ENC28J60.h ported to a non-Microchip device used in 
 *      conjunction with a Microchip ethernet controller for the 
 *      sole purpose of interfacing with the ethernet controller. 
 *
 * You should refer to the license agreement accompanying this 
 * Software for additional information regarding your rights and 
 * obligations.
 *
 * THE SOFTWARE AND DOCUMENTATION ARE PROVIDED “AS IS” WITHOUT 
 * WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT 
 * LIMITATION, ANY WARRANTY OF MERCHANTABILITY, FITNESS FOR A 
 * PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT SHALL 
 * MICROCHIP BE LIABLE FOR ANY INCIDENTAL, SPECIAL, INDIRECT OR 
 * CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF 
 * PROCUREMENT OF SUBSTITUTE GOODS, TECHNOLOGY OR SERVICES, ANY CLAIMS 
 * BY THIRD PARTIES (INCLUDING BUT NOT LIMITED TO ANY DEFENSE 
 * THEREOF), ANY CLAIMS FOR INDEMNITY OR CONTRIBUTION, OR OTHER 
 * SIMILAR COSTS, WHETHER ASSERTED ON THE BASIS OF CONTRACT, TORT 
 * (INCLUDING NEGLIGENCE), BREACH OF WARRANTY, OR OTHERWISE.
 *
 *
 * Author               Date		Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Howard Schlunder		10/03/06	Original, copied from Compiler.h
 * Jayanth Murthy       06/25/09    dsPIC & PIC24H support 
 * Pradeep Budagutta	15 Sep 2009 Added PIC24FJ256DA210 Development Board Support
 ********************************************************************/

#if defined (__PIC24F__) || defined(__dsPIC33F__) || defined(__PIC24H__)

	#if defined (__PIC24FJ256DA210__)
		/*********************************************************************
	     * Hardware Configuration for 
	     * PIC24FJ256DA210 Development Board
	     * Display TFT-G240320LTSW-118W-E
	     ********************************************************************/
		#include "Alternative Configurations\HardwareProfile_PIC24FJ256DA210_DEV_BOARD_16PMP_MCHP_DA210_TFT_G240320LTSW_118W_E.h"
		
		/*********************************************************************
	     * Hardware Configuration for 
	     * PIC24FJ256DA210 Development Board
	     * Display PH480272T-005-I11Q
	     ********************************************************************/
		//#include "Alternative Configurations\HardwareProfile_PIC24FJ256DA210_DEV_BOARD_16PMP_MCHP_DA210_PH480272T_005_I11Q.h"

	#else
		/*********************************************************************
	     * Hardware Configuration for 
	     * Explorer 16
    	 * Graphics PicTail v3
	     * Display TFT-G240320LTSW-118W-E
	     ********************************************************************/
		#include "Alternative Configurations\HardwareProfile_GFX_PICTAIL_V3_8PMP_SSD1926_TFT_G240320LTSW_118W_E.h"
		//#include "Alternative Configurations\HardwareProfile_GFX_PICTAIL_V3_16PMP_SSD1926_TFT_G240320LTSW_118W_E.h"

		/*********************************************************************
	     * Hardware Configuration for 
	     * Explorer 16
    	 * Graphics PicTail v3
	     * Display PH480272T-005-I11Q
	     ********************************************************************/
		//#include "Alternative Configurations\HardwareProfile_GFX_PICTAIL_V3_8PMP_SSD1926_PH480272T_005_I11Q.h"
		//#include "Alternative Configurations\HardwareProfile_GFX_PICTAIL_V3_16PMP_SSD1926_PH480272T_005_I11Q.h"

		/*********************************************************************
	     * Hardware Configuration for 
	     * Explorer 16
     	 * Graphics PicTail v2
         * Display LGDP4531
	     ********************************************************************/
		//#include "Alternative Configurations\HardwareProfile_GFX_PICTAIL_V2_8PMP_LGDP4531.h"
		
	#endif

#elif defined (__PIC32MX__) 

    /*********************************************************************
     * Hardware Configuration for 
     * Explorer 16
     * Graphics PicTail v3
     * Display TFT-G240320LTSW-118W-E
     ********************************************************************/
    #include "Alternative Configurations\HardwareProfile_GFX_PICTAIL_V3_8PMP_SSD1926_TFT_G240320LTSW_118W_E.h"
	//#include "Alternative Configurations\HardwareProfile_GFX_PICTAIL_V3_16PMP_SSD1926_TFT_G240320LTSW_118W_E.h"

    /*********************************************************************
     * Hardware Configuration for 
     * Explorer 16
     * Graphics PicTail v3
     * Display PH480272T-005-I11Q
     ********************************************************************/
	//#include "Alternative Configurations\HardwareProfile_GFX_PICTAIL_V3_8PMP_SSD1926_PH480272T_005_I11Q.h"
	//#include "Alternative Configurations\HardwareProfile_GFX_PICTAIL_V3_16PMP_SSD1926_PH480272T_005_I11Q.h"

    /*********************************************************************
     * Hardware Configuration for 
     * Explorer 16
     * Graphics PicTail v2
     * Display LGDP4531
     ********************************************************************/
	//#include "Alternative Configurations\HardwareProfile_GFX_PICTAIL_V2_8PMP_LGDP4531.h"

    /*********************************************************************
     * Hardware Configuration for 
     * Starter Kit
     * Graphics PicTail v3
     * Display TFT-G240320LTSW-118W-E
     ********************************************************************/
	//#include "Alternative Configurations\HardwareProfile_GFX_PICTAIL_V3_8PMP_PIC32_STK_SSD1926_TFT_G240320LTSW_118W_E.h"
	//#include "Alternative Configurations\HardwareProfile_GFX_PICTAIL_V3_16PMP_PIC32_STK_SSD1926_TFT_G240320LTSW_118W_E.h"

	//#include "Alternative Configurations\HardwareProfile_GFX_PICTAIL_V3_8PMP_PIC32_USB_STK_SSD1926_TFT_G240320LTSW_118W_E.h"
	//#include "Alternative Configurations\HardwareProfile_GFX_PICTAIL_V3_16PMP_PIC32_USB_STK_SSD1926_TFT_G240320LTSW_118W_E.h"

    /*********************************************************************
     * Hardware Configuration for 
     * Starter Kit
     * Graphics PicTail v3
     * Display PH480272T-005-I11Q
     ********************************************************************/
	//#include "Alternative Configurations\HardwareProfile_GFX_PICTAIL_V3_8PMP_PIC32_STK_SSD1926_PH480272T_005_I11Q.h"
	//#include "Alternative Configurations\HardwareProfile_GFX_PICTAIL_V3_16PMP_PIC32_STK_SSD1926_PH480272T_005_I11Q.h"
	
	//#include "Alternative Configurations\HardwareProfile_GFX_PICTAIL_V3_8PMP_PIC32_USB_STK_SSD1926_PH480272T_005_I11Q.h"
	//#include "Alternative Configurations\HardwareProfile_GFX_PICTAIL_V3_16PMP_PIC32_USB_STK_SSD1926_PH480272T_005_I11Q.h"
	
    /*********************************************************************
     * Hardware Configuration for 
     * Starter Kit
     * MultiMedia Development Board
     * Display TFT-G240320LTSW-118W-E
     ********************************************************************/
    //#include "Alternative Configurations\HardwareProfile_MULTI_MEDIA_BOARD_DM00123_16PMP_PIC32_STK_SSD1926_TFT_G240320LTSW_118W_E.h"
    //#include "Alternative Configurations\HardwareProfile_MULTI_MEDIA_BOARD_DM00123_16PMP_PIC32_USB_STK_SSD1926_TFT_G240320LTSW_118W_E.h"
    //#include "Alternative Configurations\HardwareProfile_MULTI_MEDIA_BOARD_DM00123_16PMP_PIC32_ENET_STK_SSD1926_TFT_G240320LTSW_118W_E.h"

    //#include "Alternative Configurations\HardwareProfile_MULTI_MEDIA_BOARD_DM00123_8PMP_PIC32_STK_SSD1926_TFT_G240320LTSW_118W_E.h"
    //#include "Alternative Configurations\HardwareProfile_MULTI_MEDIA_BOARD_DM00123_8PMP_PIC32_ENET_STK_SSD1926_TFT_G240320LTSW_118W_E.h"
    //#include "Alternative Configurations\HardwareProfile_MULTI_MEDIA_BOARD_DM00123_8PMP_PIC32_USB_STK_SSD1926_TFT_G240320LTSW_118W_E.h"

#endif

    
