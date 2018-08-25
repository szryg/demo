#include "window.h"
#include "include.h"

#define Activity1_element_num 7    //设定元素数


void Activity1_event(Window_Type *window, signed short element_num);

Window_element_Type Activity1_element[Activity1_element_num] = {
	{28,16, 192, 40, GUIE_TAG, 0, 0, "清  洗  程  序"},
	{28,72, 87, 40, GUIE_BUTTON, 0, 0, "智 能"},
	{124,72, 87, 40, GUIE_BUTTON, 0, 0, "标 准"},
	{28,120, 87, 40, GUIE_BUTTON, 0, 0, "节 能"},
	{124,120, 87, 40, GUIE_BUTTON, 0, 0, "果 蔬"},
	{28,168, 184, 40, GUIE_BUTTON, 0, 0, "腔 体 清 洁"},
	{28,232, 184, 40, GUIE_BUTTON, 0, 0, "返 回"}
};

Window_Type Activity1_window = {
	Activity1_element_num,        //元素数量
	Activity1_element,            //元素列表指针
	Activity1_event               //窗口事件回调函数
};

void Activity1_event(Window_Type *window, signed short element_num)
{
	printf("Main window event: click %s\r\n", window->element[element_num].text);
	switch(element_num) {
		case 1:
			TaskMan_State.mode1 = 1;
			TaskMan_TaskStart(Task_Auto);
			break;
		case 2:
			TaskMan_State.mode1 = 1;
			TaskMan_TaskStart(Task_NormX2);
			break;
		case 3:
			TaskMan_State.mode1 = 1;
			TaskMan_TaskStart(Task_Norm);				
			break;
		case 4:
			TaskMan_State.mode1 = 1;
			TaskMan_TaskStart(Task_Fruit);
			break;
		case 5:
			TaskMan_State.mode1 = 1;
			TaskMan_TaskStart(Task_Cavity);	
			break;
		case 6:
			EasyGUI_WindowShow(&Activity_main_window);
			break;
		default:printf("Activity1 error \r\n");
		}
}
