#include "LPC11xx.h"                    // Device header
#include "string.h"

uint16_t R;
uint8_t SETTEMP=30;
char LEDBuffer[20];

void newp()
{  

	uint32_t I;
	uint32_t analog;
	uint32_t digit ;

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
	 
		if((0<digit)&&(366>digit))
		 R=20;
		if((0<digit)&&(412>digit))
		 R=21;
		if((824<digit)&&(1236>digit))
		 R=22;
		if((1236<digit)&&(1648>digit))
		 R=23;
		if((1648<digit)&&(2060>digit))
		 R=24;
		if((2060<digit)&&(2472>digit))
		 R=25;
		if((2472<digit)&&(2884>digit))
		 R=26;
		if((2884<digit)&&(3296>digit))
		 R=27;
		if((3296<digit)&&(3708>digit))
		 R=28;
		SETTEMP=R;
    sprintf ( LEDBuffer,"SET=%d'C",SETTEMP);
	}