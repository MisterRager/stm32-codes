	IMPORT  OSRunning               ; External references
    IMPORT  OSPrioCur
    IMPORT  OSPrioHighRdy
    IMPORT  OSTCBCur
    IMPORT  OSTCBHighRdy
    IMPORT  OSIntNesting
    IMPORT  OSIntExit
    IMPORT  OSTaskSwHook
		
         
            
    EXPORT  OSStartHighRdy               
    EXPORT  OSCtxSw
    EXPORT  OSIntCtxSw
	EXPORT  OS_CPU_SR_SAVE
    EXPORT  OS_CPU_SR_RESTORE               
    EXPORT  PendSVC_Handler

NVIC_INT_CTRL   	EQU     0xE000ED04  ; 中断控制寄存器
NVIC_SYSPRI14    	EQU     0xE000ED22  ; 系统优先级寄存器14
NVIC_PENDSV_PRI 	EQU     0xFF        ; 软件中断和系统节拍中断(都为最低，0xff).
NVIC_PENDSVSET  	EQU     0x10000000  ; 触发软件中断的值.

	PRESERVE8
	AREA |.text|, CODE, READONLY
	THUMB

	
OS_CPU_SR_SAVE 
	MRS 	R0,PRIMASK 	;Get value of PRIMASK which will later be returned as cpu_sr
;//	CPSID 	I		;Disable all interrupts.
	BX 	LR		;return

OS_CPU_SR_RESTORE
	MSR	PRIMASK,R0   	;Restore cpu_sr to PRIMASK
	BX	LR		;Return

OSStartHighRdy
	LDR	R0,=NVIC_SYSPRI14
	LDR	R1,=NVIC_PENDSV_PRI
	STRB	R1,[R0]

	MOVS	R0,#0
	MSR		PSP,R0
	
	LDR	R0,=OSRunning
	MOVS	R1,#1
	STRB	R1,[R0]
	
	LDR	R0,=NVIC_INT_CTRL
	LDR	R1,=NVIC_PENDSVSET
	STR	R1,[R0]
	
	CPSIE	I
	
OSStartHang
	B 	OSStartHang

OSCtxSw
	LDR	R0,=NVIC_INT_CTRL
	LDR	R1,=NVIC_PENDSVSET
	STR	R1,[R0]
	BX	LR

OSIntCtxSw	
	LDR	R0,=NVIC_INT_CTRL
	LDR	R1,=NVIC_PENDSVSET
	STR	R1,[R0]
	BX	LR

PendSVC_Handler
	CPSID	I
	MRS	R0,PSP
	CBZ	R0,PendSVC_Handler_nosave
	
	SUBS	R0,R0,#0x20
	STM	R0,{R4-R11}
	
	LDR	R1,=OSTCBCur
	LDR	R1,[R1]
	STR	R0,[R1]
PendSVC_Handler_nosave
	PUSH	{R14}
	LDR	R0,=OSTaskSwHook
	BLX	R0
	POP	{R14}

	LDR	R0,=OSPrioCur
	LDR	R1,=OSPrioHighRdy
	LDRB	R2,[R1]
	STRB	R2,[R0]

	LDR	R0,=OSTCBCur
	LDR	R1,=OSTCBHighRdy
	LDR	R2,[R1]
	STR	R2,[R0]

	LDR	R0,[R2]
	LDM	R0,{R4-R11}
	ADDS	R0,R0,#0x20
	MSR	PSP,R0
	ORR	LR,LR,#0x04
	CPSIE	I
	BX	LR

	END


