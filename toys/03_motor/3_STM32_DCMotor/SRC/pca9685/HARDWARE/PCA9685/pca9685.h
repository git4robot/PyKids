#ifndef __PCA_H
#define __PCA_H	
#include "stm32f10x.h"

#define pca_adr1 0x80
#define pca_adr2 0x82

#define pca_mode1 0x0
#define pca_pre 0xFE


#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9

void PCA_Init(void);
void PCA_SetPWMFreq(float freq);
void PCA_SetPWM(u8 num, u32 on, u32 off);

void pca_write(u8 busAddr, u8 regAdr,u8 data);
u8 pca_read(u8 busAddr, u8 regAdr);
void pca_reset(u8 busAddr);
void pca_setfreq(u8 busAddr, float freq);
void pca_setpwm(u8 busAddr, u8 num, u32 on, u32 off);

#endif



