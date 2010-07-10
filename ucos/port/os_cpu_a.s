;/****************************Copyright (c)*********************************************                                     
;*
;*               (c) Copyright 2006-2008, hui lian. luo, china, zj. hz 
;*                            All Rights Reserved
;*
;*							  深圳市英蓓特信息技术有限公司
;*                            http://www.embedinfo.com
;*                            博格达科技有限公司
;*                            http://www.bogodtech.com                         
;*
;*---------- File Info ---------------------------------------------------------------
;* File name: 		OS_CPU_A.S
;* Created By: 		罗辉联(armgcc@foxmail.com, wyuyun@hotmail.com, lhlzjut@hotmail.com)	
;* Created date: 	2007.11.28
;* Descriptions: 	ucos asm port
;* Adviser: 		楼东武(professor)  浙江大学信电系
;*
;*---------- History Info -------------------------------------------------------------
;* Version: 		Ver1.0
;* Descriptions: 	Create Initilze file
;*
;*-------------------------------------------------------------------------------------
;**************************************************************************************/


		IMPORT  OSRunning               ; External references
        IMPORT  OSPrioCur
        IMPORT  OSPrioHighRdy
        IMPORT  OSTCBCur
        IMPORT  OSTCBHighRdy
        IMPORT  OSIntNesting
        IMPORT  OSIntExit
        IMPORT  OSTaskSwHook
		IMPORT  OSInterrputSum
         
            
        EXPORT  OSStartHighRdy               
        EXPORT  OSCtxSw
        EXPORT  OSIntCtxSw
		EXPORT  OS_ENTER_CRITICAL
        EXPORT  OS_EXIT_CRITICAL
		EXPORT  ItDisAll        
            
        EXPORT  OSPendSV
        	
     
NVIC_INT_CTRL   	EQU     0xE000ED04  ; 中断控制寄存器
NVIC_SYSPRI2    	EQU     0xE000ED20  ; 系统优先级寄存器(2)
NVIC_PENDSV_PRI 	EQU     0xFFFF0000  ; 软件中断和系统节拍中断
                                        ; (都为最低，0xff).
NVIC_PENDSVSET  	EQU     0x10000000  ; 触发软件中断的值.


		PRESERVE8 
		
		AREA    |.text|, CODE, READONLY
        THUMB 
    
           

;/***************************************************************************************
;* 函数名称: OS_ENTER_CRITICAL, 
;*
;* 功能描述: 进入临界区 
;*            
;* 参    数: None
;*
;* 返 回 值: None
;*         
;* 作　  者: 罗辉联
;* 日  　期: 2007年11月10日
;*----------------------------------------------------------------------------------------
;*****************************************************************************************/ 

OS_ENTER_CRITICAL
 
		CPSID   I                       ; Disable all the interrupts
                                                                        
		PUSH 	{R1,R2}      

		LDR 	R1, =OSInterrputSum	    ; OSInterrputSum++
        LDRB 	R2, [R1]
        ADD   	R2, R2, #1
        STRB 	R2, [R1]
		POP     {R1,R2}
  		BX LR

;/***************************************************************************************
;* 函数名称: OS_EXIT_CRITICAL, 
;*
;* 功能描述: 退出临界区 
;*            
;* 参    数: None
;*
;* 返 回 值: None
;*         
;* 作　  者: 罗辉联
;* 日  　期: 2007年11月10日
;*----------------------------------------------------------------------------------------
;*****************************************************************************************/

OS_EXIT_CRITICAL
		PUSH    {R1, R2}
		LDR     R1, =OSInterrputSum     ; OSInterrputSum--
        LDRB    R2, [R1]
        SUB     R2, R2, #1
        STRB    R2, [R1]
		MOV     R1,  #0	      
		CMP     R2,  #0			        ; if OSInterrputSum=0,enable 
                                        ; interrupts如果OSInterrputSum=0，
		MSREQ  PRIMASK, R1   
	    POP   	{R1, R2}
		BX LR

;/**************************************************************************************
;* 函数名称: OSStartHighRdy
;*
;* 功能描述: 使用调度器运行第一个任务
;* 
;* 参    数: None
;*
;* 返 回 值: None
;*         
;* 作　  者: 罗辉联
;* 日  　期: 2007年11月10日
;*--------------------------------------------------------------------------------------
;**************************************************************************************/  

OSStartHighRdy
        LDR     R4, =NVIC_SYSPRI2      ; set the PendSV exception priority
        LDR     R5, =NVIC_PENDSV_PRI
        STR     R5, [R4]			; //将R5保存到内存为R4的地方

        MOV     R4, #0                 ; set the PSP to 0 for initial context switch call
        MSR     PSP, R4

        LDR     R4, =OSRunning         ; OSRunning = TRUE
        MOV     R5, #1
        STRB    R5, [R4]

                                       ;切换到最高优先级的任务
        LDR     R4, =NVIC_INT_CTRL     ;rigger the PendSV exception (causes context switch)
        LDR     R5, =NVIC_PENDSVSET
        STR     R5, [R4]

        CPSIE   I                      ;enable interrupts at processor level
OSStartHang
        B       OSStartHang            ;should never get here

;/**************************************************************************************
;* 函数名称: OSCtxSw
;*
;* 功能描述: 任务级上下文切换         
;*
;* 参    数: None
;*
;* 返 回 值: None
;*         
;* 作　  者: 罗辉联
;* 日  　期: 2007年11月10日
;*--------------------------------------------------------------------------------------
;***************************************************************************************/
  
OSCtxSw
		PUSH    {R4, R5}
        LDR     R4, =NVIC_INT_CTRL  	;触发PendSV异常 (causes context switch)
        LDR     R5, =NVIC_PENDSVSET
        STR     R5, [R4]
		POP     {R4, R5}
        BX      LR

;/**************************************************************************************
;* 函数名称: OSIntCtxSw
;*
;* 功能描述: 中断级任务切换
;*
;* 参    数: None
;*
;* 返 回 值: None
;*         
;* 作　  者: 罗辉联
;* 日  　期: 2007年11月10日
;*--------------------------------------------------------------------------------------
;***************************************************************************************/

OSIntCtxSw
		PUSH    {R4, R5}
        LDR     R4, =NVIC_INT_CTRL      ;触发PendSV异常 (causes context switch)
        LDR     R5, =NVIC_PENDSVSET
        STR     R5, [R4]
		POP     {R4, R5}
        BX      LR
        NOP

;/**************************************************************************************
;* 函数名称: OSPendSV
;*
;* 功能描述: OSPendSV is used to cause a context switch.
;*
;* 参    数: None
;*
;* 返 回 值: None
;*         
;* 作　  者: 罗辉联
;* 日  　期: 2007年11月10日
;*--------------------------------------------------------------------------------------
;***************************************************************************************/

OSPendSV
		MRS     R3, PRIMASK                
        CPSID   I

        MRS     R0, PSP                 ; PSP is process stack pointer
        CBZ     R0, OSPendSV_nosave     ; skip register save the first time

        SUB     R0, R0, #0x20           ; save remaining regs r4-11 on process stack
        STM     R0, {R4-R11}

        LDR     R4, =OSTCBCur         	; OSTCBCur->OSTCBStkPtr = SP;
        LDR     R4, [R4]
        STR     R0, [R4]                ; R0 is SP of process being switched out

                                        ; at this point, entire context of process has been saved
OSPendSV_nosave
        PUSH    {R14}                   ; need to save LR exc_return value
        LDR     R0, =OSTaskSwHook     	; OSTaskSwHook();
        BLX     R0
        POP     {R14}

        LDR     R4, =OSPrioCur        	; OSPrioCur = OSPrioHighRdy
        LDR     R5, =OSPrioHighRdy
        LDRB    R6, [R5]
        STRB    R6, [R4]

        LDR     R4, =OSTCBCur         	; OSTCBCur  = OSTCBHighRdy;
        LDR     R6, =OSTCBHighRdy
        LDR     R6, [R6]
        STR     R6, [R4]

        LDR     R0, [R6]                ; R0 is new process SP; SP = OSTCBHighRdy->OSTCBStkPtr;
        LDM     R0, {R4-R11}            ; restore r4-11 from new process stack
        ADD     R0, R0, #0x20
        MSR     PSP, R0                 ; load PSP with new process SP
        ORR     LR, LR, #0x04           ; ensure exception return uses process stack

		MSR     PRIMASK, R3
        BX      LR                      ; exception return will restore remaining context

        NOP

;/**************************************************************************************
;* 函数名称: ItDisAll
;*
;* 功能描述: 关闭中断控制器的所有中断.
;*
;* 参    数: None
;*
;* 返 回 值: None
;*         
;* 作　  者: 罗辉联
;* 日  　期: 2007年11月10日
;*--------------------------------------------------------------------------------------
;***************************************************************************************/

ItDisAll
    	CPSID   I
    	BX      LR


    	ALIGN
		
;****************************************************************************************
;*  End Of File                                                     
;****************************************************************************************				
        END
        
        
