#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "dma.h"
#include "adc.h"
#include "FreeRTOS.h"
#include "task.h"

//ALIENTEK Mini STM32开发板范例代码3
//实验   
// 1, 串口
// 2, 基于DMA的ADC多通道采集

volatile u16 ADCConvertedValue[10][3];//用来存放ADC转换结果，也是DMA的目标地址,3通道，每通道采集10次后面取平均数

static void vCheckTask( void *pvParameters );
static void vLEDTask( void *pvParameters );


/* The check task uses the sprintf function so requires a little more stack. */
#define mainCHECK_TASK_STACK_SIZE			( configMINIMAL_STACK_SIZE + 50 )

/* Task priorities. */
#define mainQUEUE_POLL_PRIORITY				( tskIDLE_PRIORITY + 2 )
#define mainCHECK_TASK_PRIORITY				( tskIDLE_PRIORITY + 3 )

int main(void)
{		
	BaseType_t xReturn = pdPASS;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	delay_init();	    	 //延时函数初始化	
	uart_init(115200);	 //串口初始化为9600
	LED_Init();		  	 //初始化与LED连接的硬件接口 
	////DMA外设ADC基地址 ADC1
	MYDMA_Config(DMA1_Channel1,(u32)&ADC1->DR,(u32)ADCConvertedValue,3*10);
	AdcDma_Init();
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//开始采集
	
	MYDMA_Enable(DMA1_Channel1);
	printf("FreeRTOS Running....\r\n");
	
	/* Start the tasks defined within this file/specific to this demo. */
  xReturn = xTaskCreate( vCheckTask, "Check", mainCHECK_TASK_STACK_SIZE, NULL, mainCHECK_TASK_PRIORITY, NULL );		
	
	if(pdPASS == xReturn) {
		printf("xReturn pdPASS....\r\n");
	}	
	
  xReturn = xTaskCreate( vLEDTask, "LCD", configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
													
	vTaskStartScheduler();   /* 启动任务，开启调度 */ 
	printf("main Running....\r\n");
	return 0;
}

static void vLEDTask(void* parameter)
{   
	printf("vLEDTask Running....\r\n");
		while (1)
		{
				LED0=!LED0;
				vTaskDelay(1000);   /* 延时500个tick */             
				printf("AppTask Running....\r\n");
		}
}

static void vCheckTask( void *pvParameters )
{
#if 0	
	u8 t;
	u8 len;	
	u16 times=0; 
#endif		
	int sum;
	u8 i,j;
	float ADC_Value[3];//用来保存经过转换得到的电压值
	
	printf("vCheckTask Running....\r\n");
	
	while(1)
	{
#if 0
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			printf("\r\n您发送的消息为:\r\n");
			for(t=0;t<len;t++)
			{
				USART1->DR=USART_RX_BUF[t];
				while((USART1->SR&0X40)==0);//等待发送结束
			}
			printf("\r\n\r\n");//插入换行
			USART_RX_STA=0;
		}else
		{
			times++;
			if(times%5000==0)
			{
				printf("\r\nALIENTEK MiniSTM32开发板 串口实验\r\n");
				printf("正点原子@ALIENTEK\r\n\r\n\r\n");
			}
			if(times%200==0)printf("请输入数据,以回车键结束\r\n");  
			if(times%30==0)LED0=!LED0;//闪烁LED,提示系统正在运行.
			delay_ms(10);   
		}
#endif
		
		for(i=0;i<3;i++)
		{
			sum=0;
			for(j=0;j<10;j++)
			{
				sum+=ADCConvertedValue[j][i];
			}
			ADC_Value[i]=(float)sum/(10*4096)*3.3;//求平均值并转换成电压值
			//打印（略）
			printf("[%d] = %.02f\r\n",i, ADC_Value[i]);
			//USART_SendData(USART1, 3);
		}
		//延时（略）		
		delay_ms(250);		
	}	 
	
}
