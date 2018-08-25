#include "window.h"
#include "EXOUT.h"
#include "include.h"

#define general_element_num 6    //设定元素数


void general_event(Window_Type *window, signed short element_num);

Window_element_Type general_element[general_element_num] = {
	{28,16, 192, 40, GUIE_TAG, 0, 0, "清洗程序"},     //0
	{0,60, 240, 40, GUIE_TAG, 0, 0, "进 行 中...."},       //1
	{28,120, 60, 40, GUIE_TAG, 0, 0, ""},              //2剩余时间
	{100,130, 48, 24, GUIE_TAG, 00, 0, ""},  //3  显示的时间
	{0,170, 240, 40, GUIE_TAG, 0, 0, "显示信息"},
	{28,232, 184, 40, GUIE_BUTTON, 0, 0, "取 消"}
};

Window_Type general_window = {
	general_element_num,        //元素数量
	general_element,            //元素列表指针
	general_event               //窗口事件回调函数
};

void general_event(Window_Type *window, signed short element_num)
{
	u32 *remain_time = &window->element[3].value;        //标签中开机时间的值  
	
	
	
	EasyGUI_TAG_SetValue(&window->element[3], *remain_time);
	
	switch(element_num) {
		case 1:
			
			break;
		case 2:
			
			break;
		case 3:
							
			break;
		case 5:
			TaskMan_TaskStop();
			EasyGUI_WindowShow(&Activity_main_window);
			break;
		default:printf("Activity2 error \r\n");
		}
}

void general_window_ShowInfo(char *text)    //通用窗口显示提示信息
{
	EasyGUI_TAG_ShowText(&general_window.element[4], text);
}

void general_window_ShowNumber(u32 num)    //在通用窗口剩余时间标签中显示数字
{
	EasyGUI_TAG_SetValue(&general_window.element[3], num);
}

void general_window_ShowTitie(char *text)
{
	EasyGUI_TAG_ShowText(&general_window.element[0], text);
}

void general_window_CloseTimeInfo()
{
	general_window.element[2].text = "";
	general_window.element[3].text = "";
}
