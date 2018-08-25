#include "window.h"
#include "include.h"

#define message_element_num 6    //设定元素数


void message_event(Window_Type *window, signed short element_num);

Window_element_Type message_element[message_element_num] = {
	{20,24, 192, 40, GUIE_TAG, 0, 0, "提 示 信 息"},
	{16,88, 208, 40, GUIE_TAG, 0, 0, ""},             //1
	{16,168, 136, 40, GUIE_TAG, 0, 0, "返回倒计时:"}, //2
	{144,168, 48, 40, GUIE_TAG, 0, 0, ""},        //3
	{40,224, 152, 48, GUIE_BUTTON, 0, 0, "返 回"},    //4
	{0, 0, 0, 0, GUIE_TIMES, 1000, 0, NULL}           //5
};

Window_Type message_window = {
	message_element_num,        //元素数量
	message_element,            //元素列表指针
	message_event               //窗口事件回调函数
};

void goto_last()
{
	if(message_element[0].value !=0 )
		EasyGUI_WindowShow((Window_Type *)message_element[0].value);
	else
		EasyGUI_WindowShow(&Activity_main_window);
}

void message_event(Window_Type *window, signed short element_num)
{
	static signed char autoreturn;
	printf("message window event: click %d\r\n", element_num);
	switch(element_num) {
		case -1:
			autoreturn = 10;
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:		
			break;
		case 4:
			goto_last();
			break;
		case 5:
			autoreturn--;
			EasyGUI_TAG_SetValue(&window->element[3], autoreturn);
			if(autoreturn <= 0)
				goto_last();
			break;
		default:printf("message error \r\n");
	}
}

