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

extern int Encoder_Timer_Overflow;

int PWM=100;
u32 encode;
float speed,t;

int main(void)
{ 
	int k;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);  //设置系统中断优先级分组2
	delay_init(168);                                 //初始化延时函数
	uart_init(115200);		                           //初始化串口波特率为115200
	LED_Init();					                             //初始化LED
	KEY_Init();					                             //初始化按键
 	LCD_Init();                                      //初始化LCD FSMC接口
	TIM3_Encode_init((ENCODER_PPR)*4,1-1);         //编码器初始化
	TIM4_PWM_Init(100-1,84-1);                       //84M/100/84=10KHZ  //GPIOB6复用为定时器4  
	TIM5_Int_Init(500-1,8400-1);                     //84M/8400=10Khz,10Khz/500 = 20hz 1秒    
	while(1)
	{
		k=KEY_Scan(0);                                 //得到键值	
	  if(k)
		{
			switch(k)                                    //根据不同按键返回值执行不同任务
			{																
			  case KEY0_PRES:                            //KEY0键增加电机转速                                           
            PWM+=20;
				    if(PWM>100)
					    PWM=0;
						break;				
			  case KEY1_PRES:                            //KEY1键用减小电机转速
            PWM-=20;
				    if(PWM<0)
					    PWM=100;
						break;						
			}
		}	
		TIM_SetCompare1(TIM4,PWM);  
	}
}

void TIM5_IRQHandler(void)                          //定时器5中断服务函数
{
	if(TIM_GetITStatus(TIM5,TIM_IT_Update)==SET)      //溢出中断
	{  
		encode=Read_Encoder();                          //获得编码器的值
		printf("编码器脉冲数为：%d\r\n",encode);
		speed=encode/390.0f/4.0f/0.05f;
		printf("电机转速为：%f\r\n",speed);		
	}
	TIM_ClearITPendingBit(TIM5,TIM_IT_Update);        //清除中断标志位
}

