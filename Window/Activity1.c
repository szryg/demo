#include "window.h"
#include "include.h"

#define Activity1_element_num 7    //�趨Ԫ����


void Activity1_event(Window_Type *window, signed short element_num);

Window_element_Type Activity1_element[Activity1_element_num] = {
	{28,16, 192, 40, GUIE_TAG, 0, 0, "��  ϴ  ��  ��"},
	{28,72, 87, 40, GUIE_BUTTON, 0, 0, "�� ��"},
	{124,72, 87, 40, GUIE_BUTTON, 0, 0, "�� ׼"},
	{28,120, 87, 40, GUIE_BUTTON, 0, 0, "�� ��"},
	{124,120, 87, 40, GUIE_BUTTON, 0, 0, "�� ��"},
	{28,168, 184, 40, GUIE_BUTTON, 0, 0, "ǻ �� �� ��"},
	{28,232, 184, 40, GUIE_BUTTON, 0, 0, "�� ��"}
};

Window_Type Activity1_window = {
	Activity1_element_num,        //Ԫ������
	Activity1_element,            //Ԫ���б�ָ��
	Activity1_event               //�����¼��ص�����
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
