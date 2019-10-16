#include "sys.h"
#include "adc.h"
#include "delay.h"
#include "timer.h"
#include "usart.h"
#include "driver.h"

u8 AD_VALUE = 0;//AD实时采样值

int main(void)
{
	delay_init();//延时初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断分组初始化
 	Driver_Init();//驱动设备初始化（预留）
	uart_init(9600);//串口波特率设置为9600
	Adc_Init();//ADC初始化
	TIM3_PWM_Init(1999, 719);//PWM频率=100000/20000=50kHz
	TIM_SetCompare3(TIM3, 0);//PWM停止
	while(1)
	{
		if(RX_STAIL == m_rxbuff.recvstatus)//如果一帧数据接收完成
		{
			AD_VALUE = Get_Adc_Average(ADC_Channel_0, 10);//AD采样
			if(AD_VALUE >= m_rxbuff.buff[0])//若AD采样值大于阈值（角度值达到预设角度）
			{
				TIM_SetCompare3(TIM3, 0);//PWM停止
				m_rxbuff.recvstatus = RX_IDLE;//接收状态清0
				m_rxbuff.count = 0;//接收计数清0
			}
		}
	}	 
}
