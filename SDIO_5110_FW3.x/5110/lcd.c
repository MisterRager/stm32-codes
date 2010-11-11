/*
 *  lcd.c : Driver for Nokia3310/5110 LCD.
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

// Nokia3310 Һ����������
 #include "stm32f10x.h"
 #include "lcd.h"
 #include "spi.h"
 #include "delay.h"
 #include "enpix.h"
/*#################��mcu �йصĶ���   ��ʼ......################*/
void Init_LCDGpio( void )
{

	GPIO_InitTypeDef GPIO_InitStructure;
	/*----- Configure IO connected to lcm ---------------*/
	 /* ------Enable GPIO_lcm  clock --------------------------*/	

	RCC_APB2PeriphClockCmd( LCD_CTL, ENABLE );
	  
	GPIO_InitStructure.GPIO_Pin = LCD_SDIN | LCD_SCLK | LCD_DC | LCD_SCE ;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP ; 	//GPIO_Mode_Out_PP ;/*pull up input*/
	GPIO_InitStructure.GPIO_Speed = LCD_Speed ;
	GPIO_Init( LCD_CTL_Pins , &GPIO_InitStructure );
	GPIO_SetBits( LCD_CTL_Pins ,  LCD_SCLK | LCD_SDIN | LCD_DC | LCD_SCE );

	GPIO_InitStructure.GPIO_Pin = LCD_RST ;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP ; 	//GPIO_Mode_Out_PP ;/*pull up input*/
	GPIO_InitStructure.GPIO_Speed = LCD_Speed ;
	GPIO_Init( LCD_RESET_CTL_Pins , &GPIO_InitStructure );
	GPIO_SetBits( LCD_RESET_CTL_Pins ,   LCD_RST );

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10|GPIO_Pin_11 ;
	GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP ; 	//GPIO_Mode_Out_PP ;/*pull up input*/
	GPIO_InitStructure.GPIO_Speed = LCD_Speed ;
	GPIO_Init( GPIOG , &GPIO_InitStructure );
	GPIO_SetBits( GPIOG , GPIO_Pin_9 );
	GPIO_SetBits( GPIOG , GPIO_Pin_10 );
	GPIO_ResetBits( GPIOG , GPIO_Pin_11 );
		  
}

void LCD_Reset(void)
{
	GPIO_ResetBits( LCD_RESET_CTL_Pins ,   LCD_RST );
	Delaynus(1000);
	GPIO_SetBits( LCD_RESET_CTL_Pins ,   LCD_RST );
}
#if 1
void LCD_IODelay(u32 count)
{
	Delay(count);
}
#endif

void LCD_WDelay(  )
{
	Delay(4);
}
void LCD_RDelay(  )
{
	Delay(2);
}
/*--------------------------------------------------------
*�źŹܽŶ���
---------------------------------------------------------*/

void LCD_DC_HIGH(void) 	/*CD = H , send CMD  mode */
{

	GPIO_SetBits(LCD_CTL_Pins, LCD_DC );
		
}
void LCD_DC_LOW(void) 	/*CD =L , send DATA mode */
{

	GPIO_ResetBits(LCD_CTL_Pins, LCD_DC);
		
}

void  LCD_SDIN_HIGH(void) 	
{

	GPIO_SetBits(LCD_CTL_Pins, LCD_SDIN );
		
}
void  LCD_SDIN_LOW(void) 	/*read  lcm mode*/
{
	GPIO_ResetBits(LCD_CTL_Pins, LCD_SDIN);	
}

void  LCD_SCLK_HIGH(void )
{	

	GPIO_SetBits(LCD_CTL_Pins, LCD_SCLK );	
		
}
void  LCD_SCLK_LOW(void) /*write  lcm mode*/
{	

	GPIO_ResetBits(LCD_CTL_Pins, LCD_SCLK) ;	
		
}

void  LCD_SCE_HIGH(void) /*chip ; disable , select  lcm*/
{	

	GPIO_SetBits(LCD_CTL_Pins, LCD_SCE ) ;		

}
void  LCD_SCE_LOW() /*chip ; enable , select  lcm*/
{	
	
	GPIO_ResetBits(LCD_CTL_Pins, LCD_SCE) ;	

}

// ������λ����
static void LcdReset(void)
{

	GPIO_ResetBits( LCD_RESET_CTL_Pins ,   LCD_RST );
	Delaynus(500);
	GPIO_SetBits( LCD_RESET_CTL_Pins ,   LCD_RST );
}

// ʹ���źŴ���
// true : ʹ�� false : ��ֹ
static void LcdEnable(bool Enable)
{

	if( Enable == TRUE )
	 	 LCD_SCE_LOW();
	else           
		LCD_SCE_HIGH();	
	Delaynus(1);
}

// �������ݻ�ָ��
// DC : ���ݻ�ָ��
// info : ���͵���Ϣ
void LcdWriteDC(u8 DC, uint8_t info)
{
	LcdEnable(TRUE);
	
	if( DC == DATA)		
		LCD_DC_HIGH();
	else
		LCD_DC_LOW();	
	Delaynus(5);
	
	SpiSendByte(info);
	LcdEnable(FALSE);
}

// ��������
// Data : ���͵�����
static void LcdWriteData(uint8_t data)
{
	LcdWriteDC(DATA, data);
}

// ��������
// cmd : ���͵�����
static void LcdWriteCommand(uint8_t cmd)
{
	LcdWriteDC(COMMAND, cmd);
}

// ��������
// Power : ������(ACTIVE or POWERDOWN)
// Addr : ˮƽ��ֱѰַ(H_ADDR or V_ADDR)
// InsSet : ��������չָ�(BAS_INS or EXT_INS)
static void LcdFunctionSet(u8 Power, u8 Addr, u8 InsSet)
{
	LcdWriteCommand((1<<5) | (Power<<2) | (Addr<<1) | InsSet);
}

/*  ����ָ�  */

// ��ʾ����
// DE : DISPLAY_BLANK����ʾ�հף�;  DISPLAY_ALL����ʾȫ����;  
//		NORMAL_MODE����ͨģʽ��;  INVERSE_MODE����תģʽ��.
static void LcdDispalyControl(u8  DE)
{
	if((DE ==(uint8_t) DISPLAY_BLANK) || (DE == (uint8_t)DISPLAY_ALL) || (DE == (uint8_t)NORMAL_MODE) || (DE == (uint8_t)INVERSE_MODE))
		LcdWriteCommand( (1<<3) | DE);	
	//else
	//	return;
	
}

// ����Y��ַ
// Addr : �Դ�Y��ַ 0~5
static void LcdSetYAddress(uint8_t Addr)
{
	if(Addr > 5)
		return;

	LcdWriteCommand((1<<6) | Addr);
}

// ����X��ַ
// Addr : �Դ�X��ַ 0~83
static void LcdSetXAddress(uint8_t addr)
{
	if(addr > 83)
		return;
	
	LcdWriteCommand((1<<7) | addr);
}

/*  ��չָ�  */

// �����¶�ϵ��
// TC : �¶�ϵ�� 0~3
static void LcdTempCtrl(uint8_t TC)
{
	if(TC > 0x03)
		return;
	
	LcdWriteCommand(_BV(2) | TC);
}

// ƫ��ϵͳ
// BS : ƫ��ϵͳ 0~7
static void LcdBiasSystem(uint8_t BS)
{
	if(BS > 0x07)
		return;

	LcdWriteCommand(_BV(4) | BS);
}

// ���ò�����ѹ
// Vop : ������ѹ 0~0x7f
static void LcdSetVop(uint8_t Vop)
{
	if(Vop > 0x7f)
		return;
	
	LcdWriteCommand(_BV(7) | Vop);
}

// ����λ��
// x : �Դ�X��ַ 0~83
// y : �Դ�Y��ַ 0~5
static void LcdSetLocation(uint8_t x, uint8_t y)
{
	LcdSetYAddress(y) ,
	LcdSetXAddress(x);
}

//�����Ļ
void LcdClsScr(void)
{	
	u16 i;
	//LcdSetLocation(0, 0);	
	LcdWriteDC(LCDCMD , 0x80);
	for ( i=0; i<(LCD_ROW*LCD_COL); i++)
		LcdWriteData(0x00);	
}

// ��ʼ��

void LcdInit(void)
{
	//������ų�ʼ��
	Init_LCDGpio();
	SpiInit();  //SPI��ʼ��
	
	LCD_SCLK_LOW();
	LCD_SCLK_HIGH();
	
	LCD_SDIN_LOW();
	LCD_SDIN_HIGH();
	
	LCD_DC_LOW();
	LCD_DC_HIGH();
	
	LCD_SCE_LOW();
	LCD_SCE_HIGH();
	
	LcdReset();  /*Һ����λ*/
   
	//LcdFunctionSet(ACTIVE, H_ADDR, EXT_INS);	/*��չָ�*/	
	LcdBiasSystem(0x03);	/*�Ƽ������ 1:48*/	
	LcdSetVop(0x32);		/*V(6.06) = 3.06 + 0.06*Vop*/
	LcdTempCtrl(0x00);		/*�¶�ϵ�� 0~3*/	
	LcdFunctionSet(ACTIVE, H_ADDR, BAS_INS);	/*����ָ�*/
	LcdDispalyControl((u8)NORMAL_MODE);		/*��ͨģʽ��ʾ*/
	//
	LcdWriteDC(LCDCMD , 0x21 ); /*��չָ��*/
	LcdWriteDC(LCDCMD , 0xc8 ); /*����ƫѹ*/
	LcdWriteDC(LCDCMD , 0x20 ); /*��׼ָ��*/
	LcdWriteDC(LCDCMD , 0x0c );/*��׼��ʾģʽ*/
	LcdClsScr();        
}

// �滭λͼ
// x : xλ��
// y : yλ��
// pBmp : λͼ
// row : λͼ����
// col : λͼ����
void LcdDrawBitmap(uint8_t x, uint8_t y, uint8_t *pBmp, uint8_t col, uint8_t row)
{
			uint8_t i,j;
	if((col > 84) || (row > 6))
		return;
	
	for ( i=0; i<row; i++)
	{

		LcdSetLocation(x, y);
		for( j=0; j<col; j++)
			LcdWriteData(*(pBmp+i*col+j));
		y++;
	}
}

// ���λͼ
// x : xλ��
// y : yλ��
// row : λͼ����
// col : λͼ����
void LcdEraseBitmap(uint8_t x, uint8_t y, uint8_t col, uint8_t row)
{
		uint8_t i,j;
	if((col > 84) || (row > 6))
		return;
	
	for ( i=0; i<row; i++)
	{
		LcdSetLocation(x, y);
		for( j=0; j<col; j++)
			LcdWriteData(0);
		y++;
	}
}

// ���Ӣ���ַ�
// x : xλ��
// y : yλ��
// c : Ӣ���ַ�
static void LcdPutEnChar(uint8_t x, uint8_t y, uint8_t c)
{
	u8 tch  = c , n;
	if((tch< 32) || (tch >= (32+NUMBER_OF_CHARACTER)))
		return;
	
	tch -= 0x20;	
	LcdSetLocation(x, y);
	
	for ( n=0; n<LCD_ROW; n++)
          LcdWriteData( EnPix[ tch ][ n] );
}

// ��������ַ�
// x : xλ��
// y : yλ��
// c : �����ַ�
//static void LcdPutCnChar(uint8_t x, uint8_t y, u16 c)
//{
//		uint8_t i,j;
//	uint8_t k = 0;
//	//for(k=0; k<sizeof(CnPix)/34; k++)
//        {
//		//if((u16 *)(CnPix + k*34)) == c)
//			//break;
//        }
//
//	if(k == sizeof(CnPix)/34)
//		return;
//
//	for( i=0; i<2; i++)
//	{
//		LcdSetLocation(x, y++);
//		for( j=0; j<16; j++)
//			LcdWriteData( *(CnPix+k*34+2+16*i+j) );
//	}
//}

// ����ַ���
// x : �Դ�X��ַ 0~83
// y : �Դ�Y��ַ 0~5
// str : �ַ���
void LcdPutString(uint8_t x, uint8_t y, const char *str)
{
	uint8_t *p = (uint8_t *)str;

	while(*p != 0)
	{
		if(*p < 128)
		{
			LcdPutEnChar(x, y, *p);
			x += 6;
			p++;
		}
		else
		{
//			LcdPutCnChar(x, y, *(u16 *)p);
			x += 16;			
			p += 2;
		}
	}
}
