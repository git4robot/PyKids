
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
    delay_init();	    	        //延时函数初始化
    LED_Init();		  	          //初始化与LED连接的硬件接口
    TIM1_PWM_Init(1999,719);    //PWM频率===(2000*720)/72000000=0.02=20ms
    while(1)
    {
        if(key3==0&&key1==0)   //key1按下，舵机缓慢正向转动
        {
            if(key1==0)
            {
                delay_ms(5);
                cout+=1;
            }
        }
        else	if(key3==1&&key1==0)  //key1、key3同时按下，舵机加速转动
        {
            delay_ms(5);
            cout+=5;
        }
        if(key1==1&&key2==1&&key3==0)    //舵机回到90度（起始位置）
        {
            cout=1850;
        }

        if(key3==0&&key2==0)      //key2按下，舵机缓慢反向转动
        {
            delay_ms(5);
            cout-=1;
        }
        else	if(key3==1&&key2==0)   //key2、key3同时按下，舵机加速转动
        {
            delay_ms(5);
            cout-=5;
        }

        TIM_SetCompare1(TIM1,cout); //PWM输出
        delay_ms(50);
    }

}
