/*******************************************************************************
*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#ifndef VS10XX_H
#define VS10XX_H
#include "stm32f10x.h"



/* Defines ------------------------------------------------------------------*/
#define VS_WRITE_COMMAND 	0x02
#define VS_READ_COMMAND 	0x03
#define SPI_MODE        	0x00   
#define SPI_STATUS      	0x01   
#define SPI_BASS        	0x02   
#define SPI_CLOCKF      	0x03   
#define SPI_DECODE_TIME 	0x04   
#define SPI_AUDATA      	0x05   
#define SPI_WRAM        	0x06   
#define SPI_WRAMADDR    	0x07   
#define SPI_HDAT0       	0x08   
#define SPI_HDAT1       	0x09   
#define SPI_AIADDR      	0x0a   
#define SPI_VOL         	0x0b   
#define SPI_AICTRL0     	0x0c   
#define SPI_AICTRL1     	0x0d   
#define SPI_AICTRL2     	0x0e   
#define SPI_AICTRL3     	0x0f   
#define SM_DIFF         	0x01   
#define SM_JUMP         	0x02   
#define SM_RESET        	0x04   
#define SM_OUTOFWAV     	0x08   
#define SM_PDOWN        	0x10   
#define SM_TESTS        	0x20   
#define SM_STREAM       	0x40   
#define SM_PLUSV        	0x80   
#define SM_DACT         	0x100   
#define SM_SDIORD       	0x200   
#define SM_SDISHARE     	0x400   
#define SM_SDINEW       	0x800   
#define SM_ADPCM        	0x1000   
#define SM_ADPCM_HP     	0x2000 


#define MP3CMD_InitVS1003		0x11
#define MP3CMD_Play				0x12
#define MP3CMD_Pause			0x13
#define MP3CMD_Stop				0x14
#define MP3CMD_Next				0x15
#define MP3CMD_TestVS1003		0x16


#define SCLK (1 << 5)						  	
#define MOSI (1 << 7)
#define MISO (1 << 6)

#define MP3_XRESET   			( 1 << 1 )
 
#define Mp3PutInReset()  		{ GPIOC->ODR &= ~MP3_XRESET; }
 
#define Mp3ReleaseFromReset() 	{ GPIOC->ODR |= MP3_XRESET; }
 
#define MP3_XCS  				( 1 << 4 )
 
#define Mp3SelectControl()  	{ GPIOA->ODR &= ~MP3_XCS; }
 
#define Mp3DeselectControl()  	{ GPIOA->ODR |= MP3_XCS; }
 
#define MP3_XDCS 				( 1 << 4 )

#define Mp3SelectData()			{ GPIOC->ODR &= ~MP3_XDCS; }

#define Mp3DeselectData()		{ GPIOC->ODR |= MP3_XDCS; }

#define MP3_DREQ 				( 1 << 2 )

#define VS_Start		0x01
#define VS_End			0x02
#define Mp3SetVolume(leftchannel,rightchannel){\
		Mp3WriteRegister(11,(leftchannel),(rightchannel));}		// 音量设置 
		
void VS1003_Config(void);		 
unsigned char  	SPIPutChar(unsigned char c);					// 通过SPI发送一个字节的数据
void  			Mp3SoftReset(void);								// vs1003的软件复位	
void  			Mp3Reset(void);
void VsRamTest(void);									// vs1003的硬件复位
void  			VsSineTest(void);								// vs1003的正弦测试
void  			Mp3WriteRegister(unsigned char addressbyte,unsigned char highbyte,unsigned char lowbyte); // 写vs1003寄存器
unsigned short 	Mp3ReadRegister(unsigned char addressbyte);		// 读vs1003寄存器
void 			Mp3MusicTest(void);
#endif
