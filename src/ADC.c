#include "LPC11xx.h"                    // Device header

void ADC_Init(void)
{
	LPC_SYSCON ->SYSAHBCLKCTRL|=(1<<16);
	LPC_IOCON ->PIO1_11 &=~0XBF;//配置PIO0_11为模拟输入模式
	LPC_IOCON ->PIO1_11 |=0X01;//PO0_11模拟输入通道1
	LPC_SYSCON->PDRUNCFG &=~(0X01<<4);//ADC模块上电
	LPC_SYSCON ->SYSAHBCLKCTRL |=(0X01<<13);//使能ADC模块时钟
	LPC_ADC ->CR = (0X01<<7)|//SEL=1，选择ADC即ADC7
	               ((SystemCoreClock /1000000-1)<<8)|//转换时钟1M
								 (0<<16)|//软件控制转换操作
								 (0<<17)|//使用1clocks转换
								 (0<<24)|//ADC转换停止
								 (0<<27);//直接启动ADC转换，此位无效
}

void ADC2_Init(void)
{
	LPC_SYSCON ->SYSAHBCLKCTRL|=(1<<16);
	LPC_IOCON ->R_PIO0_11 &=~0XBF;//配置PIO0_11为模拟输入模式
	LPC_IOCON ->R_PIO0_11 |=0X02;//PO0_11模拟输入通道0
	LPC_SYSCON->PDRUNCFG &=~(0X01<<4);//ADC模块上电
	LPC_SYSCON ->SYSAHBCLKCTRL |=(0X01<<13);//使能ADC模块时钟
	LPC_ADC ->CR = (0X01<<0)|//SEL=1，选择ADC即ADC0
	               ((SystemCoreClock /1000000-1)<<8)|//转换时钟1M
								 (0<<16)|//软件控制转换操作
								 (0<<17)|//使用1clocks转换
								 (0<<24)|//ADC转换停止
								 (0<<27);//直接启动ADC转换，此位无效

}