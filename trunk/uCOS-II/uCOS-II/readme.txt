Here are the steps to follow to port uCOS-II to stm32:
1.Download uCOS-II source code and put them in uCOS-II-V290 directory.
2.Create the directory "Port", read the readme file in the directory to see how.
3.Modify vector table and point pendsv and systick ISR to PendSVC_Handler and SysTick_Handler.
You can simply change file ../startup/stm32f10x_vector.s,
Changes are:
                 IMPORT  PendSVC_Handler
                 IMPORT  SysTick_Handler
                 DCD  PendSVC_Handler
                 DCD  SysTick_Handler
4.Add all files in ./Port except readme.txt to the project, another file is ucos_ii.c in ./uCOS-II-V290
5.Portation is over and you can't test whether is works or not, possible codes are in ./source/main.c
