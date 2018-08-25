#ifndef __Process_Administrator_H
#define __Process_Administrator_H	 
#include "include.h"

#define gate GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5)//读取按键 平时 高电平 关闭低电平 打开 高电平

typedef struct{
	u8 Admin_value;         //
	signed short Admin_go;  //记录当前
}Admin_State_Type;


void Pro_Admin(void);
void Exit_Admin(void);
void Admin_Begin(void);
extern void Norm(u8 in, u8 in2);
extern void Cavity(u8 in);
extern void Wind(u8 in);
extern void Light(u8 in);

#endif





