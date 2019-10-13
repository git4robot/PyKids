/**---------------------------------------------------------------
	��Ŀ��������ƽ��С��(Two-Wheels Auto-Balancing Vechile)
	�汾��v1.0.0
	�ļ�: GlobalVars.c
	���ܣ�ȫ�ֱ�������
	���ߣ�flotox@yeah.net
	���ڣ�2014.9.4
	���£�2014.9.4
----------------------------------------------------------------*/

#include "stm32f10x.h"
#include "GlobalVars.h"

volatile int32_t		iCount_R = 0;															//�ڵ�λʱ��(20ms)��,���ֹ�դ�������,����0����ת,С��0��ת,��ʱʱ�䵽�����������ֵ
volatile int32_t		iCount_L = 0;															//�ڵ�λʱ��(20ms)��,���ֹ�դ�������,����0����ת,С��0��ת,��ʱʱ�䵽�����������ֵ
volatile uint32_t		uiCount_Led = 0;													//Led��˸������
volatile int32_t		iMotion_Type = MOTION_TYPE_NONE;					//��������
volatile int32_t		iMotion_Type_Last = MOTION_TYPE_NONE;			//���������ݴ�
volatile uint32_t		iCount_Motion_Type_Change = 0;							//�������͸ı���Ϊ1,����Ϊ0

volatile float			fPitchAngle = 0;													//�����Ƕ�,С��0��ǰ��,����0�����
volatile float			fPitchAngle_Last = 0;											//��һ�����ǽǶ�,С��0��ǰ��,����0�����
volatile float			fAngle_Vel = 0;														//�������ٶ�,С��0��Ǽ��ٶȷ���Ϊǰ�㷽��,����0��Ǽ��ٶȷ���Ϊ��������

volatile float			fpid_angle = 29;													//�Ƕȿ���ϵ��/34
volatile float			fpid_angle_vel = 170;											//�Ǽ��ٶȿ���ϵ��/210
volatile float			fpid_speed = 7;														//6.7�ٶȿ���ϵ��/8.8
volatile float			fpid_position = 0.085;										//0.095λ�ƿ���ϵ��/0.095
volatile float			fLimit_Speed = 1.0;												//�ٶ���������

volatile float			fTarget_Speed = 0;												//�ٶȵ�����
volatile float			fTarget_Turn = 0;													//��ת������

volatile float			fSpeed_L = 0;															//�����ٶ�
volatile float			fSpeed_R = 0;															//�����ٶ�
volatile float			fSpeed_Vechile = 0;												//С�������ٶ�
volatile float			fSpeed_Vechile_F = 0;											//��ͨ�˲����С�������ٶ�
volatile float			fPosition = 0;														//λ��

volatile float			fPWM = 0;																	//����ó���PWM�����
volatile float			fPWM_L = 0;																//����PWM�����
volatile float			fPWM_R = 0;																//����PWM�����
