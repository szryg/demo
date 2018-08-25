#include "include.h"

#define FRUIT_T1 3000   //注水时间
#define FRUIT_T2 3000   //清洁时间
#define FRUIT_T3 30000   //排水超时
#define FRUIT_T4 3000   //排水等待

void Fruit(u8 in, u8 in2)    //如果流程刚启动，则in为1，否则为0   舱门 (key类) gate 
{
	static u8 state = 0;
	static u8 last_in2 = 1;
    static u32 Time_Past1;
	//***********************************//
	if(in == 1)
	{
		last_in2 = 0;
		state=1;
		EasyGUI_WindowShow(&general_window);
		general_window_ShowTitie("果蔬清洗");
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
    //***********************************//

	if(state == 1)
	{
		//开 进水 
		general_window_ShowInfo("正在注水");
		EXOUT_Open(SW_WATER_IN);
		Time_Past1 = time();
		state = 2;
	}
	
	if(state == 2)
	{
		if((time() - Time_Past1) >= FRUIT_T1 || high )  //等待30min  就关闭 
		{
			//关闭 进水
			EXOUT_Close(SW_WATER_IN);			
	        state = 3;
		} 
		else
		    return;
			
	}
	if(state == 3)
	{
	    //打开 超声波 
		general_window_ShowInfo("正在清洁");
		EXOUT_Open(SW_WAVE);
		Time_Past1 = time();
		state = 4;
	}
	if(state == 4)
	{
		if(time()-Time_Past1 >= FRUIT_T2)
		{
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
		Time_Past1 = time();
		state = 6;
	}
	if(state == 6)
	{
		if(low == 1 || time() - Time_Past1 >=FRUIT_T3)   //到达限低   需要等待超时30分钟
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
		if(time() - Time_Past1 >=FRUIT_T4)
		{
			EXOUT_Close(SW_WATER_OUT);
			
			TaskMan_TaskStop();
			EasyGUI_Message(&Activity1_window, "清洗完成");   //显示信息框
		}
		else
			return;
	}
	
}

