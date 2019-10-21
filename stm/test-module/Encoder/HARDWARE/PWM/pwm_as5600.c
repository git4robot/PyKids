#include "pwm_as5600.h"
#include "sys.h"
#include "usart.h"

volatile uint16_t IC2Value = 0;
volatile uint16_t DutyCycle = 0;
volatile uint32_t Frequency = 0;

/*
重要概念理解（对于理解输入捕获功能很重要，特别看了数据手册CCR1\CCR2\CCR3\CCR3云里雾里）
PWM输入捕获模式是输入捕获模式的特例，自己理解如下
1. 每个定时器有四个输入捕获通道IC1、IC2、IC3、IC4。且IC1 IC2一组，IC3 IC4一组。并且可是设置管脚和寄存器的对应关系。
2. 同一个TIx输入映射了两个ICx信号。
3. 这两个ICx信号分别在相反的极性边沿有效。
4. 两个边沿信号中的一个被选为触发信号，并且从模式控制器被设置成复位模式。
5. 当触发信号来临时，被设置成触发输入信号的捕获寄存器，捕获“一个PWM周期（即连续的两个上升沿或下降沿）”，
   它等于包含TIM时钟周期的个数（即捕获寄存器中捕获的为TIM的计数个数n）。
6. 同样另一个捕获通道捕获触发信号和下一个相反极性的边沿信号的计数个数m，即（即高电平的周期或低电平的周期）
7. 由此可以计算出PWM的时钟周期和占空比了
   frequency=f（TIM时钟频率）/n。
    duty cycle=（高电平计数个数/n），
    若m为高电平计数个数，则duty cycle=m/n
    若m为低电平计数个数，则duty cycle=（n-m）/n
注：因为计数器为16位，所以一个周期最多计数65535个，所以测得的 最小频率= TIM时钟频率/65535。
程序概述：选择TIM3的通道2作为PWM输入捕获。IC2设置为上升沿，并设置为有效的触发输入信号。
所以IC2的捕获寄存器捕获PWM周期，IC1的捕获寄存器捕获PWM的高电平周期。
*/
void PWM_INPUT_Config(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    //时钟配置
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //NVIC配置
    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
#if 0
	//想改变测量的PWM频率范围，可将TIM时钟频率做分频处理
    TIM_TimeBaseStructure.TIM_Period = 0xFFFF; //周期0～FFFF 设定计数器自动重装值
    TIM_TimeBaseStructure.TIM_Prescaler = 5; 	//预分频器 分频数为5+1即6分频
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; //设置时钟分割:TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
#endif	
    TIM_ICInitStructure.TIM_Channel=TIM_Channel_2;					//通道选择
    TIM_ICInitStructure.TIM_ICFilter=0x0;
    TIM_ICInitStructure.TIM_ICPolarity=TIM_ICPolarity_Rising;		//上升沿触发
    TIM_ICInitStructure.TIM_ICPrescaler=TIM_ICPSC_DIV1;
    TIM_ICInitStructure.TIM_ICSelection=TIM_ICSelection_DirectTI;	//管脚与寄存器对应关系

	//输入预分频。意思是控制在多少个  输入周期做一次捕获，如果
	//输入的信号频率没有变，测得的周期也不会变。比如选择4分频，
	//则每四个输入周期才做一次捕获，这样在输入信号变化不频繁的情况下，
	//可以减少软件被不断中断的次数。
    TIM_ICInitStructure.TIM_ICFilter = 0x0;      	//滤波设置，经历几个周期跳变认定波形稳定0x0～0xF
    TIM_PWMIConfig(TIM3,&TIM_ICInitStructure);		//根据参数配置TIM外设信息
    TIM_SelectInputTrigger(TIM3,TIM_TS_TI2FP2);		//选择IC2为始终触发源
    TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);
    //TIM从模式：触发信号的上升沿重新初始化计数器和触发寄存器的更新事件
    TIM_SelectMasterSlaveMode(TIM3,TIM_MasterSlaveMode_Enable);		//启动定时器的被动触发
    TIM_Cmd(TIM3,ENABLE);										//启动TIM3
    TIM_ITConfig(TIM3,TIM_IT_CC2,ENABLE);				//打开中断
}

//中断处理函数
void TIM3_IRQHandler(void)
{
	//这里最好加判断
    TIM_ClearITPendingBit(TIM3, TIM_IT_CC2);	//清除TIM的中断待处理位
    IC2Value = TIM_GetCapture2(TIM3);			//读取IC2捕获寄存器的值，即为PWM周期的计数值

    if (IC2Value != 0)
    {
		//读取IC1捕获寄存器的值，并计算占空比
        DutyCycle = (TIM_GetCapture1(TIM3) * 100) / IC2Value;
		//计算PWM频率
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

