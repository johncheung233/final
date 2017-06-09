#include "LPC11xx.h"                    // Device header

void ADC_Init(void)
{
	LPC_SYSCON ->SYSAHBCLKCTRL|=(1<<16);
	LPC_IOCON ->PIO1_11 &=~0XBF;//����PIO0_11Ϊģ������ģʽ
	LPC_IOCON ->PIO1_11 |=0X01;//PO0_11ģ������ͨ��1
	LPC_SYSCON->PDRUNCFG &=~(0X01<<4);//ADCģ���ϵ�
	LPC_SYSCON ->SYSAHBCLKCTRL |=(0X01<<13);//ʹ��ADCģ��ʱ��
	LPC_ADC ->CR = (0X01<<7)|//SEL=1��ѡ��ADC��ADC7
	               ((SystemCoreClock /1000000-1)<<8)|//ת��ʱ��1M
								 (0<<16)|//�������ת������
								 (0<<17)|//ʹ��1clocksת��
								 (0<<24)|//ADCת��ֹͣ
								 (0<<27);//ֱ������ADCת������λ��Ч
}

void ADC2_Init(void)
{
	LPC_SYSCON ->SYSAHBCLKCTRL|=(1<<16);
	LPC_IOCON ->R_PIO0_11 &=~0XBF;//����PIO0_11Ϊģ������ģʽ
	LPC_IOCON ->R_PIO0_11 |=0X02;//PO0_11ģ������ͨ��0
	LPC_SYSCON->PDRUNCFG &=~(0X01<<4);//ADCģ���ϵ�
	LPC_SYSCON ->SYSAHBCLKCTRL |=(0X01<<13);//ʹ��ADCģ��ʱ��
	LPC_ADC ->CR = (0X01<<0)|//SEL=1��ѡ��ADC��ADC0
	               ((SystemCoreClock /1000000-1)<<8)|//ת��ʱ��1M
								 (0<<16)|//�������ת������
								 (0<<17)|//ʹ��1clocksת��
								 (0<<24)|//ADCת��ֹͣ
								 (0<<27);//ֱ������ADCת������λ��Ч

}