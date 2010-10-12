#ifndef _FAT_H_65226575624
#define _FAT_H_65226575624

#define USE_FAT                         1
#define FAT_READ_ONLY                   1	 

typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;

typedef __packed struct 
{
	u8 			BootFlag; 			//������־
	u8 			StartCHS[3]; 		//������ʼ�����桢��ͷ������
	u8 			SystemID; 			//��������
	u8 			EndCHS[3]; 			//�������������桢��ͷ������
	u32 		RelativeSectors; 	//������ʼ��������ָ��������ڼ�¼�÷����ķ����������λ��֮�� (�÷�����LBA=0x0)��
	u32 		TotalSectors;		//������������
} PartitionTable;

typedef __packed struct 
{
	u8 				bootcode[446];	//ofs:0.�������롣��FA 33 C0 8E D0 BC����.
	PartitionTable 	PT[4]; 			//ofs:446.������length=4*16.
	u16 			EndingFlag; 	//ofs:510.������ʶ:0xAA55.
}MBR_tag;

typedef __packed struct
{//����Ĭ��������Զ��뷽ʽ���ʣ���˿��ܵ����ṹ��Ԫ��֮���С���϶����
 //�����ڲ����������Ҫ���Ϲؼ���__packedǿ������ѹ����ʽ�洢�ṹ�塣
 //�����ýṹ�����ڴ�ռ�����һƬ�����Ŀռ䣬�����ڡ���϶������������ط���ͬ��
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
//��ʼ������,������Ҫ���ݽṹ
void FAT_Init(void);
//�г�ָ�������ͳ��ȣ�������Ϊ��λ��������Ŀ¼��Ϣ��dirAddrΪ������ַ��secNumΪ������
void List_AllDir_Long(u32 dirAddr);
//��ָ����������������ַΪdirAddr��������Ŀ¼���в�����Ŀ¼��������Ϊfoldername[],
//type��ʶ��Ŀ¼�����ļ�, 0��ʾ��Ŀ¼��1��ʾ���ļ���������Ŀ¼���ļ�����������
u32 SearchFoler(u32 dirAddr, u8 foldername[], u8 namelen, u8 type);
//��ȡ��Ŀ¼��ʼ������
u32 DirStartSec(void);
//��ָ���ļ�,firstSecΪ�ļ���������
void FAT_FileOpen(u32 firstSec);
//��ȡ�ļ�������,startָ�ļ�����,lengthָ��ȡ����,buff�����ȡ����
void FAT_FileRead(u32 start, u32 length, u8* buff);
//������ÿռ�,�����ֽ���
u32 CalcuFreeSpace(void);

void FAT_Info(void);
//********************************************************************************************
#endif
