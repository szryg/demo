#include "stm32f10x.h"
#include "sys.h"
#include "stdio.h"
#include "EXOUT.h"

unsigned int EXOUT_DATBUFF = 0x00;
#define HC595_Delay_Time 10

#define HC595_OUT_CLK(x) GPIO_WriteBit(GPIOA, GPIO_Pin_1, x?Bit_SET:Bit_RESET)
#define HC595_OUT_DAT(x) GPIO_WriteBit(GPIOA, GPIO_Pin_4, x?Bit_SET:Bit_RESET)
#define HC595_OUT_L(x)   GPIO_WriteBit(GPIOC, GPIO_Pin_4, x?Bit_SET:Bit_RESET)


void GPIO_Auto_Init(GPIO_TypeDef * GPIOx,uint32_t PINx, GPIOMode_TypeDef GPIOMode);

void HC595_Delay()
{
	unsigned int t = HC595_Delay_Time;
	while(t--);
}

void EXOUT_PutDat()
{
	unsigned char bit_num = 16;
	unsigned int buf = EXOUT_DATBUFF;
	HC595_OUT_L(1);
	HC595_OUT_CLK(1);
	while(bit_num--)
	{
		HC595_OUT_DAT(buf&0x8000);
		HC595_Delay();
		HC595_OUT_CLK(0);
		HC595_Delay();
		HC595_OUT_CLK(1);
		HC595_Delay();
		buf<<=1;
	}
	HC595_OUT_L(0);
	HC595_Delay();
	HC595_OUT_L(1);
	HC595_Delay();
}

void EXOUT_Init(void)
{
	GPIO_Auto_Init(GPIOA, 1,GPIO_Mode_Out_PP);
	GPIO_Auto_Init(GPIOA, 4,GPIO_Mode_Out_PP);
	GPIO_Auto_Init(GPIOC, 4,GPIO_Mode_Out_PP);
	
	HC595_OUT_CLK(1);
	HC595_OUT_DAT(1);
	HC595_OUT_L(1);
	EXOUT_DATBUFF = 0x00;
	EXOUT_PutDat();
}

void EXOUT_Out(unsigned char com, unsigned char value) //com是指定0-15哪个端口，value是开关那个端口
{
	EXOUT_DATBUFF &= ~(0x01<<com);
	EXOUT_DATBUFF |= value?0x01<<com:0;
	EXOUT_PutDat();
}

void EXOUT_Open(unsigned int v)	
{
	u32 buf = EXOUT_DATBUFF;
	buf |= v;
	if(buf != EXOUT_DATBUFF)
	{
		EXOUT_DATBUFF = buf;
		EXOUT_PutDat();
	}

}

void EXOUT_Close(unsigned int v)
{
	u32 buf = EXOUT_DATBUFF;
	buf &= ~v;
	if(buf != EXOUT_DATBUFF)
	{
		EXOUT_DATBUFF = buf;
		EXOUT_PutDat();
	}
}

unsigned int EXOUT_Read_16Bit()
{
	return EXOUT_DATBUFF;
}

void EXOUT_Out_16Bit(unsigned int dat)
{
	EXOUT_DATBUFF = dat;
	EXOUT_PutDat();
}
