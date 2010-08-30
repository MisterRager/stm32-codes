#include "../Config.h"
#if ( USE_LCD==1 && LCD_ILI9325==1 )

#include "LCD_ILI9325.h"

#if ( USE_UCOS_II==1)
	#include "ucos_ii.h"
	#define Delay(nCount) OSTimeDly(nCount/7200+1)
#else
	#define Delay(nCount) RawDelay(nCount) 
#endif


void RawDelay(volatile uint32_t nCount)
{
  for(; nCount != 0; nCount--);
}


// ++++++++++++++++TFT ¸´Î»²Ù×÷
void LCD_Reset(void)
{
	GPIO_ResetBits(GPIOE, GPIO_Pin_1);
  Delay(72000);					   
  GPIO_SetBits(GPIOE, GPIO_Pin_1 );		 	 
}

/* Write to LCD index register */
void ILI9325_WriteIR(unsigned int index)
{
	*(volatile uint16_t *) (Bank1_LCD_C)= index;
}

/* write 16-bit  data */ 
void ILI9325_WriteWDR(unsigned int val)
{   
	*(volatile uint16_t *) (Bank1_LCD_D)= val; 	
}

/* write cmd through a two-transfer operation */
void ILI9325_SetRegister(unsigned int index,unsigned int val)
{	
	*(volatile uint16_t *) (Bank1_LCD_C)= index;	
	*(volatile uint16_t *) (Bank1_LCD_D)= val;
}

unsigned int ILI9325_ReadRDR(void)
{
	unsigned int a=0;
	a=*(volatile uint16_t *) (Bank1_LCD_D); //L
	return(a);	
}

void ILI9325_Init(void)
{
	unsigned int i;
	LCD_Reset();	 
	ILI9325_SetRegister(0x00E3, 0x3008); // Set internal timing
	ILI9325_SetRegister(0x00E7, 0x0012); // Set internal timing
	ILI9325_SetRegister(0x00EF, 0x1231); // Set internal timing
	ILI9325_SetRegister(0x0000, 0x0001); // Start Oscillation
	ILI9325_SetRegister(0x0001, 0x0100); // set SS and SM bit
	ILI9325_SetRegister(0x0002, 0x0700); // set 1 line inversion

	ILI9325_SetRegister(0x0003, 0x1018); // set GRAM write direction and BGR=0,262K colors,1 transfers/pixel.
	ILI9325_SetRegister(0x0004, 0x0000); // Resize register
	ILI9325_SetRegister(0x0008, 0x0e02); // set the back porch and front porch
	ILI9325_SetRegister(0x0009, 0x0000); // set non-display area refresh cycle ISC[3:0]
	ILI9325_SetRegister(0x000A, 0x0000); // FMARK function
	ILI9325_SetRegister(0x000C, 0x0000); // RGB interface setting
	ILI9325_SetRegister(0x000D, 0x0000); // Frame marker Position
	ILI9325_SetRegister(0x000F, 0x0000); // RGB interface polarity
//Power On sequence 
	ILI9325_SetRegister(0x0010, 0x0000); // SAP, BT[3:0], AP, DSTB, SLP, STB
	ILI9325_SetRegister(0x0011, 0x0007); // DC1[2:0], DC0[2:0], VC[2:0]
	ILI9325_SetRegister(0x0012, 0x0000); // VREG1OUT voltage
	ILI9325_SetRegister(0x0013, 0x0000); // VDV[4:0] for VCOM amplitude
	Delay(200); // Dis-charge capacitor power voltage
	ILI9325_SetRegister(0x0010, 0x1690); // SAP, BT[3:0], AP, DSTB, SLP, STB
	ILI9325_SetRegister(0x0011, 0x0227); // R11h=0x0221 at VCI=3.3V, DC1[2:0], DC0[2:0], VC[2:0]
	Delay(50); // Delay 50ms
	ILI9325_SetRegister(0x0012, 0x001C); // External reference voltage= Vci;
	Delay(50); // Delay 50ms
	ILI9325_SetRegister(0x0013, 0x1800); // R13=1200 when R12=009D;VDV[4:0] for VCOM amplitude
	ILI9325_SetRegister(0x0029, 0x001C); // R29=000C when R12=009D;VCM[5:0] for VCOMH
	ILI9325_SetRegister(0x002B, 0x000D); // Frame Rate = 91Hz
	Delay(50); // Delay 50ms
	ILI9325_SetRegister(0x0020, 0x0000); // GRAM horizontal Address
	ILI9325_SetRegister(0x0021, 0x0000); // GRAM Vertical Address
// ----------- Adjust the Gamma Curve ----------//
	ILI9325_SetRegister(0x0030, 0x0007);
	ILI9325_SetRegister(0x0031, 0x0302);
	ILI9325_SetRegister(0x0032, 0x0105);
	ILI9325_SetRegister(0x0035, 0x0206);
	ILI9325_SetRegister(0x0036, 0x0808);
	ILI9325_SetRegister(0x0037, 0x0206);
	ILI9325_SetRegister(0x0038, 0x0504);
	ILI9325_SetRegister(0x0039, 0x0007);
	ILI9325_SetRegister(0x003C, 0x0105);
	ILI9325_SetRegister(0x003D, 0x0808);
//------------------ Set GRAM area ---------------//
	ILI9325_SetRegister(0x0050, 0x0000); // Horizontal GRAM Start Address
	ILI9325_SetRegister(0x0051, 0x00EF); // Horizontal GRAM End Address
	ILI9325_SetRegister(0x0052, 0x0000); // Vertical GRAM Start Address
	ILI9325_SetRegister(0x0053, 0x013F); // Vertical GRAM Start Address
	ILI9325_SetRegister(0x0060, 0xA700); // Gate Scan Line
	ILI9325_SetRegister(0x0061, 0x0001); // NDL,VLE, REV
	ILI9325_SetRegister(0x006A, 0x0000); // set scrolling line
//-------------- Partial Display Control ---------//
	ILI9325_SetRegister(0x0080, 0x0000);
	ILI9325_SetRegister(0x0081, 0x0000);
	ILI9325_SetRegister(0x0082, 0x0000);
	ILI9325_SetRegister(0x0083, 0x0000);
	ILI9325_SetRegister(0x0084, 0x0000);
	ILI9325_SetRegister(0x0085, 0x0000);
//-------------- Panel Control -------------------//
	ILI9325_SetRegister(0x0090, 0x0010);
	ILI9325_SetRegister(0x0092, 0x0000);
	ILI9325_SetRegister(0x0093, 0x0003);
	ILI9325_SetRegister(0x0095, 0x0110);
	ILI9325_SetRegister(0x0097, 0x0000);
	ILI9325_SetRegister(0x0098, 0x0000);
	ILI9325_SetRegister(0x0007, 0x0133); // 262K color and display ON

  ILI9325_SetRegister(0x20, 0);
  ILI9325_SetRegister(0x21, 319);
	ILI9325_GRAMOperation();
	for(i=0;i<76800;i++)
	{
	  ILI9325_WritePixel(0x0000);
	}
				

}

void ILI9325_DrawWindowArea(unsigned int startX,unsigned int startY,
                            unsigned int width,unsigned int height,unsigned int pixels[])
{
	unsigned int i,j,n=0;
  
	ILI9325_SetRegister(0x20,startX);
	ILI9325_SetRegister(0x21,startY);   
  ILI9325_SetRegister(0x0050,startX); /* Start point X */ 
  ILI9325_SetRegister(0x0052,startY); /* Start point Y */ 
  ILI9325_SetRegister(0x0051,startX+width-1); /* End point X */  
  ILI9325_SetRegister(0x0053,startY+height-1);/* End point Y */
	ILI9325_GRAMOperation();

	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			ILI9325_WriteWDR(pixels[n++]);
		}
	} 
}

void ILI9325_FillWindowArea(unsigned int startX,unsigned int startY,
                            unsigned int width,unsigned int height,unsigned int pixel)
{
	unsigned int i,j;
  ILI9325_SetRegister(0x20,startX);
	ILI9325_SetRegister(0x21,startY);
	   
  ILI9325_SetRegister(0x0050,startX); /* Start point X */ 
  ILI9325_SetRegister(0x0052,startY); /* Start point Y */
  ILI9325_SetRegister(0x0051,startX+width-1); /* End point X */
  ILI9325_SetRegister(0x0053,startY+height-1); /* End point Y */

	ILI9325_GRAMOperation();

	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			ILI9325_WriteWDR(pixel);
		}
	} 
}

void ILI9325_SetCursorPos(unsigned int x ,unsigned int y)
{
	ILI9325_SetRegister(0x20,x);
	ILI9325_SetRegister(0x21,y);
}

#endif 




