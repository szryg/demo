#include "window.h"

#define Activity_main_element_num 5    //�趨Ԫ����


void Activity_main_event(Window_Type *window, signed short element_num);

Window_element_Type Activity_main_element[Activity_main_element_num] = {
	{24,16, 192, 40, GUIE_TAG, 0, 0, "����������ϴ���"},
	{41,80, 152, 40, GUIE_BUTTON, 0, 0, "�� ϴ �� ��"},
	{41,128, 152, 40, GUIE_BUTTON, 0, 0, "�� �� ģ ʽ"},
	{41,176, 152, 40, GUIE_BUTTON, 0, 0, "Ԥ Լ ģ ʽ"},
	{41,240, 152, 40, GUIE_BUTTON, 0, 0, "�� ��"}
};

Window_Type Activity_main_window = {
	Activity_main_element_num,        //Ԫ������
	Activity_main_element,            //Ԫ���б�ָ��
	Activity_main_event               //�����¼��ص�����
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
