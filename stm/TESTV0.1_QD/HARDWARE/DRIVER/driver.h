#ifndef __DRIVER_H
#define __DRIVER_H
#include "sys.h"
#include "stdlib.h"	

/********** ������ �˿ڶ��� **************
Ԥ���ӿ�PC0 PC1
******************************************/
#define PC0 PCout(0) 
#define PC1 PCout(1)

typedef enum
{
	CW = 1,//�ߵ�ƽ˳ʱ��
	CCW = 0,//�͵�ƽ��ʱ��
}DIR_Type;//���з���

void Driver_Init(void);//��������ʼ��

#endif


