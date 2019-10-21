#include "encode.h"
#include "sys.h"

int Encoder_Timer_Overflow;                                      //���������������ÿ389*4���һ�Σ�
u16 Previous_Count;                                              //�ϴ�TIM3->CNT��ֵ

void TIM3_Encode_init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;    

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);    
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  
		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;          //GPIOA6��GPIOA7
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                    //����ģʽ
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;              //�ٶ�100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;                //����	
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                  //���츴�����
  GPIO_Init(GPIOA, &GPIO_InitStructure);                          //��ʼ��PA6��PA7

  GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3);           //GPIOA6����Ϊ��ʱ��3ͨ��1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3);           //GPIOA6����Ϊ��ʱ��3ͨ��2
	
  TIM_TimeBaseStructure.TIM_Period = arr; 	                      //(����������-1)*4	�ı�Ƶԭ��
	TIM_TimeBaseStructure.TIM_Prescaler=psc;                        //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;       //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;           //ʱ�ӷ�Ƶ���ӣ�����Ƶ
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);                  //��ʼ��TIM3
	
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;                  //ѡ�������IC1ӳ�䵽TI1��
  TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;	      //�����ز���
  TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;   //ӳ�䵽TI1��
  TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;	            //���������Ƶ,����Ƶ 
  TIM_ICInitStructure.TIM_ICFilter =6;                            //���������˲���
  TIM_ICInit(TIM3,&TIM_ICInitStructure);

		
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_2;                  //ѡ�������IC2ӳ�䵽TI2��
  TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;	      //�����ز���
  TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;   //ӳ�䵽TI2��
  TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;	            //���������Ƶ,����Ƶ 
  TIM_ICInitStructure.TIM_ICFilter=6;                             //���������˲���
  TIM_ICInit(TIM3,&TIM_ICInitStructure);
	
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising , TIM_ICPolarity_Rising );//���������ã���ʱ��������ģʽ�������ء������أ�
		
  NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;                   //��ʱ��3�жϷ�������
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;                   //ʹ��
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01;      //��ռ���ȼ�1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0x02;            //��Ӧ���ȼ�2
	NVIC_Init(&NVIC_InitStructure);                                 //���ö�ʱ��3
		
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);                        //����ʱ��3�����ж�
	TIM_Cmd(TIM3,ENABLE);                                           //ʹ�ܶ�ʱ��3
}

void TIM3_IRQHandler(void)                                        //��ʱ��3�жϷ�����
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)                    //����ж�
	{   
		Encoder_Timer_Overflow++;     		
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);                      //����жϱ�־λ
}



