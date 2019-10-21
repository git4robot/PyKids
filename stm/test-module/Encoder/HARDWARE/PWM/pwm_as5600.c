#include "pwm_as5600.h"
#include "sys.h"
#include "usart.h"

volatile uint16_t IC2Value = 0;
volatile uint16_t DutyCycle = 0;
volatile uint32_t Frequency = 0;

/*
��Ҫ������⣨����������벶���ܺ���Ҫ���ر��������ֲ�CCR1\CCR2\CCR3\CCR3�������
PWM���벶��ģʽ�����벶��ģʽ���������Լ��������
1. ÿ����ʱ�����ĸ����벶��ͨ��IC1��IC2��IC3��IC4����IC1 IC2һ�飬IC3 IC4һ�顣���ҿ������ùܽźͼĴ����Ķ�Ӧ��ϵ��
2. ͬһ��TIx����ӳ��������ICx�źš�
3. ������ICx�źŷֱ����෴�ļ��Ա�����Ч��
4. ���������ź��е�һ����ѡΪ�����źţ����Ҵ�ģʽ�����������óɸ�λģʽ��
5. �������ź�����ʱ�������óɴ��������źŵĲ���Ĵ���������һ��PWM���ڣ������������������ػ��½��أ�����
   �����ڰ���TIMʱ�����ڵĸ�����������Ĵ����в����ΪTIM�ļ�������n����
6. ͬ����һ������ͨ�����񴥷��źź���һ���෴���Եı����źŵļ�������m���������ߵ�ƽ�����ڻ�͵�ƽ�����ڣ�
7. �ɴ˿��Լ����PWM��ʱ�����ں�ռ�ձ���
   frequency=f��TIMʱ��Ƶ�ʣ�/n��
    duty cycle=���ߵ�ƽ��������/n����
    ��mΪ�ߵ�ƽ������������duty cycle=m/n
    ��mΪ�͵�ƽ������������duty cycle=��n-m��/n
ע����Ϊ������Ϊ16λ������һ������������65535�������Բ�õ� ��СƵ��= TIMʱ��Ƶ��/65535��
���������ѡ��TIM3��ͨ��2��ΪPWM���벶��IC2����Ϊ�����أ�������Ϊ��Ч�Ĵ��������źš�
����IC2�Ĳ���Ĵ�������PWM���ڣ�IC1�Ĳ���Ĵ�������PWM�ĸߵ�ƽ���ڡ�
*/
void PWM_INPUT_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    //ʱ������
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //NVIC����
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
#if 0
	//��ı������PWMƵ�ʷ�Χ���ɽ�TIMʱ��Ƶ������Ƶ����
    TIM_TimeBaseStructure.TIM_Period = 0xFFFF; //����0��FFFF �趨�������Զ���װֵ
    TIM_TimeBaseStructure.TIM_Prescaler = 5; 	//Ԥ��Ƶ�� ��Ƶ��Ϊ5+1��6��Ƶ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //����ʱ�ӷָ�:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
#endif	
    TIM_ICInitStructure.TIM_Channel=TIM_Channel_2;					//ͨ��ѡ��
    TIM_ICInitStructure.TIM_ICFilter=0x0;
    TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;		//�����ش���
    TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;	//�ܽ���Ĵ�����Ӧ��ϵ

	//����Ԥ��Ƶ����˼�ǿ����ڶ��ٸ�  ����������һ�β������
	//������ź�Ƶ��û�б䣬��õ�����Ҳ����䡣����ѡ��4��Ƶ��
	//��ÿ�ĸ��������ڲ���һ�β��������������źű仯��Ƶ��������£�
	//���Լ�������������жϵĴ�����
    TIM_ICInitStructure.TIM_ICFilter = 0x0;      	//�˲����ã������������������϶������ȶ�0x0��0xF
    TIM_PWMIConfig(TIM3,&TIM_ICInitStructure);		//���ݲ�������TIM������Ϣ
    TIM_SelectInputTrigger(TIM3,TIM_TS_TI2FP2);		//ѡ��IC2Ϊʼ�մ���Դ
    TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);
    //TIM��ģʽ�������źŵ����������³�ʼ���������ʹ����Ĵ����ĸ����¼�
    TIM_SelectMasterSlaveMode(TIM3,TIM_MasterSlaveMode_Enable);		//������ʱ���ı�������
    TIM_Cmd(TIM3,ENABLE);										//����TIM3
    TIM_ITConfig(TIM3,TIM_IT_CC2,ENABLE);				//���ж�
}

//�жϴ�����
void TIM3_IRQHandler(void)
{
	//������ü��ж�
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);	//���TIM���жϴ�����λ
    IC2Value = TIM_GetCapture2(TIM3);			//��ȡIC2����Ĵ�����ֵ����ΪPWM���ڵļ���ֵ

    if (IC2Value != 0)
    {
		//��ȡIC1����Ĵ�����ֵ��������ռ�ձ�
        DutyCycle = (TIM_GetCapture1(TIM3) * 100) / IC2Value;
		//����PWMƵ��
        Frequency = 72000000 / IC2Value;
    }
    else
    {
        DutyCycle = 0;
        Frequency = 0;
    }

    printf("DutyCycle= %d, ",DutyCycle);
	printf("Frequency= %d \r\n\r\n",Frequency);
}

