#include "include.h"
#include "EXOUT.h"

#define CAVITY_T1 3000     //挤入清洁液时间
#define CAVITY_T2 3000     //继续清洗时间
#define CAVITY_T3 30000    //排水超时
#define CAVITY_T4 3000     //排水等待

void Cavity(u8 in, u8 in2)    //如果流程刚启动，则in为1，否则为0   舱门 (key类) gate 
{
	static u8 state = 0;
	static u8 last_in2 = 1;
    static u32 Time_Past1;
	
	
	if(in == 1)
	{
		last_in2 = 0;
		state=1;
		EasyGUI_WindowShow(&general_window);
		general_window_ShowTitie("腔体清洁");
	}
	
	if(in2!=last_in2 && in2 == 1)    //舱门打开事件
	{
		EasyGUI_TAG_ShowText(&general_window.element[1], "请关闭盖门以继续清洗");
	}
	else if(in2!=last_in2 && in2 == 0)  //舱门关闭事件
	{
		EasyGUI_TAG_ShowText(&general_window.element[1], "正在清洗中...");
	}
	last_in2 = in2;
	if(in2 == 1)   //如果舱门打开，什么都不做
		return;
	
	if(state == 1)
	{
		//开水阀
		//开 排水阀
		//开 齿轮泵
		general_window_ShowInfo("开始清洗");
		EXOUT_Open(SW_WATER_IN | SW_WATER_OUT | SW_MOTOR);
		Time_Past1 = time();
		state = 2;
	}
	
	if(state == 2)
	{
		if((time() - Time_Past1) >= CAVITY_T1 )
		{
			//关齿轮泵
			general_window_ShowInfo("清洗进行中");
			EXOUT_Close(SW_MOTOR);
			if((time() - Time_Past1) >= CAVITY_T2)
			{
				Time_Past1 = time();
				state = 3;
				general_window_ShowInfo("正在排水");
			}
		}
	}
	
	if(state == 3)
	{
		if(low == 1 || time() - Time_Past1 >=CAVITY_T3)   //到达限低   需要等待超时30分钟
		{
			state =4;
		    Time_Past1 = time();
			general_window_ShowInfo("等待排水完成");
		}
		else
			return;
	}
	
	if(state == 4)
	{
		if(time() - Time_Past1 >=CAVITY_T4)
		{
			EXOUT_Close(SW_WATER_IN | SW_WATER_OUT);
			
			TaskMan_TaskStop();
			EasyGUI_Message(&Activity1_window, "工作完成");   //显示信息框
		}
		else
			return;
	}
	
}






