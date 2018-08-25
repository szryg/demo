#include "window.h"
#include "include.h"

#define Poweron_element_num 7    //�趨Ԫ����


void Poweron_event(Window_Type *window, signed short element_num);

Window_element_Type Poweron_element[Poweron_element_num] = {
	{8,40, 224, 40, GUIE_TAG, 0, 0, "Ҫ �� ʼ �� ϴ"},
	{8,104, 224, 40, GUIE_TAG, 0, 0, "�� �� ��"},
	{40,184, 160, 48, GUIE_BUTTON, 0, 0, "����"},
	{56,256, 128, 32, GUIE_BUTTON, 0, 0, "ȡ��"}
};

Window_Type Poweron_window = {
	Poweron_element_num,        //Ԫ������
	Poweron_element,            //Ԫ���б�ָ��
	Poweron_event               //�����¼��ص�����
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
