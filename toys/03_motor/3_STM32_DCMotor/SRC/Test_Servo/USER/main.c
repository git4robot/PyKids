#include "led.h"
#include "delay.h"
#include "sys.h"
#include "servo.h"

//ALIENTEK Mini STM32�����巶������8
//PWM���ʵ��   
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾

int main(void)
{
	delay_init();	    	 	//��ʱ������ʼ��	  

#if 0	
	//LED_Init();		  			//��ʼ����LED���ӵ�Ӳ���ӿ�
	TIM1_PWM_Init(719,1999);		//PWMƵ��=72000000/(719+1)/(1999+1)=50Hz
	
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

