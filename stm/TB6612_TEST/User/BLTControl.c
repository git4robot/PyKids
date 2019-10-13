/**---------------------------------------------------------------
	��Ŀ��������ƽ��С��(Two-Wheels Auto-Balancing Vechile)
	�汾��v1.0.0
	�ļ���BLTControl.c
	���ܣ���������ָ�����
	���ߣ�flotox@yeah.net
	���ڣ�2014.9.5
	���£�2014.9.5
----------------------------------------------------------------*/

#include "stm32f10x.h"
#include "BLTControl.h"

/**
	*	@brief		������������
	*	@param		none
	*	@retval		none
	*/
void	BLTControl_Init(void){
	
	GPIO_InitTypeDef	GPIO_InitStructure;
	USART_InitTypeDef	USART_InitStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;
	
	/*����GPIOB��GPIOC��GPIOD����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE);
	
	/*��ʼ��PB.00�˿�ΪOut_PPģʽ*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/*��ʼ��PC.05�˿�ΪOut_PPģʽ*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	/*�ر�����ģ���Դ*/
	BLTCONTROL_POWER_OFF;
	
	/*����UART5����ʱ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);
	
	/*UART5��GPIO����*/
	/*����USART5 Tx(PC.12)ΪAF_PP*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	/*����UART5 Rx(PD.02)ΪIN_FLOATING*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	/*UART5 NVIC����*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);													//2 bits for pre-emption priority 2 bits for subpriority
	
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;								//ָ����ռʽ���ȼ���,��ȡ0~3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;											//ָ����Ӧʽ���ȼ���,��ȡ0~3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/*UART5ģʽ����*/
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART5, &USART_InitStructure);
	USART_Cmd(UART5, ENABLE);
	
	/*�����ж�ʹ��*/
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);
	
	/*��������ģ���Դ*/
	BLTCONTROL_POWER_ON;
}
