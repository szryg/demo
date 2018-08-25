#include "include.h"

#define WIND_T1 30000   //���ʱ��



void Wind(u8 in, u8 in2)    //������̸���������inΪ1������Ϊ0   ���� (key��) gate 
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
		general_window_ShowTitie("�ȷ���");
	}
	
	if(in2!=last_in2 && in2 == 1)    //���Ŵ��¼�
	{
		EasyGUI_TAG_ShowText(&general_window.element[1], "��رո����Լ���");
	}
	else if(in2!=last_in2 && in2 == 0)  //���Źر��¼�
	{
		EasyGUI_TAG_ShowText(&general_window.element[1], "���ڽ�����...");
	}
	last_in2 = in2;
	if(in2 == 1)   //������Ŵ򿪣�ʲô������
		return;
    //***********************************//

	if(state == 1)
	{
		//�� ����	
		general_window_ShowInfo("��������");
		EXOUT_Open(SW_FAN2 | SW_FAN3);		
		state = 2;
	}
	
	if(state == 2)
	{
		//�� �¶ȿ��Ƴ���
		Temp_Set(48);
		Time_Past1 = time();
		state = 3;
		general_window_ShowInfo("���ڹ���");
		general_window.element[2].text = "�¶�:";
		general_window.element[2].reflash = 1;
	}
	
	if(state == 3)
	{

			
		general_window_ShowNumber((GetTemp(0, 5)+GetTemp(1, 5))/20);

		if((time() - Time_Past1) >= WIND_T1 )  //�ȴ�30min  �͹ر� 
		{
			//�� ����
			//���¶ȿ��Ƴ���
			EXOUT_Close(SW_FAN2 | SW_FAN3);		
			Temp_Set(0);
	
			TaskMan_TaskStop();
			EasyGUI_Message(&Activity2_window, "��ϴ���");   //��ʾ��Ϣ��
		} 
		else
		    return;
			
	}
	
}






