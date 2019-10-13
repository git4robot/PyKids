/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "stm32f10x_it.h"
#include "GlobalVars.h"
#include "Balancing.h"

//PA.15�˿�����ֵ
#define		PA15In		(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_15))
//PB.4�˿�����ֵ
#define		PB4In			(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_4))

uint32_t		uchUSART2_REC_BUF[20] = {0};							//USART2�������ݻ�����,20�ֽ�					
uint32_t		uchUART5_REC_BUF[7] = {0};								//UART5�������ݻ�����,7�ֽ�

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/**
	*	@brief		EXTI3�жϴ���
	*	@param		none
	*	@retval		none
	*/
void EXTI3_IRQHandler(void){
	
	//��ⴥ���¼��Ƿ���
	if(EXTI_GetITStatus(EXTI_Line3) != RESET){
		
		if(PA15In == 1){
			
			iCount_L--;				//���ּ�����1
		}
		else{
			
			iCount_L++;				//���ּ�����1
		}
		
		//����¼��жϹ���λ
		EXTI_ClearITPendingBit(EXTI_Line3);
	}
}

/**
	*	@brief		EXTI9_5�жϴ���
	*	@param		none
	*	@retval		none
	*/
void EXTI9_5_IRQHandler(void){
	
	//��ⴥ���¼��Ƿ���
	if(EXTI_GetITStatus(EXTI_Line5) != RESET){
		
		if(PB4In == 1){
			
			iCount_R++;				//���ּ�����1
		}
		else{
			
			iCount_R--;				//���ּ�����1
		}
		
		//����¼��жϹ���λ
		EXTI_ClearITPendingBit(EXTI_Line5);
	}
}

/**
	*	@brief		TIM4�жϴ���(2.5ms)
	*	@param		none
	*	@retval		none
	*/
void	TIM4_IRQHandler(void){
	
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=RESET){
		
		TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
		Balancing_Loop();																				//��ƽ�����ѭ���ӳ���
	}
}

/**
	*	@brief		USART2�жϴ���
	*	@param		none
	*	@retval		none
	*/
void USART2_IRQHandler(void){
	
	uint32_t	i;
	
	if(USART_GetFlagStatus(USART2, USART_IT_RXNE) == SET){
		
		/*����20�ֽ�FIFO*/
		for(i = 1; i <= 19; i++){
			
			uchUSART2_REC_BUF[i - 1] = uchUSART2_REC_BUF[i];
		}
		
		/*���������ֽ�,�������*/
		uchUSART2_REC_BUF[19] = USART_ReceiveData(USART2);
		
		/*����20�ֽ�FIFO�Ƿ����֡�ṹ*/
		if( (uchUSART2_REC_BUF[0]  == 0xa5) &&
				(uchUSART2_REC_BUF[1]  == 0x5a) &&
				(uchUSART2_REC_BUF[2]  == 0x12) &&
				(uchUSART2_REC_BUF[3]  == 0xa1) &&
				(uchUSART2_REC_BUF[19] == 0xaa) &&
				(((uchUSART2_REC_BUF[2] + uchUSART2_REC_BUF[3] + uchUSART2_REC_BUF[6] + uchUSART2_REC_BUF[7]) % 256) == uchUSART2_REC_BUF[18])){
					
					/*���С��0*/
					if(uchUSART2_REC_BUF[6] >= 0x80){
						
						fPitchAngle = ((uchUSART2_REC_BUF[6] - 0x80) * 256 + uchUSART2_REC_BUF[7]) * (-0.1);
					}
					
					/*��Ǵ���0*/
					else{
						
						fPitchAngle = (uchUSART2_REC_BUF[6] * 256 + uchUSART2_REC_BUF[7]) * (0.1);
					}
		}
	}
	
	
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET){
		
		/*������жϱ�־*/
		USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	}
}

/**
	*	@brief		UART5�жϴ���
	*	@param		none
	*	@retval		none
	*/
void	UART5_IRQHandler(void){
	
	uint32_t	i;
	
	if(USART_GetFlagStatus(UART5, USART_IT_RXNE) == SET){

		/*����7�ֽ�FIFO*/
		for(i = 1; i <= 6; i++){
			
			uchUART5_REC_BUF[i - 1] = uchUART5_REC_BUF[i];
		}
		
		/*���������ֽ�,�������*/
		uchUART5_REC_BUF[6] = USART_ReceiveData(UART5);
		
		/*����7�ֽ�FIFO�Ƿ����֡�ṹ*/
		if( (uchUART5_REC_BUF[0] == 0x5a) &&
				(uchUART5_REC_BUF[1] == 0xa5) &&
				(uchUART5_REC_BUF[2] == 0x04) &&
				(uchUART5_REC_BUF[6] == 0xaa) &&
				((uchUART5_REC_BUF[2] + uchUART5_REC_BUF[3] + uchUART5_REC_BUF[4]) == uchUART5_REC_BUF[5])){
					
					/*������*/
					if( (uchUART5_REC_BUF[3] == 0) && (uchUART5_REC_BUF[4] == 0) ){
						
						iMotion_Type = MOTION_TYPE_NONE;
					}
					
					/*ǰ��*/
					else if( (uchUART5_REC_BUF[3] == 1) && (uchUART5_REC_BUF[4] == 0) ){
						
						iMotion_Type = MOTION_TYPE_FORWARDS;
					}

					/*����*/
					else if( (uchUART5_REC_BUF[3] == 2) && (uchUART5_REC_BUF[4] == 0) ){
						
						iMotion_Type = MOTION_TYPE_BACKWARDS;
					}
					
					/*��ת*/
					else if( (uchUART5_REC_BUF[3] == 0) && (uchUART5_REC_BUF[4] == 1) ){
						
						iMotion_Type = MOTION_TYPE_TURN_LEFT;
					}
					
					/*��ת*/
					else if( (uchUART5_REC_BUF[3] == 0) && (uchUART5_REC_BUF[4] == 2) ){
						
						iMotion_Type = MOTION_TYPE_TURN_RIGHT;
					}
					
					/*ǰ������ת*/
					else if( (uchUART5_REC_BUF[3] == 1) && (uchUART5_REC_BUF[4] == 1) ){
						
						iMotion_Type = MOTION_TYPE_FORWARDS_TURN_LEFT;
					}
					
					/*ǰ������ת*/
					else if( (uchUART5_REC_BUF[3] == 1) && (uchUART5_REC_BUF[4] == 2) ){
						
						iMotion_Type = MOTION_TYPE_FORWARDS_TURN_RIGHT;
					}
					
					/*���˲���ת*/
					else if( (uchUART5_REC_BUF[3] == 2) && (uchUART5_REC_BUF[4] == 1) ){
						
						iMotion_Type = MOTION_TYPE_BACKWARDS_TURN_LEFT;
					}
					
					/*���˲���ת*/
					else if( (uchUART5_REC_BUF[3] == 2) && (uchUART5_REC_BUF[4] == 2) ){
						
						iMotion_Type = MOTION_TYPE_BACKWARDS_TURN_RIGHT;
					}
		}
	}

	if(USART_GetITStatus(UART5, USART_IT_RXNE) != RESET){
		
		/*������жϱ�־*/
		USART_ClearITPendingBit(UART5, USART_IT_RXNE);
	}
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
