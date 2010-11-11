/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2007        */
/*-----------------------------------------------------------------------*/
/* by grqd_xp                                                            */
/* This is a stub disk I/O module that acts as front end of the existing */
/* disk I/O modules and attach it to FatFs module with common interface. */
/*-----------------------------------------------------------------------*/
#include <string.h>
#include "diskio.h"
#include "../sdio/sdcard.h"

/*-----------------------------------------------------------------------*/
/* Correspondence between physical drive number and physical drive.      */
/* Note that Tiny-FatFs supports only single drive and always            */
/* accesses drive number 0.                                              */

#define SECTOR_SIZE 512U

extern SD_CardInfo SDCardInfo;
u32 buff2[4096];//16384/4
/*-----------------------------------------------------------------------*/
/* Initialize a Drive                                                    */

DSTATUS disk_initialize (
                         BYTE drv				/* Physical drive nmuber (0..) */
                             )
{    
    //////////这个个地方最好什么都不干，一次SD_Init();会消耗8495/100000s
//    u8 state;
//
//    if(drv)
//    {
//        return STA_NOINIT;  //仅支持磁盘0的操作
//    }
//
//    state = SD_Init();
//    if(state == STA_NODISK)
//    {
//        return STA_NODISK;
//    }
//    else if(state != 0)
//    {
//        return STA_NOINIT;  //其他错误：初始化失败
//    }
//    else
//    {
//        return 0;           //初始化成功
//    }
	return 0;
}

/*-----------------------------------------------------------------------*/
/* Return Disk Status                                                    */

DSTATUS disk_status (
                     BYTE drv		/* Physical drive nmuber (0..) */
                         )
{	
    DSTATUS state = SD_OK;
//       u32 cmd = 1000000;
//       u32 cmd2 = 1000000;
       
    if(drv)
    {
        return STA_NOINIT;  //仅支持磁盘0操作
    }
//    cmd = SD_GetTransferState();
//    if(cmd==0) return SD_OK;
//    if(cmd==0x01) return STA_NODISK;
    
    //state = SD_SelectDeselect((uint32_t) (SDCardInfo.RCA << 16));

    //    SDIO_CmdInitTypeDef SDIO_CmdInitStructure_Diskio;
//    /* Send ACMD13 SD_APP_STAUS  with argument as card's RCA.*/
//    SDIO_CmdInitStructure_Diskio.SDIO_Argument = 0;
//    SDIO_CmdInitStructure_Diskio.SDIO_CmdIndex = 13;//SDIO_SD_APP_STAUS;
//    SDIO_CmdInitStructure_Diskio.SDIO_Response = SDIO_Response_Short;
//    SDIO_CmdInitStructure_Diskio.SDIO_Wait = SDIO_Wait_No;
//    SDIO_CmdInitStructure_Diskio.SDIO_CPSM = SDIO_CPSM_Enable;
//    SDIO_SendCommand(&SDIO_CmdInitStructure_Diskio);
//    cmd = SDIO_GetCommandResponse();
//    cmd2 = 2;
//    if(cmd == 0) return STA_NODISK;
//    if(cmd == 1) return STA_NODISK;
//    if(cmd == 0) return STA_NODISK;
//    if(cmd == 1) return STA_NODISK;
//    if(cmd == 0) return STA_NODISK;
//    if(cmd == 1) return STA_NODISK;
//    if(cmd == 0) return STA_NODISK;
//    if(cmd == 1) return STA_NODISK;
//    if(cmd == 0) return STA_NODISK;
//    if(cmd == 1) return STA_NODISK;
//    if(cmd == 0) return STA_NODISK;
//    if(cmd == 1) return STA_NODISK;
//    if(cmd == 0) return STA_NODISK;
//    if(cmd == 1) return STA_NODISK;
    
//    cmd2 = SDIO_GetFIFOCount();//SDIO_GetPowerState();
//    cmd = SDIO_GetResponse(SDIO_RESP1);
//    if((cmd2 == 0x00)&&(cmd == 0x00));//{return STA_NODISK;}
//    else if(cmd2 ==  0x02){return STA_NODISK;}
//    else if(cmd2 ==  SDIO_PowerState_ON){return STA_NODISK;}
        //* - 0x00: Power OFF
        //* - 0x02: Power UP
        //* - 0x03: Power ON 
//
//    cmd = SDIO_GetResponse(SDIO_RESP1);
//    if(cmd == 0x00)
//    {
//        return STA_NODISK;
//    }
//    
        //* - 0x00: Power OFF
//    if(cmd != 13) return STA_NODISK;//state = STA_NODISK;//SDIO_SD_APP_STAUS
        //state = CmdResp1Error(SDIO_SD_APP_STAUS);
//    
//        /* CMD0: GO_IDLE_STATE -------------------------------------------------------*/
//    /* No CMD response required */
//    SDIO_CmdInitStructure_Diskio.SDIO_Argument = 0x0;
//    SDIO_CmdInitStructure_Diskio.SDIO_CmdIndex = SDIO_GO_IDLE_STATE;
//    SDIO_CmdInitStructure_Diskio.SDIO_Response = SDIO_Response_No;
//    SDIO_CmdInitStructure_Diskio.SDIO_Wait = SDIO_Wait_No;
//    SDIO_CmdInitStructure_Diskio.SDIO_CPSM = SDIO_CPSM_Enable;
//    SDIO_SendCommand(&SDIO_CmdInitStructure_Diskio);
//    ///////从sdcard抄的私有函数
//    state = SD_OK;//CmdError();
//    //        SD_Error errorstatus = 
//    uint32_t timeout;
//    
//    timeout = 10000;//SDIO_CMD0TIMEOUT; /* 10000 */
//    
//    while ((timeout > 0) && (SDIO_GetFlagStatus(SDIO_FLAG_CMDSENT) == RESET))
//    {
//        timeout--;
//    }
//    
//    if (timeout == 0)
//    {
//        state = SD_CMD_RSP_TIMEOUT;
//        //return(errorstatus);
//    }
    
    /* Clear all the static flags */
//    SDIO_ClearFlag((uint32_t)0x000005FF);//(SDIO_STATIC_FLAGS);
//    
//    //return(errorstatus);
//    ///////从sdcard抄的私有函数
//    
//    //if(state != SD_OK) return state;
//    //else return 0;
//        SD_Error errorstatus = SD_OK;
//    uint32_t status;
//    
//    status = SDIO->STA;
//    
//    while (!(status & (SDIO_FLAG_CCRCFAIL | SDIO_FLAG_CMDREND | SDIO_FLAG_CTIMEOUT)))
//    {
//        status = SDIO->STA;
//    }
//    
//    if (status & SDIO_FLAG_CTIMEOUT)
//    {
//        errorstatus = SD_CMD_RSP_TIMEOUT;
//        SDIO_ClearFlag(SDIO_FLAG_CTIMEOUT);
//        return(errorstatus);
//    }
//    /* Clear all the static flags */
//    SDIO_ClearFlag((uint32_t)0x000005FF);//(SDIO_STATIC_FLAGS);
//    return(errorstatus);
    
    return state;
}

/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */

DRESULT disk_read (
                   BYTE drv,		/* Physical drive nmuber (0..) */
                   BYTE *buff,		/* Data buffer to store read data */
                   DWORD sector,	/* Sector address (LBA) */
                   BYTE count		/* Number of sectors to read (1..255) */
                       )
{
    //    memset(buff2, 0, sizeof(buff2));
	if(count==1)
    {
        SD_ReadBlock(sector << 9, buff2, SECTOR_SIZE);
        memcpy(buff, buff2, SECTOR_SIZE);
	}
	else
    {
        SD_ReadMultiBlocks(sector << 9, buff2, SECTOR_SIZE, count);
        memcpy(buff, buff2, SECTOR_SIZE * count);
	}
	return RES_OK;
}


/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */

#if _READONLY == 0
DRESULT disk_write (
                    BYTE drv,			/* Physical drive nmuber (0..) */
                    const BYTE *buff,	/* Data to be written */
                    DWORD sector,		/* Sector address (LBA) */
                    BYTE count			/* Number of sectors to write (1..255) */
                        )
{
    //    memset(buff2, 0, sizeof(buff2));
	if(count==1)
    {
        memcpy(buff2, buff, SECTOR_SIZE);
        SD_WriteBlock(sector << 9, buff2, SECTOR_SIZE);
	}
	else
    {
        memcpy(buff2, buff, SECTOR_SIZE * count);
        SD_WriteMultiBlocks(sector << 9, buff2, SECTOR_SIZE, count);
	}
    
    return RES_OK;
}
#endif /* _READONLY */

/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */

DRESULT disk_ioctl (
                    BYTE drv,		/* Physical drive nmuber (0..) */
                    BYTE ctrl,		/* Control code */
                    void *buff		/* Buffer to send/receive control data */
                        )
{

    DRESULT res;

    if (drv)
    {    
        return RES_PARERR;  //仅支持单磁盘操作，否则返回参数错误
    }
//    2010.02.16  23：35 完成此模块。
    switch(ctrl)
    {
    case CTRL_SYNC:

        while(SDIO_GetResponse(SDIO_RESP1)==0);//(SD_WaitReady
//        {
            res = RES_OK;
//        }
//        else
//        {
//            res = RES_ERROR;
//        }
        break;
    case GET_SECTOR_SIZE:
        *(WORD*)buff = 512;
        res = RES_OK;
        break;
    case GET_SECTOR_COUNT:
        if((SDCardInfo.CardType == SDIO_STD_CAPACITY_SD_CARD_V1_1) || (SDCardInfo.CardType == SDIO_STD_CAPACITY_SD_CARD_V2_0))
            *(DWORD*)buff = SDCardInfo.CardCapacity >> 9;
        else if(SDCardInfo.CardType == SDIO_HIGH_CAPACITY_SD_CARD)
            *(DWORD*)buff = (SDCardInfo.SD_csd.DeviceSize+1)*1024;
        //else;////SD_GetCapacity();
        res = RES_OK;
        break;
    case GET_BLOCK_SIZE:
        *(WORD*)buff = SDCardInfo.CardBlockSize;
        res = RES_OK;
        break;

    default:
        res = RES_PARERR;
        break;
    }
    return res;//RES_OK;//
}


/*******************************************************************************
* Function Name  : get_fattime
* Description    : Displays the current time.
* Input          : - TimeVar: RTC counter value.
* Output         : None
* Return         : None
*******************************************************************************/
#define SecsPerComYear  31536000//(365*3600*24)
#define SecsPerLeapYear 31622400//(366*3600*24)
#define SecsPerFourYear 126230400//((365*3600*24)*3+(366*3600*24))
#define SecsPerDay      86400   //(3600*24)

s32 Year_Secs_Accu[5] = {0,31622400,63158400,94694400,126230400};
s32 Month_Secs_Accu_C[13] = {0,2678400,5097600,7776000,10368000,13046400,15638400,18316800,20995200,23587200,26265600,28857600,31536000};
s32 Month_Secs_Accu_L[13] = {0,2678400,5184000,7862400,10454400,13132800,15724800,18403200,21081600,23673600,26352000,28944000,31622400};

DWORD get_fattime(void){
	DWORD CurrentTime = 0;
#if 1
    u32 RTCMount = 0;
    u32 TY = 0, TM = 1, TD = 1, THH = 0, TMM = 0, TSS = 0;
    s32 Num4Y = 0, NumY = 0, OffSec = 0, Off4Y = 0, NumDay = 0;//OffDay;
#endif
    u32 i = 0;
    RTCMount = RTC_GetCounter();
    Num4Y = RTCMount/SecsPerFourYear;//有多少个整四年
    OffSec = RTCMount%SecsPerFourYear;//除了整四年，剩下多少秒
    i = 1;
    while(OffSec > Year_Secs_Accu[i++])
        Off4Y++;//除了整四年还有几年，OffSec作用1
            
    /* Numer of Complete Year */
    NumY = Num4Y*4 + Off4Y;
    TY = NumY << 25;//得到年份 bit31:25 Year from 1980 (0..127) 
            
    OffSec = OffSec - Year_Secs_Accu[i-2];//不足一年的月份共有多少秒，OffSec作用2
            
    /* Month (TBD with OffSec)*/
    i = 0;
    if(Off4Y != 0)
    {// common year
        while(OffSec > Month_Secs_Accu_C[i++]);
        TM = i-1;
        OffSec = OffSec - Month_Secs_Accu_C[i-2];//不足一月的天共有多少秒，OffSec作用3
    }
    else
    {// leap year
        while(OffSec > Month_Secs_Accu_L[i++]);
        TM = i-1;
        OffSec = OffSec - Month_Secs_Accu_L[i-2];
    }
    TM = TM << 21;//bit24:21 Month (1..12) 
 
    /* Date (TBD with OffSec) */
    NumDay = OffSec/SecsPerDay;
    TD = (NumDay+1) << 16;//bit20:16 Day in month(1..31)
    
    OffSec = OffSec%SecsPerDay;//不到一天的时间里还剩多少秒，OffSec作用34
        
    /* Compute  hours */
    THH = (OffSec/3600) << 11;//bit15:11 Hour (0..23) 
    /* Compute minutes */
    TMM = ((OffSec % 3600)/60) << 5;//bit10:5 Minute (0..59)
    /* Compute seconds */
    TSS = ((OffSec % 3600)% 60) >> 1;//bit4:0 Second / 2 (0..29) 
    
    CurrentTime = TY + TM + TD + THH + TMM + TSS;
    return CurrentTime;
}
