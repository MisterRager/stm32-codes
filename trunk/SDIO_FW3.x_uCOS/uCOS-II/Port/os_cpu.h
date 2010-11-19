#ifndef  OS_CPU_H
#define  OS_CPU_H


#ifdef   OS_CPU_GLOBALS
#define  OS_CPU_EXT
#else
#define  OS_CPU_EXT  extern
#endif

/* 11 typedefs */

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

/* critical management */

#define  OS_CRITICAL_METHOD   3

#if OS_CRITICAL_METHOD == 3
#define OS_ENTER_CRITICAL()   	{ cpu_sr=OS_CPU_SR_SAVE(); }
#define OS_EXIT_CRITICAL()	{ OS_CPU_SR_RESTORE(cpu_sr); }     
#endif

#if OS_CRITICAL_METHOD == 3
OS_CPU_SR OS_CPU_SR_SAVE(void );
void OS_CPU_SR_RESTORE(OS_CPU_SR cpu_sr);
#endif


/*
****************************************************************************************
*                          ARM Miscellaneous
****************************************************************************************
*/

#define  OS_STK_GROWTH        1      /* Stack grows from HIGH to LOW memory on ARM    */

#define  OS_TASK_SW()         OSCtxSw()

/* four assembly functions */
void     OSCtxSw(void);
void     OSIntCtxSw(void);
void     OSStartHighRdy(void);
void     PendSVC_Handler(void);

#endif

/***************************************************************************************
                            End of file 
***************************************************************************************/
