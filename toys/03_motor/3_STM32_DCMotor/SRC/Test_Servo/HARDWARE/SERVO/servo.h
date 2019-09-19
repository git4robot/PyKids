#ifndef __SERVO_H
#define __SERVO_H	 
#include "sys.h"

void TIM1_PWM_Init(u16 arr,u16 psc); //定时器初始化
void Servo_TurnAngle(u16 angle);//舵机角度旋转


void TIM1_PWM_Init_Ex(void);
void Servo_out(void);

#endif

