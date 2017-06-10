#include "LPC11xx.h"                    // Device header
#include "stdio.h"

float T;
float F;
extern int change;
char mea[40];
char elec[50];

void measure()
{
	uint32_t i;
	float   ulADCData;
	uint32_t ulADCBuf;
	float  res;
	uint32_t D;

		for(i=0;i<10;i++)
		{
			LPC_ADC ->CR |=(1<<24);//Á¢¼´×ª»»
			while((LPC_ADC->DR[7]&0X80000000)==0);//¶ÁÈ¡DR0µÄDone
			LPC_ADC ->CR |=(1<<24);//Á¢¼´×ª»»
			while((LPC_ADC->DR[7]&0X80000000)==0);//¶ÁÈ¡DR0µÄDone
			ulADCBuf=LPC_ADC->DR[7];//¶ÁÈ¡½á¹û¼Ä´æÆ÷
			ulADCBuf=(ulADCBuf>>6)&0x3ff;//Êý¾Ý ´ÓµÚÁùÎ»¿ªÊ¼´æ´¢£¬Õ¼¾Ý10Î
      ulADCData=(ulADCBuf*1.00)+ulADCData;		
	  }
		ulADCData=(ulADCData*1.00)/10;//??10?????
		ulADCData=((ulADCData*3300)*1.00)/1024;//?????????
		res=((ulADCData*10000)*1.00)/(3300-ulADCData);
		if (res==28017)
			T=0;
		if (res==26825)
			T=1;
		if(( 26825>res)&&(res>18560))
	 	  T= 1+(26825-res)*1.00/1000;
	  if((18560 >res )&&(res>12690))
			T=	10+(18560-res)*1.00/700;
		if(( 12690>res )&&(res>10953))
  		T= 20+(12690-res)*1.00/600;
		if(( 10953>res )&&(res>9576))
		  T=23+(10953-res)*1.00/500; 	
		if(( 9576>res )&&(res>8160))
		  T=26+(9576-res)*1.00/350;		 
		if(( 8160>res )&&(res>7578))
			T=30+(8160-res)*1.00/300;
		if(( 7578>res )&&(res>6357))
			T=32+(7578-res)*1.00/250;
		if(( 6357>res )&&(res>4828))
			T=37+(6357-res)*1.00/200;
	
		if(change>=0)			
		{
			sprintf (mea,"NOW=%.2f'C%2d",T,change);
			mea[6]='.';
		}
		else
		{
			F=32+1.8*T;
			sprintf (mea,"NOW=%.2f'F%2d",F,change);
		  mea[6]='.';
		}
		
		 sprintf (elec,"NOW=%fmv\r\n",res);
		 elec[8]='.';
		
		
		
}