#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"	
#include "usmart.h"
#include "led.h"
#include "rgb_led.h"

//ALIENTEK Mini STM32开发板代码2
//ATK-RGB LED实验		   
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司

//颜色值
#define Red    1   //红色
#define Green  2   //绿色
#define Blue   3   //蓝色
#define Yellow 4   //黄色
#define Purple 5   //紫色
#define Pink   6   //粉色

//WS2812 LED
#define 	RGB_LED 	GPIO_Pin_9
#define		RGB_LED_HIGH	(GPIO_SetBits(GPIOB,RGB_LED))
#define 	RGB_LED_LOW		(GPIO_ResetBits(GPIOB,RGB_LED))

void RGB_LED_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
 	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		
	GPIO_Init(GPIOB, &GPIO_InitStructure);					
	GPIO_SetBits(GPIOB,GPIO_Pin_9);						 
}

/********************************************************/
//
/********************************************************/
void RGB_LED_Write0(void)
{
	RGB_LED_HIGH;
	__nop();__nop();__nop();__nop();__nop();__nop();
	RGB_LED_LOW;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();
}

/********************************************************/
//
/********************************************************/

void RGB_LED_Write1(void)
{
	RGB_LED_HIGH;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();
	RGB_LED_LOW;
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();
}

void RGB_LED_Reset(void)
{
	RGB_LED_LOW;
	delay_us(80);
}

void RGB_LED_Write_Byte(uint8_t byte)
{
	uint8_t i;

	for(i=0;i<8;i++)
	{
		if(byte&0x80)
			{
				RGB_LED_Write1();
		}
		else
			{
				RGB_LED_Write0();
		}
		byte <<= 1;
	}
}

void RGB_LED_Write_24Bits(uint8_t green,uint8_t red,uint8_t blue)
{
	RGB_LED_Write_Byte(green);
	RGB_LED_Write_Byte(red);
	RGB_LED_Write_Byte(blue);
}

//亮灯颜色设定，其他颜色以此类推
void RGB_LED_Red(void)
{
	 uint8_t i;
	//4个LED全彩灯
	for(i=0;i<8;i++)
	{
		RGB_LED_Write_24Bits(0, 0xff, 0);
	}
}

void RGB_LED_Green(void)
{
	uint8_t i;

	for(i=0;i<8;i++)
	{
		RGB_LED_Write_24Bits(0xff, 0, 0);
	}
}

void RGB_LED_Blue(void)
{
	uint8_t i;

	for(i=0;i<8;i++)
	{
		RGB_LED_Write_24Bits(0, 0xF0, 0xFF);
	}
}


 int main(void)
 {	
	u8 key;	 
    u8 color=0;	 
	delay_init();	    	                        //延时函数初始化	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级 
	uart_init(115200);	                            //串口初始化为115200
	usmart_dev.init(72);	                        //初始化USMART	
	KEY_Init();                                     //按键初始化
	LED_Init();                                     //LED初始化
	RGBLED_Init();					                //RGB灯初始化
	RGBLED_Show(255,0,0);                           //红灯亮起
	color=1;
	 
	 RGB_LED_Init();
	 
	while(1)
	{
		key=KEY_Scan(0);//得到键值
		if(KEY1_PRES==key)//颜色切换
		{
			color++;
			if(color>6) color=1;
			switch(color)
			{
				 case Red:     RGBLED_Show(255,0,0);   break;//红色
				 case Green:   RGBLED_Show(0,255,0);   break;//绿色
				 case Blue:    RGBLED_Show(0,0,255);   break;//蓝色
				 case Yellow:  RGBLED_Show(254,254,0); break;//黄色
				 case Purple:  RGBLED_Show(254,0,70);  break;//紫色
				 case Pink:    RGBLED_Show(238,30,30); break;//粉色
			} 
		}
		else if(KEY0_PRES==key)//亮
		{    
		     switch(color)
			 {
				 case Red:     RGBLED_Show(255,0,0);   break;//红色
				 case Green:   RGBLED_Show(0,255,0);   break;//绿色
				 case Blue:    RGBLED_Show(0,0,255);   break;//蓝色
				 case Yellow:  RGBLED_Show(254,254,0); break;//黄色
				 case Purple:  RGBLED_Show(254,0,70);  break;//紫色
				 case Pink:    RGBLED_Show(238,30,30); break;//粉色
			 } 
			
		}
		else if(WKUP_PRES==key)//灭
		{
			 RGBLED_Show(0,0,0);
			RGB_LED_Red();
		}
		LED1=!LED1;//闪烁LED,提示系统正在运行.
		delay_ms(1000);
		RGB_LED_Green();
		delay_ms(1000);
		RGB_LED_Blue();
		delay_ms(1000);
	}		 
}
