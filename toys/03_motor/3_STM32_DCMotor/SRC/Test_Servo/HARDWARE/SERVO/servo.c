#include "servo.h"
#include "led.h"
#include "delay.h"



//PWM输出初始化
//arr：自动重装值
//psc：时钟预分频数
//72000000/(719+1)/(1999+1)=50Hz  1/50*1000=20ms
//Timer2--通道二-->PA1
void TIM1_PWM_Init(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);// 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);  //使能GPIO外设时钟使能
																		

	//设置该引脚为复用输出功能,输出TIM1 CH4的PWM脉冲波形
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13; //TIM1_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/****************** 72000000Hz / 2000 / 720=50Hz*******************/
	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 80K
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位


	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; //选择定时器模式:TIM脉冲宽度调制模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //比较输出使能
	TIM_OCInitStructure.TIM_Pulse = 0; //设置待装入捕获比较寄存器的脉冲值
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; //输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //根据TIM_OCInitStruct中指定的参数初始化外设TIMx

	TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE 主输出使能	

	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //CH1预装载使能	 

	TIM_ARRPreloadConfig(TIM1, ENABLE); //使能TIMx在ARR上的预装载寄存器

	TIM_Cmd(TIM1, ENABLE);  //使能TIM1外设
}

/*****************************************************
* 函数：Servo_TurnAngle
* 参数：angle--舵机能转过的角度
* 功能：定时器产生20ms的基准脉冲
* 备注：
*      脉冲     0.5   1.0   1.5   2.0   2.5
*      角度     0     45    90   135   180                    
*****************************************************/	
void Servo_TurnAngle(u16 angle)
{
	float count;//定时器2计数值
	count = (10.0 / 9.0) * angle + 50.0;//定时器计数值与角度的关系（角度 *（10 / 9）+ 50 = 计数值）
	TIM_SetCompare1(TIM1, (uint16_t)count);//定时器2通道1比较寄存器设置	
}


// 多路PWM输出
void TIM_Configuration(void)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    GPIO_InitTypeDef    GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4 , ENABLE);
    

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; //TIM3的1、2通道    ，产生PWM
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);       //PA的6，7口对应TIM3的1、2通道，设置为复用推挽输出
 
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9; //TIM4的1、2、3、4通道
    GPIO_Init(GPIOB,&GPIO_InitStructure);     //B口的6，7，8，9对应TIM4的1、2、3、4通道，设置为复用推挽输出
 
    TIM_TimeBaseStructure.TIM_Period =9999;           //自动重载周期值
    TIM_TimeBaseStructure.TIM_Prescaler =143;          //预分频值 ,这里是50HZ
    TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;        //时钟分割
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;      //计数摸式为向上计数
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);         //TIM3,和TIM4用的相同配置，写入配置  ,PWM频率为50HZ
                                                                      
    //设定占空比
    
    TIM_OCStructInit(& TIM_OCInitStructure);      //恢复初始
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;  //定时器模式为pwm模式1
    TIM_OCInitStructure.TIM_Pulse =0;              //脉冲值，即输出都是低电平
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //极性为高
    
    TIM_OC1Init(TIM3, &TIM_OCInitStructure);     //将配置数据写入TIM3的通道1
    TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);    //预装载使能
    TIM_OC2Init(TIM3, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
 
    TIM_OC1Init(TIM4, &TIM_OCInitStructure);
    TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_OC2Init(TIM4, &TIM_OCInitStructure);
    TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_OC3Init(TIM4, &TIM_OCInitStructure);
    TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
    TIM_OC4Init(TIM4, &TIM_OCInitStructure);
    TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);//TIM4的4个通道都用相同的配置
    TIM_Cmd(TIM3, ENABLE);
    TIM_CtrlPWMOutputs(TIM3, ENABLE);
    TIM_Cmd(TIM4, ENABLE);
    TIM_CtrlPWMOutputs(TIM4, ENABLE);          //使能PWM模式
}

void SetJointAngle(u8 ID, float angle)
{
    switch(ID)
    {
        case 0:                                      //-90°~90°   
            angle=angle+90.0;                      
            angle=(u16)(50.0*angle/9.0+249.0);     
            TIM_SetCompare1(TIM3,angle);        
            break;
                                                 //0°~180°
        case 1:
            angle=(u16)(4.175*angle+409.25);
            TIM_SetCompare2(TIM3,angle);          
            break;
 
        case 2:                                    //-150°~0°
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
                                              //-90°~90°
        case 4:
            angle=90.0+angle;
            angle=(u16)(249.0+50.0*angle/9.0);
            TIM_SetCompare3(TIM4,angle);            
            break; 
 
        default: break;
    }    
}

/***************STM32F103C8T6**********************
* 描述    : 舵机测试
* 实验平台：STM32F103RCT6
* 备注    ：使用定时器来产生pwm波，控制舵机动作
* 接口    ：TIM1, CH1-PB13, CH2-PB14, CH3-PB15
****************STM32F103C8T6**********************/
/* 配置TIM1复用输出PWM时用到的I/O  */
static void TIM1_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);//定时器1时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//GPIOB时钟使能

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOB, &GPIO_InitStructure);

}

/*配置TIM1输出的PWM信号的模式，如周期、极性、占空比 */
static void TIM1_Mode_Config(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	/* PWM信号电平跳变值 */
	u16 CCR1_Val = 0;        
	u16 CCR2_Val = 0;
	//u16 CCR3_Val = 50000;


	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 20000 - 1;//定时器周期,20ms
	TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1;//时钟预分频
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;//计数方式：向上计数

	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1 */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;//选择定时器模式：tim脉宽调制2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//比较输出使能
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse = CCR1_Val;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;//极性
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;//开反向通道
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
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;//开反向通道
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
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;//开反向通道
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;         

	TIM_OC3Init(TIM1, &TIM_OCInitStructure);

	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);        */



	TIM_ARRPreloadConfig(TIM1, ENABLE);

	/* TIM1 enable counter */
	TIM_Cmd(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);      
}

/*配置和初始化TIM1 */
void TIM1_PWM_Init_Ex(void)
{
	TIM1_GPIO_Config();
	TIM1_Mode_Config();      
}

//舵机摆动
void Servo_out(void)
{
	TIM1->CCR1 = 2000;//pwm波高电平持续时间，2ms
	delay_ms(2000);
	while(1)
	{
		TIM1->CCR1 = 1500;
		delay_ms(1000);
		TIM1->CCR1 = 2500;      
		delay_ms(1000);
	}
}

