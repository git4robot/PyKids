
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
    delay_init();	    	     //延时函数初始化
    LED_Init();		  	          //初始化与LED连接的硬件接口	
    TIM3_CH1_Init();
	TIM3_CH2_Init();
	
	// 占空比：x / 20
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
		
		// 占空比：x / 20
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

    //设置该引脚为复用输出功能,输出TIM1 CH1的PWM脉冲波形
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //TIM3_CH1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//arr=499 psc=71 -->PWM 频率=72000000/(500*72)=2khz， 周期=0.0005s
	TIM3_CH1.TIM_Period=20-1;  //自动重载值	
    TIM3_CH1.TIM_Prescaler=72-1;  //分频系数 72,000,000Hz /(20*72) = 50kHz
	
    TIM3_CH1.TIM_CounterMode=TIM_CounterMode_Up;

    TIM3_CH1.TIM_ClockDivision=TIM_CKD_DIV1;

    TIM_TimeBaseInit(TIM3,&TIM3_CH1);


    TIM3_OC_PWM.TIM_OCMode=TIM_OCMode_PWM1;

    TIM3_OC_PWM.TIM_OutputState=TIM_OutputState_Enable;

    TIM3_OC_PWM.TIM_OCPolarity=TIM_OCPolarity_High;

    TIM3_OC_PWM.TIM_Pulse=0;//占空比为50%

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

    //设置该引脚为复用输出功能,输出TIM1 CH1的PWM脉冲波形
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; //TIM3_CH2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);	

	//arr=499 psc=71 -->PWM 频率=72000000/(500*72)=2khz， 周期=0.0005s
	TIM3_CH2.TIM_Period=20-1;  //自动重载值	
    TIM3_CH2.TIM_Prescaler=72-1;  //分频系数 72,000,000Hz /(20*72) = 50kHz

    TIM3_CH2.TIM_CounterMode=TIM_CounterMode_Up;

    TIM3_CH2.TIM_ClockDivision=TIM_CKD_DIV1;

    TIM_TimeBaseInit(TIM3,&TIM3_CH2);


    TIM3_OC_PWM.TIM_OCMode=TIM_OCMode_PWM1;

    TIM3_OC_PWM.TIM_OutputState=TIM_OutputState_Enable;

    TIM3_OC_PWM.TIM_OCPolarity=TIM_OCPolarity_High;

    TIM3_OC_PWM.TIM_Pulse=0;//占空比为50%

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

    //开启定时器2
    TIM_Cmd(TIM3,ENABLE);

    //呼吸灯
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

    //全部映射，将TIM3_CH2映射到PB5
    //根据STM32中文参考手册2010中第第119页可知：
    //当没有重映射时，TIM3的四个通道CH1，CH2，CH3，CH4分别对应PA6，PA7,PB0,PB1
    //当部分重映射时，TIM3的四个通道CH1，CH2，CH3，CH4分别对应PB4，PB5,PB0,PB1
    //当完全重映射时，TIM3的四个通道CH1，CH2，CH3，CH4分别对应PC6，PC7,PC8,PC9
    //也即是说，完全重映射之后，四个通道的PWM输出引脚分别为PC6，PC7,PC8,PC9，
	//我们用到了通道1和通道2，所以对应引脚为PC6，PC7,PC8,PC9
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM3, ENABLE);

    //部分重映射的参数
    //GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);

    //设置PC6、PC7、PC8、PC9为复用输出，输出4路PWM
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
    GPIO_Init(GPIOC,&GPIO_InitStructure);
}

void TIM_Cfg(void)
{
    //定义结构体
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

    //重新将Timer设置为缺省值
    TIM_DeInit(TIM3);
    //采用内部时钟给TIM2提供时钟源
    TIM_InternalClockConfig(TIM3);

    //预分频系数为0，即不进行预分频，此时TIMER的频率为72MHzre.TIM_Prescaler =0;
    TIM_TimeBaseStructure.TIM_Prescaler = 2000-1;
    //设置计数溢出大小，每计20000个数就产生一个更新事件
    TIM_TimeBaseStructure.TIM_Period = 720 - 1;
    //设置时钟分割
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    //设置计数器模式为向上计数模式
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    //将配置应用到TIM2中
    TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
    //清除溢出中断标志
    //TIM_ClearFlag(TIM2, TIM_FLAG_Update);
    //禁止ARR预装载缓冲器
    //TIM_ARRPreloadConfig(TIM2, DISABLE);
    //开启TIM2的中断
    //TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
}



/*******************************************************************************
* 函 数 名         : PWM波产生配置函数
* 函数功能         : PWM_Cfg
* 输    入         : dutyfactor 占空比数值，大小从0.014到100
* 输    出         : 无
*******************************************************************************/
void PWM_Cfg(float dutyfactor1,float dutyfactor2,float dutyfactor3,float dutyfactor4)
{
    TIM_OCInitTypeDef TIM_OCInitStructure;
    //设置缺省值
    TIM_OCStructInit(&TIM_OCInitStructure);

    //TIM3的CH1输出
    TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1; //设置是PWM模式还是比较模式
    TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable; //比较输出使能，使能PWM输出到端口
    TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High; //设置极性是高还是低
    //设置占空比，占空比=(CCRx/ARR)*100%或(TIM_Pulse/TIM_Period)*100%
    TIM_OCInitStructure.TIM_Pulse = dutyfactor1;// * 7200 / 100;
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);

    //TIM3的CH2输出
    TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1; //设置是PWM模式还是比较模式
    TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable; //比较输出使能，使能PWM输出到端口
    TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High; //设置极性是高还是低
    //设置占空比，占空比=(CCRx/ARR)*100%或(TIM_Pulse/TIM_Period)*100%
    TIM_OCInitStructure.TIM_Pulse = dutyfactor2;// * 7200 / 100;
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);

    //TIM3的CH3输出
    TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1; //设置是PWM模式还是比较模式
    TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable; //比较输出使能，使能PWM输出到端口
    TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High; //设置极性是高还是低
    //设置占空比，占空比=(CCRx/ARR)*100%或(TIM_Pulse/TIM_Period)*100%
    TIM_OCInitStructure.TIM_Pulse = dutyfactor3;// * 7200 / 100;
    TIM_OC3Init(TIM3, &TIM_OCInitStructure);

    //TIM3的CH4输出
    TIM_OCInitStructure.TIM_OCMode       = TIM_OCMode_PWM1; //设置是PWM模式还是比较模式
    TIM_OCInitStructure.TIM_OutputState  = TIM_OutputState_Enable; //比较输出使能，使能PWM输出到端口
    TIM_OCInitStructure.TIM_OCPolarity   = TIM_OCPolarity_High; //设置极性是高还是低
    //设置占空比，占空比=(CCRx/ARR)*100%或(TIM_Pulse/TIM_Period)*100%
    TIM_OCInitStructure.TIM_Pulse = dutyfactor4;// * 7200 / 100;
    TIM_OC4Init(TIM3, &TIM_OCInitStructure);

    //使能输出状态
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;

    //设置TIM3的PWM输出为使能
    TIM_CtrlPWMOutputs(TIM3,ENABLE);
}


void NVIC_Cfg(void)
{
    //定义结构体
    NVIC_InitTypeDef NVIC_InitStructure;

    //选择中断分组1
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    //选择TIM2的中断通道
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    //抢占式中断优先级设置为0
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    //响应式中断优先级设置为0
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    //使能中断
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    NVIC_Init(&NVIC_InitStructure);
}

void RCC_Cfg(void)
{
#if 0
    //定义错误状态变量
    ErrorStatus HSEStartUpStatus;

    //将RCC寄存器重新设置为默认值
    RCC_DeInit();

    //打开外部高速时钟晶振
    RCC_HSEConfig(RCC_HSE_ON);

    //等待外部高速时钟晶振工作
    HSEStartUpStatus = RCC_WaitForHSEStartUp();

    if(HSEStartUpStatus == SUCCESS)
    {
        //设置AHB时钟(HCLK)为系统时钟
        RCC_HCLKConfig(RCC_SYSCLK_Div1);

        //设置高速AHB时钟(APB2)为HCLK时钟
        RCC_PCLK2Config(RCC_HCLK_Div1);

        //设置低速AHB时钟(APB1)为HCLK的2分频
        RCC_PCLK1Config(RCC_HCLK_Div2);

        //设置FLASH代码延时
        //FLASH_SetLatency(FLASH_Latency_2);

        //使能预取指缓存
        //FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

        //设置PLL时钟，为HSE的9倍频 8MHz * 9 = 72MHz
        RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

        //使能PLL
        RCC_PLLCmd(ENABLE);

        //等待PLL准备就绪
        while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);

        //设置PLL为系统时钟源
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

        //判断PLL是否是系统时钟
        while(RCC_GetSYSCLKSource() != 0x08);
    }
#endif
    //允许TIM2的时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);

    //允许GPIO的时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);
}

void TIM2_IRQHandler(void)
{
    u16 aa=10;
    if(TIM_GetFlagStatus(TIM2,TIM_IT_Update)!=RESET)
    {
        //清除TIM2的中断待处理位
        TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);


        TIM_Cmd(TIM2,DISABLE);
        //通过循环让灯闪烁
        while (aa) {
            GPIO_SetBits(GPIOC,GPIO_Pin_3);
            delay_ms(10);
            GPIO_ResetBits(GPIOC,GPIO_Pin_3);
            delay_ms(10);
            aa--;
        }
        //使灯的状态为灭
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
    delay_init();	    	     //延时函数初始化
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
#endif
