#include "include.h"
#include "EXOUT.h"

#define LIGHT_T1 3000   //消毒时间

void Light(u8 in, u8 in2)    //如果流程刚启动，则in为1，否则为0   舱门 (key类) gate 
{
	static u8 state = 0;
	static u8 last_in2 = 1;
    static u32 Time_Past1;
	
	if(in == 1)
	{
		last_in2 = 0;
		state=1;
		EasyGUI_WindowShow(&general_window);
		general_window_ShowTitie("紫外杀菌");
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
		//开 紫外线
		general_window_ShowInfo("正在工作");
		EXOUT_Open(SW_LIGHT);
		Time_Past1 = time();
		state = 2;
	}
	
	if(state == 2)
	{
		if((time() - Time_Past1) >= LIGHT_T1 )  //等待30min 就关闭
		{
			//关 灯
			EXOUT_Close(SW_LIGHT);
			
			TaskMan_TaskStop();
			EasyGUI_Message(&Activity2_window, "工作完成");   //显示信息框
		} else
		    {
				return;
			}
	}
	
}






