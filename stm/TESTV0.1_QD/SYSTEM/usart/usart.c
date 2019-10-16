#include "sys.h"
#include "usart.h"	 

UART_RX_FORMAT m_rxbuff;

/***************************************************/
//函数名：crc_16
//功  能：crc_16校验
//参  数：byte、crc_sum
//返回值：crc_sum
/**************************************************/
unsigned short crc_16(char* byte,unsigned short crc_sum)
{	
  volatile unsigned char i,j;
  crc_sum ^= *byte;
  for (i = 0;i < 8;i ++)
  {
    j = crc_sum&1;
    crc_sum >>= 1;
    if(j)crc_sum ^= 0xA001;
  }
  return crc_sum;
}
/***************************************************/
//函数名：CRCSUB
//功  能：crc_16校验
//参  数：CrcDataBuffer 校验内容首地址
//				dataNumber    待校验数据长度
//返回值：crc_sumer     crc校验结果
/**************************************************/
unsigned short CRCSUB(char* CrcDataBuffer,unsigned short dataNumber)
{
	unsigned short crc_sumer;
  unsigned int i;
  crc_sumer=0xffff;
  for(i=0;i<dataNumber;i++)
  {	
    crc_sumer=crc_16(CrcDataBuffer,crc_sumer);
    CrcDataBuffer ++;
  }
	return crc_sumer;
}

/***************************************************/
//函数名：uartdataproc
//功  能：串口数据处理函数
//参  数：buff串口接收数据缓冲区
//返回值：无
/**************************************************/
unsigned char uartdataproc(UART_RX_FORMAT * m_rx)
{
	//判断crc
	if(0 == CRCSUB((char *)m_rx->buff+2, m_rx->count-4))//校验成功
	{
		return m_rx->buff[3];
	}
	else//校验失败
	{
		return 0;
	}
}

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*使用microLib的方法*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
 
#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	  
  
void uart_init(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 

}

void OnUART1_RecvData(unsigned char c)
{
	m_rxbuff.buff[m_rxbuff.count++] = c;
	TIM_SetCompare3(TIM3, 1000);//PWM启动
	m_rxbuff.recvstatus = RX_STAIL;//接收结束
//	//判断缓冲区是否满
//	if(m_rxbuff.count >= (USART_REC_LEN-3))
//	{
//		//串口缓冲区满回到最初状态
//		m_rxbuff.count = 0;
//		m_rxbuff.recvstatus=RX_IDLE;
//	}
}

void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		Res =USART_ReceiveData(USART1);	//读取接收到的数据
		OnUART1_RecvData(Res);//处理接收到的数据
  }
}

#endif
