 #include "adc.h"
 #include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK miniSTM32开发板
//ADC 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/7
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
////////////////////////////////////////////////////////////////////////////////// 
	   
		   
//初始化ADC
//这里我们仅以规则通道为例
//我们默认将开启通道0~3																	   
void  Adc_Init(void)
{ 	
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	  //使能ADC1通道时钟
 
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);   //设置ADC分频因子6 72M/6=12,ADC最大时间不能超过14M

	//PA1 作为模拟通道输入引脚                         
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;		//模拟输入引脚
	GPIO_Init(GPIOA, &GPIO_InitStructure);	

	ADC_DeInit(ADC1);  //复位ADC1,将外设 ADC1 的全部寄存器重设为缺省值

	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;	//模数转换工作在单次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐
	ADC_InitStructure.ADC_NbrOfChannel = 1;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   

	ADC_TempSensorVrefintCmd(ENABLE); //开启内部温度传感器
  
	ADC_Cmd(ADC1, ENABLE);	//使能指定的ADC1
	
	ADC_ResetCalibration(ADC1);	//使能复位校准  
	 
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	
	ADC_StartCalibration(ADC1);	 //开启AD校准
 
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
 
//	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能

}				  
//获得ADC值
//ch:通道值 0~3
u16 Get_Adc(u8 ch)   
{
  	//设置指定ADC的规则组通道，一个序列，采样时间
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道,采样时间为239.5周期	  			    
  
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能	
	 
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束

	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
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

// 内部温度传感器 ADC_Channel_16
u16 T_Get_Adc(u8 ch)   
{
	ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );	//ADC1,ADC通道3,第一个转换,采样时间为239.5周期	  			    

	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能
	while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));//等待转换结束
	return ADC_GetConversionValue(ADC1);	//返回最近一次ADC1规则组的转换结果
}

//获取通道ch的转换值
//取times次,然后平均
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
	temprate = (float)adcx*(3.3/4096);	//电压值
	temprate = (1.43-temprate)/0.0043 + 25; // 转换为温度值
	return temprate;
}


// 多通道(非DMA)
void adc_gpio_init_nodma(void)
{
    GPIO_InitTypeDef t_gpio;
   
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC,ENABLE);//使能 GPIOA GPIOB GPIOC 时钟
    t_gpio.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;//GPIOA
    t_gpio.GPIO_Mode=GPIO_Mode_AIN;//模拟输入模式
    GPIO_Init(GPIOA,&t_gpio);//初始化GPIOA
    
    t_gpio.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1;//GPIOB 
    GPIO_Init(GPIOB,&t_gpio);//初始化GPIOB
    
    t_gpio.GPIO_Pin=GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5;//GPIOC  
    GPIO_Init(GPIOC,&t_gpio);//初始化GPIOC      
}
 
void adc_init_nodma(void)
{
    ADC_InitTypeDef t_adc;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);//使能ADC1时钟 
    
    t_adc.ADC_Mode = ADC_Mode_Independent;               //独立模式：ADC1与ADC2独立
    t_adc.ADC_ScanConvMode = DISABLE;                      //禁用通道扫描
    t_adc.ADC_ContinuousConvMode = DISABLE;                //禁用连续转换
    t_adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//不使用外部触发
    t_adc.ADC_DataAlign = ADC_DataAlign_Right;             //数据位右对齐
    t_adc.ADC_NbrOfChannel = 1;                            //转换通道数为1
    ADC_Init(ADC1,&t_adc);                                 //初始化ADC1
    
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);//配置ADC时钟为PCLK2的8分频
 
    ADC_Cmd(ADC1,ENABLE); //使能ADC1
        
    ADC_ResetCalibration(ADC1);          
    while(ADC_GetResetCalibrationStatus(ADC1));     
    ADC_StartCalibration(ADC1); //校准
    while(ADC_GetCalibrationStatus(ADC1)){}; 
}
 
uint16_t read_adc_value_nodma(uint8_t ch)
{
    uint16_t adc_value = 0;
    
    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_7Cycles5 );   //设置ADC1通道ch的转换周期为7.5个采样周期，采样次序为1
 
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);//使能软件触发
    
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC )){};//等待转换完成
        
    adc_value = ADC_GetConversionValue(ADC1); //获取转换值
  
    return adc_value;
}
























