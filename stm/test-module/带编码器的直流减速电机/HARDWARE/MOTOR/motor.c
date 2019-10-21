#include "motor.h"
#include "sys.h"

void MOTOR_Init(void)//�����ʼ��	
{
	GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOEʱ��
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5| GPIO_Pin_6| GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;                  //��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                 //�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;             //100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                   //����
  GPIO_Init(GPIOF, &GPIO_InitStructure);                         //��ʼ��GPIO
	
	AIN1=0;                                                       //��ʼ��TB6612FNG����ģ�飬ʹ�ĸ������ָ���ķ�����ת
	AIN2=1;
	BIN1=0;
	BIN2=1;
	AIN3=0;
	AIN4=1;
	BIN3=0;
	BIN4=1;
}	






