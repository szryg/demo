#include "include.h"
#include "EXOUT.h"

#define CAVITY_T1 3000     //�������Һʱ��
#define CAVITY_T2 3000     //������ϴʱ��
#define CAVITY_T3 30000    //��ˮ��ʱ
#define CAVITY_T4 3000     //��ˮ�ȴ�

void Cavity(u8 in, u8 in2)    //������̸���������inΪ1������Ϊ0   ���� (key��) gate 
{
	static u8 state = 0;
	static u8 last_in2 = 1;
    static u32 Time_Past1;
	
	
	if(in == 1)
	{
		last_in2 = 0;
		state=1;
		EasyGUI_WindowShow(&general_window);
		general_window_ShowTitie("ǻ�����");
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
		//��ˮ��
		//�� ��ˮ��
		//�� ���ֱ�
		general_window_ShowInfo("��ʼ��ϴ");
		EXOUT_Open(SW_WATER_IN | SW_WATER_OUT | SW_MOTOR);
		Time_Past1 = time();
		state = 2;
	}
	
	if(state == 2)
	{
		if((time() - Time_Past1) >= CAVITY_T1 )
		{
			//�س��ֱ�
			general_window_ShowInfo("��ϴ������");
			EXOUT_Close(SW_MOTOR);
			if((time() - Time_Past1) >= CAVITY_T2)
			{
				Time_Past1 = time();
				state = 3;
				general_window_ShowInfo("������ˮ");
			}
		}
	}
	
	if(state == 3)
	{
		if(low == 1 || time() - Time_Past1 >=CAVITY_T3)   //�����޵�   ��Ҫ�ȴ���ʱ30����
		{
			state =4;
		    Time_Past1 = time();
			general_window_ShowInfo("�ȴ���ˮ���");
		}
		else
			return;
	}
	
	if(state == 4)
	{
		if(time() - Time_Past1 >=CAVITY_T4)
		{
			EXOUT_Close(SW_WATER_IN | SW_WATER_OUT);
			
			TaskMan_TaskStop();
			EasyGUI_Message(&Activity1_window, "�������");   //��ʾ��Ϣ��
		}
		else
			return;
	}
	
}






