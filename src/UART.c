#include "LPC11xx.h"                    // Device header
#define UART_BPS 115200
void UART_Init()
{
	uint16_t usFdiv;
	LPC_SYSCON->SYSAHBCLKCTRL|=(1<<16);//ʹ��IOCONʱ��
	LPC_IOCON->PIO1_6&=~0x07;//��P1.6�ȸ�λ
	LPC_IOCON->PIO1_6|=0x01;//��P1.6����ΪRXD����������
	LPC_IOCON->PIO1_7&=~0x07;//��P1.7�ȸ�λ
	LPC_IOCON->PIO1_7|=0x01;//��P1.7����ΪTXD����������
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16);//�ر�IOCONʱ��
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);//��UARTʱ��
	LPC_SYSCON->UARTCLKDIV|=0x01;//����UARTʱ�ӷ�ƵֵΪ1
	LPC_UART->LCR=0x83;//0X83������λ1000 0011������Ϊ8λ�ַ����� һ��ֹͣλ ����żУ�� ������Գ����������ķ���
	//LCRΪUART�߿��ƼĴ��������շ��������ַ���ʽ
	
	usFdiv=(SystemCoreClock /LPC_SYSCON ->UARTCLKDIV/16)/UART_BPS;//����ò�����Ҫ��ĳ���������ֵ
	LPC_UART->DLM=usFdiv/256;//д�����������ĸ�8λ
	LPC_UART->DLL=usFdiv%256;//д�����������ĵ�8λ
	//DLM��DLL����UART�ĳ���������DLLΪ��8λ DLMΪ��8λ
	LPC_UART->LCR=0x03;//����������
	LPC_UART->FCR=0x07;//ʹ��FIFO ����8�ֽڴ���
	
}
void UART_SendByte(uint8_t ucDAT)
{
		LPC_UART->THR=ucDAT;//��������
		while((LPC_UART->LSR&0x40)==0);//�ȴ������꣬TEMT��λ
} 
void UART_SendStr( char  *pucStr)
{
	while(1)
	{
			if(*pucStr =='\0')
				break;//�����������˳�
			UART_SendByte(*pucStr++);  
	}
}
