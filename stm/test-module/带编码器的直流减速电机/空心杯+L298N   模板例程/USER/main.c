#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "motor.h"
#include "timer.h"
#include "pwm.h"
#include "key.h"
#include "encode.h"
int PWM=100,t;
u32 encode;
u16 speed;
extern int Encoder_Timer_Overflow;
int main(void)
{ 
	int k;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //����ϵͳ�ж����ȼ�����2
	delay_init(168);                                 //��ʼ����ʱ����
	uart_init(115200);		                           //��ʼ�����ڲ�����Ϊ115200
	LED_Init();					                             //��ʼ��LED
	KEY_Init();					                             //��ʼ������
 	LCD_Init();                                      //��ʼ��LCD FSMC�ӿ�
	TIM3_Encode_init(65534,1-1);                 //��������ʼ��
	TIM4_PWM_Init(100-1,84-1);                       //84M/100/84=10KHZ  //GPIOB6����Ϊ��ʱ��4  
	TIM5_Int_Init(50-1,8400-1);                     //84M/8400=10Khz,10Khz/500 = 20hz 1��    
	while(1)
	{
		k=KEY_Scan(0);                                 //�õ���ֵ	
	  if(k)
		{
			switch(k)                                    //���ݲ�ͬ��������ִֵ�в�ͬ����
			{																
			  case KEY0_PRES:                            //KEY0�����ӵ��ת��                                           
            PWM+=20;
				    if(PWM>100)
					    PWM=0;
						break;				
			  case KEY1_PRES:                            //KEY1���ü�С���ת��
            PWM-=20;
				    if(PWM<0)
					    PWM=100;
						break;						
			}
		}	
		TIM_SetCompare1(TIM4,PWM);  
	}
}

void TIM5_IRQHandler(void)                          //��ʱ��5�жϷ�����
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET)      //����ж�
	{   
		encode=TIM3->CNT;//��ñ�������ֵ
		TIM3->CNT=0;
		printf("������������Ϊ��%d\r\n",encode);
		
	}
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);        //����жϱ�־λ
}

