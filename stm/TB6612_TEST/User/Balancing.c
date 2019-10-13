/**---------------------------------------------------------------
	��Ŀ��������ƽ��С��(Two-Wheels Auto-Balancing Vechile)
	�汾��v1.0.0
	�ļ�: Balancing.c
	���ܣ���ƽ�����
	���ߣ�flotox@yeah.net
	���ڣ�2014.9.5
	���£�2014.9.5
----------------------------------------------------------------*/

#include "stm32f10x.h"
#include "GlobalVars.h"
#include "MotorDriver.h"

// float		Temp[200] = {0};
// uint32_t	Temp_i = 0;

/**
	*	@brief		��ƽ����������ʼ��
	*	@param		none
	*	@retval		none
	*/
void	Balancing_Init(void){
	
	GPIO_InitTypeDef				GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef	TIM_TimeBaseStructure;
	NVIC_InitTypeDef				NVIC_InitStructure;
	
	/*����GPIOC����ʱ��*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	/*����TIM4����ʱ��*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	/*����PC.15�˿�ΪOut_PPģʽ*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	/*TIM4 NVIC����*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);													//2 bits for pre-emption priority 2 bits for subpriority
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;								//ָ����ռʽ���ȼ���,��ȡ0~3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;											//ָ����Ӧʽ���ȼ���,��ȡ0~3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_DeInit(TIM4);
	
	/*��ʱ����������*/
	TIM_TimeBaseStructure.TIM_Prescaler = 0;																//ʱ��Ԥ��Ƶ��0,TIM4��ʱ�Ӽ���Ƶ��Ϊ72MHz
	TIM_TimeBaseStructure.TIM_Period = 20 - 1;															//�Զ���װ�ؼĴ�����20,10ms���1��
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;														//������Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;							//���ϼ���
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	TIM_PrescalerConfig(TIM4, 0x8c9f, TIM_PSCReloadMode_Immediate);					//ʱ�ӷ�Ƶϵ��36000,��ʱ��ʱ��Ϊ2KHz
	TIM_ARRPreloadConfig(TIM4, DISABLE);																		//��ֹARRԤװ�ػ�����
	TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);															//ʹ��Update�ж�
	
	TIM_Cmd(TIM4, ENABLE);																									//����ʱ��
}

/**
	*	@brief		��ƽ�����ѭ���ӳ���(10ms������һ��)
	*	@param		none
	*	@retval		none
	*/
void	Balancing_Loop(void){

	uiCount_Led++;
	
	/*Led��˸*/
	if(uiCount_Led >= 40){
		
		uiCount_Led = 0;
		GPIO_WriteBit(GPIOC,GPIO_Pin_15,(BitAction)(1-GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_15)));
	}
	
	switch(iMotion_Type){

		case	MOTION_TYPE_NONE:
			
			fTarget_Speed = 0;
			fTarget_Turn = 0;
			break;
		
		case	MOTION_TYPE_FORWARDS:
			
			fTarget_Speed = -150;
			fTarget_Turn = 0;
			break;
		
		case	MOTION_TYPE_BACKWARDS:
			
			fTarget_Speed = 150;			//150
			fTarget_Turn = 0;
			break;
		
		case	MOTION_TYPE_TURN_LEFT:
			
			fTarget_Speed = 0;
			fTarget_Turn = -210;
			break;
		
		case	MOTION_TYPE_TURN_RIGHT:
			
			fTarget_Speed = 0;
			fTarget_Turn = 210;
			break;
		
		case	MOTION_TYPE_FORWARDS_TURN_LEFT:
			
			fTarget_Speed = -150;
			fTarget_Turn = -210;
			break;
		
		case	MOTION_TYPE_FORWARDS_TURN_RIGHT:
			
			fTarget_Speed = -150;
			fTarget_Turn = 210;
			break;
		
		case	MOTION_TYPE_BACKWARDS_TURN_LEFT:
			
			fTarget_Speed = 150;
			fTarget_Turn = -210;
			break;
		
		case	MOTION_TYPE_BACKWARDS_TURN_RIGHT:
			
			fTarget_Speed = 150;
			fTarget_Turn = 210;
			break;
	}
	
	/*�����ı�ʱ�����м�Ĺ��ȹ���,���ȹ���Ϊ50ms*/
	if((iMotion_Type != iMotion_Type_Last) && (iCount_Motion_Type_Change == 0)){
		
		iCount_Motion_Type_Change = 10;
		iMotion_Type_Last = iMotion_Type;
	}
	
	if(iCount_Motion_Type_Change != 0){
		
		iCount_Motion_Type_Change --;
		fTarget_Speed = 0;
		fTarget_Turn = 0;
	}
	
	/*�ٶȺ�λ��һ�׵�ͨ�˲�*/
	fSpeed_Vechile = (iCount_L + iCount_R) * 0.5;
	fSpeed_Vechile_F = fSpeed_Vechile_F * 0.7 + fSpeed_Vechile * 0.3;
	
	/*�ۼ���λ��*/
	fPosition += fSpeed_Vechile_F;

	/*λ�Ƶ�����*/
	fPosition += fTarget_Speed;

	/*λ������,�����޴�����*/
	if(fPosition > 5000){																//5000
		
		fPosition = 5000;
	}
	else if(fPosition < -5000){
		
		fPosition = -5000;
	}
	
	/*���ֺ����ֹ�դ�������������*/
	iCount_L = 0;
	iCount_R = 0;
	
	/*�Ƕ�����*/
	if( (fPitchAngle < 40.0) && (fPitchAngle > -40.0) ){
		
		
		/*�������ٶ�,��λdeg/s,����0����ٶȷ�����ǰ,С��0����ٶȷ������*/
		fAngle_Vel = -(fPitchAngle - fPitchAngle_Last);
		
		/*����˴θ����Ƕ�*/
		fPitchAngle_Last = fPitchAngle;
		
		/*����PWM���������*/
		fPWM =	(-fpid_angle) * fPitchAngle +
						fpid_angle_vel * fAngle_Vel +
						fpid_speed * fSpeed_Vechile_F +
						fPosition * fpid_position;
		
		/*��ת������*/
		fPWM_L = fPWM + fTarget_Turn;
		fPWM_R = fPWM - fTarget_Turn;
		
		/*���ֿ���*/
		if(fPWM_L > 0){
			
			MotorDriver_L_Turn_Forward();
		}
		else{
			
			MotorDriver_L_Turn_Reverse();
			fPWM_L = -fPWM_L;
		}
			
		/*���ֿ���*/
		if(fPWM_R > 0){
			
			MotorDriver_R_Turn_Forward();
		}
		else{
			
			MotorDriver_R_Turn_Reverse();
			fPWM_R = -fPWM_R;
		}
		
		/*����������ѹ*/
		fPWM_L += 40;
		fPWM_R += 10;
		
		/*����PWM*/
		if(fPWM_L > 1000){
			
			fPWM_L = 1000;
		}
		
		if(fPWM_R > 1000){
			
			fPWM_R = 1000;
		}
		
		/*���PWM������*/
		TIM_SetCompare2(TIM8, (uint16_t)fPWM_L);					//����
		TIM_SetCompare2(TIM1, (uint16_t)fPWM_R);					//����
	}
	/*��ǹ���ʱ����̬���ݲ��������*/
	else{
		
		TIM_SetCompare2(TIM8, 0);													//����
		TIM_SetCompare2(TIM1, 0);													//����
	}
	
}
