#ifndef __NTC_Temp_H
#define __NTC_Temp_H
#include "adc.h"
#include "stdio.h"
////////////////////////////////////////////////////////////////////////////////// 
 
#define R 40      //cd4051导通电阻 40
#define Rd 10000  //接地电阻 10K

int GetTemp(u8 CD4051_ch, u8 order);  // CD4051_ch 输入选择通道  order 平均次数
                                      // 注意 ADC 初始化
									  
u32 Get_zhuodu(void);

#endif 
