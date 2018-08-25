#include "window.h"
#include "TaskMan.h"

#define Activity3_element_num 13    //设定元素数


void Activity3_event(Window_Type *window, signed short element_num);

Window_element_Type Activity3_element[Activity3_element_num] = {
	{28,16, 192, 40, GUIE_TAG, 0, 0, "预  约  模  式"},
	{41,64, 152, 40, GUIE_TAG, 0, 0, "定 时 开 机"},
	{24,112, 32, 32, GUIE_BUTTON, 0, 0, "减"},
	{112,112, 32, 32, GUIE_BUTTON, 0, 0, "加"},
	{152,112, 64, 32, GUIE_TAG, 0, 0, "分钟"},
	{41,152, 152, 40, GUIE_TAG, 0, 0, "定 时 关 机"},
	{24,200, 32, 32, GUIE_BUTTON, 0, 0, "减"},
	{112,200, 32, 32, GUIE_BUTTON, 0, 0, "加"},
	{152,200, 64, 32, GUIE_TAG, 0, 0, "分钟"},
	{28,240, 184, 40, GUIE_BUTTON, 0, 0, "返 回"},
	{61,115, 48, 24, GUIE_TAG, 20, 0, NULL},  //10
	{61,203, 48, 24, GUIE_TAG, 30, 0, NULL},   //11
	{61,115, 48, 24, GUIE_TIMES, 200, 0, NULL} //定时器1000MS
};

Window_Type Activity3_window = {
	Activity3_element_num,        //元素数量
	Activity3_element,            //元素列表指针
	Activity3_event               //窗口事件回调函数
};

void Activity3_event(Window_Type *window, signed short element_num)
{

//	printf("Main window event: click %s\r\n", window->element[element_num].text);
	switch(element_num) {
		case 3:
		    TaskMan_State.auto_start+=60;
			if(TaskMan_State.auto_start>1440*60)
				TaskMan_State.auto_start = 1440*60;
			EasyGUI_TAG_SetValue(&window->element[10], TaskMan_State.auto_start/60);
			break;
		case 2:
			TaskMan_State.auto_start-=60;
			if(TaskMan_State.auto_start<0 || TaskMan_State.auto_start/60==0)
				TaskMan_State.auto_start = 0;
			EasyGUI_TAG_SetValue(&window->element[10], TaskMan_State.auto_start/60);
			break;
		case 7:
			TaskMan_State.auto_shutdown+=60;
			if(TaskMan_State.auto_shutdown>1440*60)
				TaskMan_State.auto_shutdown = 1440*60;
			EasyGUI_TAG_SetValue(&window->element[11], TaskMan_State.auto_shutdown/60);
			break;
		case 6:
			TaskMan_State.auto_shutdown-=60;
			if(TaskMan_State.auto_shutdown<0 || TaskMan_State.auto_shutdown/60==0)
				TaskMan_State.auto_shutdown = 0;
			EasyGUI_TAG_SetValue(&window->element[11], TaskMan_State.auto_shutdown/60);
			break;
		case 9:
			EasyGUI_WindowShow(&Activity_main_window);
			break;
		case 12:     //定时器事件
			EasyGUI_TAG_SetValue(&window->element[11], TaskMan_State.auto_shutdown/60);
			EasyGUI_TAG_SetValue(&window->element[10], TaskMan_State.auto_start/60);
			break;
		default:printf("Activity3 error \r\n");
		}
	
}
