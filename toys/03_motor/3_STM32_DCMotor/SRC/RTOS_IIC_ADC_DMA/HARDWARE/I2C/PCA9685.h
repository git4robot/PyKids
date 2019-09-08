#ifndef __PCA9685_H
#define __PCA9685_H	
#include "sys.h"

#define PCA9685_I2Cx I2C1    //PCA9685所用的iic外设
#define PCA9685_ADDR  0xA0   //设备地址

void PCA9685_Init(void);
void I2C_AcknowledgePolling(I2C_TypeDef *I2Cx,uint8_t I2C_Addr);
uint8_t PCA9685_ReadOneByte(uint8_t ReadAddr);
void PCA9685_WriteOneByte(uint8_t WriteAddr, uint8_t DataToWrite);
void PCA9685_Read(uint8_t ReadAddr,uint8_t *Buffer,uint16_t Num);

#endif
