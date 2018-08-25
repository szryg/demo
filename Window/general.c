#include "window.h"
#include "EXOUT.h"
#include "include.h"

#define general_element_num 6    //�趨Ԫ����


void general_event(Window_Type *window, signed short element_num);

Window_element_Type general_element[general_element_num] = {
	{28,16, 192, 40, GUIE_TAG, 0, 0, "��ϴ����"},     //0
	{0,60, 240, 40, GUIE_TAG, 0, 0, "�� �� ��...."},       //1
	{28,120, 60, 40, GUIE_TAG, 0, 0, ""},              //2ʣ��ʱ��
	{100,130, 48, 24, GUIE_TAG, 00, 0, ""},  //3  ��ʾ��ʱ��
	{0,170, 240, 40, GUIE_TAG, 0, 0, "��ʾ��Ϣ"},
	{28,232, 184, 40, GUIE_BUTTON, 0, 0, "ȡ ��"}
};

Window_Type general_window = {
	general_element_num,        //Ԫ������
	general_element,            //Ԫ���б�ָ��
	general_event               //�����¼��ص�����
};

void general_event(Window_Type *window, signed short element_num)
{
	u32 *remain_time = &window->element[3].value;        //��ǩ�п���ʱ���ֵ  
	
	
	
	EasyGUI_TAG_SetValue(&window->element[3], *remain_time);
	
	switch(element_num) {
		case 1:
			
			break;
		case 2:
			
			break;
		case 3:
							
			break;
		case 5:
			TaskMan_TaskStop();
			EasyGUI_WindowShow(&Activity_main_window);
			break;
		default:printf("Activity2 error \r\n");
		}
}

void general_window_ShowInfo(char *text)    //ͨ�ô�����ʾ��ʾ��Ϣ
{
	EasyGUI_TAG_ShowText(&general_window.element[4], text);
}

void general_window_ShowNumber(u32 num)    //��ͨ�ô���ʣ��ʱ���ǩ����ʾ����
{
	EasyGUI_TAG_SetValue(&general_window.element[3], num);
}

void general_window_ShowTitie(char *text)
{
	EasyGUI_TAG_ShowText(&general_window.element[0], text);
}

void general_window_CloseTimeInfo()
{
	general_window.element[2].text = "";
	general_window.element[3].text = "";
}
