#include "include.h"


void test(u8 in)  //������̸���������inΪ1������Ϊ0
{
	static u8 a=0;
	static u32 time1;
	
	if(in == 1)
	{
		a = 1;
		time_init();
	}
	
	if(a == 1)
	{
		//��ˮ��
		time1 = time();
		a=2;
	}
	if(a == 2)
	{
		if(time()-time1 >= 60000)
		{
			//��ˮ��
			a=3;
		}
		else
			return;
	}
}