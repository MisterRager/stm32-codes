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
u8  			SystemID;	   				// ��������
u32 			RelativeSectors; 			// ������ʼ��������ָ��������ڼ�¼�÷����ķ����������λ��֮�� (�÷�����LBA=0x0)��
u32 			TotalSectors;				// ������������

u8           	BUFFER[512];      			// 512�ֽڵĻ�����
u16          	ClusterNum;
FATFileIndex    FileIndex;        			// ��ǰ�򿪵��ļ�
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
extern u16 		UnicodeToGB2312(u16 unicode);	// �ö��ֲ����㷨
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

	//������ز���
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
	//������ز���
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
		   if(RAM[j] == 0x00)//�ձմ�
		      size += BPB_SecPerClus * BPB_BytesPerSec;
		}
	}
	return size;
}

/*******************************************************************************
* Function Name  : GetFileName
* Description    : Get the file name 
* Input          : secAddr--ָ��Ҫ���ļ�������������ַ
				   secNumOff--ָ�����������ƫ��	
				   persecdirOff--ָ��������Ŀ¼���ƫ��
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
	if(persecdirOff == 0)	 //�����ļ����������ĵ�һĿ¼��ʱ��������Ҫ����һĿ¼�����ж��Ƿ��г��ļ�������Ҫ���⴦��
	{
		ReadBlock(secAddr + secNumOff - 1);
		if( BUFFER[15 * 32 + 0xB] == 0x0F) //���ļ��г��ļ���
			persecdirOff = 16;//����һ���������һ��Ŀ¼�ʼ�������ļ���Ŀ¼���ǵ����������У�
	    else 
    		ReadBlock(secAddr + secNumOff);//���ļ��޳�������Ҫ����ԭ�����������ļ���
	}
	if( BUFFER[(persecdirOff - 1) * 32 + 0xB] == 0x0F) //���ļ��г��ļ���
	{
		k = persecdirOff;
		while(1)
		{
	        ID = (DIR*)(&BUFFER[(k - 1) * 32]);

			//�ӳ��ļ�Ŀ¼���ж�ȡ�ļ�����ÿ����Ŀ¼��3��������  
    		for(i = 0x1 ; i <=  0xA; i+=2)
			{
			   tmp = *(((u8 *)ID) + i) + (*(((u8 *)ID) + i + 1) << 8);
			   GB2312 = UnicodeToGB2312(tmp); //����Ӧ��Unicode��ת��ΪGB2312��
	  		   if(((GB2312 & 0xFF00) != 0) && ((GB2312 & 0xFF00) != 0xFF00))//ȥ��0��FF
    		      filename[(*len)++] = (GB2312 & 0xFF00) >> 8;
    		   if(((GB2312 & 0x00FF) != 0) && ((GB2312 & 0x00FF) != 0x00FF))
    		      filename[(*len)++] = (GB2312 & 0x00FF);
			}
    		for(i = 0xE ; i <=  0x19; i+=2)
			{
			   tmp = *(((u8 *)ID) + i) + (*(((u8 *)ID) + i + 1) << 8);
			   GB2312 = UnicodeToGB2312(tmp); //����Ӧ��Unicode��ת��ΪGB2312��
	  		   if(((GB2312 & 0xFF00) != 0) && ((GB2312 & 0xFF00) != 0xFF00))//ȥ��0��FF
    		      filename[(*len)++] = (GB2312 & 0xFF00) >> 8;
    		   if(((GB2312 & 0x00FF) != 0) && ((GB2312 & 0x00FF) != 0x00FF))
    		      filename[(*len)++] = (GB2312 & 0x00FF);
			}
            for(i = 0x1C ; i <=  0x1F; i+=2)
			{
			   tmp = *(((u8 *)ID) + i) + (*(((u8 *)ID) + i + 1) << 8);
			   GB2312 = UnicodeToGB2312(tmp); //����Ӧ��Unicode��ת��ΪGB2312��
	  		   if(((GB2312 & 0xFF00) != 0) && ((GB2312 & 0xFF00) != 0xFF00))//ȥ��0��FF
    		      filename[(*len)++] = (GB2312 & 0xFF00) >> 8;
    		   if(((GB2312 & 0x00FF) != 0) && ((GB2312 & 0x00FF) != 0x00FF))
    		      filename[(*len)++] = (GB2312 & 0x00FF);
			}
			if(k > 0)
			{
				if( ((BUFFER[(k - 1) * 32]) & 0x40) != 0)  //�Ѿ����ﳤ�ļ��������һ��Ŀ¼��
				    break;
				k--;	   
			}
			else if(k == 0)	 //�������Ѷ��꣬��Ҫ����һ����
			{
			    ReadBlock(secAddr + secNumOff - 1);
				k = 16;//����һ���������һ��Ŀ¼�ʼ�������ļ���Ŀ¼���ǵ����������У�
			}
		}
	}	
	else //�޳��ļ���
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
		if(j >= 8)//����չ������¼����
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
	ReadBlock(secAddr + secNumOff);	 //��������BUFFER�����ݿ����б仯������ڷ���ʱӦ��ԭ
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
   	//��ȡ����
   	tmp = ID->FileUpdateData[0] + (ID->FileUpdateData[1] <<8);
   	year = ((tmp & 0xFE00) >>9) + 1980;
   	month = (tmp & 0x01E0) >>5;
   	date = (tmp & 0x001F);
   	printf("%4u-%02u-%02u", year, month, date);
   	//��ȡʱ��
   	tmp = ID->FileUpdateTime[0] + (ID->FileUpdateTime[1] <<8) ;
   	hour = (tmp & 0xF800) >>11;
   	minite = (tmp & 0x07E0) >>5;
   	second = (tmp & 0x001F) * 2;
   	printf("   %02u:%02u:%02u", hour, minite, second);
	if(ID->FileAttrib & 0x10)//��Ŀ¼
    	printf("    <DIR>     ");
	else //�ļ�
		printf("              ");
}

/*******************************************************************************
* Function Name  : SearchFoler
* Description    : ��ָ����������������ַΪdirAddr��������Ŀ¼���в�����Ŀ¼���ļ� 
* Input          : dirAddr--��������ַ
				   foldername--Ŀ¼���ļ���
				   namelen--Ŀ¼���ļ�������
				   type--1:��ʾ�ҵ��ļ���0����ʾ�ҵ���Ŀ¼
* Output         : None
* Return         : ��Ŀ¼���ļ�����������
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
	cluster = LBAConvClus(dirAddr);	//��������ת��Ϊ�غ�
	while(1)
	{ //����һ��Ŀ¼���ռ�õĿռ䲻ֻһ���أ�Ҳ���Խ��
    	dirAddr = ClusConvLBA(cluster);	//���غ�תΪ������
      	for(i = 0; i < BPB_SecPerClus; i++)
    	{
    	    ReadBlock(dirAddr + i);	
    		for(m = 0; m < 16; m++)
    		{
    		    if(BUFFER[m * 32] != 0x00 && BUFFER[m * 32] != 0xE5  && BUFFER[m * 32 + 0xB] != 0x0F && (BUFFER[m * 32 + 0xB] & 0x10 ) && type)  
    			//����Ϊ��Ŀ¼��
     			{
     				ID = (DIR*)(&BUFFER[m * 32]);
    				GetFileName(dirAddr, i, m, filename, &len);
    				if(len != namelen) //�����ļ������Ȳ��ȣ�ֱ������
    				    continue;
    				if(IsEqual(foldername, filename, len))//�ļ�����ȣ���ȡ����������
    				{
    				    cluster = BUFFER[m * 32 + 0x1A] + (BUFFER[m * 32 + 0x1B] << 8);//�����
    					if(cluster == 0)
    	    			   return  ClusConvLBA(1) ;	  //�����Ŀ¼��ת��Ϊ����������
    			 		else
    	    			   return ( ClusConvLBA(cluster))	;  //�����ת��Ϊ�����Ų�����
    		 		}
    			}
    		    else if(BUFFER[m * 32] != 0x00 && BUFFER[m * 32] != 0xE5  && BUFFER[m * 32 + 0xB] != 0x0F && (!(BUFFER[m * 32 + 0xB] & 0x10 )) && (!type))  
    			//����Ϊ�ļ���
     			{
     				ID = (DIR*)(&BUFFER[m * 32]);
    				GetFileName(dirAddr, i, m, filename, &len);
    				if(len != namelen) //�����ļ������Ȳ��ȣ�ֱ������
    				    continue;
    				if(IsEqual(foldername, filename, len))//�ļ�����ȣ���ȡ����������
    				{
    				    cluster = BUFFER[m * 32 + 0x1A] + (BUFFER[m * 32 + 0x1B] << 8);//�����
                        FAT_FileOpen(ClusConvLBA(cluster));//��ʼ��FATFileIndex�ṹ
						 //�����ļ�����
						return (  BUFFER[m * 32 + 0x1c]+ (BUFFER[m * 32 + 0x1c + 1] << 8) + (BUFFER[m * 32 + 0x1c + 2]<< 16)  + (BUFFER[m * 32 + 0x1c + 3]<< 24))	; 
    		 		}
    			}				
    		}
    	}
		cluster = ReadFAT(cluster);
        if(cluster != 0x00 && cluster < 0xFFF0);  //����һ����
        else if( cluster <= 0xFFFF && cluster >= 0xFFF8) //���һ����
            break;
		else if (cluster  <= 0xFFF7 && cluster >= 0xFFF0) //���ػ���ֵ
		    return 0;
	}
	return 0;
}

/*******************************************************************************
* Function Name  : List_AllDir_Long
* Description    : �г�ָ�������ͳ��ȣ�������Ϊ��λ��������Ŀ¼��Ϣ 
* Input          : dirAddr--��������ַ
* Output         : None
* Return         : None
*******************************************************************************/
//�г�ָ�������ͳ��ȣ�������Ϊ��λ��������Ŀ¼��Ϣ��dirAddrΪ������ַ
void List_AllDir_Long(u32 dirAddr)
{
    u16 i, m;
	DIR *ID;
	u8 tmp;
	u8 filename[256];
	u8 len;
    u16 cluster ;
	cluster = LBAConvClus(dirAddr);	//��������ת��Ϊ�غ�
	while(1)
	{ //����һ��Ŀ¼���ռ�õĿռ䲻ֻһ���أ�Ҳ���Խ��
		dirAddr = ClusConvLBA(cluster);	//���غ�תΪ������
		for(i = 0; i < BPB_SecPerClus; i++)	//��һ������ѭ��,ÿ��������BPB_SecPerClus(8~32)������.
		{
		    ReadBlock(dirAddr + i);	
			for(m = 0; m < 16; m++)//��һ����������16��Ŀ¼��,�ڸ�Ŀ¼��32�ֽ�,��16*32=512
			{
			  if(BUFFER[m * 32] != 0x00 && BUFFER[m * 32] != 0xE5  && BUFFER[m * 32 + 0xB] != 0x0F)
				{	//ÿ��Ŀ¼���λ32(ʵ�����ǵ�0λ,0*32=0,1*32=32),Ŀ¼���ǰ�˸��ֽ�Ϊ�ļ���,������0�ֽ���0x00,�����
					//Ŀ¼��Ϊ��,��Ϊ0xE5,�����Ŀ¼��ù�,����ɾ��.��0xBλ��Ϊ0x0F,��Ϊ���ļ���.����ֻ�����ļ���.
      	  if((dirAddr + i * BPB_BytesPerSec ) ==  DirStartSec() && m == 0) //��Ŀ¼�����Դ�
					//�����ŵ��Ǿ��
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
		if(cluster != 0x00 && cluster < 0xFFF0);  //����һ����
        else if( cluster <= 0xFFFF && cluster >= 0xFFF8) //���һ����
            break;
		else if (cluster  <= 0xFFF7 && cluster >= 0xFFF0) //���ػ���ֵ
		    break;
	}
}

/*******************************************************************************
* Function Name  : FAT_FileOpen
* Description    : Open the file 
* Input          : firstSec--��������ַ
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
//��ȡ�ļ�������
void FAT_FileRead(u32 start,u32 length, u8* buff)
{
	u16 BytePerClus;//, ClusNum;
	u8 *data = buff;
	BytePerClus = BPB_SecPerClus * 512; // ÿ�ص��ֽ���

    if(length == 0)
	    return;	

	FileIndex.SecOff = (start % BytePerClus) / 512; //��ʼλ��������������ƫ��
	FileIndex.ByteOff = (start % BytePerClus) % 512; //��ʼλ��������ƫ��

	FileIndex.LBA = ClusConvLBA(FileIndex.ClusID) + FileIndex.SecOff; //��ʼλ�����ڵ�������
	
	ReadBlock(FileIndex.LBA); //Ԥ��ȡһ������������

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
            		FileIndex.ClusID = ReadFAT(FileIndex.ClusID); //��һ�شغ�
            		FileIndex.LBA = ClusConvLBA(FileIndex.ClusID);
            		FileIndex.SecOff = 0;
        		}
				//�����ȡ��ɾ��˳�
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
	printf("\n\rSystemID:0x%x\n\r",SystemID);	   				// ��������
	printf("RelativeSectorNO:0x%x\n\r",RelativeSectors); 			// ������ʼ��������ָ��������ڼ�¼�÷����ķ����������λ��֮�� (�÷�����LBA=0x0)��
	printf("TotalSectorNO:0x%x\n\r",TotalSectors);				// ������������
	printf("%d Secters Per Cluster.\n\r",BPB_SecPerClus);
	printf("%d Reserved Sectors.\n\r",BPB_RsvdSecCnt);
	printf("%d Fat Tables.\n\r",BPB_NumFATs);
	printf("%d Root Entries.\n\r",BPB_RootEntCnt);
	printf("%d Total Secters.\n\r",BPB_TotSec16);
	printf("FAT size:%d.\n\r",BPB_FATSz16);
	printf("%d Hidden Sectors.\n\r",BPB_HiddSec);
	printf("%d Bytes per sector.\n\r",BPB_BytesPerSec	);
}
