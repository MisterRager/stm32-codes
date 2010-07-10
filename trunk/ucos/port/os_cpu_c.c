/****************************Copyright (c)*********************************************                                     
*
*               (c) Copyright 2006-2008, hui lian. luo, china, zj. hz 
*                            All Rights Reserved
*
*							 ������Ӣ������Ϣ�������޹�˾
*                            http://www.embedinfo.com
*                            �����Ƽ����޹�˾
*                            http://www.bogodtech.com                         
*
*---------- File Info ---------------------------------------------------------------
* File name: 		os_cpu_c.c
* Created By: 		�޻���(armgcc@foxmail.com, wyuyun@hotmail.com, lhlzjut@hotmail.com) 	
* Created date: 	2007.11.28
* Descriptions: 	The C functions that a uC/OS-II port requires
* Adviser: 			¥����(professor)  �㽭��ѧ�ŵ�ϵ
*
*---------- History Info -------------------------------------------------------------
* Version: 			Ver1.0
* Descriptions: 	Create Initilze file
*
*-------------------------------------------------------------------------------------
**************************************************************************************/

#define  OS_CPU_GLOBALS

#include "ucos_ii.h"

#define  OS_VIEW_MODULE   0


#if OS_TMR_EN > 0
static  INT16U  OSTmrCtr;
#endif

/***************************************************************************************
* ��������: OSInitHookBegin 
*
* ��������: This function is called by OSInit() at the beginning of OSInit(). 
*            
* ��    ��: None
*
* �� �� ֵ: None
*         
* ����  ��: �޻���
* ��  ����: 2007��11��10��
*----------------------------------------------------------------------------------------
*****************************************************************************************/

#if OS_CPU_HOOKS_EN > 0 && OS_VERSION > 203
void  OSInitHookBegin (void)
{
	#if OS_TMR_EN > 0 
		OSTmrCtr = 0; 
	#endif
}
#endif

/***************************************************************************************
* ��������: OSInitHookEnd, 
*
* ��������: This function is called by OSInit() at the end of OSInit().
*            
* ��    ��: None
*
* �� �� ֵ: None
*         
* ����  ��: �޻���
* ��  ����: 2007��11��10��
*----------------------------------------------------------------------------------------
*****************************************************************************************/

#if OS_CPU_HOOKS_EN > 0 && OS_VERSION > 203
void  OSInitHookEnd (void)
{

}
#endif

/***************************************************************************************
* ��������: OSTaskCreateHook 
*
* ��������: This function is called when a task is created. 
*            
* ��    ��: ptcb   is a pointer to the task control block of the task being created.
*
* �� �� ֵ: None
*         
* ����  ��: �޻���
* ��  ����: 2007��11��10��
*----------------------------------------------------------------------------------------
*****************************************************************************************/

#if OS_CPU_HOOKS_EN > 0
void  OSTaskCreateHook (OS_TCB *ptcb)
{
#if OS_VIEW_MODULE > 0
    OSView_TaskCreateHook(ptcb);
#else
    ptcb = ptcb;                       /* Prevent compiler warning  */
#endif
}
#endif

/***************************************************************************************
* ��������: OSTaskDelHook 
*
* ��������: This function is called when a task is deleted.
*            
* ��    ��: ptcb   is a pointer to the task control block of the task being deleted.
*
* �� �� ֵ: None
*         
* ����  ��: �޻���
* ��  ����: 2007��11��10��
*----------------------------------------------------------------------------------------
*****************************************************************************************/

#if OS_CPU_HOOKS_EN > 0
void  OSTaskDelHook (OS_TCB *ptcb)
{
    ptcb = ptcb;                       /* Prevent compiler warning  */
}
#endif

/***************************************************************************************
* ��������: OSTaskIdleHook 
*
* ��������: This function is called by the idle task.  This hook has been added to allow 
*           you to do such things as STOP the CPU to conserve power.
*            
* ��    ��: None
*
* �� �� ֵ: None
*         
* ����  ��: �޻���
* ��  ����: 2007��11��10��
*----------------------------------------------------------------------------------------
*****************************************************************************************/

#if OS_CPU_HOOKS_EN > 0 && OS_VERSION >= 251
extern volatile unsigned long	wdg_clr_flag;
void  OSTaskIdleHook (void)
{
	wdg_clr_flag = 1;
}
#endif

/***************************************************************************************
* ��������: OSTaskStatHook 
*
* ��������: This function is called every second by uC/OS-II's statistics task.This allows 
*           your application to add functionality to the statistics task.
*            
* ��    ��: none
*
* �� �� ֵ: None
*         
* ����  ��: �޻���
* ��  ����: 2007��11��10��
*----------------------------------------------------------------------------------------
*****************************************************************************************/

#if OS_CPU_HOOKS_EN > 0
void  OSTaskStatHook (void)
{
}
#endif

/****************************************************************************************
* ��������: OSTaskStkInit
* ��������: OSTaskCreate() �� OSTaskCreateExt()���ñ�������ʼ����������������Ķ�ջ
*            �������;���Ĵ������й� 
* 
* ��    ��: task  : ����ʼִ�еĵ�ַ
*           pdata �����ݸ�����Ĳ���
*           ptos  ������Ķ�ջ��ʼλ��
*           opt   �����Ӳ�������������μ�OSTaskCreateExt()��opt����
*
* �� �� ֵ: ջ��ָ��λ��
*         
* ����  ��: �޻���
* ��  ����: 2006��6��10��
*----------------------------------------------------------------------------------------
*****************************************************************************************/ 

OS_STK *OSTaskStkInit (void  (*task)(void  *parg), void  *parg, OS_STK  *ptos, INT16U  opt)
{
    OS_STK *stk;


    (void)opt;                                        /*  'opt' is not used, prevent  */
                                                      /*  warning û����'opt'��       */
                                                      /*  ��ֹ���뾯��                */
                                                                            
    stk = ptos;                                       /*  Load stack pointer          */
                                                      /*  װ�ض�ջָ��                */                                    

                                                      /*  Registers stacked as if     */
                                                      /*  auto-saved on exception     */             
	                                                  /*  ģ����쳣���Զ��ѼĴ���ѹջ*/

    *(stk) = (INT32U)0x01000000L;                     /*  xPSR                        */ 
    *(--stk) = (INT32U)task;                          /*  Entry Point of the task     */
                                                      /*  ������ڵ�ַ                */
    *(--stk) = (INT32U)0xFFFFFFFEL;                   /*  R14 (LR)  (init value will  */
                                                      /*  cause fault if ever used)   */
                                                                           
    *(--stk) = (INT32U)0x12121212L;                   /*  R12                         */
    *(--stk) = (INT32U)0x03030303L;                   /*  R3                          */
    *(--stk) = (INT32U)0x02020202L;                   /*  R2                          */
    *(--stk) = (INT32U)0x01010101L;                   /*  R1                          */
    *(--stk) = (INT32U)parg;                          /*  R0 : argument  �������     */
                                                      /*  Remaining registers saved on*/
                                                      /*  process stack               */   
	                                                  /*  ʣ�µļĴ������浽��ջ      */

    *(--stk) = (INT32U)0x11111111L;                   /*  R11                         */
    *(--stk) = (INT32U)0x10101010L;                   /*  R10                         */
    *(--stk) = (INT32U)0x09090909L;                   /*  R9                          */
    *(--stk) = (INT32U)0x08080808L;                   /*  R8                          */
    *(--stk) = (INT32U)0x07070707L;                   /*  R7                          */
    *(--stk) = (INT32U)0x06060606L;                   /*  R6                          */
    *(--stk) = (INT32U)0x05050505L;                   /*  R5                          */
    *(--stk) = (INT32U)0x04040404L;                   /*  R4                          */

    return(stk);
}

/***************************************************************************************
* ��������: OSTaskSwHook 
*
* ��������: This function is called when a task switch is performed.  This allows you
*           perform other operations during a context switch. 
*           you to do such things as STOP the CPU to conserve power.
*            
* ��    ��: None
*
* �� �� ֵ: None
*         
* ����  ��: �޻���
* ��  ����: 2007��11��10��
*----------------------------------------------------------------------------------------
*****************************************************************************************/

#if (OS_CPU_HOOKS_EN > 0) && (OS_TASK_SW_HOOK_EN > 0)
void  OSTaskSwHook (void)
{
#if OS_VIEW_MODULE > 0
    OSView_TaskSwHook();
#endif
}
#endif

/***************************************************************************************
* ��������: OSTCBInitHook, 
*
* ��������: This function is called by OS_TCBInit() after setting up most of the TCB.
*            
* ��    ��: ptcb    is a pointer to the TCB of the task being created.
*
* �� �� ֵ: None
*         
* ����  ��: �޻���
* ��  ����: 2007��11��10��
*----------------------------------------------------------------------------------------
*****************************************************************************************/

#if OS_CPU_HOOKS_EN > 0 && OS_VERSION > 203
void  OSTCBInitHook (OS_TCB *ptcb)
{
    ptcb = ptcb;                            /* Prevent Compiler warning                 */
}
#endif

/***************************************************************************************
* ��������: OSTimeTickHook, 
*
* ��������: This function is called every tick.
*            
* ��    ��: None
*
* �� �� ֵ: None
*         
* ����  ��: �޻���
* ��  ����: 2007��11��10��
*----------------------------------------------------------------------------------------
*****************************************************************************************/

#if (OS_CPU_HOOKS_EN > 0) && (OS_TIME_TICK_HOOK_EN > 0)
void  OSTimeTickHook (void)
{
	#if OS_VIEW_MODULE > 0
		OSView_TickHook(); 
	#endif
	
	#if OS_TMR_EN > 0
		OSTmrCtr++; 
		if (OSTmrCtr >= (OS_TICKS_PER_SEC / OS_TMR_CFG_TICKS_PER_SEC)) 
		{
			OSTmrCtr = 0;
			OSTmrSignal(); 
		} 
	#endif
}
#endif

#if OS_CPU_HOOKS_EN > 0 && OS_VERSION > 203
void  OSTaskReturnHook (OS_TCB * a)
{

}
#endif

/****************** http://www.bogodtech.com *******End of file ******************/

