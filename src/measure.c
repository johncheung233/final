#include "LPC11xx.h"                    // Device header
#include "stdio.h"
float T;
float F;
extern int change;
extern uint16_t R;
char mea[20]={0};
char elec[20];
void measure()
{
	uint32_t i;
	double  ulADCData;
	uint32_t ulADCBuf;
	double res;

		 

		ulADCData=0;
		for(i=0;i<10;i++)
		{
			LPC_ADC ->CR |=(1<<24);//����ת��
			while((LPC_ADC->DR[7]&0X80000000)==0);//��ȡDR0��Done
			ulADCBuf=LPC_ADC ->DR[7];//��ȡ����Ĵ���
			ulADCBuf=(ulADCBuf>>6)&0x3ff;//���� �ӵ���λ��ʼ�洢��ռ��10λ
			ulADCData+=ulADCBuf ;//�����ۼ�
	
			
		}
		ulADCData=ulADCData/10;//����10�ν����˲�
		ulADCData=(ulADCData*3300)/1024;//������ת����ģ����
		res=(ulADCData*10000)/(3300-ulADCData);
		
		if (res==28017)
			T=0;
		if (res==26825)
			T=1;
		if(( 26825>res)&&(res>18560))
	 	  T= 1+(26825-res)/1000;
	  if((18560 >res )&&(res>12690))
			T=	10+(18560-res)/700;
		if(( 12690>res )&&(res>10953))
			T= 20+(12690-res)/600;
		if(( 10953>res )&&(res>9576))
		  T=23+(10953-res)/500; 	
		if(( 9576>res )&&(res>8160))
		  T=26+(9576-res)/350;
		if(( 8160>res )&&(res>7578))
			T=30+(8160-res)/300;
		if(( 7578>res )&&(res>6357))
			T=32+(7578-res)/250;
		if(( 6357>res )&&(res>4828))
			T=37+(6357-res)/200;
		
    F=32+1.8*T;
    
		if(change>=0)		
		 sprintf (mea,"NOW=%.2f'C%d",T,R);
		else
		 sprintf (mea,"NOW=%.2f'F%d",F,change);
		
		sprintf (elec,"NOW=%fMV\r\n",res); 
		
}