#include "driver.h"
#include "delay.h"
#include "usart.h"

/********** 驱动器 端口定义 **************
预留接口PC0 PC1
******************************************/

/************** 驱动器控制信号线初始化 ****************/
void Driver_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//使能PC端口时钟

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;	//端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		//推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//IO口速度为50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);					//根据设定参数初始化GPIOC
	GPIO_SetBits(GPIOC, GPIO_Pin_0);//X顺时针方向
	GPIO_SetBits(GPIOC, GPIO_Pin_1);//Y顺时针方向
}
