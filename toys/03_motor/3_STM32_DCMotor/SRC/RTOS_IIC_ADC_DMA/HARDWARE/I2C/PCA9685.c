
#include "PCA9685.h"
 
static void delay(unsigned int us) //大概延时 
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

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE); //使能iic外设时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO , ENABLE); //使能GPIO时钟

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
	I2C_InitStructure.I2C_ClockSpeed = 100000;  /* 100K速度 */

	I2C_Cmd(I2C1, ENABLE);
	I2C_Init(I2C1, &I2C_InitStructure);
	/*允许1字节1应答模式*/
	I2C_AcknowledgeConfig(I2C1, ENABLE);
}
 
void I2C_AcknowledgePolling(I2C_TypeDef *I2Cx,uint8_t I2C_Addr)
{
	vu16 SR1_Tmp;

	do
	{   
		I2C_GenerateSTART(PCA9685_I2Cx, ENABLE); /*起始位*/
		/*读SR1*/
		SR1_Tmp = I2C_ReadRegister(PCA9685_I2Cx, I2C_Register_SR1);
		/*器件地址(写)*/
		I2C_Send7bitAddress(PCA9685_I2Cx, I2C_Addr, I2C_Direction_Transmitter);
	}while(!(I2C_ReadRegister(PCA9685_I2Cx, I2C_Register_SR1) & 0x0002));

	I2C_ClearFlag(PCA9685_I2Cx, I2C_FLAG_AF);

	I2C_GenerateSTOP(PCA9685_I2Cx, ENABLE);  /*停止位*/  
} 

uint8_t PCA9685_ReadOneByte(uint8_t ReadAddr) //从PCA9685指定的地址读取一个字节
{
	uint8_t recvalue;

	while(I2C_GetFlagStatus(PCA9685_I2Cx, I2C_FLAG_BUSY));

	/*允许1字节1应答模式*/
	I2C_AcknowledgeConfig(PCA9685_I2Cx, ENABLE);


	/* 发送起始位 */
	I2C_GenerateSTART(PCA9685_I2Cx, ENABLE);
	while(!I2C_CheckEvent(PCA9685_I2Cx, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,主模式*/
	/*发送器件地址(写)*/
	I2C_Send7bitAddress(PCA9685_I2Cx,  PCA9685_ADDR, I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(PCA9685_I2Cx,                    I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	/*发送地址*/
	I2C_SendData(PCA9685_I2Cx, ReadAddr);
	while (!I2C_CheckEvent(PCA9685_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));/*数据已发送*/

	/*起始位*/
	I2C_GenerateSTART(PCA9685_I2Cx, ENABLE);
	while(!I2C_CheckEvent(PCA9685_I2Cx, I2C_EVENT_MASTER_MODE_SELECT));

	/*器件读*/
	I2C_Send7bitAddress(PCA9685_I2Cx, PCA9685_ADDR, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(PCA9685_I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

	I2C_AcknowledgeConfig(PCA9685_I2Cx, DISABLE);	/* 最后一位后要关闭应答的 */
	I2C_GenerateSTOP(PCA9685_I2Cx, ENABLE);			/* 发送停止位 */
	while(!I2C_CheckEvent(PCA9685_I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED));  /* EV7 */
	recvalue = I2C_ReceiveData(PCA9685_I2Cx);

	/* 再次允许应答模式 */
	I2C_AcknowledgeConfig(PCA9685_I2Cx, ENABLE);

	return recvalue;
}	
 
void PCA9685_WriteOneByte(uint8_t WriteAddr, uint8_t DataToWrite)
{
	/* 起始位 */
	I2C_GenerateSTART(PCA9685_I2Cx, ENABLE);
	while(!I2C_CheckEvent(PCA9685_I2Cx, I2C_EVENT_MASTER_MODE_SELECT));  

	/* 发送器件地址(写)*/
	I2C_Send7bitAddress(PCA9685_I2Cx, PCA9685_ADDR, I2C_Direction_Transmitter);
	while(!I2C_CheckEvent(PCA9685_I2Cx,     I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	/*发送地址*/
	I2C_SendData(PCA9685_I2Cx, WriteAddr);
	while(!I2C_CheckEvent(PCA9685_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	/* 写一个字节*/
	I2C_SendData(PCA9685_I2Cx, DataToWrite); 
	while(!I2C_CheckEvent(PCA9685_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	/* 停止位*/
	I2C_GenerateSTOP(PCA9685_I2Cx, ENABLE);

	I2C_AcknowledgePolling(PCA9685_I2Cx,PCA9685_ADDR);

	delay(100);

	return ;
} 
 
void PCA9685_Write(uint8_t WriteAddr,uint8_t *Buffer,uint16_t Num)//向指定地址连续写入过个字节
{
	while(Num--)
	{
		PCA9685_WriteOneByte(WriteAddr,*Buffer);
		WriteAddr++;
		Buffer++;
	}
}

void PCA9685_Read(uint8_t ReadAddr,uint8_t *Buffer,uint16_t Num)//从指定地址连续读取多个字节
{
	if(Num==0)
		return;

	while(I2C_GetFlagStatus(PCA9685_I2Cx, I2C_FLAG_BUSY));

	/*允许1字节1应答模式*/
	I2C_AcknowledgeConfig(PCA9685_I2Cx, ENABLE);


	/* 发送起始位 */
	I2C_GenerateSTART(PCA9685_I2Cx, ENABLE);
	while(!I2C_CheckEvent(PCA9685_I2Cx, I2C_EVENT_MASTER_MODE_SELECT));/*EV5,主模式*/
	/*发送器件地址(写)*/
	I2C_Send7bitAddress(PCA9685_I2Cx,  PCA9685_ADDR, I2C_Direction_Transmitter);
	while (!I2C_CheckEvent(PCA9685_I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	/*发送地址*/
	I2C_SendData(PCA9685_I2Cx, ReadAddr);
	while (!I2C_CheckEvent(PCA9685_I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED));/*数据已发送*/

	/*起始位*/
	I2C_GenerateSTART(PCA9685_I2Cx, ENABLE);
	while(!I2C_CheckEvent(PCA9685_I2Cx, I2C_EVENT_MASTER_MODE_SELECT));

	/*器件读*/
	I2C_Send7bitAddress(PCA9685_I2Cx, PCA9685_ADDR, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(PCA9685_I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

	while (Num){
		if(Num==1)
		{
			I2C_AcknowledgeConfig(PCA9685_I2Cx, DISABLE);	/* 最后一位后要关闭应答的 */
			I2C_GenerateSTOP(PCA9685_I2Cx, ENABLE);			/* 发送停止位 */
		}

		while(!I2C_CheckEvent(PCA9685_I2Cx,I2C_EVENT_MASTER_BYTE_RECEIVED));  /* EV7 */

		*Buffer = I2C_ReceiveData(PCA9685_I2Cx);
		Buffer++;
		/* Decrement the read bytes counter */
		Num--;
	}
	/* 再次允许应答模式 */
	I2C_AcknowledgeConfig(PCA9685_I2Cx, ENABLE);

	return;
}

