/**---------------------------------------------------------------
	��Ŀ��������ƽ��С��(Two-Wheels Auto-Balancing Vechile)
	�汾��v1.0.0
	�ļ�: MotorDriver.c
	���ܣ��������
	���ߣ�flotox@yeah.net
	���ڣ�2014.9.5
	���£�2014.9.5
----------------------------------------------------------------*/

#include "stm32f10x.h"
#include "MotorDriver.h"
#include "GlobalVars.h"

#define	MOTOR_L_IN1_LOW			(GPIO_ResetBits(GPIOC, GPIO_Pin_6))
#define	MOTOR_L_IN1_HIGH		(GPIO_SetBits(GPIOC, GPIO_Pin_6))
#define	MOTOR_L_IN2_LOW			(GPIO_ResetBits(GPIOA, GPIO_Pin_7))
#define	MOTOR_L_IN2_HIGH		(GPIO_SetBits(GPIOA, GPIO_Pin_7))

#define	MOTOR_R_IN1_LOW			(GPIO_ResetBits(GPIOA, GPIO_Pin_8))
#define	MOTOR_R_IN1_HIGH		(GPIO_SetBits(GPIOA, GPIO_Pin_8))
#define	MOTOR_R_IN2_LOW			(GPIO_ResetBits(GPIOB, GPIO_Pin_13))
#define	MOTOR_R_IN2_HIGH		(GPIO_SetBits(GPIOB, GPIO_Pin_13))

/**
	*	@brief		���������������
	*	@param		none
	*	@retval		none
	*/
void	MotorDriver_L_Config(void){
	
	GPIO_InitTypeDef					GPIO_InitStructure ;
	TIM_TimeBaseInitTypeDef		TIM_BaseInitStructure;
	TIM_OCInitTypeDef					TIM_OCInitStructure;
	
	/*ʹ��GPIOA��GPIOC��AFIO��TIM8����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO | RCC_APB2Periph_TIM8, ENABLE);
	
	/*��ʼ��PA.07�˿�ΪOut_PPģʽ*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/*��ʼ��PC.06�˿�ΪOut_PPģʽ*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	/*��ʼ��PC.07�˿�(TIM8_CH2)ΪAF_PPģʽ*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	/*��ʱ����������*/
	TIM_BaseInitStructure.TIM_Prescaler = 3-1;													//ʱ��Ԥ��Ƶ��3,TIM8�ļ���ʱ��Ƶ��Ϊ24MHz
	TIM_BaseInitStructure.TIM_Period = 1000-1;													//�Զ���װ�ؼĴ�����ֵ,PWM2Ƶ��Ϊ24MHz/1000=24KHz
	TIM_BaseInitStructure.TIM_ClockDivision = 0;												//������Ƶ
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;					//���ϼ���
	TIM_BaseInitStructure.TIM_RepetitionCounter = 0;										//�ظ��Ĵ���
	TIM_TimeBaseInit(TIM8, &TIM_BaseInitStructure);

	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;										//PWM1���ģʽ
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;				//ʹ�ܸ�ͨ�����
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;						//�������
	TIM_OC2Init(TIM8, &TIM_OCInitStructure);														//��ָ��������ʼ��

	TIM_OC2PreloadConfig(TIM8, TIM_OCPreload_Enable);										//ʹ��TIM8��CCR2�ϵ�Ԥװ�ؼĴ���
	TIM_ARRPreloadConfig(TIM8, ENABLE);																	//ʹ��TIM8��ARR�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM8, ENABLE);																							//��TIM8
	TIM_CtrlPWMOutputs(TIM8, ENABLE);																		//PWM���ʹ��
}

/**
	*	@brief		���������������
	*	@param		none
	*	@retval		none
	*/
void	MotorDriver_R_Config(void){

	GPIO_InitTypeDef					GPIO_InitStructure ;
	TIM_TimeBaseInitTypeDef		TIM_BaseInitStructure;
	TIM_OCInitTypeDef					TIM_OCInitStructure;

	/*ʹ��GPIOA��GPIOB��AFIO��TIM1����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO | RCC_APB2Periph_TIM1, ENABLE);

	/*��ʼ��PA.08�˿�ΪOut_PPģʽ*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/*��ʼ��PB.13�˿�ΪOut_PPģʽ*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/*��ʼ��PA.09�˿�(TIM1_CH2)ΪAF_PPģʽ*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/*��ʱ����������*/
	TIM_BaseInitStructure.TIM_Prescaler = 3-1;													//ʱ��Ԥ��Ƶ��3,TIM1�ļ���ʱ��Ƶ��Ϊ24MHz
	TIM_BaseInitStructure.TIM_Period = 1000-1;													//�Զ���װ�ؼĴ�����ֵ,PWM2Ƶ��Ϊ24MHz/1000=24KHz
	TIM_BaseInitStructure.TIM_ClockDivision = 0;												//������Ƶ
	TIM_BaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;					//���ϼ���
	TIM_BaseInitStructure.TIM_RepetitionCounter = 0;										//�ظ��Ĵ���
	TIM_TimeBaseInit(TIM1, &TIM_BaseInitStructure);

	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;										//PWM1���ģʽ
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;				//ʹ�ܸ�ͨ�����
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;						//�������
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);														//��ָ��������ʼ��

	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);										//ʹ��TIM1��CCR2�ϵ�Ԥװ�ؼĴ���
	TIM_ARRPreloadConfig(TIM1, ENABLE);																	//ʹ��TIM1��ARR�ϵ�Ԥװ�ؼĴ���

	TIM_Cmd(TIM1, ENABLE);																							//��TIM1
	TIM_CtrlPWMOutputs(TIM1, ENABLE);																		//PWM���ʹ��
}

/**
	*	@brief		���ֵ����ת
	*	@param		none
	*	@retval		none
	*/
void	MotorDriver_L_Turn_Forward(void){
	
	MOTOR_L_IN1_LOW;
	MOTOR_L_IN2_HIGH;
}

/**
	*	@brief		���ֵ����ת
	*	@param		none
	*	@retval		none
	*/
void	MotorDriver_L_Turn_Reverse(void){
	
	MOTOR_L_IN1_HIGH;
	MOTOR_L_IN2_LOW;
}

/**
	*	@brief		���ֵ����ת
	*	@param		none
	*	@retval		none
	*/
void	MotorDriver_R_Turn_Forward(void){
	
	MOTOR_R_IN1_HIGH;
	MOTOR_R_IN2_LOW;
}

/**
	*	@brief		���ֵ����ת
	*	@param		none
	*	@retval		none
	*/
void	MotorDriver_R_Turn_Reverse(void){
	
	MOTOR_R_IN1_LOW;
	MOTOR_R_IN2_HIGH;
}

/**
	*	@brief		������������ʼ��
	*	@param		none
	*	@retval		none
	*/
void	MotorDriver_Init(void){
	
	MotorDriver_L_Config();
	MotorDriver_R_Config();
	
	MotorDriver_L_Turn_Forward();
	MotorDriver_R_Turn_Forward();
}
