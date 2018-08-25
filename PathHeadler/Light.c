#include "include.h"
#include "EXOUT.h"

#define LIGHT_T1 3000   //����ʱ��

void Light(u8 in, u8 in2)    //������̸���������inΪ1������Ϊ0   ���� (key��) gate 
{
	static u8 state = 0;
	static u8 last_in2 = 1;
    static u32 Time_Past1;
	
	if(in == 1)
	{
		last_in2 = 0;
		state=1;
		EasyGUI_WindowShow(&general_window);
		general_window_ShowTitie("����ɱ��");
	}
	
	if(in2!=last_in2 && in2 == 1)    //���Ŵ��¼�
	{
		EasyGUI_TAG_ShowText(&general_window.element[1], "��رո����Լ�����ϴ");
	}
	else if(in2!=last_in2 && in2 == 0)  //���Źر��¼�
	{
		EasyGUI_TAG_ShowText(&general_window.element[1], "������ϴ��...");
	}
	last_in2 = in2;
	if(in2 == 1)   //������Ŵ򿪣�ʲô������
		return;
	
	if(state == 1)
	{
		//�� ������
		general_window_ShowInfo("���ڹ���");
		EXOUT_Open(SW_LIGHT);
		Time_Past1 = time();
		state = 2;
	}
	
	if(state == 2)
	{
		if((time() - Time_Past1) >= LIGHT_T1 )  //�ȴ�30min �͹ر�
		{
			//�� ��
			EXOUT_Close(SW_LIGHT);
			
			TaskMan_TaskStop();
			EasyGUI_Message(&Activity2_window, "�������");   //��ʾ��Ϣ��
		} else
		    {
				return;
			}
	}
	
}






