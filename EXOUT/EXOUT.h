#ifndef __EXOUT_H__
#define __EXOUT_H__
#include "stm32f10x.h"

void EXOUT_Init(void);
//com��ָ��0-15�ĸ��˿ڣ�value�ǿ����Ǹ��˿�
void EXOUT_Out(unsigned char com, unsigned char value); 
//��ĳЩ�˿�
void EXOUT_Open(unsigned int v);
//�ر�ĳЩ�˿ڣ����������ֵ����һλΪ1�������ĸ�����
void EXOUT_Close(unsigned int v);
//һ���Զ������п���״̬
unsigned int EXOUT_Read_16Bit(void);
//
void EXOUT_Out_16Bit(unsigned int dat);

#define SW_FAN1 (1<<0)
#define SW_FAN2 (1<<1)
#define SW_FAN3 (1<<2)
#define SW_PTC1 (1<<3)
#define SW_PTC2 (1<<4)
#define SW_LIGHT (1<<5)
#define SW_WATER_IN (1<<6)
#define SW_WATER_OUT (1<<7)
#define SW_MOTOR (1<<8)
#define SW_WAVE (1<<9)


#endif

