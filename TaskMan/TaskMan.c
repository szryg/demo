#include "TaskMan.h"

#define get_gate() GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//读取按键 平时 高电平 关闭低电平 打开 高电平
//#define get_high() GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)//读取按键 平时 高电平 关闭低电平 打开 高电平
//#define get_low() GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)//读取按键 平时 高电平 关闭低电平 打开 高电平

#define GATE_OPEN  1
#define GATE_CLOSE 0

unsigned int TaskMan_TIME_MS;   //用于控制器计时
extern u8 TIME_SW;   //计时器开关 0,关闭 1，打开，此定时器用于任务计时用


void (*Task_List[])(u8, u8) = {    //定义任务列表
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

void TaskMan_Handler()   //负责调用对应的处理任务
{
	u8 gate_state = get_gate();
	static u32 continue_cnt = 0;   //当任务暂停之后，再开始之前，这个计数值要达到设定值
	
	if(TaskMan_State.current_task < 0)  //没有任务执行
		return;
	
	if(TaskMan_State.init == 1)   //如果任务刚启动
	{
		Task_List[TaskMan_State.current_task](1, gate_state);
		TaskMan_State.init = 0;
		return;
	}
	
	if(TaskMan_State.pause==0 && gate_state==GATE_OPEN)    //如果当前是运行状态，并且门被打开了，开始执行暂停操作
	{
		TaskMan_State.EXOUT_State = EXOUT_Read_16Bit();   //保存当前输出寄存器数据
		EXOUT_Out_16Bit(0x00);                            //关闭所有输出
		TIME_SW = 0;                                      //暂停计时
		TaskMan_State.pause = 1;                          //标志暂停状态
		continue_cnt = TaskMan_TIME_MS;
	}
	else if(TaskMan_State.pause==1 && gate_state==GATE_OPEN)   //如果还处于暂停状态，舱门又被打开了，重新开始计数
	{
		continue_cnt = TaskMan_TIME_MS;
	}
	else if(TaskMan_State.pause==1 && gate_state==GATE_CLOSE)   //当前状态暂停， 门被关上了，继续任务
	{
		if(TaskMan_TIME_MS-continue_cnt >= 500)
		{
			EXOUT_Out_16Bit(TaskMan_State.EXOUT_State);   //恢复输出继电器状态
			TIME_SW = 1;
			TaskMan_State.pause = 0;                     //复位暂停标志
			printf("继续执行,dat: %04x\r\n", TaskMan_State.EXOUT_State);
		}
	}
	Task_List[TaskMan_State.current_task](0, gate_state|TaskMan_State.pause);
}

void TaskMan_TaskStart(u16 task_num)     //启动一个任务
{
	if(TaskMan_State.power_sw == 0)
	{
		EasyGUI_WindowShow(&Poweron_window);
		return;
	}
	
	if(TaskMan_State.current_task != -1)
		TaskMan_TaskStop();
	general_window_CloseTimeInfo();
	Temp_Set(0);  //默认关闭温度控制
	time_init();
	TaskMan_State.init = 1;
	TaskMan_State.pause = 0;
	TaskMan_State.current_task = task_num;
}

void TaskMan_TaskStop(void)    //停止当前任务
{
	TaskMan_State.current_task = -1;
	EXOUT_Out_16Bit(0x00);
	TaskMan_State.mode1 = 0;
	TaskMan_State.mode2 = 0;
}
