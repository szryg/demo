#include "include.h"
#include "EXOUT.h"

#define AUTO_T1 3000  //���ֱ�����ʱ��
#define AUTO_T2 6000  //��ˮ������ʱ��
#define AUTO_T3 6000  //������
#define AUTO_T4 30000  //��ˮ��ʱ
#define AUTO_T5 10000  //�ﵽ�޵ͺ��ӳٹط�ʱ��

#define AUTO_T6 3000   //����Ƕ�ʱ�ķ�ˮʱ��

u8 AUTOX1_REPEAT_TIMES;    //�ظ�����

u8 Auto_Get_RepeatTimes()
{
	u8 i = 20;
	u32 a = 0;
	while(i--)
		a += Get_zhuodu();
	a = a/20;
	printf("�Ƕȼ������%u\r\n", a);
	if(a>3753)
		return 1;
	else if(a < 2906)
		return 3;
	else
		return 2;
}

void Auto(u8 in, u8 in2)    //������̸���������inΪ1������Ϊ0   ���� (key��) gate 
{
    static u8 state = 0, repeat;
	static u8 last_in2 = 1;
    static u32 Time_Past1, Time_Past2;	
	
	
	
	if(in == 1)
	{
		last_in2 = 0;
		state=1;
		repeat = 1;
		AUTOX1_REPEAT_TIMES = 0;
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
	
	if(state == 1)
	{
		//��ˮ��//�����ֱ�
		general_window_ShowInfo("����ע��ˮ����ϴ��");
		EXOUT_Open(SW_WATER_IN|SW_MOTOR);
		Time_Past1 = time();
		state = 2;
	}
	
	
	if(state == 2)
	{
		if((time() - Time_Past1) >= AUTO_T1)
		{
			EXOUT_Close(SW_MOTOR);
			general_window_ShowInfo("�ȴ�עˮ���");
			if(AUTOX1_REPEAT_TIMES == 0)
			{
				AUTOX1_REPEAT_TIMES = Auto_Get_RepeatTimes();
			}
			if(((time() - Time_Past1) >= AUTO_T2) || high)  //�ȴ�60s ���� �����޸� �͹ر�ˮ�� 
			{
				EXOUT_Close(SW_WATER_IN);
				EXOUT_Close(SW_MOTOR);
				printf("�ص�ˮ��---------------------%u\r\n", time() - Time_Past1);
				//��ˮ��
				state = 3;
			}
			else
				return;
		}
		else
			return;
		
	}
	
	if(state == 3)
	{
		// ������ ���� 
		general_window_ShowInfo("����ʹ�ó��������");
		EXOUT_Open(SW_WAVE);
		Time_Past2 = time();
		state = 4;
	}
	
	if(state == 4)
	{
	    if((time() - Time_Past2) >= AUTO_T3)        // 20min
		{
			//�س�����
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
		Time_Past2 = time();
		state = 6;
	}
	if(state == 6)
	{
		if(low == 1 || time() - Time_Past2 >=AUTO_T4)   //�����޵�   ��Ҫ�ȴ���ʱ30����
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
		if(time() - Time_Past1 >=AUTO_T5)
		{
			EXOUT_Close(SW_WATER_OUT);
			state = 8;
		}
		else
			return;
	}
	
	if(state == 8)
	{
		if(repeat++ < AUTOX1_REPEAT_TIMES)      //�ظ�ִ��
		{
			state = 1;
			return;
		}
		
		TaskMan_TaskStop();
		EasyGUI_Message(&Activity1_window, "��ϴ���");   //��ʾ��Ϣ��
	}
	
	
}   //���һ�� ���� ��

