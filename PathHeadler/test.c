#include "include.h"


void test(u8 in)  //如果流程刚启动，则in为1，否则为0
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
		//开水伐
		time1 = time();
		a=2;
	}
	if(a == 2)
	{
		if(time()-time1 >= 60000)
		{
			//关水伐
			a=3;
		}
		else
			return;
	}
}