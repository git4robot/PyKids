#include "encode.h"
#include "sys.h"

int Encoder_Timer_Overflow;                                      //编码器溢出次数（每389*4溢出一次）
u16 Previous_Count;                                              //上次TIM3->CNT的值

void TIM3_Encode_init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_ICInitTypeDef TIM_ICInitStructure;    

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);    
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);  
		
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;          //GPIOA6和GPIOA7
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;                    //复用模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;              //速度100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;                //浮空	
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;                  //推挽复用输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);                          //初始化PA6和PA7

  GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_TIM3);           //GPIOA6复用为定时器3通道1
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_TIM3);           //GPIOA6复用为定时器3通道2
	
  TIM_TimeBaseStructure.TIM_Period = arr; 	                      //(编码器线数-1)*4	四倍频原理
	TIM_TimeBaseStructure.TIM_Prescaler=psc;                        //定时器分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;       //向上计数模式
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;           //时钟分频因子，不分频
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);                  //初始化TIM3
	
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_1;                  //选择输入端IC1映射到TI1上
  TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;	      //上升沿捕获
  TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;   //映射到TI1上
  TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;	            //配置输入分频,不分频 
  TIM_ICInitStructure.TIM_ICFilter =6;                            //配置输入滤波器
  TIM_ICInit(TIM3,&TIM_ICInitStructure);

		
	TIM_ICInitStructure.TIM_Channel=TIM_Channel_2;                  //选择输入端IC2映射到TI2上
  TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;	      //上升沿捕获
  TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;   //映射到TI2上
  TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;	            //配置输入分频,不分频 
  TIM_ICInitStructure.TIM_ICFilter=6;                             //配置输入滤波器
  TIM_ICInit(TIM3,&TIM_ICInitStructure);
	
	TIM_EncoderInterfaceConfig(TIM3, TIM_EncoderMode_TI12, TIM_ICPolarity_Rising , TIM_ICPolarity_Rising );//编码器配置（定时器、编码模式、上升沿、上升沿）
		
  NVIC_InitStructure.NVIC_IRQChannel=TIM3_IRQn;                   //定时器3中断分组配置
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;                   //使能
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x01;      //抢占优先级1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0x02;            //响应优先级2
	NVIC_Init(&NVIC_InitStructure);                                 //配置定时器3
		
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);                        //允许定时器3更新中断
	TIM_Cmd(TIM3,ENABLE);                                           //使能定时器3
}

void TIM3_IRQHandler(void)                                        //定时器3中断服务函数
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET)                    //溢出中断
	{   
		Encoder_Timer_Overflow++;     		
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);                      //清除中断标志位
}



