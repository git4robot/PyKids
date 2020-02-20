
/*
     �˳����Ǵ������ҵ��ģ������޸�����
     ����С�ף����д��������^_^
*/


#include "led.h"
#include "delay.h"
#include "sys.h"
#include "pwm.h"
#include "key.h"
#define key1 PCin(5)
#define key2 PAin(15)
#define key3 PAin(0)

u16 cout;
int main(void)
{
    cout=1850;
    KEY_Init();
    delay_init();	    	        //��ʱ������ʼ��
    LED_Init();		  	          //��ʼ����LED���ӵ�Ӳ���ӿ�
    //TIM3_PWM_Init(1999,719);    //PWMƵ��===(2000*720)/72000000=0.02=20ms
    TIM1_1PWM_Init(1999,7199);
    TIM1_2PWM_Init(1999,719);

    TIM1_3PWM_Init(1999,719);
    TIM1_4PWM_Init(1999,719);

    TIM8_1PWM_Init(1999,719);
    TIM8_2PWM_Init(1999,719);

    TIM8_3PWM_Init(1999,719);
    TIM8_4PWM_Init(1999,719);

    TIM2_3PWM_Init(1999,719);
    TIM2_4PWM_Init(1999,719);
    TIM3_2PWM_Init(1999,719);

    while(1)
    {
        if(key3==0&&key1==0)   //key1���£������������ת��
        {
            if(key1==0)
            {
                delay_ms(5);
                cout+=1;
            }
        }
        else	if(key3==1&&key1==0)  //key1��key3ͬʱ���£��������ת��
        {
            delay_ms(5);
            cout+=5;
        }
        if(key1==1&&key2==1&&key3==0)    //����ص�90�ȣ���ʼλ�ã�
        {
            cout=1850;
        }

        if(key3==0&&key2==0)      //key2���£������������ת��
        {
            delay_ms(5);
            cout-=1;
        }
        else	if(key3==1&&key2==0)   //key2��key3ͬʱ���£��������ת��
        {
            delay_ms(5);
            cout-=5;
        }

        TIM_SetCompare1(TIM1,cout);
        //TIM_SetCompare2(TIM3,cout); //PWM���(ͨ��2�ıȽ�)
		TIM_SetCompare1(TIM1,cout);
		TIM_SetCompare2(TIM1,cout);
	   
		TIM_SetCompare3(TIM1,cout);               
		TIM_SetCompare4(TIM1,cout);
	   
		TIM_SetCompare1(TIM8,cout);
		TIM_SetCompare2(TIM8,cout);
	   
		TIM_SetCompare3(TIM8,cout);
		TIM_SetCompare4(TIM8,cout);
	   
		TIM_SetCompare3(TIM2,cout);
		TIM_SetCompare4(TIM2,cout);
		TIM_SetCompare2(TIM3,cout);		
		
        delay_ms(50);
    }
}