#ifndef __TASKMAN_H
#define __TASKMAN_H	 
#include "include.h"

//#define gate GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//��ȡ���� ƽʱ �ߵ�ƽ �رյ͵�ƽ �� �ߵ�ƽ
#define high GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)//��ȡ���� ƽʱ �ߵ�ƽ �رյ͵�ƽ �� �ߵ�ƽ
#define low GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)//��ȡ���� ƽʱ �ߵ�ƽ �رյ͵�ƽ �� �ߵ�ƽ

//#define get_high() GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)//��ȡ���� ƽʱ �ߵ�ƽ �رյ͵�ƽ �� �ߵ�ƽ
//#define get_low() GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_3)//��ȡ���� ƽʱ �ߵ�ƽ �رյ͵�ƽ �� �ߵ�ƽ


typedef struct{
	signed int current_task;         //��ǰ����� -1Ϊ������
	signed int init;
	signed int pause;
	unsigned int EXOUT_State;
	signed int power_sw;            //��Դ���أ�1Ϊ��
	unsigned char mode1;
	unsigned char mode2;
	signed int auto_start;
	signed int auto_shutdown;
}TaskMan_Type;


void TaskMan_Handler(void);    //ִ�к���

void TaskMan_TaskStart(u16 task_num);   //�ӿں���
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

//������� ������c��Ķ��������б�
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

