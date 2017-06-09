#include "LPC11xx.h"                    // Device header
#include <stdio.h>
#include <string.h>
uint8_t  table[9]={0x00,0x01,0x03,0x07,0x0f,0x1f,0x3f,0x7f,0xff};
void Delay(uint32_t ulTime)
{
	uint32_t i;
	i=0;
		while(ulTime--)
	{
		for(i=0;i<5000;i++);
	}
}

void alarm()
{
	int a=0;
	for(a=0;a<9;a++)
	{
		LPC_GPIO2->DATA |= table[a];
	  Delay(200);		
	}
	
}
	