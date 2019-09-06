#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "dma.h"
#include "adc.h"
#include "FreeRTOS.h"
#include "task.h"

//ALIENTEK Mini STM32�����巶������3
//ʵ��   
// 1, ����
// 2, ����DMA��ADC��ͨ���ɼ�




//�������ȼ�
#define START_TASK_PRIO		0
//�����ջ��С	
#define START_STK_SIZE 		128  
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);

//�������ȼ�
#define LED0_TASK_PRIO		2
//�����ջ��С	
#define LED0_STK_SIZE 		50  
//������
TaskHandle_t LED0Task_Handler;
//������
void led0_task(void *pvParameters);

//�������ȼ�
#define LED1_TASK_PRIO		3
//�����ջ��С	
#define LED1_STK_SIZE 		50  
//������
TaskHandle_t LED1Task_Handler;
//������
void led1_task(void *pvParameters);

//�������ȼ�
#define ADC_MON_TASK_PRIO		1
//�����ջ��С	
#define ADC_MON_STK_SIZE 		128  
//������
TaskHandle_t ADC_MONTask_Handler;
//������
void vADCMonitorTask(void *pvParameters);

volatile u16 ADCConvertedValue[10][3];//�������ADCת�������Ҳ��DMA��Ŀ���ַ,3ͨ����ÿͨ���ɼ�10�κ���ȡƽ����


int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);// �����ж����ȼ�����2
	delay_init();	    	 //��ʱ������ʼ��	
	uart_init(115200);	 //���ڳ�ʼ��Ϊ9600
	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ� 
#if 1
	////DMA����ADC����ַ ADC1
	MYDMA_Config(DMA1_Channel1,(u32)&ADC1->DR,(u32)ADCConvertedValue,3*10);
	AdcDma_Init();
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//��ʼ�ɼ�
	
	MYDMA_Enable(DMA1_Channel1);
#endif	
	printf("FreeRTOS Running....\r\n");
	
	
	//������ʼ����
	xTaskCreate((TaskFunction_t )start_task,            //������
							(const char*    )"start_task",          //��������
							(uint16_t       )START_STK_SIZE,        //�����ջ��С
							(void*          )NULL,                  //���ݸ��������Ĳ���
							(UBaseType_t    )START_TASK_PRIO,       //�������ȼ�
							(TaskHandle_t*  )&StartTask_Handler);   //������              

	vTaskStartScheduler();          //�����������
								
	return 0;
}

//��ʼ����������
void start_task(void *pvParameters)
{
	printf("start_task Running....\r\n");
    taskENTER_CRITICAL();           //�����ٽ���
    //����LED0����
    xTaskCreate((TaskFunction_t )led0_task,     	
                (const char*    )"led0_task",   	
                (uint16_t       )LED0_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )LED0_TASK_PRIO,	
                (TaskHandle_t*  )&LED0Task_Handler);   
    //����LED1����
    xTaskCreate((TaskFunction_t )led1_task,     
                (const char*    )"led1_task",   
                (uint16_t       )LED1_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )LED1_TASK_PRIO,
                (TaskHandle_t*  )&LED1Task_Handler);       
    //����Demo����
    xTaskCreate((TaskFunction_t )vADCMonitorTask,     
                (const char*    )"adc_monitor_task",   
                (uint16_t       )ADC_MON_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )ADC_MON_TASK_PRIO,
                (TaskHandle_t*  )&ADC_MONTask_Handler);   				
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
}

//LED0������ 
void led0_task(void *pvParameters)
{
    printf("led0_task Running....\r\n");
    while(1)
    {
        LED0=~LED0;
        vTaskDelay(500);
    }
}   

//LED1������
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
	float ADC_Value[3];//�������澭��ת���õ��ĵ�ѹֵ
	
	printf("vADCMonitorTask Running....\r\n");
	
	while(1)
	{
#if 0
		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			printf("\r\n�����͵���ϢΪ:\r\n");
			for(t=0;t<len;t++)
			{
				USART1->DR=USART_RX_BUF[t];
				while((USART1->SR&0X40)==0);//�ȴ����ͽ���
			}
			printf("\r\n\r\n");//���뻻��
			USART_RX_STA=0;
		}else
		{
			times++;
			if(times%5000==0)
			{
				printf("\r\nALIENTEK MiniSTM32������ ����ʵ��\r\n");
				printf("����ԭ��@ALIENTEK\r\n\r\n\r\n");
			}
			if(times%200==0)printf("����������,�Իس�������\r\n");  
			if(times%30==0)LED0=!LED0;//��˸LED,��ʾϵͳ��������.
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
			ADC_Value[i]=(float)sum/(10*4096)*3.3;//��ƽ��ֵ��ת���ɵ�ѹֵ
			//��ӡ���ԣ�
			printf("[%d] = %.02f\r\n",i, ADC_Value[i]);
			//USART_SendData(USART1, 3);
		}
		printf("\r\n\r\n");//���뻻��
		//��ʱ���ԣ�		
		delay_ms(250);		
	}	 
	
}

