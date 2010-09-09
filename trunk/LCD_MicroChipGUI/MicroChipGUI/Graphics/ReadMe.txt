1. Copy the same directory from MicroChip.
2. Delete all other directories except Drivers.
3. Insert into line 101 in DisplayDriver.c
	 #elif (DISPLAY_CONTROLLER == ILI9325)
		#include "Drivers/drvILI9325.c"
4. Add file Drivers/drvILI9325.c.
5. In GOL.c find(at about line 561):
    if(GOLDrawCallback())
        {
            // It's last object jump to head
            pCurrentObj = _pGolObjects;

            #ifdef USE_DOUBLE_BUFFERING
            if(DisplayUpdated)
            {
                RequestDisplayUpdate();
                DisplayUpdated = 0;
                return(0);
            }
            #endif //USE_DOUBLE_BUFFERING
        }
Modify it as:
    if(0)
        {
            // It's last object jump to head
            pCurrentObj = _pGolObjects;

            #ifdef USE_DOUBLE_BUFFERING
            if(DisplayUpdated)
            {
                RequestDisplayUpdate();
                DisplayUpdated = 0;
                return(0);
            }
            #endif //USE_DOUBLE_BUFFERING
        }
6. After you have done all the changes in this file and the ReadMe file in ../include, it's time to try it out. Go to you main.c:
1) Include the header file:
	#include "Graphics\Graphics.h"
2) Declarations:
		WINDOW * wnd;
		BUTTON * btn;
		GOL_SCHEME *pScheme;
3) Action:
		pScheme = GOLCreateScheme();


		wnd=WndCreate(0,                // ID
                         0,0,GetMaxX(),GetMaxY(),   // whole screen dimension
                         WND_DRAW,                  // set state to draw all
                         NULL,             // icon
                         "Place Title Here.",       // text
                         pScheme);                     // use default GOL scheme
		WndDraw(wnd);

		btn=BtnCreate(1,20,64,50,118,0, BTN_DRAW, NULL, "ON", pScheme);
		BtnDraw(btn);
The code above will draw a window and a button on you screen. OK! My instruction is over, but more work remains to be done before you can use all functions this GUI can offer. 		

