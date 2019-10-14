
#include "PCA9685.h"
 
static void delay(unsigned int us) //�����ʱ 
{
    uint8_t i = 10;
    while(us--)
    {
		while(i--);
    }
}

void PCA9685_Init(void)
{
	I2C_InitTypeDef  I2C_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure; 

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE); //ʹ��iic����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO , ENABLE); //ʹ��GPIOʱ��

	/* Configure I2C1 pins: PB6->SCL and PB7->SDA */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
		
	I2C_DeInit(I2C1);
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_InitStructure.I2C_ClockSpeed = 100000;  /* 100K�ٶ� */

	I2C_Cmd(I2C1, ENABLE);
	I2C_Init(I2C1, &I2C_InitStructure);
	/*����1�ֽ�1Ӧ��ģʽ*/
	I2C_AcknowledgeConfig(I2C1, ENABLE);
}
 
void I2C_AcknowledgePolling(I2C_TypeDef *I2Cx,uint8_t I2C_Addr)
{
	vu16 SR1_Tmp;

	do
	{   
		I2C_GenerateSTART(PCA9685_I2Cx, ENABLE); /*��ʼλ*/
		/*��SR1*/
		SR1_Tmp = I2C_ReadRegister(PCA9685_I2Cx, I2C_Register_SR1);
		/*������ַ(д)*/
		I2C_Send7bitAddress(PCA9685_I2Cx, I2C_Addr, I2C_Direction_Transmitter);
	}while(!(I2C_ReadRegister(PCA9685_I2Cx, I2C_Register_SR1) & 0x0002));

	I2C_ClearFlag(PCA9685_I2Cx, I2C_FLAG_AF);

	I2C_GenerateSTOP(PCA9685_I2Cx, ENABLE);  /*ֹͣλ*/  
} 

uint8_t PCA9685_ReadOneByte(uint8_t ReadAddr) //��PCA9685ָ���ĵ�ַ��ȡһ���ֽ�
{
	uint8_t recvalue;

	while(I2C_GetFlagStatus(PCA9685_I2Cx, I2C_FLAG_BUSY));

	/*����1�ֽ�1Ӧ��ģʽ*/
	I2C_AcknowledgeConfig(PCA9685_I2Cx, ENABLE);


	/* ������ʼλ */
	I2C_GenerateSTART(PCA9685_I2Cx, ENABLE);
	while(!I2C_CheckEvent(PCA9685_I2Cx, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,��ģʽ*/
	/*����������ַ(д)*/
	I2C_Send7bitAddress(PCA9685_I2Cx,  PCA9685_ADDR, I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(PCA9685_I2Cx,                    I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	/*���͵�ַ*/
	I2C_SendData(PCA9685_I2Cx, ReadAddr);
	while (!I2C_CheckEvent(PCA9685_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));/*�����ѷ���*/

	/*��ʼλ*/
	I2C_GenerateSTART(PCA9685_I2Cx, ENABLE);
	while(!I2C_CheckEvent(PCA9685_I2Cx, I2C_EVENT_MASTER_MODE_SELECT));

	/*������*/
	I2C_Send7bitAddress(PCA9685_I2Cx, PCA9685_ADDR, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(PCA9685_I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

	I2C_AcknowledgeConfig(PCA9685_I2Cx, DISABLE);	/* ���һλ��Ҫ�ر�Ӧ��� */
	I2C_GenerateSTOP(PCA9685_I2Cx, ENABLE);			/* ����ֹͣλ */
	while(!I2C_CheckEvent(PCA9685_I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));  /* EV7 */
	recvalue = I2C_ReceiveData(PCA9685_I2Cx);

	/* �ٴ�����Ӧ��ģʽ */
	I2C_AcknowledgeConfig(PCA9685_I2Cx, ENABLE);

	return recvalue;
}	
 
void PCA9685_WriteOneByte(uint8_t WriteAddr, uint8_t DataToWrite)
{
	/* ��ʼλ */
	I2C_GenerateSTART(PCA9685_I2Cx, ENABLE);
	while(!I2C_CheckEvent(PCA9685_I2Cx, I2C_EVENT_MASTER_MODE_SELECT));  

	/* ����������ַ(д)*/
	I2C_Send7bitAddress(PCA9685_I2Cx, PCA9685_ADDR, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(PCA9685_I2Cx,     I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	/*���͵�ַ*/
	I2C_SendData(PCA9685_I2Cx, WriteAddr);
	while(!I2C_CheckEvent(PCA9685_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	/* дһ���ֽ�*/
	I2C_SendData(PCA9685_I2Cx, DataToWrite); 
	while(!I2C_CheckEvent(PCA9685_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	/* ֹͣλ*/
	I2C_GenerateSTOP(PCA9685_I2Cx, ENABLE);

	I2C_AcknowledgePolling(PCA9685_I2Cx,PCA9685_ADDR);

	delay(100);

	return ;
} 
 
void PCA9685_Write(uint8_t WriteAddr,uint8_t *Buffer,uint16_t Num)//��ָ����ַ����д������ֽ�
{
	while(Num--)
	{
		PCA9685_WriteOneByte(WriteAddr,*Buffer);
		WriteAddr++;
		Buffer++;
	}
}

void PCA9685_Read(uint8_t ReadAddr,uint8_t *Buffer,uint16_t Num)//��ָ����ַ������ȡ����ֽ�
{
	if(Num==0)
		return;

	while(I2C_GetFlagStatus(PCA9685_I2Cx, I2C_FLAG_BUSY));

	/*����1�ֽ�1Ӧ��ģʽ*/
	I2C_AcknowledgeConfig(PCA9685_I2Cx, ENABLE);


	/* ������ʼλ */
	I2C_GenerateSTART(PCA9685_I2Cx, ENABLE);
	while(!I2C_CheckEvent(PCA9685_I2Cx, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,��ģʽ*/
	/*����������ַ(д)*/
	I2C_Send7bitAddress(PCA9685_I2Cx,  PCA9685_ADDR, I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(PCA9685_I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	/*���͵�ַ*/
	I2C_SendData(PCA9685_I2Cx, ReadAddr);
	while (!I2C_CheckEvent(PCA9685_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));/*�����ѷ���*/

	/*��ʼλ*/
	I2C_GenerateSTART(PCA9685_I2Cx, ENABLE);
	while(!I2C_CheckEvent(PCA9685_I2Cx, I2C_EVENT_MASTER_MODE_SELECT));

	/*������*/
	I2C_Send7bitAddress(PCA9685_I2Cx, PCA9685_ADDR, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(PCA9685_I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

	while (Num){
		if(Num==1)
		{
			I2C_AcknowledgeConfig(PCA9685_I2Cx, DISABLE);	/* ���һλ��Ҫ�ر�Ӧ��� */
			I2C_GenerateSTOP(PCA9685_I2Cx, ENABLE);			/* ����ֹͣλ */
		}

		while(!I2C_CheckEvent(PCA9685_I2Cx,I2C_EVENT_MASTER_BYTE_RECEIVED));  /* EV7 */

		*Buffer = I2C_ReceiveData(PCA9685_I2Cx);
		Buffer++;
		/* Decrement the read bytes counter */
		Num--;
	}
	/* �ٴ�����Ӧ��ģʽ */
	I2C_AcknowledgeConfig(PCA9685_I2Cx, ENABLE);

	return;
}

