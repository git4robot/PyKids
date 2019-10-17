
#include "led.h"
#include "delay.h"
#include "sys.h"
#include "pwm.h"
#include "key.h"
#define key1 PCin(5)
#define key2 PAin(15)
#define key3 PAin(0)


void TIM3_CH1_Init();
void TIM3_CH2_Init();

int main()
{
	u8 flag = 20;
	
    KEY_Init();
    delay_init();	    	     //��ʱ������ʼ��
    LED_Init();		  	          //��ʼ����LED���ӵ�Ӳ���ӿ�	
    TIM3_CH1_Init();
	TIM3_CH2_Init();
	
	// ռ�ձȣ�x / 20
	TIM_SetCompare1(TIM3, 16);	
	TIM_SetCompare2(TIM3, 0);
	delay_ms(2000);
	TIM_SetCompare1(TIM3, 8);	// 8/20 = 40%
	TIM_SetCompare2(TIM3, 0);
	delay_ms(2000);
	
    while(1)
    {
		if(flag == 20) {
			flag = 0;
		} else {
			flag = 20;
		}
		
		// ռ�ձȣ�x / 20
		TIM_SetCompare1(TIM3, 13);	
		TIM_SetCompare2(TIM3, 0);
		delay_ms(5000);
		TIM_SetCompare1(TIM3, 13);	
		TIM_SetCompare2(TIM3, 20);
		delay_ms(5000);		
		TIM_SetCompare1(TIM3, 0);	
		TIM_SetCompare2(TIM3, 13);
		delay_ms(5000);	
		TIM_SetCompare1(TIM3, 20);	
		TIM_SetCompare2(TIM3, 13);
		delay_ms(5000);			
		//TIM_SetCompare1(TIM3, 4);	// 8/20 = 40%
		//TIM_SetCompare2(TIM3, flag);
		//delay_ms(3000);	
		
		#if 0
		TIM_SetCompare1(TIM3, 6);	//6/20 = 30%
		TIM_SetCompare2(TIM3, 12);	// 12/20 = 60%
		delay_us(2000);
		TIM_SetCompare1(TIM3, 0);
		TIM_SetCompare2(TIM3, 0);
		#endif
		delay_us(2000);
    }
}


void TIM3_CH1_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
    TIM_TimeBaseInitTypeDef TIM3_CH1;

    TIM_OCInitTypeDef TIM3_OC_PWM;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    //���ø�����Ϊ�����������,���TIM1 CH1��PWM���岨��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM3_CH1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//arr=499 psc=71 -->PWM Ƶ��=72000000/(500*72)=2khz�� ����=0.0005s
	TIM3_CH1.TIM_Period=20-1;  //�Զ�����ֵ	
    TIM3_CH1.TIM_Prescaler=72-1;  //��Ƶϵ�� 72,000,000Hz /(20*72) = 50kHz
	
    TIM3_CH1.TIM_CounterMode=TIM_CounterMode_Up;

    TIM3_CH1.TIM_ClockDivision=TIM_CKD_DIV1;

    TIM_TimeBaseInit(TIM3,&TIM3_CH1);


    TIM3_OC_PWM.TIM_OCMode=TIM_OCMode_PWM1;

    TIM3_OC_PWM.TIM_OutputState=TIM_OutputState_Enable;

    TIM3_OC_PWM.TIM_OCPolarity=TIM_OCPolarity_High;

    TIM3_OC_PWM.TIM_Pulse=0;//ռ�ձ�Ϊ50%

    TIM_OC1Init(TIM3,&TIM3_OC_PWM);

    TIM_OC1PreloadConfig(TIM3,TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM3,ENABLE);

    TIM_Cmd(TIM3,ENABLE);
}


void TIM3_CH2_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
    TIM_TimeBaseInitTypeDef TIM3_CH2;

    TIM_OCInitTypeDef TIM3_OC_PWM;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    //���ø�����Ϊ�����������,���TIM1 CH1��PWM���岨��
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM3_CH2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);	

	//arr=499 psc=71 -->PWM Ƶ��=72000000/(500*72)=2khz�� ����=0.0005s
	TIM3_CH2.TIM_Period=20-1;  //�Զ�����ֵ	
    TIM3_CH2.TIM_Prescaler=72-1;  //��Ƶϵ�� 72,000,000Hz /(20*72) = 50kHz

    TIM3_CH2.TIM_CounterMode=TIM_CounterMode_Up;

    TIM3_CH2.TIM_ClockDivision=TIM_CKD_DIV1;

    TIM_TimeBaseInit(TIM3,&TIM3_CH2);


    TIM3_OC_PWM.TIM_OCMode=TIM_OCMode_PWM1;

    TIM3_OC_PWM.TIM_OutputState=TIM_OutputState_Enable;

    TIM3_OC_PWM.TIM_OCPolarity=TIM_OCPolarity_High;

    TIM3_OC_PWM.TIM_Pulse=0;//ռ�ձ�Ϊ50%

    TIM_OC2Init(TIM3,&TIM3_OC_PWM);

    TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(TIM3, ENABLE);

    TIM_Cmd(TIM3,ENABLE);
}



#if 0
#include"stm32f10x.h"


void RCC_Cfg(void);
void GPIO_Cfg(void);
void TIM_Cfg(void);
void NVIC_Cfg(void);
void PWM_Cfg(float dutyfactor1,float dutyfactor2,float dutyfactor3,float dutyfactor4);


int main(void)
{
    u8 flag = 1;
    float ooo=0.1;
    RCC_Cfg();
    NVIC_Cfg();
    GPIO_Cfg();
    TIM_Cfg();

    //������ʱ��2
    TIM_Cmd(TIM3,ENABLE);

    //������
    while(1) {
        PWM_Cfg(100,200,300,400);
#if 0
        if(flag == 1)
        {
            ooo=ooo+0.002;
        }
        if(flag == 0)
        {
            ooo=ooo-0.002;
        }
        if(ooo>100) {
            flag = 0;
        }
        if(ooo<0.5)
        {
            flag = 1;
        }
#endif
    }
}
#endif

void GPIO_Cfg(void)
{

    GPIO_InitTypeDef GPIO_InitStructure;
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);

    //ȫ��ӳ�䣬��TIM3_CH2ӳ�䵽PB5
    //����STM32���Ĳο��ֲ�2010�еڵ�119ҳ��֪��
    //��û����ӳ��ʱ��TIM3���ĸ�ͨ��CH1��CH2��CH3��CH4�ֱ��ӦPA6��PA7,PB0,PB1
    //��������ӳ��ʱ��TIM3���ĸ�ͨ��CH1��CH2��CH3��CH4�ֱ��ӦPB4��PB5,PB0,PB1
    //����ȫ��ӳ��ʱ��TIM3���ĸ�ͨ��CH1��CH2��CH3��CH4�ֱ��ӦPC6��PC7,PC8,PC9
    //Ҳ����˵����ȫ��ӳ��֮���ĸ�ͨ����PWM������ŷֱ�ΪPC6��PC7,PC8,PC9��
	//�����õ���ͨ��1��ͨ��2�����Զ�Ӧ����ΪPC6��PC7,PC8,PC9
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);

    //������ӳ��Ĳ���
    //GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);

    //����PC6��PC7��PC8��PC9Ϊ������������4·PWM
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
    GPIO_Init(GPIOC,&GPIO_InitStructure);
}

void TIM_Cfg(void)
{
    //����ṹ��
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    //���½�Timer����Ϊȱʡֵ
    TIM_DeInit(TIM3);
    //�����ڲ�ʱ�Ӹ�TIM2�ṩʱ��Դ
    TIM_InternalClockConfig(TIM3);

    //Ԥ��Ƶϵ��Ϊ0����������Ԥ��Ƶ����ʱTIMER��Ƶ��Ϊ72MHzre.TIM_Prescaler =0;
    TIM_TimeBaseStructure.TIM_Prescaler = 2000-1;
    //���ü��������С��ÿ��20000�����Ͳ���һ�������¼�
    TIM_TimeBaseStructure.TIM_Period = 720 - 1;
    //����ʱ�ӷָ�
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    //���ü�����ģʽΪ���ϼ���ģʽ
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    //������Ӧ�õ�TIM2��
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
    //�������жϱ�־
    //TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    //��ֹARRԤװ�ػ�����
    //TIM_ARRPreloadConfig(TIM2, DISABLE);
    //����TIM2���ж�
    //TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
}



/*******************************************************************************
* �� �� ��         : PWM���������ú���
* ��������         : PWM_Cfg
* ��    ��         : dutyfactor ռ�ձ���ֵ����С��0.014��100
* ��    ��         : ��
*******************************************************************************/
void PWM_Cfg(float dutyfactor1,float dutyfactor2,float dutyfactor3,float dutyfactor4)
{
    TIM_OCInitTypeDef TIM_OCInitStructure;
    //����ȱʡֵ
    TIM_OCStructInit(&TIM_OCInitStructure);

    //TIM3��CH1���
    TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1; //������PWMģʽ���ǱȽ�ģʽ
    TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable; //�Ƚ����ʹ�ܣ�ʹ��PWM������˿�
    TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High; //���ü����Ǹ߻��ǵ�
    //����ռ�ձȣ�ռ�ձ�=(CCRx/ARR)*100%��(TIM_Pulse/TIM_Period)*100%
    TIM_OCInitStructure.TIM_Pulse = dutyfactor1;// * 7200 / 100;
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);

    //TIM3��CH2���
    TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1; //������PWMģʽ���ǱȽ�ģʽ
    TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable; //�Ƚ����ʹ�ܣ�ʹ��PWM������˿�
    TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High; //���ü����Ǹ߻��ǵ�
    //����ռ�ձȣ�ռ�ձ�=(CCRx/ARR)*100%��(TIM_Pulse/TIM_Period)*100%
    TIM_OCInitStructure.TIM_Pulse = dutyfactor2;// * 7200 / 100;
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);

    //TIM3��CH3���
    TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1; //������PWMģʽ���ǱȽ�ģʽ
    TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable; //�Ƚ����ʹ�ܣ�ʹ��PWM������˿�
    TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High; //���ü����Ǹ߻��ǵ�
    //����ռ�ձȣ�ռ�ձ�=(CCRx/ARR)*100%��(TIM_Pulse/TIM_Period)*100%
    TIM_OCInitStructure.TIM_Pulse = dutyfactor3;// * 7200 / 100;
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);

    //TIM3��CH4���
    TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1; //������PWMģʽ���ǱȽ�ģʽ
    TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable; //�Ƚ����ʹ�ܣ�ʹ��PWM������˿�
    TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High; //���ü����Ǹ߻��ǵ�
    //����ռ�ձȣ�ռ�ձ�=(CCRx/ARR)*100%��(TIM_Pulse/TIM_Period)*100%
    TIM_OCInitStructure.TIM_Pulse = dutyfactor4;// * 7200 / 100;
    TIM_OC4Init(TIM3, &TIM_OCInitStructure);

    //ʹ�����״̬
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;

    //����TIM3��PWM���Ϊʹ��
    TIM_CtrlPWMOutputs(TIM3,ENABLE);
}


void NVIC_Cfg(void)
{
    //����ṹ��
    NVIC_InitTypeDef NVIC_InitStructure;

    //ѡ���жϷ���1
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    //ѡ��TIM2���ж�ͨ��
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    //��ռʽ�ж����ȼ�����Ϊ0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    //��Ӧʽ�ж����ȼ�����Ϊ0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    //ʹ���ж�
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);
}

void RCC_Cfg(void)
{
#if 0
    //�������״̬����
    ErrorStatus HSEStartUpStatus;

    //��RCC�Ĵ�����������ΪĬ��ֵ
    RCC_DeInit();

    //���ⲿ����ʱ�Ӿ���
    RCC_HSEConfig(RCC_HSE_ON);

    //�ȴ��ⲿ����ʱ�Ӿ�����
    HSEStartUpStatus = RCC_WaitForHSEStartUp();

    if(HSEStartUpStatus == SUCCESS)
    {
        //����AHBʱ��(HCLK)Ϊϵͳʱ��
        RCC_HCLKConfig(RCC_SYSCLK_Div1);

        //���ø���AHBʱ��(APB2)ΪHCLKʱ��
        RCC_PCLK2Config(RCC_HCLK_Div1);

        //���õ���AHBʱ��(APB1)ΪHCLK��2��Ƶ
        RCC_PCLK1Config(RCC_HCLK_Div2);

        //����FLASH������ʱ
        //FLASH_SetLatency(FLASH_Latency_2);

        //ʹ��Ԥȡָ����
        //FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

        //����PLLʱ�ӣ�ΪHSE��9��Ƶ 8MHz * 9 = 72MHz
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

        //ʹ��PLL
        RCC_PLLCmd(ENABLE);

        //�ȴ�PLL׼������
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

        //����PLLΪϵͳʱ��Դ
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

        //�ж�PLL�Ƿ���ϵͳʱ��
        while(RCC_GetSYSCLKSource() != 0x08);
    }
#endif
    //����TIM2��ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

    //����GPIO��ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);
}

void TIM2_IRQHandler(void)
{
    u16 aa=10;
    if(TIM_GetFlagStatus(TIM2,TIM_IT_Update)!=RESET)
    {
        //���TIM2���жϴ�����λ
        TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);


        TIM_Cmd(TIM2,DISABLE);
        //ͨ��ѭ���õ���˸
        while (aa) {
            GPIO_SetBits(GPIOC,GPIO_Pin_3);
            delay_ms(10);
            GPIO_ResetBits(GPIOC,GPIO_Pin_3);
            delay_ms(10);
            aa--;
        }
        //ʹ�Ƶ�״̬Ϊ��
        GPIO_SetBits(GPIOC,GPIO_Pin_3);
        TIM_Cmd(TIM2,ENABLE);
    }
}

#if 0
u16 cout;
int main(void)
{
    cout=1850;
    KEY_Init();
    delay_init();	    	     //��ʱ������ʼ��
    LED_Init();		  	          //��ʼ����LED���ӵ�Ӳ���ӿ�
    TIM1_PWM_Init(1999,719);    //PWMƵ��===(2000*720)/72000000=0.02=20ms

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

        TIM_SetCompare1(TIM1,cout); //PWM���
        delay_ms(50);
    }
}
#endif
