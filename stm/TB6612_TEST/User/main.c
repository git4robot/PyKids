/**---------------------------------------------------------------
	��Ŀ��������ƽ��С��(Two-Wheels Auto-Balancing Vechile)
	�汾��v1.0.0
	�ļ���main.c
	���ܣ�������
	���ߣ�flotox@yeah.net
	���ڣ�2014.9.4
	���£�2014.9.4
----------------------------------------------------------------*/

#include "stm32f10x.h"
#include "QuadratureEncoder.h"
#include "MotorDriver.h"
#include "Balancing.h"
#include "BLTControl.h"
#include "AHRS_Rcv.h"

/**
	*	@brief		������
	*	@param		none
	*	@retval		none
	*/
int	main(void){

	QE_Init();											//���������������ʼ��
	MotorDriver_Init();							//������������ʼ��
	Balancing_Init();								//��ƽ����������ʼ��
	BLTControl_Init();							//����ģ�������ʼ��
	AHRS_Rcv_Init();								//AHRS��̬���ݽ��������ʼ��

	while(1);
}
