#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "adc.h"

//ALIENTEK Mini STM32开发板范例代码15
//ADC实验  
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
   	
 int main(void)
 { 
	u16 adcx;
	float temp;
	delay_init();	    	 //延时函数初始化	  
	uart_init(115200);	 //串口初始化为115200
	LED_Init();		  		 //初始化与LED连接的硬件接口
 	Adc_Init();		  		 //ADC初始化	    
   
	while(1)
	{
		//PA2引脚接点位计测试电压变化
		adcx=Get_Adc_Average(ADC_Channel_2,10);
		temp = Get_Temprate();
		printf("V-Out: %d , T-Out: %.02f\r\n", adcx, temp);//显示ADC的值
		
		//LED0=!LED0;
		delay_ms(250);	
	}											    
}	
