			  /* Includes ------------------------------------------------------------------*/

#include "FAT16.h"
#include "../source/sdcard.h"
#include "stdio.h"

/* Global declare -------------------------------------------------------------*/
typedef __packed struct
{
	u16 ByteOff;
	u16 ClusID;
	u32 SecOff;
	u32 LBA;
	u32 HaveReadByte;
} FATFileIndex;
u8  			SystemID;	   				// 分区类型
u32 			RelativeSectors; 			// 分区起始扇区数，指分区相对于记录该分区的分区表的扇区位置之差 (该分区表：LBA=0x0)。
u32 			TotalSectors;				// 分区总扇区数

u8           	BUFFER[512];      			// 512字节的缓冲区
u16          	ClusterNum;
FATFileIndex    FileIndex;        			// 当前打开的文件
u8          	BPB_SecPerClus;
u16          	BPB_RsvdSecCnt;
u8           	BPB_NumFATs;
u16          	BPB_RootEntCnt;
u16          	BPB_TotSec16;
u16          	BPB_FATSz16;
u32          	BPB_HiddSec;
u16          	BPB_BytesPerSec	;

/* Fuction declare ------------------------------------------------------------*/
void 			ReadBlock (u32 LBA);
u8 				IsEqual (void* A, void* B, u8 Size);
void 			ReadMBR (void);
void 			ReadBPB (void);
u32 			ClusConvLBA (u16 ClusID);
u16 			LBAConvClus(u32 LBA);
u16 			ReadFAT (u16 Index);
void 			GetFileName(u32 secAddr, u16 secNumOff, u8 persecdirOff, u8 filename[], u8 *len);

/* Extern declare -------------------------------------------------------------*/
extern u16 		UnicodeToGB2312(u16 unicode);	// 用二分查找算法
extern u8 		MSD_ReadBlock(u8* pBuffer, u32 ReadAddr, u16 NumByteToRead);

/* Function define ------------------------------------------------------------*/

/*******************************************************************************
* Function Name  : FAT_Init
* Description    : Init the FAT16 File System.
* Input          : Mone
* Output         : None
* Return         : None
*******************************************************************************/
void FAT_Init(void)
{
	ReadMBR();
	ReadBPB();
}

/*******************************************************************************
* Function Name  : ReadBlock
* Description    : Read a block from the sd card
* Input          : LBA--the sd card address
* Output         : None
* Return         : None
*******************************************************************************/
static void ReadBlock(u32 LBA)
{
	SD_ReadBlock(LBA*512,(u32 *)BUFFER,512);
}

/*******************************************************************************
* Function Name  : IsEqual
* Description    : Compare the two strings
* Input          : A--one string,B--the other string
* Output         : None
* Return         : 0-- not equal, 1--equal
*******************************************************************************/
static u8 IsEqual(void* A, void* B, u8 Size)
{
	u8 i, *a = A, *b = B;
	for(i = 0; i < Size; i++)
		if(a[i] != b[i])
			return 0;
	return 1;
}

/*******************************************************************************
* Function Name  : ReadMBR
* Description    : Read the sd card's first block--MBR
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void ReadMBR(void)
{	
	MBR_tag* MBR = (MBR_tag*)BUFFER;
	ReadBlock(0);

	//缓存相关参数
	SystemID		=  MBR->PT[0].SystemID;
	RelativeSectors =  MBR->PT[0].RelativeSectors;
	TotalSectors	=  MBR->PT[0].TotalSectors;
}

/*******************************************************************************
* Function Name  : ReadBPB
* Description    : Read BPB struct
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void ReadBPB(void)
{	
	FAT_BPB* BPB = (FAT_BPB*)BUFFER;
	ReadBlock(RelativeSectors);
	//缓存相关参数
	BPB_SecPerClus  =  BPB->BPB_SecPerClus;
	BPB_RsvdSecCnt  =  BPB->BPB_RsvdSecCnt;
	BPB_NumFATs     =  BPB->BPB_NumFATs;
	BPB_RootEntCnt  =  BPB->BPB_RootEntCnt;
	BPB_TotSec16    =  BPB->BPB_TotSec16;
	BPB_FATSz16     =  BPB->BPB_FATSz16;
	BPB_HiddSec     =  BPB->BPB_HiddSec;
	BPB_BytesPerSec =  BPB->BPB_BytesPerSec;
}

/*******************************************************************************
* Function Name  : DirStartSec
* Description    : Get the root directory's sector No.  
* Input          : None
* Output         : None
* Return         : Root directory's sector No. 
*******************************************************************************/
u32 DirStartSec(void)
{
	return RelativeSectors + BPB_RsvdSecCnt + BPB_NumFATs * BPB_FATSz16;
}

/*******************************************************************************
* Function Name  : DataStartSec
* Description    : Get the data area's start sector NO.  
* Input          : None
* Output         : None
* Return         : The data area's start sector NO. 
*******************************************************************************/
static u32 DataStartSec(void)
{
	return DirStartSec() + BPB_RootEntCnt * 32 / 512;
}

/*******************************************************************************
* Function Name  : ClusConvLBA
* Description    : Get one cluster's first sector NO.  
* Input          : The cluster's NO.
* Output         : None
* Return         : The cluster's first sector NO.
*******************************************************************************/
static u32 ClusConvLBA(u16 ClusID)
{
	return DataStartSec() + BPB_SecPerClus * (ClusID - 2);
}

/*******************************************************************************
* Function Name  : LBAConvClus
* Description    : Convert from sector NO. to cluster NO. 
* Input          : The cluster's NO.
* Output         : None
* Return         : The cluster NO.
*******************************************************************************/
static u16 LBAConvClus(u32 LBA)
{
	return (LBA - DataStartSec()) / BPB_SecPerClus + 2;
}

/*******************************************************************************
* Function Name  : ReadFAT
* Description    : Read the value of FAT table 
* Input          : The FAT table's index
* Output         : None
* Return         : The value of assigned FAT index
*******************************************************************************/
static u16 ReadFAT(u16 Index)
{
	u16 *RAM = (u16*)BUFFER;
	ReadBlock(RelativeSectors + BPB_RsvdSecCnt + Index / 256);
	return RAM[Index % 256];
}

/*******************************************************************************
* Function Name  : CalcuFreeSpace
* Description    : Calculate the free space 
* Input          : None
* Output         : None
* Return         : The free space num(in bytes)
*******************************************************************************/
u32 CalcuFreeSpace()
{
    u32 size;
	u16 i, j;
	u16 *RAM = (u16*)BUFFER;
	size = 0;
	//BPB_FATSz16
	for(i = 0 ; i < BPB_FATSz16 ; i++)
	{
	    ReadBlock(RelativeSectors + BPB_RsvdSecCnt + i);
		for(j = 0; j < 256; j++)
		{
		   if(RAM[j] == 0x00)//空闭簇
		      size += BPB_SecPerClus * BPB_BytesPerSec;
		}
	}
	return size;
}

/*******************************************************************************
* Function Name  : GetFileName
* Description    : Get the file name 
* Input          : secAddr--指所要找文件名的首扇区地址
				   secNumOff--指相对首扇区的偏移	
				   persecdirOff--指在扇区内目录项的偏移
				   filename[]--the file name
				   len--the file name length
* Output         : None
* Return         : None
*******************************************************************************/
void GetFileName(u32 secAddr, u16 secNumOff, u8 persecdirOff, u8 filename[], u8 *len)	
{
    u8 i,k;
	DIR *ID;
	u16 tmp ,GB2312;
	signed char j;
	*len = 0;
	if(persecdirOff == 0)	 //当短文件名在扇区的第一目录项时，由于需要以上一目录项来判断是否有长文件名，需要特殊处理
	{
		ReadBlock(secAddr + secNumOff - 1);
		if( BUFFER[15 * 32 + 0xB] == 0x0F) //该文件有长文件名
			persecdirOff = 16;//从上一扇区的最后一个目录项开始读（长文件的目录项是倒放在扇区中）
	    else 
    		ReadBlock(secAddr + secNumOff);//该文件无长名，需要返回原来扇区读短文件名
	}
	if( BUFFER[(persecdirOff - 1) * 32 + 0xB] == 0x0F) //该文件有长文件名
	{
		k = persecdirOff;
		while(1)
		{
	        ID = (DIR*)(&BUFFER[(k - 1) * 32]);

			//从长文件目录项中读取文件名，每个长目录分3个区域存放  
    		for(i = 0x1 ; i <=  0xA; i+=2)
			{
			   tmp = *(((u8 *)ID) + i) + (*(((u8 *)ID) + i + 1) << 8);
			   GB2312 = UnicodeToGB2312(tmp); //将对应的Unicode码转化为GB2312码
	  		   if(((GB2312 & 0xFF00) != 0) && ((GB2312 & 0xFF00) != 0xFF00))//去掉0和FF
    		      filename[(*len)++] = (GB2312 & 0xFF00) >> 8;
    		   if(((GB2312 & 0x00FF) != 0) && ((GB2312 & 0x00FF) != 0x00FF))
    		      filename[(*len)++] = (GB2312 & 0x00FF);
			}
    		for(i = 0xE ; i <=  0x19; i+=2)
			{
			   tmp = *(((u8 *)ID) + i) + (*(((u8 *)ID) + i + 1) << 8);
			   GB2312 = UnicodeToGB2312(tmp); //将对应的Unicode码转化为GB2312码
	  		   if(((GB2312 & 0xFF00) != 0) && ((GB2312 & 0xFF00) != 0xFF00))//去掉0和FF
    		      filename[(*len)++] = (GB2312 & 0xFF00) >> 8;
    		   if(((GB2312 & 0x00FF) != 0) && ((GB2312 & 0x00FF) != 0x00FF))
    		      filename[(*len)++] = (GB2312 & 0x00FF);
			}
            for(i = 0x1C ; i <=  0x1F; i+=2)
			{
			   tmp = *(((u8 *)ID) + i) + (*(((u8 *)ID) + i + 1) << 8);
			   GB2312 = UnicodeToGB2312(tmp); //将对应的Unicode码转化为GB2312码
	  		   if(((GB2312 & 0xFF00) != 0) && ((GB2312 & 0xFF00) != 0xFF00))//去掉0和FF
    		      filename[(*len)++] = (GB2312 & 0xFF00) >> 8;
    		   if(((GB2312 & 0x00FF) != 0) && ((GB2312 & 0x00FF) != 0x00FF))
    		      filename[(*len)++] = (GB2312 & 0x00FF);
			}
			if(k > 0)
			{
				if( ((BUFFER[(k - 1) * 32]) & 0x40) != 0)  //已经到达长文件名的最后一个目录项
				    break;
				k--;	   
			}
			else if(k == 0)	 //该扇区已读完，需要读上一扇区
			{
			    ReadBlock(secAddr + secNumOff - 1);
				k = 16;//从上一扇区的最后一个目录项开始读（长文件的目录项是倒放在扇区中）
			}
		}
	}	
	else //无长文件名
	{
        ID = (DIR*)(&BUFFER[persecdirOff * 32]);
		j = 7;
		while( ID->FileName[j--] == 0x20);
		j++;
	 	while(j >= 0)
		{	   
		   filename[j] = ID->FileName[j];
		   (*len)++;
		   j--;
		}
		j = 10;
		while( ID->FileName[j--] == 0x20);
		j++;		    
		if(j >= 8)//有扩展名，记录下来
		{
		   filename[(*len)++] = '.';
	       if(ID->FileName[8] != 0x20)
    		   filename[(*len)++] = ID->FileName[8]; 
		   if(ID->FileName[9] != 0x20)
	    	   filename[(*len)++] = ID->FileName[9]; 
		   if(ID->FileName[10] != 0x20)
	    	   filename[(*len)++] = ID->FileName[10];
		}
	}
	ReadBlock(secAddr + secNumOff);	 //由于这里BUFFER的内容可能有变化，因此在返回时应复原
}

/*******************************************************************************
* Function Name  : List_DateAndTime
* Description    : List the file's date and time 
* Input          : ID-- director items
* Output         : None
* Return         : None
*******************************************************************************/
void List_DateAndTime(DIR * ID)	
{
    u8 month = 0, date = 0, hour = 0 , minite = 0, second = 0;
	u16 tmp = 0 , year = 0;
   	//获取日期
   	tmp = ID->FileUpdateData[0] + (ID->FileUpdateData[1] <<8);
   	year = ((tmp & 0xFE00) >>9) + 1980;
   	month = (tmp & 0x01E0) >>5;
   	date = (tmp & 0x001F);
   	printf("%4u-%02u-%02u", year, month, date);
   	//获取时间
   	tmp = ID->FileUpdateTime[0] + (ID->FileUpdateTime[1] <<8) ;
   	hour = (tmp & 0xF800) >>11;
   	minite = (tmp & 0x07E0) >>5;
   	second = (tmp & 0x001F) * 2;
   	printf("   %02u:%02u:%02u", hour, minite, second);
	if(ID->FileAttrib & 0x10)//子目录
    	printf("    <DIR>     ");
	else //文件
		printf("              ");
}

/*******************************************************************************
* Function Name  : SearchFoler
* Description    : 在指定扇区（首扇区地址为dirAddr）的所有目录项中查找子目录或文件 
* Input          : dirAddr--首扇区地址
				   foldername--目录或文件名
				   namelen--目录或文件名长度
				   type--1:表示找到文件，0：表示找到子目录
* Output         : None
* Return         : 子目录或文件的首扇区号
*******************************************************************************/

u32 SearchFoler(u32 dirAddr, u8 foldername[], u8 namelen, u8 type)
{  
    u16 cluster ;
    u32 i;//totalSec, i;
    u8 m ;
	DIR *ID;
	u8 filename[256];
	u8 len ;
    if(namelen == 0)
	   return 0;
	cluster = LBAConvClus(dirAddr);	//将扇区号转化为簇号
	while(1)
	{ //这里一个目录如果占用的空间不只一个簇，也可以解决
    	dirAddr = ClusConvLBA(cluster);	//将簇号转为扇区号
      	for(i = 0; i < BPB_SecPerClus; i++)
    	{
    	    ReadBlock(dirAddr + i);	
    		for(m = 0; m < 16; m++)
    		{
    		    if(BUFFER[m * 32] != 0x00 && BUFFER[m * 32] != 0xE5  && BUFFER[m * 32 + 0xB] != 0x0F && (BUFFER[m * 32 + 0xB] & 0x10 ) && type)  
    			//该项为子目录名
     			{
     				ID = (DIR*)(&BUFFER[m * 32]);
    				GetFileName(dirAddr, i, m, filename, &len);
    				if(len != namelen) //两个文件名长度不等，直接跳过
    				    continue;
    				if(IsEqual(foldername, filename, len))//文件名相等，读取其首扇区号
    				{
    				    cluster = BUFFER[m * 32 + 0x1A] + (BUFFER[m * 32 + 0x1B] << 8);//首族号
    					if(cluster == 0)
    	    			   return  ClusConvLBA(1) ;	  //到达根目录，转化为扇区并返回
    			 		else
    	    			   return ( ClusConvLBA(cluster))	;  //将族号转化为扇区号并返回
    		 		}
    			}
    		    else if(BUFFER[m * 32] != 0x00 && BUFFER[m * 32] != 0xE5  && BUFFER[m * 32 + 0xB] != 0x0F && (!(BUFFER[m * 32 + 0xB] & 0x10 )) && (!type))  
    			//该项为文件名
     			{
     				ID = (DIR*)(&BUFFER[m * 32]);
    				GetFileName(dirAddr, i, m, filename, &len);
    				if(len != namelen) //两个文件名长度不等，直接跳过
    				    continue;
    				if(IsEqual(foldername, filename, len))//文件名相等，读取其首扇区号
    				{
    				    cluster = BUFFER[m * 32 + 0x1A] + (BUFFER[m * 32 + 0x1B] << 8);//首族号
                        FAT_FileOpen(ClusConvLBA(cluster));//初始化FATFileIndex结构
						 //返回文件长度
						return (  BUFFER[m * 32 + 0x1c]+ (BUFFER[m * 32 + 0x1c + 1] << 8) + (BUFFER[m * 32 + 0x1c + 2]<< 16)  + (BUFFER[m * 32 + 0x1c + 3]<< 24))	; 
    		 		}
    			}				
    		}
    	}
		cluster = ReadFAT(cluster);
        if(cluster != 0x00 && cluster < 0xFFF0);  //有下一个簇
        else if( cluster <= 0xFFFF && cluster >= 0xFFF8) //最后一个簇
            break;
		else if (cluster  <= 0xFFF7 && cluster >= 0xFFF0) //坏簇或保留值
		    return 0;
	}
	return 0;
}

/*******************************************************************************
* Function Name  : List_AllDir_Long
* Description    : 列出指定扇区和长度（以扇区为单位）的所有目录信息 
* Input          : dirAddr--首扇区地址
* Output         : None
* Return         : None
*******************************************************************************/
//列出指定扇区和长度（以扇区为单位）的所有目录信息，dirAddr为扇区地址
void List_AllDir_Long(u32 dirAddr)
{
    u16 i, m;
	DIR *ID;
	u8 tmp;
	u8 filename[256];
	u8 len;
    u16 cluster ;
	cluster = LBAConvClus(dirAddr);	//将扇区号转化为簇号
	while(1)
	{ //这里一个目录如果占用的空间不只一个簇，也可以解决
		dirAddr = ClusConvLBA(cluster);	//将簇号转为扇区号
		for(i = 0; i < BPB_SecPerClus; i++)	//在一个簇里循环,每个簇里有BPB_SecPerClus(8~32)个扇区.
		{
		    ReadBlock(dirAddr + i);	
			for(m = 0; m < 16; m++)//在一个扇区内有16个目录项,第个目录项32字节,共16*32=512
			{
			  if(BUFFER[m * 32] != 0x00 && BUFFER[m * 32] != 0xE5  && BUFFER[m * 32 + 0xB] != 0x0F)
				{	//每个目录项的位32(实际上是第0位,0*32=0,1*32=32),目录项的前八个字节为文件名,但若第0字节是0x00,则表明
					//目录项为空,若为0xE5,则表明目录项被用过,但己删除.第0xB位若为0x0F,则为长文件名.这里只处理长文件名.
      	  if((dirAddr + i * BPB_BytesPerSec ) ==  DirStartSec() && m == 0) //根目录项，区别对待
					//这里存放的是卷号
					{
					    printf("Driver Name Is: ");
							GetFileName(dirAddr, i, m, filename, &len);
					    for(tmp = 0; tmp < len; tmp++)
    					    printf("%c",filename[tmp]);
		   		 		printf("\r\n");
						continue;
					}

					ID = (DIR*)(&BUFFER[m * 32]);
				    List_DateAndTime(ID);
					GetFileName(dirAddr, i, m, filename, &len);
					for(tmp = 0; tmp < len; tmp++)
					    printf("%c",filename[tmp]);
					printf("\r\n");
				}
			}
		}
		cluster = ReadFAT(cluster);
		if(cluster != 0x00 && cluster < 0xFFF0);  //有下一个簇
        else if( cluster <= 0xFFFF && cluster >= 0xFFF8) //最后一个簇
            break;
		else if (cluster  <= 0xFFF7 && cluster >= 0xFFF0) //坏簇或保留值
		    break;
	}
}

/*******************************************************************************
* Function Name  : FAT_FileOpen
* Description    : Open the file 
* Input          : firstSec--首扇区地址
* Output         : None
* Return         : None
*******************************************************************************/
void FAT_FileOpen(u32 firstSec)
{
	FileIndex.HaveReadByte = 0;
	FileIndex.ClusID = LBAConvClus(firstSec);
}

/*******************************************************************************
* Function Name  : FAT_FileRead
* Description    : Read the file content 
* Input          : start--the file offset
				   length--the length to read
				   buff--save the read content
* Output         : None
* Return         : None
*******************************************************************************/
//读取文件的数据
void FAT_FileRead(u32 start,u32 length, u8* buff)
{
	u16 BytePerClus;//, ClusNum;
	u8 *data = buff;
	BytePerClus = BPB_SecPerClus * 512; // 每簇的字节数

    if(length == 0)
	    return;	

	FileIndex.SecOff = (start % BytePerClus) / 512; //开始位置所在扇区簇内偏移
	FileIndex.ByteOff = (start % BytePerClus) % 512; //开始位置扇区内偏移

	FileIndex.LBA = ClusConvLBA(FileIndex.ClusID) + FileIndex.SecOff; //开始位置所在的扇区号
	
	ReadBlock(FileIndex.LBA); //预读取一个扇区的内容

	goto FAT_FileRead_Start;

	while(1)
	{ 
		while(FileIndex.SecOff < BPB_SecPerClus)
		{
			ReadBlock(FileIndex.LBA);
			FileIndex.ByteOff = 0;
FAT_FileRead_Start:
			while(FileIndex.ByteOff < 512)
			{
				*data++ = BUFFER[FileIndex.ByteOff];
				FileIndex.ByteOff++;
				FileIndex.HaveReadByte++;
	 		    if(FileIndex.HaveReadByte % BytePerClus == 0)
        	    {
            		FileIndex.ClusID = ReadFAT(FileIndex.ClusID); //下一簇簇号
            		FileIndex.LBA = ClusConvLBA(FileIndex.ClusID);
            		FileIndex.SecOff = 0;
        		}
				//如果读取完成就退出
				if(--length == 0)
				   return;
			}
			FileIndex.LBA++;
			FileIndex.SecOff++;
		}
	}
}

/////////////////////////////////
void FAT_Info(void)
{
	printf("\n\rSystemID:0x%x\n\r",SystemID);	   				// 分区类型
	printf("RelativeSectorNO:0x%x\n\r",RelativeSectors); 			// 分区起始扇区数，指分区相对于记录该分区的分区表的扇区位置之差 (该分区表：LBA=0x0)。
	printf("TotalSectorNO:0x%x\n\r",TotalSectors);				// 分区总扇区数
	printf("%d Secters Per Cluster.\n\r",BPB_SecPerClus);
	printf("%d Reserved Sectors.\n\r",BPB_RsvdSecCnt);
	printf("%d Fat Tables.\n\r",BPB_NumFATs);
	printf("%d Root Entries.\n\r",BPB_RootEntCnt);
	printf("%d Total Secters.\n\r",BPB_TotSec16);
	printf("FAT size:%d.\n\r",BPB_FATSz16);
	printf("%d Hidden Sectors.\n\r",BPB_HiddSec);
	printf("%d Bytes per sector.\n\r",BPB_BytesPerSec	);
}
