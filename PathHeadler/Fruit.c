#include "include.h"

#define FRUIT_T1 3000   //עˮʱ��
#define FRUIT_T2 3000   //���ʱ��
#define FRUIT_T3 30000   //��ˮ��ʱ
#define FRUIT_T4 3000   //��ˮ�ȴ�

void Fruit(u8 in, u8 in2)    //������̸���������inΪ1������Ϊ0   ���� (key��) gate 
{
	static u8 state = 0;
	static u8 last_in2 = 1;
    static u32 Time_Past1;
	//***********************************//
	if(in == 1)
	{
		last_in2 = 0;
		state=1;
		EasyGUI_WindowShow(&general_window);
		general_window_ShowTitie("������ϴ");
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
    //***********************************//

	if(state == 1)
	{
		//�� ��ˮ 
		general_window_ShowInfo("����עˮ");
		EXOUT_Open(SW_WATER_IN);
		Time_Past1 = time();
		state = 2;
	}
	
	if(state == 2)
	{
		if((time() - Time_Past1) >= FRUIT_T1 || high )  //�ȴ�30min  �͹ر� 
		{
			//�ر� ��ˮ
			EXOUT_Close(SW_WATER_IN);			
	        state = 3;
		} 
		else
		    return;
			
	}
	if(state == 3)
	{
	    //�� ������ 
		general_window_ShowInfo("�������");
		EXOUT_Open(SW_WAVE);
		Time_Past1 = time();
		state = 4;
	}
	if(state == 4)
	{
		if(time()-Time_Past1 >= FRUIT_T2)
		{
			EXOUT_Close(SW_WAVE);
            state = 5;
			
		}
		else
			return;
	}
	
	if(state == 5)
	{
	    //�� ��ˮ��
		general_window_ShowInfo("������ˮ");
		EXOUT_Open(SW_WATER_OUT);
		Time_Past1 = time();
		state = 6;
	}
	if(state == 6)
	{
		if(low == 1 || time() - Time_Past1 >=FRUIT_T3)   //�����޵�   ��Ҫ�ȴ���ʱ30����
		{
			state =7;
		    Time_Past1 = time();
			general_window_ShowInfo("�ȴ���ˮ���");
		}
		else
			return;
	}
	if(state == 7)
	{
		if(time() - Time_Past1 >=FRUIT_T4)
		{
			EXOUT_Close(SW_WATER_OUT);
			
			TaskMan_TaskStop();
			EasyGUI_Message(&Activity1_window, "��ϴ���");   //��ʾ��Ϣ��
		}
		else
			return;
	}
	
}

