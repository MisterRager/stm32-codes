How did this directory happen or how to port uCOS-II to stm32? The following are steps to follow:
1.Copy ../uCOS-II-V290/os_cfg_r.h  ./os_cfg.h
2.Copy ../uCOS-II-V290/os_dbg_r.c  ./os_dbg.c
3.notepad ./ucos_ii.c and copy my code.
4.notepad ./os_cpu.h and copy my code.
5.notepad ./os_cpu_a.s and copy my code.
6.notepad ./os_cpu_c.c and copy my code.
7.notepad ./os_cfg.h and disable OS_TMR_EN        
#define OS_TMR_EN                 0u   /* Enable (1) or Disable (0) code generation for TIMERS         */
8.notepad ./systick.c and copy my code. note:this file needs the stm32 fwlib to work well.