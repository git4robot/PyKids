#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"

//电机端口定义
#define AIN1 PFout(0)	  //控制电机1   前
#define AIN2 PFout(1)	
#define BIN1 PFout(2)		//控制电机2   后
#define BIN2 PFout(3) 
#define AIN3 PFout(4)	  //控制电机3   左
#define AIN4 PFout(5)
#define BIN3 PFout(6)	  //控制电机4   右
#define BIN4 PFout(7)


void MOTOR_Init(void);



#endif

