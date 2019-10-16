#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 

#define USART_REC_LEN  	200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收

//串口接收状态定义
#define RX_IDLE 					0   //接收空闲状态
#define RX_STAIL					1		//接收完成标志
//#define RX_FHEAD					1   //接收到第一个0xAA
//#define RX_SHEAD					2   //连续接收到第2个0xAA
//#define RX_FTAIL          3   //接收到第一个0xBB

typedef struct recvbuff
{
	unsigned char buff[USART_REC_LEN]; //接收数据缓冲区
	unsigned char count;//接收到的字节数
	unsigned char recvstatus;//串口接收状态
}UART_RX_FORMAT;

extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	
extern UART_RX_FORMAT m_rxbuff;	
void uart_init(u32 bound);
unsigned char uartdataproc(UART_RX_FORMAT * m_rx);
unsigned short crc_16(char* byte,unsigned short crc_sum);
unsigned short CRCSUB(char* CrcDataBuffer,unsigned short dataNumber);

#endif
