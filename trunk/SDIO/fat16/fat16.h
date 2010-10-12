#ifndef _FAT_H_65226575624
#define _FAT_H_65226575624

#define USE_FAT                         1
#define FAT_READ_ONLY                   1	 

typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;

typedef __packed struct 
{
	u8 			BootFlag; 			//启动标志
	u8 			StartCHS[3]; 		//分区开始的柱面、磁头、扇区
	u8 			SystemID; 			//分区类型
	u8 			EndCHS[3]; 			//分区结束的柱面、磁头、扇区
	u32 		RelativeSectors; 	//分区起始扇区数，指分区相对于记录该分区的分区表的扇区位置之差 (该分区表：LBA=0x0)。
	u32 		TotalSectors;		//分区总扇区数
} PartitionTable;

typedef __packed struct 
{
	u8 				bootcode[446];	//ofs:0.启动代码。“FA 33 C0 8E D0 BC…”.
	PartitionTable 	PT[4]; 			//ofs:446.分区表length=4*16.
	u16 			EndingFlag; 	//ofs:510.结束标识:0xAA55.
}MBR_tag;

typedef __packed struct
{//由于默认情况下以对齐方式访问，因此可能导至结构体元素之间有“空隙”，
 //不利于操作，因此需要加上关键字__packed强制其以压缩方式存储结构体。
 //这样该结构体在内存空间上是一片连续的空间，不存在“空隙”情况。其它地方类同。
	u8         BS_jmpBoot[3];
	u8         BS_OEMName[8];
	u16        BPB_BytesPerSec;
	u8         BPB_SecPerClus;
	u16        BPB_RsvdSecCnt;
	u8         BPB_NumFATs;
	u16        BPB_RootEntCnt;
	u16        BPB_TotSec16;
	u8         BPB_Media;
	u16        BPB_FATSz16;
	u16        BPB_SecPerTrk;
	u16        BPB_NumHeads;
	u32        BPB_HiddSec;
	u32        BPB_TotSec32;
	u8         BS_DrvNum;
	u8         BS_Reservedl;
	u8         BS_BootSig;
	u32        BS_VolID;
	u8         BS_VolLab[11];
	u8         BS_FilSysType[8];
	u8         ExecutableCode[448];
	u8         ExecutableMarker[2];
} FAT_BPB;

typedef __packed struct
{
	u16        Start;
	u32        Size;
} FILE_POSIT;

typedef __packed struct
{
	u8         FileName[11];
	u8         FileAttrib;
	u8         UnUsed[10];
	u8         FileUpdateTime[2];
	u8         FileUpdateData[2];
	FILE_POSIT    FilePosit;
} DIR;

//********************************************************************************************
//初始化驱动,建立必要数据结构
void FAT_Init(void);
//列出指定扇区和长度（以扇区为单位）的所有目录信息，dirAddr为扇区地址，secNum为扇区数
void List_AllDir_Long(u32 dirAddr);
//在指定扇区（首扇区地址为dirAddr）的所有目录项中查找子目录，其名字为foldername[],
//type标识找目录还是文件, 0表示找目录，1表示找文件，返回子目录或文件的首扇区号
u32 SearchFoler(u32 dirAddr, u8 foldername[], u8 namelen, u8 type);
//获取根目录开始扇区号
u32 DirStartSec(void);
//打开指定文件,firstSec为文件的首扇区
void FAT_FileOpen(u32 firstSec);
//读取文件的数据,start指文件编移,length指读取长度,buff存入读取内容
void FAT_FileRead(u32 start, u32 length, u8* buff);
//计算可用空间,返回字节数
u32 CalcuFreeSpace(void);

void FAT_Info(void);
//********************************************************************************************
#endif
