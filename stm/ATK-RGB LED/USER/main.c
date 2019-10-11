#include "delay.h"
#include "sys.h"
#include "key.h"
#include "usart.h"	
#include "usmart.h"
#include "led.h"
#include "rgb_led.h"

//ALIENTEK Mini STM32���������2
//ATK-RGB LEDʵ��		   
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾

//��ɫֵ
#define Red    1   //��ɫ
#define Green  2   //��ɫ
#define Blue   3   //��ɫ
#define Yellow 4   //��ɫ
#define Purple 5   //��ɫ
#define Pink   6   //��ɫ

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

//������ɫ�趨��������ɫ�Դ�����
void RGB_LED_Red(void)
{
	 uint8_t i;
	//4��LEDȫ�ʵ�
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
	delay_init();	    	                        //��ʱ������ʼ��	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ� 
	uart_init(115200);	                            //���ڳ�ʼ��Ϊ115200
	usmart_dev.init(72);	                        //��ʼ��USMART	
	KEY_Init();                                     //������ʼ��
	LED_Init();                                     //LED��ʼ��
	RGBLED_Init();					                //RGB�Ƴ�ʼ��
	RGBLED_Show(255,0,0);                           //�������
	color=1;
	 
	 RGB_LED_Init();
	 
	while(1)
	{
		key=KEY_Scan(0);//�õ���ֵ
		if(KEY1_PRES==key)//��ɫ�л�
		{
			color++;
			if(color>6) color=1;
			switch(color)
			{
				 case Red:     RGBLED_Show(255,0,0);   break;//��ɫ
				 case Green:   RGBLED_Show(0,255,0);   break;//��ɫ
				 case Blue:    RGBLED_Show(0,0,255);   break;//��ɫ
				 case Yellow:  RGBLED_Show(254,254,0); break;//��ɫ
				 case Purple:  RGBLED_Show(254,0,70);  break;//��ɫ
				 case Pink:    RGBLED_Show(238,30,30); break;//��ɫ
			} 
		}
		else if(KEY0_PRES==key)//��
		{    
		     switch(color)
			 {
				 case Red:     RGBLED_Show(255,0,0);   break;//��ɫ
				 case Green:   RGBLED_Show(0,255,0);   break;//��ɫ
				 case Blue:    RGBLED_Show(0,0,255);   break;//��ɫ
				 case Yellow:  RGBLED_Show(254,254,0); break;//��ɫ
				 case Purple:  RGBLED_Show(254,0,70);  break;//��ɫ
				 case Pink:    RGBLED_Show(238,30,30); break;//��ɫ
			 } 
			
		}
		else if(WKUP_PRES==key)//��
		{
			 RGBLED_Show(0,0,0);
			RGB_LED_Red();
		}
		LED1=!LED1;//��˸LED,��ʾϵͳ��������.
		delay_ms(1000);
		RGB_LED_Green();
		delay_ms(1000);
		RGB_LED_Blue();
		delay_ms(1000);
	}		 
}
