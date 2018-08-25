#include "window.h"
#include "include.h"

#define Activity2_element_num 5    //设定元素数


void Activity2_event(Window_Type *window, signed short element_num);

Window_element_Type Activity2_element[Activity2_element_num] = {
	{28,16, 192, 40, GUIE_TAG, 0, 0, "保  管  模  式"},
	{41,80, 152, 40, GUIE_BUTTON, 0, 0, "热 风 烘 干"},
	{41,128, 152, 40, GUIE_BUTTON, 0, 0, "紫 外 杀 菌"},
	{41,176, 152, 40, GUIE_BUTTON, 0, 0, "混 合 模 式"},
	{28,232, 184, 40, GUIE_BUTTON, 0, 0, "返 回"}
};

Window_Type Activity2_window = {
	Activity2_element_num,        //元素数量
	Activity2_element,            //元素列表指针
	Activity2_event               //窗口事件回调函数
};

void Activity2_event(Window_Type *window, signed short element_num)
{
	printf("Main window event: click %s\r\n", window->element[element_num].text);
	switch(element_num) {
		case 1:
			TaskMan_State.mode2 = 1;
			TaskMan_TaskStart(Task_Wind);
			break;
		case 2:
			TaskMan_State.mode2 = 1;
			TaskMan_TaskStart(Task_Light);
			break;
		case 3:
			TaskMan_State.mode2 = 1;
			TaskMan_TaskStart(Task_Wind_Light);				
			break;
		case 4:
			EasyGUI_WindowShow(&Activity_main_window);
			break;
		default:printf("Activity2 error \r\n");
		}
}
