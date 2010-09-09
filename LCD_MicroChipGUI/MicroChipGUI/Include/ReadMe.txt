1. Copy this Include directory from Include directory in MicroChip.
2. Delete all subdirectories except Graphics.
3. Copy HardwareProfile.h and GraphicsConfig.h from MicroChip/Graphics/GDD/Default_Template.
4. Make a dummy GDD_GraphicsConfig.h within the directory.
5. Comment line 113 out in file Compiler.h
6. Insert into line 103 the following content:
	  #elif (DISPLAY_CONTROLLER == ILI9325)
		#include "Graphics/drvILI9325.h"
7. Comment out line 64 and 65 in GenericTypeDefs.h and add behind it:
#define BOOL bool
#define BIT 	 FlagStatus

Add header file "stm32f10x_type.h"
   This is done to avoid conflict with stm32 firmware lib. 
8. Comment out line 143 and 144 in Graphics/Primitive.h and rewrite it as :
        #define FLASH_BYTE  char 
        #define FLASH_WORD  short 
9. Comment and rewrite line 119 in the same file as:
	FLASH_   = 0,            // internal flash
10.Comment and rewrite other "FLASH" to "FLASH_" in Primitive.c, nominations are:
line 2274
line 2213
line 1972
line 1931
line 1853
line 1681
line 1515
and line 105
	procedure 8 through 10 are also for avoiding conflicts with stm32 fireware lib.
11. Comment and rewrite line 958 in Graphics/GOL.h
	void GOLInit(); ->void GOLInit(void);
	This is done for Armcc compiler's need.
12. Add file Graphics/drvILI9325.h
13. Uncomment USE_BUTTON and USE_WINDOW in GraphicsConfig.h
14. Comment the following out at about line 810:
                if(GOLMsgCallback(translatedMsg, pCurrentObj, pMsg))
                    BtnMsgDefault(translatedMsg, (BUTTON *)pCurrentObj, pMsg);
                break;
and at about line 820:
//                GOLMsgCallback(translatedMsg, pCurrentObj, pMsg);

