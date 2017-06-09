#include "LPC11xx.h"                    // Device header
#include "string.h"
#include "stdio.h"
#define LCD_DATAPORT	LPC_GPIO2->DATA
char first[20];

static volatile unsigned int ticks = 0;
/********************************************************************************
* FunctionName   : Delayms(uint16_t ms)
* Description    : ??????????????
* EntryParameter : ms:?????
* ReturnValue    : None
********************************************************************************/
void Delayms(uint16_t ms)					
{
	SysTick->CTRL &= ~(1<<2);
	SysTick->LOAD = 25000*ms-1;			
	SysTick->VAL = 0;						
	SysTick->CTRL = ((1<<1)|(1<<0));       
	while(!ticks);						    
	ticks = 0;							    
	SysTick->CTRL = 0;	
}
/********************************************************************************
* FunctionName   : SysTick_Handler()
* Description    : ?????????????
* EntryParameter : None
* ReturnValue    : None
********************************************************************************/
void SysTick_Handler(void)
{
	ticks++;
}
/********************************************************************************
* FunctionName   : Busy_Check()
* Description    : ??LCD?????,???????8?,???????
* EntryParameter : None
* ReturnValue    : ?LCD?????????
********************************************************************************/
uint8_t Busy_Check()
{
 	uint8_t LCD_Status;
	LPC_GPIO2->DATA &= ~(1<<0);
	LPC_GPIO2->DATA |=  (1<<1);
	LPC_GPIO2->DATA |=  (1<<2);	//??????????
	Delayms(1);
	
//	LCD_DATA_IN;	//????????
    LPC_GPIO2->DIR &= ~(0x7F8);
    
    LCD_Status = (LPC_GPIO2->DATA & 0x7F8) >> 3;	//??????
//	LCD_DATA_OUT;	//????????
	LPC_GPIO2->DIR |= 0x7F8;
    
	LPC_GPIO2->DATA &= ~(1<<2);	
	return LCD_Status;
}
/********************************************************************************
* FunctionName   : LCD_WriteCommand()
* Description    : ?????
* EntryParameter : cmd:??
* ReturnValue    : None
********************************************************************************/
void LCD_WriteCommand(uint32_t cmd)
{
 	while((Busy_Check()	&	0x80)	==	0x80);	//??LCD?????
	LPC_GPIO2->DATA &= ~(1<<0);
	LPC_GPIO2->DATA &= ~(1<<1);
	LPC_GPIO2->DATA &= ~(1<<2);	//??????????
    
	LPC_GPIO2->DATA = ((cmd << 3) & 0x7F8) | 0x00;	//?????
	Delayms(1);	
	LPC_GPIO2->DATA |=  (1<<2);
	Delayms(1);
	LPC_GPIO2->DATA &= ~(1<<2);
}
/********************************************************************************
* FunctionName   : LCD_WriteData()
* Description    : ???????
* EntryParameter : dat:??
* ReturnValue    : None
********************************************************************************/
void LCD_WriteData(uint32_t dat)
{
 	while((Busy_Check() & 0x80) == 0x80);	//??LCD?????
	LPC_GPIO2->DATA |=  (1<<0);
	LPC_GPIO2->DATA &= ~(1<<1);
	LPC_GPIO2->DATA &= ~(1<<2);	//??????????
	LPC_GPIO2->DATA = ((dat << 3) & 0x7F8) | 0x01;	//?????
	Delayms(1);	
	LPC_GPIO2->DATA |=  (1<<2);
	Delayms(1);
	LPC_GPIO2->DATA &= ~(1<<2);
}
/********************************************************************************
* FunctionName   : LCD_DisplayChar()
* Description    : ?????????,y????0,1?x?0=<x<=16?
* EntryParameter : x:x??(0~16), y: y??(0~1),ch:???
* ReturnValue    : None
********************************************************************************/
uint8_t LCD_DisplayChar(uint8_t x, uint8_t y, uint8_t ch)
{
	if ((y > 2) || (x > 16)) // x,y????
	{
	    return 1;
	}
	x |= ((y == 1) ? 0xC0 : 0x80); // ????
	LCD_WriteCommand(x); // ????????,?????
	LCD_WriteData(ch);
	return 0;
}
/********************************************************************************
* FunctionName   : LCD_DisplayStr()
* Description    : ???????????
* EntryParameter : x - x??(0~15), y - y??(0~1), *pStr - ?????
* ReturnValue    : ????0,????1
********************************************************************************/
uint8_t LCD_DisplayStr(uint8_t x, uint8_t y,uint8_t *pStr)
{
  uint8_t i;
	uint8_t lineAddr[] = {0x80, 0xC0};

	if ((y >= 2) || (x >= 16))	// x, y????
	{
	    return 1;
	}
	LCD_WriteCommand(lineAddr[y] + x);  // ????
	for (i=x; ((i<16) && (*pStr!='\0')); i++)
	{
 		LCD_WriteData(*(pStr++)); // ????
	}
	if (*pStr != '\0') // ????????
	{
 		x = 0; // ??????2?
		if (++y < 2)
		{
		    LCD_DisplayStr(x, y, pStr); // ???????(????)
		} 
	}
	return 0;
}
/********************************************************************************
* FunctionName   : LCDIOInit()
* Description    : ???LCD?????,
                   DB0~DB7??P2.0~P2.7,RS?RW?E??P3.0~P3.3
* EntryParameter : None
* ReturnValue    : None
********************************************************************************/
void LCD_IOInit(void)
{
	LPC_GPIO2->DIR |= 0xFFF;	//??P2_0~P2_7???
//	LPC_GPIO3->DIR |= 0x0F;	//??P3_0~P3_3???
    LPC_GPIO0->DIR |= 0x02;
    LPC_GPIO0->DATA |= (0x02);    
}
/********************************************************************************
* FunctionName   : InitLCD()
* Description    : ???LCD??????????
* EntryParameter : None
* ReturnValue    : None
********************************************************************************/
void InitLCD()
{
	LCD_IOInit();	//???LCD???GPIO
 	LCD_WriteCommand(0x38);	//???8????2????5×7????
	Delayms(1);	
	LCD_WriteCommand(0x01);	//??,?HOME?
	Delayms(1);	
	LCD_WriteCommand(0x06);	//?????????,???????
	Delayms(1);	
	LCD_WriteCommand(0x0c);	//???,????,?????
	Delayms(1);	
}

