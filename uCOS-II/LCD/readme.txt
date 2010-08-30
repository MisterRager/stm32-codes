To use lcd based on ILI9325, take to following precedure:
1. Enable FSMC. You can do this by using the following line of code:
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
2. Configure GPIO Ports and FSMC. To do this, you can:
	include LCD_IOCFG.c 
	call LCD_GPIO_Configuration
	call LCD_FSMC_Configuration
3. Initialize ILI9325 by calling "ILI9325_Init", and turn on the backlight using LCD_BackLightOn(). Be sure to include LCD_ILI9325.h before doing that.
4. Now you can call functions we offer, again, you should've included LCD_ILI9325.h before that:
	ILI9325_FillWindowArea(10,10,200,200,0xf800); //this will draw a red rect on your screen.