// Author		: 	Dean Sinaean
// Home Page	:  	http://zhuifeng.usr.cc
// Email Address:	Dean.Sinaean@gmail.com

# ifndef  __LED_H__
# define __LED_H__
#define LEDs P2
sbit LED1 =LEDs^0;
sbit LED2=LEDs^1  ;
sbit LED3=LEDs^2   ;
sbit LED4=LEDs^3	;
sbit LED5=LEDs^4	 ;
sbit LED6=LEDs^5	  ;
sbit LED7=LEDs^6	   ;
sbit LED8=LEDs^7		;
#define LightUpLed(x)  x=0
#define TurnOffLed(x)  x=1

# endif 