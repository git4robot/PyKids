#include "pca9685.h"
#include "myiic.h"
#include "delay.h"
#include "math.h"

void PCA_Init(void)
{
	pca_reset(0x80);
	pca_reset(0x82);
}

void PCA_SetPWMFreq(float freq)
{
	pca_setfreq(0x80, 50);
	pca_setfreq(0x82, 50);	
}

void PCA_SetPWM(u8 num, u32 on, u32 off)
{
	pca_setpwm(0x80, num, on, off);
	pca_setpwm(0x82, num, on, off);	
}

u8 pca_read(u8 busAddr, u8 regAdr)
{
	u8 data;
	IIC_Start();

	IIC_Send_Byte(busAddr);
	IIC_Wait_Ack();

	IIC_Send_Byte(regAdr);
	IIC_Wait_Ack();

	IIC_Start();

	IIC_Send_Byte(pca_adr1|0x01);
	IIC_Wait_Ack();

	data=IIC_Read_Byte(0);
	IIC_Stop();

	return data;
}

void pca_write(u8 busAddr, u8 regAdr,u8 data)
{ 
	IIC_Start();

	IIC_Send_Byte(busAddr);
	IIC_Wait_Ack();

	IIC_Send_Byte(regAdr);
	IIC_Wait_Ack();

	IIC_Send_Byte(data);
	IIC_Wait_Ack();

	IIC_Stop();
}

void pca_reset(u8 busAddr)
{
	IIC_Init();
	pca_write(busAddr, pca_mode1,0x0);
}

void pca_setfreq(u8 busAddr, float freq) 
{
	u8 prescale,oldmode,newmode;
	double prescaleval;
	freq *= 0.92; 
	prescaleval = 25000000;
	prescaleval /= 4096;
	prescaleval /= freq;
	prescaleval -= 1;
	prescale =floor(prescaleval + 0.5f);

	oldmode = pca_read(busAddr, pca_mode1);

	newmode = (oldmode&0x7F) | 0x10; // sleep

	pca_write(busAddr, pca_mode1, newmode); // go to sleep

	pca_write(busAddr, pca_pre, prescale); // set the prescaler

	pca_write(busAddr, pca_mode1, oldmode);
	delay_ms(2);

	pca_write(busAddr, pca_mode1, oldmode | 0xa1); 
}

void pca_setpwm(u8 busAddr, u8 num, u32 on, u32 off) 
{
	pca_write(busAddr, LED0_ON_L+4*num,on);
	pca_write(busAddr, LED0_ON_H+4*num,on>>8);
	pca_write(busAddr, LED0_OFF_L+4*num,off);
	pca_write(busAddr, LED0_OFF_H+4*num,off>>8);
}

