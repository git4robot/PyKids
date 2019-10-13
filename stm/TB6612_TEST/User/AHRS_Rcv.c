/**---------------------------------------------------------------
	��Ŀ��������ƽ��С��(Two-Wheels Auto-Balancing Vechile)
	�汾��v1.0.0
	�ļ���AHRS_Rcv.c
	���ܣ�AHRS��̬���ݽ���
	���ߣ�flotox@yeah.net
	���ڣ�2014.9.7
	���£�2014.9.7
----------------------------------------------------------------*/

#include "stm32f10x.h"
#include "AHRS_Rcv.h"

/**
	*	@brief		AHRS��̬���ݽ��������ʼ��
	*	@param		none
	*	@retval		none
	*/
void	AHRS_Rcv_Init(void){
	
	GPIO_InitTypeDef	GPIO_InitStructure;
	USART_InitTypeDef	USART_InitStructure;
	NVIC_InitTypeDef	NVIC_InitStructure;
	
	/*����GPIOC����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	/*����USART2����ʱ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	/*USART2��GPIO����*/
	/*����USART2 Tx(PA.02)ΪAF_PPģʽ*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/*����USART2 Rx(PA.03)ΪIN_FLOATING*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	/*USART2 NVIC����*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);													//2 bits for pre-emption priority 2 bits for subpriority
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;								//ָ����ռʽ���ȼ���,��ȡ0~3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;											//ָ����Ӧʽ���ȼ���,��ȡ0~3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	/*USART2ģʽ����*/
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART2, &USART_InitStructure);
	
	USART_Cmd(USART2, ENABLE);
	
	/*�����ж�ʹ��*/
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
}
