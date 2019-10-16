#include "sys.h"
#include "adc.h"
#include "delay.h"
#include "timer.h"
#include "usart.h"
#include "driver.h"

u8 AD_VALUE = 0;//ADʵʱ����ֵ

int main(void)
{
	delay_init();//��ʱ��ʼ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�жϷ����ʼ��
 	Driver_Init();//�����豸��ʼ����Ԥ����
	uart_init(9600);//���ڲ���������Ϊ9600
	Adc_Init();//ADC��ʼ��
	TIM3_PWM_Init(1999, 719);//PWMƵ��=100000/20000=50kHz
	TIM_SetCompare3(TIM3, 0);//PWMֹͣ
	while(1)
	{
		if(RX_STAIL == m_rxbuff.recvstatus)//���һ֡���ݽ������
		{
			AD_VALUE = Get_Adc_Average(ADC_Channel_0, 10);//AD����
			if(AD_VALUE >= m_rxbuff.buff[0])//��AD����ֵ������ֵ���Ƕ�ֵ�ﵽԤ��Ƕȣ�
			{
				TIM_SetCompare3(TIM3, 0);//PWMֹͣ
				m_rxbuff.recvstatus = RX_IDLE;//����״̬��0
				m_rxbuff.count = 0;//���ռ�����0
			}
		}
	}	 
}
