#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"

//����˿ڶ���
#define AIN1 PFout(0)	  //���Ƶ��1   ǰ
#define AIN2 PFout(1)	
#define BIN1 PFout(2)		//���Ƶ��2   ��
#define BIN2 PFout(3) 
#define AIN3 PFout(4)	  //���Ƶ��3   ��
#define AIN4 PFout(5)
#define BIN3 PFout(6)	  //���Ƶ��4   ��
#define BIN4 PFout(7)


void MOTOR_Init(void);



#endif

