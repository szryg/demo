#ifndef __TASKMAN_H
#define __TASKMAN_H	 
#include "include.h"

//#define gate GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//读取按键 平时 高电平 关闭低电平 打开 高电平
#define high GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)//读取按键 平时 高电平 关闭低电平 打开 高电平
#define low GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)//读取按键 平时 高电平 关闭低电平 打开 高电平

//#define get_high() GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)//读取按键 平时 高电平 关闭低电平 打开 高电平
//#define get_low() GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)//读取按键 平时 高电平 关闭低电平 打开 高电平


typedef struct{
	signed int current_task;         //当前任务号 -1为无任务
	signed int init;
	signed int pause;
	unsigned int EXOUT_State;
	signed int power_sw;            //电源开关，1为开
	unsigned char mode1;
	unsigned char mode2;
	signed int auto_start;
	signed int auto_shutdown;
}TaskMan_Type;


void TaskMan_Handler(void);    //执行函数

void TaskMan_TaskStart(u16 task_num);   //接口函数
void TaskMan_TaskStop(void);


void Norm(u8, u8);
void Cavity(u8, u8);
void Wind(u8, u8);
void Light(u8, u8);
void Wind_Light(u8, u8);
void NormX2(u8, u8);
void Fruit(u8, u8);
void NormX3(u8 in, u8 in2);
void Auto(u8 in, u8 in2);

extern void (*Task_List[])(u8, u8);
extern TaskMan_Type TaskMan_State;

//添加任务 还有在c里的定义任务列表
#define Task_Norm       0
#define Task_Cavity     1
#define Task_Wind       2
#define Task_Light      3
#define Task_Wind_Light 4
#define Task_NormX2     5
#define Task_Fruit      6
#define Task_NormX3     7
#define Task_Auto       8


#endif

