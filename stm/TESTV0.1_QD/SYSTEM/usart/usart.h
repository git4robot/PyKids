#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

#define USART_REC_LEN  	200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����

//���ڽ���״̬����
#define RX_IDLE 					0   //���տ���״̬
#define RX_STAIL					1		//������ɱ�־
//#define RX_FHEAD					1   //���յ���һ��0xAA
//#define RX_SHEAD					2   //�������յ���2��0xAA
//#define RX_FTAIL          3   //���յ���һ��0xBB

typedef struct recvbuff
{
	unsigned char buff[USART_REC_LEN]; //�������ݻ�����
	unsigned char count;//���յ����ֽ���
	unsigned char recvstatus;//���ڽ���״̬
}UART_RX_FORMAT;

extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	
extern UART_RX_FORMAT m_rxbuff;	
void uart_init(u32 bound);
unsigned char uartdataproc(UART_RX_FORMAT * m_rx);
unsigned short crc_16(char* byte,unsigned short crc_sum);
unsigned short CRCSUB(char* CrcDataBuffer,unsigned short dataNumber);

#endif
