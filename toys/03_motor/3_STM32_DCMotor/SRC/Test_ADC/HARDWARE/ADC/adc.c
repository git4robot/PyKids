 #include "adc.h"
 #include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK miniSTM32������
//ADC ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
	   
		   
//��ʼ��ADC
//�������ǽ��Թ���ͨ��Ϊ��
//����Ĭ�Ͻ�����ͨ��0~3																	   
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //ʹ��ADC1ͨ��ʱ��
 
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //����ADC��Ƶ����6 72M/6=12,ADC���ʱ�䲻�ܳ���14M

	//PA1 ��Ϊģ��ͨ����������                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//ģ����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  //��λADC1,������ ADC1 ��ȫ���Ĵ�������Ϊȱʡֵ

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//ģ��ת�������ڵ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   

	ADC_TempSensorVrefintCmd(ENABLE); //�����ڲ��¶ȴ�����
  
	ADC_Cmd(ADC1, ENABLE);	//ʹ��ָ����ADC1
	
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	
	ADC_StartCalibration(ADC1);	 //����ADУ׼
 
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������

}				  
//���ADCֵ
//ch:ͨ��ֵ 0~3
u16 Get_Adc(u8 ch)   
{
  	//����ָ��ADC�Ĺ�����ͨ����һ�����У�����ʱ��
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��,����ʱ��Ϊ239.5����	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������

	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}

u16 Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/times;
} 	 

// �ڲ��¶ȴ����� ADC_Channel_16
u16 T_Get_Adc(u8 ch)   
{
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADCͨ��3,��һ��ת��,����ʱ��Ϊ239.5����	  			    

	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//�ȴ�ת������
	return ADC_GetConversionValue(ADC1);	//�������һ��ADC1�������ת�����
}

//��ȡͨ��ch��ת��ֵ
//ȡtimes��,Ȼ��ƽ��
u16 T_Get_Adc_Average(u8 ch,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=T_Get_Adc(ch);
		delay_ms(5);
	}
	return temp_val/times;
} 	   

double Get_Temprate(void)
{
	u32 adcx;
	double temprate;
	adcx = T_Get_Adc_Average(ADC_Channel_16, 20);
	temprate = (float)adcx*(3.3/4096);	//��ѹֵ
	temprate = (1.43-temprate)/0.0043 + 25; // ת��Ϊ�¶�ֵ
	return temprate;
}


// ��ͨ��(��DMA)
void adc_gpio_init_nodma(void)
{
    GPIO_InitTypeDef t_gpio;
   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);//ʹ�� GPIOA GPIOB GPIOC ʱ��
    t_gpio.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;//GPIOA
    t_gpio.GPIO_Mode=GPIO_Mode_AIN;//ģ������ģʽ
    GPIO_Init(GPIOA,&t_gpio);//��ʼ��GPIOA
    
    t_gpio.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;//GPIOB 
    GPIO_Init(GPIOB,&t_gpio);//��ʼ��GPIOB
    
    t_gpio.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;//GPIOC  
    GPIO_Init(GPIOC,&t_gpio);//��ʼ��GPIOC      
}
 
void adc_init_nodma(void)
{
    ADC_InitTypeDef t_adc;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//ʹ��ADC1ʱ�� 
    
    t_adc.ADC_Mode = ADC_Mode_Independent;               //����ģʽ��ADC1��ADC2����
    t_adc.ADC_ScanConvMode = DISABLE;                      //����ͨ��ɨ��
    t_adc.ADC_ContinuousConvMode = DISABLE;                //��������ת��
    t_adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//��ʹ���ⲿ����
    t_adc.ADC_DataAlign = ADC_DataAlign_Right;             //����λ�Ҷ���
    t_adc.ADC_NbrOfChannel = 1;                            //ת��ͨ����Ϊ1
    ADC_Init(ADC1,&t_adc);                                 //��ʼ��ADC1
    
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);//����ADCʱ��ΪPCLK2��8��Ƶ
 
    ADC_Cmd(ADC1,ENABLE); //ʹ��ADC1
        
    ADC_ResetCalibration(ADC1);          
    while(ADC_GetResetCalibrationStatus(ADC1));     
    ADC_StartCalibration(ADC1); //У׼
    while(ADC_GetCalibrationStatus(ADC1)){}; 
}
 
uint16_t read_adc_value_nodma(uint8_t ch)
{
    uint16_t adc_value = 0;
    
    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_7Cycles5 );   //����ADC1ͨ��ch��ת������Ϊ7.5���������ڣ���������Ϊ1
 
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);//ʹ���������
    
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC )){};//�ȴ�ת�����
        
    adc_value = ADC_GetConversionValue(ADC1); //��ȡת��ֵ
  
    return adc_value;
}
























