#include "sys.h"
#include "usart.h"	 

UART_RX_FORMAT m_rxbuff;

/***************************************************/
//��������crc_16
//��  �ܣ�crc_16У��
//��  ����byte��crc_sum
//����ֵ��crc_sum
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
//��������CRCSUB
//��  �ܣ�crc_16У��
//��  ����CrcDataBuffer У�������׵�ַ
//				dataNumber    ��У�����ݳ���
//����ֵ��crc_sumer     crcУ����
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
//��������uartdataproc
//��  �ܣ��������ݴ�����
//��  ����buff���ڽ������ݻ�����
//����ֵ����
/**************************************************/
unsigned char uartdataproc(UART_RX_FORMAT * m_rx)
{
	//�ж�crc
	if(0 == CRCSUB((char *)m_rx->buff+2, m_rx->count-4))//У��ɹ�
	{
		return m_rx->buff[3];
	}
	else//У��ʧ��
	{
		return 0;
	}
}

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*ʹ��microLib�ķ���*/
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
 
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	  
  
void uart_init(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

}

void OnUART1_RecvData(unsigned char c)
{
	m_rxbuff.buff[m_rxbuff.count++] = c;
	TIM_SetCompare3(TIM3, 1000);//PWM����
	m_rxbuff.recvstatus = RX_STAIL;//���ս���
//	//�жϻ������Ƿ���
//	if(m_rxbuff.count >= (USART_REC_LEN-3))
//	{
//		//���ڻ��������ص����״̬
//		m_rxbuff.count = 0;
//		m_rxbuff.recvstatus=RX_IDLE;
//	}
}

void USART1_IRQHandler(void)                	//����1�жϷ������
{
	u8 Res;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		Res =USART_ReceiveData(USART1);	//��ȡ���յ�������
		OnUART1_RecvData(Res);//������յ�������
  }
}

#endif
