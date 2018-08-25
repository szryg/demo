#include "TaskMan.h"

#define get_gate() GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//��ȡ���� ƽʱ �ߵ�ƽ �رյ͵�ƽ �� �ߵ�ƽ
//#define get_high() GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)//��ȡ���� ƽʱ �ߵ�ƽ �رյ͵�ƽ �� �ߵ�ƽ
//#define get_low() GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)//��ȡ���� ƽʱ �ߵ�ƽ �رյ͵�ƽ �� �ߵ�ƽ

#define GATE_OPEN  1
#define GATE_CLOSE 0

unsigned int TaskMan_TIME_MS;   //���ڿ�������ʱ
extern u8 TIME_SW;   //��ʱ������ 0,�ر� 1���򿪣��˶�ʱ�����������ʱ��


void (*Task_List[])(u8, u8) = {    //���������б�
	&Norm,
	&Cavity,
	&Wind,
	&Light,
	&Wind_Light,
	&NormX2,
	&Fruit,
	&NormX3,
	&Auto
};

TaskMan_Type TaskMan_State = {-1, 0, 0, 0, 1, 0, 0, 0, 0};

void TaskMan_Handler()   //������ö�Ӧ�Ĵ�������
{
	u8 gate_state = get_gate();
	static u32 continue_cnt = 0;   //��������֮ͣ���ٿ�ʼ֮ǰ���������ֵҪ�ﵽ�趨ֵ
	
	if(TaskMan_State.current_task < 0)  //û������ִ��
		return;
	
	if(TaskMan_State.init == 1)   //������������
	{
		Task_List[TaskMan_State.current_task](1, gate_state);
		TaskMan_State.init = 0;
		return;
	}
	
	if(TaskMan_State.pause==0 && gate_state==GATE_OPEN)    //�����ǰ������״̬�������ű����ˣ���ʼִ����ͣ����
	{
		TaskMan_State.EXOUT_State = EXOUT_Read_16Bit();   //���浱ǰ����Ĵ�������
		EXOUT_Out_16Bit(0x00);                            //�ر��������
		TIME_SW = 0;                                      //��ͣ��ʱ
		TaskMan_State.pause = 1;                          //��־��ͣ״̬
		continue_cnt = TaskMan_TIME_MS;
	}
	else if(TaskMan_State.pause==1 && gate_state==GATE_OPEN)   //�����������ͣ״̬�������ֱ����ˣ����¿�ʼ����
	{
		continue_cnt = TaskMan_TIME_MS;
	}
	else if(TaskMan_State.pause==1 && gate_state==GATE_CLOSE)   //��ǰ״̬��ͣ�� �ű������ˣ���������
	{
		if(TaskMan_TIME_MS-continue_cnt >= 500)
		{
			EXOUT_Out_16Bit(TaskMan_State.EXOUT_State);   //�ָ�����̵���״̬
			TIME_SW = 1;
			TaskMan_State.pause = 0;                     //��λ��ͣ��־
			printf("����ִ��,dat: %04x\r\n", TaskMan_State.EXOUT_State);
		}
	}
	Task_List[TaskMan_State.current_task](0, gate_state|TaskMan_State.pause);
}

void TaskMan_TaskStart(u16 task_num)     //����һ������
{
	if(TaskMan_State.power_sw == 0)
	{
		EasyGUI_WindowShow(&Poweron_window);
		return;
	}
	
	if(TaskMan_State.current_task != -1)
		TaskMan_TaskStop();
	general_window_CloseTimeInfo();
	Temp_Set(0);  //Ĭ�Ϲر��¶ȿ���
	time_init();
	TaskMan_State.init = 1;
	TaskMan_State.pause = 0;
	TaskMan_State.current_task = task_num;
}

void TaskMan_TaskStop(void)    //ֹͣ��ǰ����
{
	TaskMan_State.current_task = -1;
	EXOUT_Out_16Bit(0x00);
	TaskMan_State.mode1 = 0;
	TaskMan_State.mode2 = 0;
}
