#ifndef __DRIVER_H
#define __DRIVER_H
#include "sys.h"
#include "stdlib.h"	

/********** 驱动器 端口定义 **************
预留接口PC0 PC1
******************************************/
#define PC0 PCout(0) 
#define PC1 PCout(1)

typedef enum
{
	CW = 1,//高电平顺时针
	CCW = 0,//低电平逆时针
}DIR_Type;//运行方向

void Driver_Init(void);//驱动器初始化

#endif


