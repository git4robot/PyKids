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




//任务优先级
#define START_TASK_PRIO		0
//任务堆栈大小	
#define START_STK_SIZE 		128  
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);

//任务优先级
#define LED0_TASK_PRIO		2
//任务堆栈大小	
#define LED0_STK_SIZE 		50  
//任务句柄
TaskHandle_t LED0Task_Handler;
//任务函数
void led0_task(void *pvParameters);

//任务优先级
#define LED1_TASK_PRIO		3
//任务堆栈大小	
#define LED1_STK_SIZE 		50  
//任务句柄
TaskHandle_t LED1Task_Handler;
//任务函数
void led1_task(void *pvParameters);

//任务优先级
#define ADC_MON_TASK_PRIO		1
//任务堆栈大小	
#define ADC_MON_STK_SIZE 		128  
//任务句柄
TaskHandle_t ADC_MONTask_Handler;
//任务函数
void vADCMonitorTask(void *pvParameters);

volatile u16 ADCConvertedValue[10][3];//用来存放ADC转换结果，也是DMA的目标地址,3通道，每通道采集10次后面取平均数


int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);// 设置中断优先级分组2
	delay_init();	    	 //延时函数初始化	
	uart_init(115200);	 //串口初始化为9600
	LED_Init();		  	 //初始化与LED连接的硬件接口 
#if 1
	////DMA外设ADC基地址 ADC1
	MYDMA_Config(DMA1_Channel1,(u32)&ADC1->DR,(u32)ADCConvertedValue,3*10);
	AdcDma_Init();
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//开始采集
	
	MYDMA_Enable(DMA1_Channel1);
#endif	
	printf("FreeRTOS Running....\r\n");
	
	
	//创建开始任务
	xTaskCreate((TaskFunction_t )start_task,            //任务函数
							(const char*    )"start_task",          //任务名称
							(uint16_t       )START_STK_SIZE,        //任务堆栈大小
							(void*          )NULL,                  //传递给任务函数的参数
							(UBaseType_t    )START_TASK_PRIO,       //任务优先级
							(TaskHandle_t*  )&StartTask_Handler);   //任务句柄              

	vTaskStartScheduler();          //开启任务调度
								
	return 0;
}

//开始任务任务函数
void start_task(void *pvParameters)
{
	printf("start_task Running....\r\n");
    taskENTER_CRITICAL();           //进入临界区
    //创建LED0任务
    xTaskCreate((TaskFunction_t )led0_task,     	
                (const char*    )"led0_task",   	
                (uint16_t       )LED0_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED0_TASK_PRIO,	
                (TaskHandle_t*  )&LED0Task_Handler);   
    //创建LED1任务
    xTaskCreate((TaskFunction_t )led1_task,     
                (const char*    )"led1_task",   
                (uint16_t       )LED1_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )LED1_TASK_PRIO,
                (TaskHandle_t*  )&LED1Task_Handler);       
    //创建Demo任务
    xTaskCreate((TaskFunction_t )vADCMonitorTask,     
                (const char*    )"adc_monitor_task",   
                (uint16_t       )ADC_MON_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )ADC_MON_TASK_PRIO,
                (TaskHandle_t*  )&ADC_MONTask_Handler);   				
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}

//LED0任务函数 
void led0_task(void *pvParameters)
{
    printf("led0_task Running....\r\n");
    while(1)
    {
        LED0=~LED0;
        vTaskDelay(500);
    }
}   

//LED1任务函数
void led1_task(void *pvParameters)
{
	printf("led1_task Running....\r\n");
    while(1)
    {
        LED1=0;
        vTaskDelay(200);
        LED1=1;
        vTaskDelay(800);
    }
}

void vADCMonitorTask( void *pvParameters )
{
#if 0	
	u8 t;
	u8 len;	
	u16 times=0; 
#endif		
	int sum;
	u8 i,j;
	float ADC_Value[3];//用来保存经过转换得到的电压值
	
	printf("vADCMonitorTask Running....\r\n");
	
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
		printf("\r\n\r\n");//插入换行
		//延时（略）		
		delay_ms(250);		
	}	 
	
}

