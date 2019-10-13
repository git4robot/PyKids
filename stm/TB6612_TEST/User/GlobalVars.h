/**---------------------------------------------------------------
	��Ŀ��������ƽ��С��(Two-Wheels Auto-Balancing Vechile)
	�汾��v1.0.0
	�ļ�: GlobalVars.h
	���ܣ�ȫ�ֱ�������
	���ߣ�flotox@yeah.net
	���ڣ�2014.9.4
	���£�2014.9.4
----------------------------------------------------------------*/

#ifndef	_GLOBALVARS_H_
#define	_GLOBALVARS_H_

#define		MOTION_TYPE_NONE									0x00		//������
#define		MOTION_TYPE_FORWARDS							0x01		//ǰ��
#define		MOTION_TYPE_BACKWARDS							0x02		//����
#define		MOTION_TYPE_TURN_LEFT							0x03		//��ת
#define		MOTION_TYPE_TURN_RIGHT						0x04		//��ת
#define		MOTION_TYPE_FORWARDS_TURN_LEFT		0x05		//ǰ������ת
#define		MOTION_TYPE_FORWARDS_TURN_RIGHT		0x06		//ǰ������ת
#define		MOTION_TYPE_BACKWARDS_TURN_LEFT		0x07		//���˲���ת
#define		MOTION_TYPE_BACKWARDS_TURN_RIGHT	0x08		//���˲���ת

extern	volatile int32_t		iCount_R;													//�ڵ�λʱ��(20ms)��,���ֹ�դ�������,����0����ת,С��0��ת,��ʱʱ�䵽�����������ֵ
extern	volatile int32_t		iCount_L;													//�ڵ�λʱ��(20ms)��,���ֹ�դ�������,����0����ת,С��0��ת,��ʱʱ�䵽�����������ֵ
extern	volatile uint32_t		uiCount_Led;											//Led��˸������
extern	volatile int32_t		iMotion_Type;											//��������
extern	volatile int32_t		iMotion_Type_Last;								//���������ݴ�
extern	volatile uint32_t		iCount_Motion_Type_Change;				//�������͸ı���Ϊ1,����Ϊ0


extern	volatile float			fPitchAngle;											//�����Ƕ�,С��0��ǰ��,����0�����
extern	volatile float			fPitchAngle_Last;									//��һ�����ǽǶ�,С��0��ǰ��,����0�����
extern	volatile float			fAngle_Vel;												//�������ٶ�,С��0��Ǽ��ٶȷ���Ϊǰ�㷽��,����0��Ǽ��ٶȷ���Ϊ��������

extern	volatile float			fpid_angle;												//�Ƕȿ���ϵ��
extern	volatile float			fpid_angle_vel;										//�Ǽ��ٶȿ���ϵ��
extern	volatile float			fpid_speed;												//�ٶȿ���ϵ��
extern	volatile float			fpid_position;										//λ�ƿ���ϵ��
extern	volatile float			fLimit_Speed;

extern	volatile float			fTarget_Speed;										//�ٶȵ�����
extern	volatile float			fTarget_Turn;											//��ת������

extern	volatile float			fSpeed_L;													//�����ٶ�
extern	volatile float			fSpeed_R;													//�����ٶ�
extern	volatile float			fSpeed_Vechile;										//С�������ٶ�
extern	volatile float			fSpeed_Vechile_F;									//��ͨ�˲����С�������ٶ�
extern	volatile float			fPosition;												//λ��

extern	volatile float			fPWM;															//����ó���PWM�����
extern	volatile float			fPWM_L;														//����PWM�����
extern	volatile float			fPWM_R;														//����PWM�����

#endif
