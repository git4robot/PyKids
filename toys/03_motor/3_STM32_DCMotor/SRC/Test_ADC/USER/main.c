#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "adc.h"

//ALIENTEK Mini STM32�����巶������15
//ADCʵ��  
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
   	
 int main(void)
 { 
	u16 adcx;
	float temp;
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	LED_Init();		  		 //��ʼ����LED���ӵ�Ӳ���ӿ�
 	Adc_Init();		  		 //ADC��ʼ��	    
   
	while(1)
	{
		//PA2���Žӵ�λ�Ʋ��Ե�ѹ�仯
		adcx=Get_Adc_Average(ADC_Channel_2,10);
		temp = Get_Temprate();
		printf("V-Out: %d , T-Out: %.02f\r\n", adcx, temp);//��ʾADC��ֵ
		
		//LED0=!LED0;
		delay_ms(250);	
	}											    
}	
