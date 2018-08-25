#include "window.h"

#define Activity4_element_num 5    //设定元素数


void Activity4_event(Window_Type *window, signed short element_num);

Window_element_Type Activity4_element[Activity4_element_num] = {
	{28,16, 192, 40, GUIE_TAG, 0, 0, "预  约  模  式"},
	{41,80, 152, 40, GUIE_BUTTON, 0, 0, "WIFI配置"},
	{41,128, 152, 40, GUIE_BUTTON, 0, 0, "WIFI复位"},
	{41,176, 152, 40, GUIE_BUTTON, 0, 0, "屏 幕 校 准"},
	{28,232, 184, 40, GUIE_BUTTON, 0, 0, "返 回"}
};

Window_Type Activity4_window = {
	Activity4_element_num,        //元素数量
	Activity4_element,            //元素列表指针
	Activity4_event               //窗口事件回调函数
};

void Activity4_event(Window_Type *window, signed short element_num)
{
	printf("Main window event: click %s\r\n", window->element[element_num].text);
	switch(element_num) {
		case 1:
			gizwitsSetMode(WIFI_AIRLINK_MODE);
			break;
		case 2:
			gizwitsSetMode(WIFI_RESET_MODE);
			break;
		case 3:
			EasyGUI_Exit();
			TP_Adjust();				
			break;
		case 4:
			EasyGUI_WindowShow(&Activity_main_window);
			break;
		default:printf("Activity4 error \r\n");
		}
		
}
