/**---------------------------------------------------------------
	��Ŀ��������ƽ��С��(Two-Wheels Auto-Balancing Vechile)
	�汾��v1.0.0
	�ļ���QuadratureEncoder.c
	���ܣ�ͨ����������������õ�С����������ת�١�ת��
	���ߣ�flotox@yeah.net
	���ڣ�2014.9.4
	���£�2014.9.4
----------------------------------------------------------------*/

#include	"stm32f10x.h"
#include	"QuadratureEncoder.h"

/**
	*	@brief		EXTI3����(����)
	*	@param		none
	*	@retval		none
	*/
void	QE_Exti3_Config(void){
	
	EXTI_InitTypeDef	EXTI_InitStructure;
	GPIO_InitTypeDef	GPIO_InitStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;
	
	/*ʹ��GPIOA��GPIOB��AFIO����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	
	/*JTAG-DP Disabled and SW-DP Enabled*/
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	/*��ʼ��PA.15�˿�ΪIN_FLOATINGģʽ*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/*��ʼ��PB.03�˿�ΪIN_FLOATINGģʽ*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/*ѡ��PB.03Ϊ�ⲿ�ж�*/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource3);
	
	/*����Px.03ΪӲ���ж�ģʽ�������ش���*/
	EXTI_InitStructure.EXTI_Line = EXTI_Line3;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	/*EXTI3 NVIC����*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);							//2 bits for pre-emption priority 2 bits for subpriority
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;		//ָ����ռʽ���ȼ���,��ȡ0~3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;					//ָ����Ӧʽ���ȼ���,��ȡ0~3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/**
	*	@brief		EXTI5����(����)
	*	@param		none
	*	@retval		none
	*/
void	QE_Exti9_5_Config(void){
	
	EXTI_InitTypeDef	EXTI_InitStructure;
	GPIO_InitTypeDef	GPIO_InitStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;
	
	/*ʹ��GPIOB��AFIO����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	
	/*JTAG-DP Disabled and SW-DP Enabled*/
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);
	
	/*��ʼ��PB.04�˿ں�PB.05�˿�ΪIN_FLOATINGģʽ*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/*ѡ��PB.05Ϊ�ⲿ�ж�*/
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource5);
	
	/*����Px.05ΪӲ���ж�ģʽ�������ش���*/
	EXTI_InitStructure.EXTI_Line = EXTI_Line5;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	/*EXTI5 NVIC����*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);							//2 bits for pre-emption priority 2 bits for subpriority
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;		//ָ����ռʽ���ȼ���,��ȡ0~3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;					//ָ����Ӧʽ���ȼ���,��ȡ0~3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/**
	*	@brief		���������������ʼ��
	*	@param		none
	*	@retval		none
	*/
void	QE_Init(void){
	
	QE_Exti3_Config();
	QE_Exti9_5_Config();
}
