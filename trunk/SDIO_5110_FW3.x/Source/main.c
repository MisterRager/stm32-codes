/**
******************************************************************************
* @file SDIO/main.c 
* @author  MCD Application Team
* @version  V3.0.0
* @date  04/06/2009
* @brief  Main program body
******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "../sdio/sdcard.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "integer.h"
#include "../filesystem/ff.h"
#include "../filesystem/diskio.h"
#include "../5110/lcd.h"
#include "../5110/delay.h"

#define buffsize 512
u8  fileBuff[buffsize];
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
SD_CardInfo SDCardInfo;//在底层函数diskio.c调用了
SD_Error Status = SD_OK;
//////////////////////////////////////////
//filessystem
FATFS fs;           // Work area (file system object) for logical drive
FIL fsrc, fdst;     // file objects
FRESULT res;        // FatFs function common result code
UINT br, bw;        // File R/W count
FILINFO fi;         // File information

/* Private function prototypes -----------------------------------------------*/
void RCC_Configuration(void);
void GPIO_Configuration_Main(void);
void NVIC_Configuration(void);
void SDCard_Configuration(void);
/* Private functions ---------------------------------------------------------*/
/////////////////////////////////////////////////////////////////////////////
/*********************ITM_Viewer***************************************/
#define ITM_Port8(n)	(*((volatile unsigned char *)(0xE0000000+4*n))) 
#define ITM_Port16(n)	(*((volatile unsigned short*)(0xE0000000+4*n))) 
#define ITM_Port32(n)	(*((volatile unsigned long *)(0xE0000000+4*n))) 
#define DEMCR			(*((volatile unsigned long *)(0xE000EDFC))) 
#define TRCENA			0x01000000 

struct __FILE { int handle; /* Add whatever you need here */ }; 
FILE __stdout; 
FILE __stdin; 
int fputc(int ch, FILE *f)
{ 
	if (DEMCR & TRCENA)
	{ 
		while (ITM_Port32(0) == 0);
		ITM_Port8(0) = ch; 
	}
	return(ch);
}	

int main(void)
{
	/* Clock Config */
	RCC_Configuration();
	/* Configure the GPIO ports */
	//GPIO_Configuration_Main();
	/* Interrupt Config */
	NVIC_Configuration();
	///////////////// SDCARD Initialisation ////
//	SDCard_Configuration();
//	res = f_open(&fsrc, "a.txt", FA_OPEN_ALWAYS | FA_WRITE |FA_READ);
//	if(res==FR_OK)
//		printf("File opened successfully.\n\r");
//	else 
//	{
//		printf("File open error.\n\r");
//		return 1;
//	}
//	printf("****************File Start***************\n\r");
//	while(f_read(&fsrc, fileBuff, buffsize,&br)==FR_OK)
//	{
//		printf("\n\r%s\n\r",fileBuff);
//		if(br!=buffsize)
//			break;
//	}
//	printf("****************File End*****************\n\r");
//	if(f_close(&fsrc)==FR_OK)
//		printf("\n\rFile closed.\n\r");
	LcdInit();
	while(1)
	{	
		LcdWriteDC(COMMAND , 0x0c );	/*标准显示模式*/
		//	LcdDrawBitmap(0, 0, (uint8_t *)logo, 80, 6);  //画一个接近全屏的位图
		LcdPutString(0, 0, "Nokia 5110 LCD");  //在位图的左上方覆盖英文字符
		LcdPutString(0, 1, "--0123456789--");  //在位图的左上方覆盖英文字符
		LcdPutString(0, 2, "--9876543210--");  //在位图的左上方覆盖英文字符
		LcdPutString(0, 3, "--0123456789--");  //在位图的左上方覆盖英文字符
		LcdPutString(0, 4, "--9876543210--");
		LcdPutString(0, 5, "--0123456789--");
		Delaynus(1000000);
		
		LcdWriteDC(COMMAND , 0x0d);   /*反显*/
		Delaynus(1000000);
	}
}

/**
* @brief  Configures the different system clocks.
* @param  None
* @retval : None
*/
void RCC_Configuration(void)
{
    /* Setup the microcontroller system. Initialize the Embedded Flash Interface,
    initialize the PLL and update the SystemFrequency variable. */
    SystemInit();
    
    /* Enable GPIOA and USART1 clocks */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOD |RCC_APB2Periph_GPIOG | RCC_APB2Periph_USART1, ENABLE);//GPIO A B C取决于USART 1 2 3
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    /* TIM2 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    /* TIM4 clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
    /* Enable PWR and BKP clocks */
    //RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);//因为模块化所以放在RTC_Configuration
}



void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
#ifdef	VECT_TAB_RAM  
	/* Set the Vector Table base location at 0x20000000 */ 
	NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
#else  /* VECT_TAB_FLASH  */
	/* Set the Vector Table base location at 0x08000000 */ 
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);	
#endif
	
	/* Configure the NVIC Preemption Priority Bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	/*SDIO*/
	NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void SDCard_Configuration(void)
{
	int i;
	for( i=0;i<109500;i++);//延时等待电容充电5760，21900//为保证多一点的板子同时脸上的时候有效就设定的大一点21900*5
	/*-------------------------- SD Init ----------------------------- */
	Status = SD_Init();
	//disk_initialize(0);//选择磁盘,这句包括上面的SD_Init();所以只需要这一次
	if (Status == SD_OK)
	{
		/*----------------- Read CSD/CID MSD registers ------------------*/
		Status = SD_GetCardInfo(&SDCardInfo); 
		/*----------------- Select Card --------------------------------*/
		Status = SD_SelectDeselect((uint32_t) (SDCardInfo.RCA << 16));
		/* Set Device Transfer Mode to 4b */
		Status = SD_EnableWideBusOperation(SDIO_BusWide_1b);
		/* Set Device Transfer Mode to DMA */
		Status = SD_SetDeviceMode(SD_DMA_MODE);
		//Status = SD_SetDeviceMode(SD_POLLING_MODE);
		//Status = SD_SetDeviceMode(SD_INTERRUPT_MODE);
	}
	res = f_mount(0,&fs);
	if(res==FR_OK)
		printf("\n\rFile system mounted.\n\r");
	else printf("Error mounting file system.\n\r");
}

/*******************************************************************************
* Function Name  : GPIO_Configuration
* Description    : Configures the different GPIO ports.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void GPIO_Configuration_Main(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	/* Configure GPIO(PD.00 PD.01 PD.02 PD.03) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;		//IN_FLOATING;IPU上拉电阻 
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	/* Configure GPIOD pin 10 11 as Output push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}


#ifdef  USE_FULL_ASSERT
/**
* @brief  Reports the name of the source file and the source line number
*   where the assert_param error has occurred.
* @param file: pointer to the source file name
* @param line: assert_param error line source number
* @retval : None
*/
void assert_failed(uint8_t* file, uint32_t line)
{
    /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
    
    /* Infinite loop */
    while (1)
    {}
}

#endif

/**
* @}
*/

/**
* @}
*/

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
