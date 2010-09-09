//******************************************************************************
//
//
//
//
//
//
//******************************************************************************


// *****************************************************************************
// Description: Includes
// *****************************************************************************
#include "stm32f10x_lib.h"
#include "stdint.h"
#include "lcd.h"
#include "usart.h"
#include "fsmc_lcd.h"
#include "Graphics\Graphics.h"



// *****************************************************************************
// Description: Private defines
// *****************************************************************************
#define VECT_TAB_FLASH



// *****************************************************************************
// Description: Private variables
// *****************************************************************************

// *****************************************************************************
// Description: Private functions prototypes
// *****************************************************************************
extern void RCC_Configuration(void); 
extern void NVIC_Configuration(void);
extern void GPIO_Configuration(void);
extern void SysTick_Configuration(void);
extern void SysTick_Start(void);
extern void LCD_Init(void);

extern void LCD_GPIO_Configuration(void);

unsigned int sig=0;







// *****************************************************************************
// Function Name  : main
// Description    : Main program.
// Input          : None
// Output         : None
// Return         : None
// *****************************************************************************
int main(void)
{
#ifdef DEBUG
	debug();
#endif
	int i,j;
		WINDOW * wnd;
		BUTTON * btn;
		GOL_SCHEME *pScheme;


    //  System clock configuration
    RCC_Configuration();  
		  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);  
    // Nested Vector Interrupt Controller configuration
    NVIC_Configuration();   

		LCD_GPIO_Configuration();
		FSMC_LCD_Init();
		USART1_Init();
		ILI9325_Init();
		ILI9325_VerticalScreen();
		ILI9325_GRAMOperation();  //Tell ILI9325 that I'm now starting to write GRAM.
    for(i=0;i<240;i++)
    {
       for(j=0;j<320;j++)
       {
          unsigned int n=i*320+j;
          if(n<25600)
          { 
            ILI9325_WriteWDR(n);
          }   
    
          else if(n<51200)
          { 
            ILI9325_WriteWDR(n);
          }
    
          else if(n<76800)
          { 
            ILI9325_WriteWDR(0xf800);
          }
      } 
		}
			

		ILI9325_FillWindowArea(10,10,100,100,0x001f);

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



						    
    while(1)
    {

		}
		

		    
}



#ifdef  DEBUG
void assert_failed(u8* file, u32 line)
{ 
  	// User can add his own implementation to report the file name and line number,
  	//   ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line)

  	while (1)
  	{

  	}
}
#endif

// ******************************** END OF FILE ********************************

