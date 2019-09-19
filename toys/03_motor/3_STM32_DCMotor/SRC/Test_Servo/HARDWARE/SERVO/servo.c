#include "servo.h"
#include "led.h"
#include "delay.h"



//PWM�����ʼ��
//arr���Զ���װֵ
//psc��ʱ��Ԥ��Ƶ��
//72000000/(719+1)/(1999+1)=50Hz  1/50*1000=20ms
//Timer2--ͨ����-->PA1
void TIM1_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);// 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);  //ʹ��GPIO����ʱ��ʹ��
																		

	//���ø�����Ϊ�����������,���TIM1 CH4��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; //TIM1_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/****************** 72000000Hz / 2000 / 720=50Hz*******************/
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ


	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0; //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx

	TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE �����ʹ��	

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	 

	TIM_ARRPreloadConfig(TIM1, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���

	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1����
}

/*****************************************************
* ������Servo_TurnAngle
* ������angle--�����ת���ĽǶ�
* ���ܣ���ʱ������20ms�Ļ�׼����
* ��ע��
*      ����     0.5   1.0   1.5   2.0   2.5
*      �Ƕ�     0     45    90   135   180                    
*****************************************************/	
void Servo_TurnAngle(u16 angle)
{
	float count;//��ʱ��2����ֵ
	count = (10.0 / 9.0) * angle + 50.0;//��ʱ������ֵ��ǶȵĹ�ϵ���Ƕ� *��10 / 9��+ 50 = ����ֵ��
	TIM_SetCompare1(TIM1, (uint16_t)count);//��ʱ��2ͨ��1�ȽϼĴ�������	
}


// ��·PWM���
void TIM_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    GPIO_InitTypeDef    GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4 , ENABLE);
    

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; //TIM3��1��2ͨ��    ������PWM
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);       //PA��6��7�ڶ�ӦTIM3��1��2ͨ��������Ϊ�����������
 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; //TIM4��1��2��3��4ͨ��
    GPIO_Init(GPIOB,&GPIO_InitStructure);     //B�ڵ�6��7��8��9��ӦTIM4��1��2��3��4ͨ��������Ϊ�����������
 
    TIM_TimeBaseStructure.TIM_Period =9999;           //�Զ���������ֵ
    TIM_TimeBaseStructure.TIM_Prescaler =143;          //Ԥ��Ƶֵ ,������50HZ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;        //ʱ�ӷָ�
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;      //������ʽΪ���ϼ���
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);         //TIM3,��TIM4�õ���ͬ���ã�д������  ,PWMƵ��Ϊ50HZ
                                                                      
    //�趨ռ�ձ�
    
    TIM_OCStructInit(& TIM_OCInitStructure);      //�ָ���ʼ
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  //��ʱ��ģʽΪpwmģʽ1
    TIM_OCInitStructure.TIM_Pulse =0;              //����ֵ����������ǵ͵�ƽ
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //����Ϊ��
    
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);     //����������д��TIM3��ͨ��1
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);    //Ԥװ��ʹ��
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
 
    TIM_OC1Init(TIM4, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);//TIM4��4��ͨ��������ͬ������
    TIM_Cmd(TIM3, ENABLE);
    TIM_CtrlPWMOutputs(TIM3, ENABLE);
    TIM_Cmd(TIM4, ENABLE);
    TIM_CtrlPWMOutputs(TIM4, ENABLE);          //ʹ��PWMģʽ
}

void SetJointAngle(u8 ID, float angle)
{
    switch(ID)
    {
        case 0:                                      //-90��~90��   
            angle=angle+90.0;                      
            angle=(u16)(50.0*angle/9.0+249.0);     
            TIM_SetCompare1(TIM3,angle);        
            break;
                                                 //0��~180��
        case 1:
            angle=(u16)(4.175*angle+409.25);
            TIM_SetCompare2(TIM3,angle);          
            break;
 
        case 2:                                    //-150��~0��
            angle=-angle;
            angle=(u16)(4.175*angle+480.0);
            TIM_SetCompare1(TIM4,angle);
            break;
 
        case 3:
            angle=-180-angle;
            angle=-angle;
            angle=(u16)(4.175*angle+315.0);
 
            TIM_SetCompare2(TIM4,angle);
            break;
                                              //-90��~90��
        case 4:
            angle=90.0+angle;
            angle=(u16)(249.0+50.0*angle/9.0);
            TIM_SetCompare3(TIM4,angle);            
            break; 
 
        default: break;
    }    
}

/***************STM32F103C8T6**********************
* ����    : �������
* ʵ��ƽ̨��STM32F103RCT6
* ��ע    ��ʹ�ö�ʱ��������pwm�������ƶ������
* �ӿ�    ��TIM1, CH1-PB13, CH2-PB14, CH3-PB15
****************STM32F103C8T6**********************/
/* ����TIM1�������PWMʱ�õ���I/O  */
static void TIM1_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);//��ʱ��1ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//GPIOBʱ��ʹ��

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOB, &GPIO_InitStructure);

}

/*����TIM1�����PWM�źŵ�ģʽ�������ڡ����ԡ�ռ�ձ� */
static void TIM1_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	/* PWM�źŵ�ƽ����ֵ */
	u16 CCR1_Val = 0;        
	u16 CCR2_Val = 0;
	//u16 CCR3_Val = 50000;


	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 20000 - 1;//��ʱ������,20ms
	TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;//ʱ��Ԥ��Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//������ʽ�����ϼ���

	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;//ѡ��ʱ��ģʽ��tim�������2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;//����
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;//������ͨ��
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;

	TIM_OC1Init(TIM1, &TIM_OCInitStructure);

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);

	/* PWM1 Mode configuration: Channel2 */

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR2_Val;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;//������ͨ��
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;         

	TIM_OC2Init(TIM1, &TIM_OCInitStructure);

	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);      


	/* PWM1 Mode configuration: Channel3 */
	/*
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR3_Val;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;//������ͨ��
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;         

	TIM_OC3Init(TIM1, &TIM_OCInitStructure);

	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);        */



	TIM_ARRPreloadConfig(TIM1, ENABLE);

	/* TIM1 enable counter */
	TIM_Cmd(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);      
}

/*���úͳ�ʼ��TIM1 */
void TIM1_PWM_Init_Ex(void)
{
	TIM1_GPIO_Config();
	TIM1_Mode_Config();      
}

//����ڶ�
void Servo_out(void)
{
	TIM1->CCR1 = 2000;//pwm���ߵ�ƽ����ʱ�䣬2ms
	delay_ms(2000);
	while(1)
	{
		TIM1->CCR1 = 1500;
		delay_ms(1000);
		TIM1->CCR1 = 2500;      
		delay_ms(1000);
	}
}

