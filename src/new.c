#include "LPC11xx.h"                    // Device header
#include <string.h>
#include <stdio.h>

uint16_t R;
uint8_t SETTEMP;
char LEDBuffer[20];

void newp()
{  
	uint32_t I;
	uint32_t analog;
	uint32_t digit ;
	R=24;

	digit=0;
		for(I=0;I<10;I++)
		{
			LPC_ADC ->CR |=(1<<24);//立即转换
			while((LPC_ADC->DR[0]&0X80000000)==0);//读取DR0的Done
			analog=LPC_ADC ->DR[0];//读取结果寄存器
			analog=(analog>>6)&0x3ff;//数据 从第六位开始存储，占据10位
			digit+=analog ;//数据累加
			
		}
		digit=digit/10;//采样10次进行滤波
		digit=(digit*3300)/1024;//数字量转换成模拟量
	 
		if((0<digit)&&(200>digit))
		 R=19;
		if((200<digit)&&(400>digit))
		 R=20;
		if((400<digit)&&(600>digit))
		 R=21;
		if((600<digit)&&(800>digit))
		 R=22;
		if((800<digit)&&(1000>digit))
		 R=23;
		if((1000<digit)&&(1200>digit))
		 R=24;
		if((1200<digit)&&(1400>digit))
		 R=25;
		if((1400<digit)&&(1600>digit))
		 R=26;
		if((1600<digit)&&(1800>digit))
		 R=27;
		if((1800<digit)&&(2000>digit))
			R=28 ;  
		if((2000<digit)&&(2200>digit))
			R=29;  
		if((2200<digit)&&(2400>digit))
			R=30;  
		if((2400<digit)&&(2600>digit))
			R=31;  
		if((2600<digit)&&(2800>digit))
			R=32;
    if((2800<digit)&&(3000>digit))
			R=33;
		if((3000<digit)&&(3200>digit))
			R=34;
		if((3200<digit)&&(3400>digit))
			R=35;
			
		SETTEMP=R;
    sprintf ( LEDBuffer,"SET=%d'C",SETTEMP);
	}