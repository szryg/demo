#include "window.h"

#define Activity_main_element_num 5    //设定元素数


void Activity_main_event(Window_Type *window, signed short element_num);

Window_element_Type Activity_main_element[Activity_main_element_num] = {
	{24,16, 192, 40, GUIE_TAG, 0, 0, "超声波智能洗碗机"},
	{41,80, 152, 40, GUIE_BUTTON, 0, 0, "清 洗 程 序"},
	{41,128, 152, 40, GUIE_BUTTON, 0, 0, "保 管 模 式"},
	{41,176, 152, 40, GUIE_BUTTON, 0, 0, "预 约 模 式"},
	{41,240, 152, 40, GUIE_BUTTON, 0, 0, "设 置"}
};

Window_Type Activity_main_window = {
	Activity_main_element_num,        //元素数量
	Activity_main_element,            //元素列表指针
	Activity_main_event               //窗口事件回调函数
};

void Activity_main_event(Window_Type *window, signed short element_num)
{
	printf("%d\r\n", element_num);
	if(element_num == 1)
	{
		EasyGUI_WindowShow(&Activity1_window);
		printf("Main window event: click %s\r\n", window->element[element_num].text);
	}
	if(element_num == 2)
	{
		EasyGUI_WindowShow(&Activity2_window);
		printf("Main window event: click %s\r\n", window->element[element_num].text);
	}
	if(element_num == 3)
	{
		EasyGUI_WindowShow(&Activity3_window);
		printf("Main window event: click %s\r\n", window->element[element_num].text);
	}
	if(element_num == 4)
	{
		EasyGUI_WindowShow(&Activity4_window);
		printf("Main window event: click %s\r\n", window->element[element_num].text);
	}
}
