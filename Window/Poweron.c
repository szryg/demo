#include "window.h"
#include "include.h"

#define Poweron_element_num 7    //设定元素数


void Poweron_event(Window_Type *window, signed short element_num);

Window_element_Type Poweron_element[Poweron_element_num] = {
	{8,40, 224, 40, GUIE_TAG, 0, 0, "要 开 始 清 洗"},
	{8,104, 224, 40, GUIE_TAG, 0, 0, "请 开 机"},
	{40,184, 160, 48, GUIE_BUTTON, 0, 0, "开机"},
	{56,256, 128, 32, GUIE_BUTTON, 0, 0, "取消"}
};

Window_Type Poweron_window = {
	Poweron_element_num,        //元素数量
	Poweron_element,            //元素列表指针
	Poweron_event               //窗口事件回调函数
};

void Poweron_event(Window_Type *window, signed short element_num)
{
	static u8 a = 0;
	switch(element_num) {
		case 1:
			
			EXOUT_Out_16Bit(a);
			a <<= 1;
			if (a == 0)
				a = 0x01;
			break;
		case 2:
			TaskMan_State.power_sw = 1;
			EasyGUI_WindowShow(&Activity_main_window);
			break;
		case 3:
			EasyGUI_WindowShow(&Activity_main_window);				
			break;
		default:printf("Poweron error \r\n");
		}
}
