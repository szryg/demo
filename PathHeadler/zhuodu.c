
#include "public.h"

u32 Get_zhuodu(void)
{
	int Voltage =0, a;
    a = 5;
	
	while(a--)
		Voltage += Get_Adc(1);                       //ADC Í¨µÀÑ¡Ôñ
	Voltage = Voltage/5;
	
	Voltage=(Voltage*3300)/4095;
	printf("ZhuoDu %u \r\n",Voltage);
	Voltage = Voltage*5000/3300;
	return Voltage;
}




