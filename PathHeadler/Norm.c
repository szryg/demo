#include "include.h"
#include "EXOUT.h"

#define NORM_T1 3000  //齿轮泵运行时长
#define NORM_T2 6000  //进水阀运行时长
#define NORM_T3 6000  //超声波
#define NORM_T4 30000  //放水超时
#define NORM_T5 10000  //达到限低后延迟关阀时间
#define NORMX1_REPEAT_TIMES 1    //重复次数


void Norm(u8 in, u8 in2)    //如果流程刚启动，则in为1，否则为0   舱门 (key类) gate 
{
    static u8 state = 0, repeat;
	static u8 last_in2 = 1;
    static u32 Time_Past1, Time_Past2;	
	
	
	
	if(in == 1)
	{
		last_in2 = 0;
		state=1;
		repeat = 1;
		EasyGUI_WindowShow(&general_window);
		general_window_ShowTitie("节能清洗");
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
		//开水阀//开齿轮泵
		general_window_ShowInfo("正在注入水与清洗剂");
		EXOUT_Open(SW_WATER_IN|SW_MOTOR);
		Time_Past1 = time();
		state = 2;
	}
	
	if(state == 2)
	{
		if((time() - Time_Past1) >= NORM_T1)
		{
			EXOUT_Close(SW_MOTOR);
			general_window_ShowInfo("等待注水完成");
			if(((time() - Time_Past1) >= NORM_T2) || high)  //等待60s 或者 到了限高 就关闭水阀 
			{
				EXOUT_Close(SW_WATER_IN);
				EXOUT_Close(SW_MOTOR);
				printf("关掉水伐---------------------%u\r\n", time() - Time_Past1);
				//关水阀
				state = 3;
			}
			else
				return;
		}
		else
			return;
		
	}
	
	if(state == 3)
	{
		// 超声波 开启 
		general_window_ShowInfo("正在使用超声波清洁");
		EXOUT_Open(SW_WAVE);
		Time_Past2 = time();
		state = 4;
	}
	
	if(state == 4)
	{
	    if((time() - Time_Past2) >= NORM_T3)        // 20min
		{
			//关超声波
			EXOUT_Close(SW_WAVE);
			state = 5;
		}
		else
			return;
	}
	
	if(state == 5)
	{
	    //开 排水阀
		general_window_ShowInfo("正在排水");
		EXOUT_Open(SW_WATER_OUT);
		Time_Past2 = time();
		state = 6;
	}
	if(state == 6)
	{
		if(low == 1 || time() - Time_Past2 >=NORM_T4)   //到达限低   需要等待超时30分钟
		{
			state =7;
		    Time_Past1 = time();
			general_window_ShowInfo("等待排水完成");
		}
		else
			return;
	}
	if(state == 7)
	{
		if(time() - Time_Past1 >=NORM_T5)
		{
			EXOUT_Close(SW_WATER_OUT);
			state = 8;
		}
		else
			return;
	}
	
	if(state == 8)
	{
		if(repeat++ < NORMX1_REPEAT_TIMES)      //重复执行
		{
			state = 1;
			return;
		}
		
		TaskMan_TaskStop();
		EasyGUI_Message(&Activity1_window, "清洗完成");   //显示信息框
	}
	
	
}   //完成一个 流程 了

