#ifndef __NTC_Temp_H
#define __NTC_Temp_H
#include "adc.h"
#include "stdio.h"
////////////////////////////////////////////////////////////////////////////////// 
 
#define R 40      //cd4051��ͨ���� 40
#define Rd 10000  //�ӵص��� 10K

int GetTemp(u8 CD4051_ch, u8 order);  // CD4051_ch ����ѡ��ͨ��  order ƽ������
                                      // ע�� ADC ��ʼ��
									  
u32 Get_zhuodu(void);

#endif 
