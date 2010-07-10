/****************************Copyright (c)*********************************************                                     
*                                          
*                      博格达科技有限公司
*
*                        http://www.bogodtech.com
*
*---------- File Info ---------------------------------------------------------------
* File name: 		OS_CPU.H
* Created By: 		罗辉联(armgcc@foxmail.com   lhlzjut@hotmail.com) 	
* Created date: 	2007.11.28
* Descriptions: 	Header file of the ported code
* Adviser: 			楼东武(professor)  浙江大学信电系
*
*---------- History Info -------------------------------------------------------------
* Version: 			Ver1.0
* Descriptions: 	Create Initilze file
*
*-------------------------------------------------------------------------------------
**************************************************************************************/

#ifndef  OS_CPU_H
#define  OS_CPU_H


#ifdef   OS_CPU_GLOBALS
#define  OS_CPU_EXT
#else
#define  OS_CPU_EXT  extern
#endif

/*
****************************************************************************************
*                        DATA TYPES
*                     (Compiler Specific)
****************************************************************************************
*/

typedef unsigned char  BOOLEAN;
typedef unsigned char  INT8U;                    /* Unsigned  8 bit quantity       */
typedef signed   char  INT8S;                    /* Signed    8 bit quantity       */
typedef unsigned short INT16U;                   /* Unsigned 16 bit quantity       */
typedef signed   short INT16S;                   /* Signed   16 bit quantity       */
typedef unsigned int   INT32U;                   /* Unsigned 32 bit quantity       */
typedef signed   int   INT32S;                   /* Signed   32 bit quantity       */
typedef float          FP32;                     /* Single precision floating point*/
typedef double         FP64;                     /* Double precision floating point*/

typedef unsigned int   OS_STK;                   /* Each stack entry is 32-bit wide*/
typedef unsigned int   OS_CPU_SR;                /* Define size of CPU status register*/

/*
*****************************************************************************************
*                             Cortex M3
*                     Critical Section Management
****************************************************************************************
*/

#define  OS_CRITICAL_METHOD   4


/*
****************************************************************************************
*                          ARM Miscellaneous
****************************************************************************************
*/

#define  OS_STK_GROWTH        1      /* Stack grows from HIGH to LOW memory on ARM    */

#define  OS_TASK_SW()         OSCtxSw()

/*
****************************************************************************************
*                               PROTOTYPES
*                           (see OS_CPU_A.ASM)
****************************************************************************************
*/

#if OS_CRITICAL_METHOD == 4
	 void OS_ENTER_CRITICAL (void);
     void OS_EXIT_CRITICAL (void);     
#endif

void       OSCtxSw(void);
void       OSIntCtxSw(void);
void       OSStartHighRdy(void);

void       OSPendSV(void);

OS_CPU_EXT INT32U OSInterrputSum;

#endif

/***************************************************************************************
                            End of file 
***************************************************************************************/
