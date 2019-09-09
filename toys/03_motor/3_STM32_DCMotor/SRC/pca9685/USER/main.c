#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"
#include "pca9685.h"


//140 307 480
int main(void)
{	
	u8 i;
	delay_init();
	PCA_Init();
	PCA_SetPWMFreq(50);
	
	while(1)
	{
		for(i = 0; i < 16; i++)
		{
			PCA_SetPWM(i, 0, 140);
			delay_ms(100);
		}
		delay_ms(1000);
		for(i = 0; i < 16; i++)
		{
			PCA_SetPWM(i, 0, 307);
			delay_ms(100);
		}
		delay_ms(1000);
	}
}



