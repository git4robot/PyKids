#include "pwm.h"
#include "stm32f4xx.h"
#include "usart.h"

void TIM4_PWM_Init(u32 arr,u32 psc) 
{		 					 
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);  	          //TIM4ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);           //ʹ��PORTFʱ��	
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource6,GPIO_AF_TIM4);           //GPIOB6����Ϊ��ʱ��4
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;                       //GPIOB6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                    //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	            //�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                  //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;                    //����
	GPIO_Init(GPIOB,&GPIO_InitStructure);                           //��ʼ��PB6
	  
	TIM_TimeBaseStructure.TIM_Prescaler=psc;                        //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;       //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=arr;                           //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);                  //��ʼ����ʱ��4
		 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;               //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;   //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;        //�������:TIM����Ƚϼ��Ե�
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);                        //����Tָ���Ĳ�����ʼ������TIM4 OC1

	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);               //ʹ��TIM4��CCR1�ϵ�Ԥװ�ؼĴ���

  TIM_ARRPreloadConfig(TIM4,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM4, ENABLE);  //ʹ��TIM4									  
}







