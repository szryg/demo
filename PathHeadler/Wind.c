#include "include.h"

#define WIND_T1 30000   //烘干时间



void Wind(u8 in, u8 in2)    //如果流程刚启动，则in为1，否则为0   舱门 (key类) gate 
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
		general_window_ShowTitie("热风烘干");
	}
	
	if(in2!=last_in2 && in2 == 1)    //舱门打开事件
	{
		EasyGUI_TAG_ShowText(&general_window.element[1], "请关闭盖门以继续");
	}
	else if(in2!=last_in2 && in2 == 0)  //舱门关闭事件
	{
		EasyGUI_TAG_ShowText(&general_window.element[1], "正在进行中...");
	}
	last_in2 = in2;
	if(in2 == 1)   //如果舱门打开，什么都不做
		return;
    //***********************************//

	if(state == 1)
	{
		//开 风扇	
		general_window_ShowInfo("启动风扇");
		EXOUT_Open(SW_FAN2 | SW_FAN3);		
		state = 2;
	}
	
	if(state == 2)
	{
		//开 温度控制程序
		Temp_Set(48);
		Time_Past1 = time();
		state = 3;
		general_window_ShowInfo("正在工作");
		general_window.element[2].text = "温度:";
		general_window.element[2].reflash = 1;
	}
	
	if(state == 3)
	{

			
		general_window_ShowNumber((GetTemp(0, 5)+GetTemp(1, 5))/20);

		if((time() - Time_Past1) >= WIND_T1 )  //等待30min  就关闭 
		{
			//关 风扇
			//关温度控制程序
			EXOUT_Close(SW_FAN2 | SW_FAN3);		
			Temp_Set(0);
	
			TaskMan_TaskStop();
			EasyGUI_Message(&Activity2_window, "清洗完成");   //显示信息框
		} 
		else
		    return;
			
	}
	
}






