			   /* Includes ------------------------------------------------------------------*/
#include "UnicodeToGB2312.h"


/* Function define -----------------------------------------------------------*/

/*******************************************************************************
* Function Name  : UnicodeToGB2312
* Description    : This function convert unicode to gb2312 code
* Input          : unicode--the unicode value
* Output         : None
* Return         : gb2312 code value
*******************************************************************************/
u16 UnicodeToGB2312(u16 unicode)//用二分查找算法
{
   	int mid, low, high, len;
	len = sizeof(UnicodeToGB2312_Tab)/sizeof(UnicodeToGB2312_Tab[0]);
	low = 0;
	high = len - 1;
	if( (unicode >= 0x20 && unicode <= 0x5b) || (unicode >= 0x5d && unicode <= 0x7e))
	   return unicode;
	while(low <= high)
	{
	    mid = (low + high) / 2;
		if(UnicodeToGB2312_Tab[mid][0] > unicode)
		    high = mid - 1;
		else if(UnicodeToGB2312_Tab[mid][0] < unicode)
		    low =  mid + 1;
		else
		    return 	UnicodeToGB2312_Tab[mid][1];
	}
	return 0 ; //没找到
}

