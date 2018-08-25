#include "window.h"
#include "include.h"

#define Activity2_element_num 5    //�趨Ԫ����


void Activity2_event(Window_Type *window, signed short element_num);

Window_element_Type Activity2_element[Activity2_element_num] = {
	{28,16, 192, 40, GUIE_TAG, 0, 0, "��  ��  ģ  ʽ"},
	{41,80, 152, 40, GUIE_BUTTON, 0, 0, "�� �� �� ��"},
	{41,128, 152, 40, GUIE_BUTTON, 0, 0, "�� �� ɱ ��"},
	{41,176, 152, 40, GUIE_BUTTON, 0, 0, "�� �� ģ ʽ"},
	{28,232, 184, 40, GUIE_BUTTON, 0, 0, "�� ��"}
};

Window_Type Activity2_window = {
	Activity2_element_num,        //Ԫ������
	Activity2_element,            //Ԫ���б�ָ��
	Activity2_event               //�����¼��ص�����
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
