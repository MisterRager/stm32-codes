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
#include "stdio.h"
#include "sdcard.h"
#include "../fat16/fat16.h"

// *****************************************************************************
// Description: Private defines
// *****************************************************************************
#define VECT_TAB_FLASH

#define BlockSize            512 /* Block Size in Bytes */
//#define BlockSize            128 /* Block Size in Bytes */
#define BufferWordsSize      (BlockSize >> 2)

#define NumberOfBlocks       2  /* For Multi Blocks operation (Read/Write) */
		u32 readBuffer[512>>2];
		int i;
		u8 wBuffer[512]={1,2,3,4,5,6,7,8,9,10,11,22,33,44,55,66,77,88,99,100,101,102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119};
		u32 * writeBuffer=(u32 *)wBuffer;
		uint32_t Buffer_Block_Tx[BufferWordsSize], Buffer_Block_Rx[BufferWordsSize];

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
unsigned long int jeffies=0;




void SD_ShowCID(SD_CardInfo* SDCardInfo)
{
				/*****************************************************************
			 *							SD_CID :Card IDentification Register.
			 *****************************************************************/
			//SD_CID register:128bits.
			//SD_CID[127:120]-->MID:8bits, binary number.
			printf("ManufacturerID:0x%x \n\r",SDCardInfo->SD_cid.ManufacturerID);	//1 byte ,binary
			//SD_CID[119:104]-->OID:16bits, two-character ascii string.
			printf("OEM_appliID:0x%x \n\r",SDCardInfo->SD_cid.OEM_AppliID);
			//SD_CID[103:64]-->PNM:40bits, five-character ascii string.
			printf("ProductName:%c%c%c%c%c \n\r",SDCardInfo->SD_cid.ProdName1>>24,SDCardInfo->SD_cid.ProdName1>>16,SDCardInfo->SD_cid.ProdName1>>8,SDCardInfo->SD_cid.ProdName1,SDCardInfo->SD_cid.ProdName2);
			//SD_CID[63:56]-->PRV:8bits, 2 BCD digits.
			printf("ProductVersion:	%d%d \n\r",SDCardInfo->SD_cid.ProdRev>>4,SDCardInfo->SD_cid.ProdRev&0x0f);
			//SD_CID[55:24]-->PSN:32bits, 32bits binary number.
			printf("ProductSerialNumber:%x \n\r",SDCardInfo->SD_cid.ProdSN);
			//SD_CID[23:20]-->Reserved:4bits.
			//SD_CID[19:8]-->MDT:12bits, 3 BCD digits:yym.
			printf("ManufactureDate:%x%x-%x \n\r",SDCardInfo->SD_cid.ManufactDate>>8&0x0f,SDCardInfo->SD_cid.ManufactDate>>4&0x0f,SDCardInfo->SD_cid.ManufactDate&0x0f);
			//SD_CID[7:1]-->CRC check sum.
			printf("CID_CRC:%x \n\r",SDCardInfo->SD_cid.CID_CRC);
			//SD_CID[0]-->Not used, always be one.
}

void SD_ShowCSD(SD_CardInfo *SDCardInfo)
{
			/*****************************************************************
			 *							SD_CSD :Card Specific Data register.
			 *****************************************************************/
			//SD_CSD register:128bits.
			//SD_CSD[127:126]-->CSD_Structure:2bits, 0--Version 1.0  1--Version 2.0 2,3---Reserved.
			printf("CSD Structure Version:%x\n\r",SDCardInfo->SD_csd.CSDStruct+1);
			if( SDCardInfo->SD_csd.CSDStruct+1==1)//Case V1.0
			{
				//SD_CSD[125:120]-->Reserved.
				//SD_CSD[119:112]-->TAAC:8bits,complicated.
				printf("Asynchronous access time:0x%x\n\r",SDCardInfo->SD_csd.TAAC);
				//SD_CSD[111:104]-->NSAC:8bits,complicated.
				printf("NSAC:0x%x",SDCardInfo->SD_csd.NSAC);
				//SD_CSD[103:96]-->TRAN_SPEED:8bits,0x32 or 0x5a.
				printf("Max data transfer rate:0x%x\n\r",SDCardInfo->SD_csd.MaxBusClkFrec);
				//SD_CSD[95:84]-->CCC:12bits,01x1 1011 0101b.
				printf("Card command classes:0x%x\n\r",SDCardInfo->SD_csd.CardComdClasses);
				//SD_CSD[83:80]-->READ_BL_LEN:4bits,9---512Bytes,10--1024Bytes,11--2048Bytes.
				printf("Max. read block length:%d\n\r",1<<SDCardInfo->SD_csd.RdBlockLen);
				//SD_CSD[79:79]-->READ_BL_PARTIAL:1bits, always 1 for SD Memory Card.
				printf("Partial block read allowed?...%d\n\r",SDCardInfo->SD_csd.PartBlockRead);
				//SD_CSD[78:78]-->WRITE_BLK_MISALIGN:1bits. 1 for allowed.
				printf("Write block misalignment allowed?...%d\n\r",SDCardInfo->SD_csd.WrBlockMisalign);
				//SD_CSD[77:77]-->READ_BLK_MISALIGN:1bits. 1 for allowed.
				printf("Read block misalignment allowed?...%d\n\r",SDCardInfo->SD_csd.RdBlockMisalign);
				//SD_CSD[76:76]-->DSR_IMP:1bits. 1 for DSR implemented.
				printf("DSR implemented?...%d\n\r",SDCardInfo->SD_csd.DSRImpl);
				//SD_CSD[75:74]-->Reserved:2bits.
				//SD_CSD[73:62]-->C_SIZE:12bits.
				printf("C_Size:%d\n\r",SDCardInfo->SD_csd.DeviceSize);
				//SD_CSD[61:59]-->VDD_R_CURR_MIN:3bits.
				printf("Max. read current@VDD min:0x%x\n\r",SDCardInfo->SD_csd.MaxRdCurrentVDDMin);
				//SD_CSD[61:59]-->VDD_R_CURR_MAX:3bits.
				printf("Max. read current@VDD max:0x%x\n\r",SDCardInfo->SD_csd.MaxRdCurrentVDDMax);
				//SD_CSD[55:53]-->VDD_W_CURR_MIN:3bits.
				printf("Max. write current@VDD min:0x%x\n\r",SDCardInfo->SD_csd.MaxWrCurrentVDDMin);
				//SD_CSD[52:50]-->VDD_W_CURR_MAX:3bits.
				printf("Max. write current@VDD max:0x%x\n\r",SDCardInfo->SD_csd.MaxWrCurrentVDDMax);
				//SD_CSD[49:47]-->C_SIZE_MULT:3bits.
				printf("Device size multiplier:%d\n\r",SDCardInfo->SD_csd.DeviceSizeMul);
				//SD_CSD[46:46]-->ERASE_BLK_EN:1bits.
				//printf("Erase single block enable?..%d\n\r",SDCardInfo->SD_csd.
				//SD_CSD[45:39]-->SECTOR_SIZE:7bits.	(by blocks)
				//printf("Sector size:%d blocks.\n\r",SDCardInfo->SD_csd.
				printf("Partial block write allowed?...%d\n\r",SDCardInfo->SD_csd.WriteBlockPaPartial);
				

			}
}


/////////////////////
/*
SD_Error SD_SetBlockLen(int size)
{
		SD_Error errorstatus = SD_OK;
    SDIO_CmdInitStructure.SDIO_Argument = (u32) (size);
    SDIO_CmdInitStructure.SDIO_CmdIndex = SDIO_SET_BLOCKLEN;
    SDIO_CmdInitStructure.SDIO_Response = SDIO_Response_Short;
    SDIO_CmdInitStructure.SDIO_Wait = SDIO_Wait_No;
    SDIO_CmdInitStructure.SDIO_CPSM = SDIO_CPSM_Enable;
    SDIO_SendCommand(&SDIO_CmdInitStructure);

    errorstatus = CmdResp1Error(SDIO_SET_BLOCKLEN);

    if (errorstatus != SD_OK)
    {
      return(errorstatus);
    }
}	*/
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

		u8 * pt;
		SD_CardInfo SDCardInfo;
		SD_Error Status = SD_OK;
    //  System clock configuration
    RCC_Configuration();    
    // Nested Vector Interrupt Controller configuration
    NVIC_Configuration();   
    // General Purpose I/O default configration
    GPIO_Configuration();
		SysTick_Configuration();
		SysTick_Start();
		//This revision temps to test SD card speed.
		printf("Initialize SD card first...\n");
		Status = SD_Init();
	  if (Status == SD_OK)
	  {
	    /*----------------- Read CSD/CID MSD registers ------------------*/
			printf("If SD card initialized, get card info.\n");
	    Status = SD_GetCardInfo(&SDCardInfo);
	  }
 
	  if (Status == SD_OK)
	  {
	    /*----------------- Select Card --------------------------------*/
			//printf("CSD:0x%x ,CID:0x%x, Capacity:%d,Blocksize:%d,RCA:0x%x,CardType:%d\n",SDCardInfo->SD_csd,SDCardInfo->SD_cid,SDCardInfo->CardCapacity,SDCardInfo->CardBlockSize,SDCardInfo->RCA,SDCardInfo->CardType);
			SD_ShowCID(&SDCardInfo);
			SD_ShowCSD(&SDCardInfo);
	    Status = SD_SelectDeselect((u32) (SDCardInfo.RCA << 16));
	  }

//		if (Status == SD_OK)
//  	{
//    	Status = SD_EnableWideBusOperation(SDIO_BusWide_1b);
//  	}

		if (Status == SD_OK)
  	{  
    	Status = SD_SetDeviceMode(SD_DMA_MODE);
			printf("In DMA mode.\n\r");
  	}
		if (Status == SD_OK)
		{
			SD_SetBlockLen(256);
			if( Status== SD_OK)
				printf("Block Length set to 16 bytes.\n\r");
		}	
	//	Status = SD_Erase(0x00, 10240);
		//Status = SD_WriteBlock(0x00, Buffer_Block_Tx, BlockSize);
		//Status = SD_WriteBlock(0x00, (u32 *)writeBuffer, 512);
		if (Status==SD_OK)
		{
  		printf("Read from 0x00~0x1f:\n\r");
			//Status=SD_WriteBlock(0<<9, (u32 *)writeBuffer, 32);
			Status=SD_ReadBlock(0x00, (u32 *)readBuffer, 32);
		}
		if(Status==SD_OK)
		{
			pt=(u8 *)readBuffer;
			for(i=0;i<32;i++)
			 printf("\t %d \t",*pt++);
		}
		printf("\n\r");
		if (Status==SD_OK)
		{
  		printf("Read from 0x20~0x3f:\n\r");
			//Status=SD_WriteBlock(0<<9, (u32 *)writeBuffer, 32);
			Status=SD_ReadBlock(0x20, (u32 *)readBuffer, 32);
		}
		if(Status==SD_OK)
		{
			pt=(u8 *)readBuffer;
			for(i=0;i<32;i++)
			 printf("\t %d \t",*pt++);
		}

		//////////////////////////////////////////
		//fat16 test
		{
			static u32 currSec;
			FAT_Init();
			FAT_Info();
			currSec = DirStartSec();
			List_AllDir_Long(currSec);
		}
    while(1)
    {	

    }
}
/////////////////////////////////////////////////////////////////////////////
/**************************************************************************/
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n))) 
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n))) 
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n))) 
#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC))) 
#define TRCENA          0x01000000 

struct __FILE { int handle; /* Add whatever you need here */ }; 
FILE __stdout; 
FILE __stdin; 
int fputc(int ch, FILE *f) { 
if (DEMCR & TRCENA) { 
while (ITM_Port32(0) == 0); 
ITM_Port8(0) = ch; 
  } 
return(ch); 
} 
/*******************************************************************************/
//////////////////////////////////////////////////////////////////////////////////

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

