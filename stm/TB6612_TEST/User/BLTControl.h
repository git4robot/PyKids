/**---------------------------------------------------------------
	��Ŀ��������ƽ��С��(Two-Wheels Auto-Balancing Vechile)
	�汾��v1.0.0
	�ļ���BLTControl.h
	���ܣ���������ָ�����
	���ߣ�flotox@yeah.net
	���ڣ�2014.9.5
	���£�2014.9.5
----------------------------------------------------------------*/

#ifndef	_BLTCONTROL_H_
#define	_BLTCONTROL_H_

/*��������ģ���Դ*/
#define		BLTCONTROL_POWER_ON					(GPIO_SetBits(GPIOB, GPIO_Pin_0))
/*�ر�����ģ���Դ*/
#define		BLTCONTROL_POWER_OFF				(GPIO_ResetBits(GPIOB, GPIO_Pin_0))

/*�ø�BLT_CONF*/
#define		BLTCONTROL_BLT_CONF_HIGH		(GPIO_SetBits(GPIOC, GPIO_Pin_5))
/*�õ�BLT_CONF*/
#define		BLTCONTROL_BLT_CONF_LOW			(GPIO_ResetBits(GPIOC, GPIO_Pin_5))

void	BLTControl_Init(void);										//���������ʼ��

#endif
