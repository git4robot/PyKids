#include "motor.h"
#include "sys.h"

void MOTOR_Init(void)//电机初始化	
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//使能GPIOE时钟
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                  //普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;             //100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                   //上拉
  GPIO_Init(GPIOF, &GPIO_InitStructure);                         //初始化GPIO
	
	AIN1=0;                                                       //初始化TB6612FNG驱动模块，使四个电机按指定的方向旋转
	AIN2=1;
	BIN1=0;
	BIN2=1;
	AIN3=0;
	AIN4=1;
	BIN3=0;
	BIN4=1;
}	






