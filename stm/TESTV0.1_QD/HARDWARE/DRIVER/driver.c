#include "driver.h"
#include "delay.h"
#include "usart.h"

/********** ������ �˿ڶ��� **************
Ԥ���ӿ�PC0 PC1
******************************************/

/************** �����������ź��߳�ʼ�� ****************/
void Driver_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//ʹ��PC�˿�ʱ��

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;	//�˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		//�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					//�����趨������ʼ��GPIOC
	GPIO_SetBits(GPIOC, GPIO_Pin_0);//X˳ʱ�뷽��
	GPIO_SetBits(GPIOC, GPIO_Pin_1);//Y˳ʱ�뷽��
}
