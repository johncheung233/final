#include "LPC11xx.h"                    // Device header
#include "ADC.h"
#include "BREAK.h"
#include "lcd.h"
#include "UART.h"
#include "measure.h"
#include "alarm.h"
#include "new.h"
#include <stdio.h>
#include <string.h>
#define UART_BPS 115200

 uint32_t i;
 uint32_t ulADCData;
 uint32_t ulADCBuf;
int main()
	{

	extern uint8_t SETTEMP;
	extern char LEDBuffer[20];
	extern char mea[20];
	extern char elec[20];
	extern 	float T;
	char GcRcvBuf[20];
	char warn[20];
	char warnbuff[]="warning!!";
	BreakInit();
	KEYinit();
	SEGinit();
	InitLCD();
	LCD_IOInit();
	ADC_Init();
	UART_Init();


	NVIC_EnableIRQ(EINT3_IRQn);//中断判断按键
	while(1) 
	{ ADC2_Init() ;
		newp();
    LCD_DisplayStr(0,0,LEDBuffer);//显示设定报警的值
		ADC_Init();
		measure();//测量
	  LCD_DisplayStr(0,1,mea);
	  sprintf (GcRcvBuf ,"TEMP=%f'C\r\n",T);//将数据传送到pc
		UART_SendStr(GcRcvBuf);//将数据传送到pc
		UART_SendStr(elec);
		if(SETTEMP<=T)
		{
			alarm();
			sprintf (LEDBuffer,"%s",warnbuff);//显示welcome
	    LCD_DisplayStr(0,0,LEDBuffer);
		}
		else
			;
	}

}