#include "led.h"
#include "delay.h"
#include "sys.h"
#include "servo.h"

//ALIENTEK Mini STM32开发板范例代码8
//PWM输出实验   
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司

int main(void)
{
	delay_init();	    	 	//延时函数初始化	  

#if 0	
	//LED_Init();		  			//初始化与LED连接的硬件接口
	TIM1_PWM_Init(719,1999);		//PWM频率=72000000/(719+1)/(1999+1)=50Hz
	
	while(1)
	{
		//LED0 = 1;
		Servo_TurnAngle(0);
		delay_ms(1000);   
		delay_ms(1000);   
		delay_ms(1000);   
		Servo_TurnAngle(90);
		//LED0 = 0;
		delay_ms(1000);   
		delay_ms(1000);   
		delay_ms(1000); 
	}	
#else
	TIM1_PWM_Init_Ex();
	
	Servo_out();
#endif
}

