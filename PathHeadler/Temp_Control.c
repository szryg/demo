#include "include.h"

unsigned int TARGET_TEMP = 0;
extern unsigned int EASYGUI_TIME_MS;

void Temp_Control_Handler()
{
	unsigned int temp1, temp2;
	static u32 temp_ct = 0;
	if(TaskMan_State.current_task == -1 || TARGET_TEMP==0)  //如果没有任务，关闭所有输出
	{
		EXOUT_Close(SW_PTC1|SW_PTC2);
		TARGET_TEMP = 0;             //将设置温度归0
		return;
	}
	if(TaskMan_State.pause )    //如果暂停了，不做任何操作
		return;
	if(EASYGUI_TIME_MS-temp_ct >= 1000)
		temp_ct = EASYGUI_TIME_MS;
	else
		return;
	
	
	temp1 = GetTemp(0, 5);
	temp2 = GetTemp(1, 5);
	
	//printf("temp1: %u, temp2: %u\r\n", temp1, temp2);
	
	if(temp1 > TARGET_TEMP)
		EXOUT_Close(SW_PTC1);
	else
		EXOUT_Open(SW_PTC1);
	
	if(temp2 > TARGET_TEMP)
		EXOUT_Close(SW_PTC2);
	else
		EXOUT_Open(SW_PTC2);
	
}

void Temp_Set(unsigned char temp)
{
	TARGET_TEMP = temp*10;
}
