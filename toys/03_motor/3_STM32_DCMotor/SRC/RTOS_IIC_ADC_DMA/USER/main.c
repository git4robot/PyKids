#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "dma.h"
#include "adc.h"

//ALIENTEK Mini STM32�����巶������3
//ʵ��   
// 1, ����
// 2, ����DMA��ADC��ͨ���ɼ�

volatile u16 ADCConvertedValue[10][3];//�������ADCת�������Ҳ��DMA��Ŀ���ַ,3ͨ����ÿͨ���ɼ�10�κ���ȡƽ����

int main(void)
{	
	//u8 t;
	//u8 len;	
	//u16 times=0; 
	int sum;
	u8 i,j;
	float ADC_Value[3];//�������澭��ת���õ��ĵ�ѹֵ
	
	delay_init();	    	 //��ʱ������ʼ��	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	uart_init(115200);	 //���ڳ�ʼ��Ϊ9600
	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ� 
	////DMA����ADC����ַ ADC1
	MYDMA_Config(DMA1_Channel1,(u32)&ADC1->DR,(u32)ADCConvertedValue,3*10);
	AdcDma_Init();
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//��ʼ�ɼ�
	
	MYDMA_Enable(DMA1_Channel1);
	
	while(1)
	{
#if 0		
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			printf("\r\n�����͵���ϢΪ:\r\n");
			for(t=0;t<len;t++)
			{
				USART1->DR=USART_RX_BUF[t];
				while((USART1->SR&0X40)==0);//�ȴ����ͽ���
			}
			printf("\r\n\r\n");//���뻻��
			USART_RX_STA=0;
		}else
		{
			times++;
			if(times%5000==0)
			{
				printf("\r\nALIENTEK MiniSTM32������ ����ʵ��\r\n");
				printf("����ԭ��@ALIENTEK\r\n\r\n\r\n");
			}
			if(times%200==0)printf("����������,�Իس�������\r\n");  
			if(times%30==0)LED0=!LED0;//��˸LED,��ʾϵͳ��������.
			delay_ms(10);   
		}
#endif
		
		for(i=0;i<3;i++)
		{
			sum=0;
			for(j=0;j<10;j++)
			{
				sum+=ADCConvertedValue[j][i];
			}
			ADC_Value[i]=(float)sum/(10*4096)*3.3;//��ƽ��ֵ��ת���ɵ�ѹֵ
			//��ӡ���ԣ�
			printf("[%d] = %.02f\r\n",i, ADC_Value[i]);
			//USART_SendData(USART1, 3);
		}
		//��ʱ���ԣ�		
		delay_ms(250);	  
	}	 
}


