#ifndef __ENCODE_H
#define __ENCODE_H
#include "sys.h"

void TIM3_Encode_init(u16 arr,u16 psc);
u32 Read_Encoder(void);
#endif

