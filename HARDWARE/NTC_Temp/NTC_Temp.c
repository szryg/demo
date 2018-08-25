#include "NTC_Temp.h"

const u16 NTC_Table[100]={
	28017, 26826, 25697, 24629, 23618, 22660, 21752, 20892, 20075, 19299, 18560, 18482, 18149, 17632, 	16992, 16280, 15535, 14787, 14055, 13354, 12690, 12068, 11490, 10954, 10458, 10000, 9576, 9184, 8819, 8478, 8160, 7861, 7579, 7311, 7056, 6813, 6581, 6357, 6142, 5934, 5734, 5541, 5353, 5173, 4998, 4829, 4665, 4507, 4355, 4208, 4065, 3927, 3794, 3664, 3538, 3415, 3294, 3175, 3058, 2941, 2825, 2776, 2718, 2652, 2582, 2508, 2432, 2356, 2280, 2207, 2135, 2066, 2000, 1938, 1879, 1823, 1770, 1720, 1673, 1628, 1586, 1546, 1508, 1471, 1435, 1401, 1367, 1334, 1301, 1268, 1236, 1204, 1171, 1139, 1107, 1074, 1042, 1010, 979, 948
};    // NTC �������� 1% 10K 
u16 *pTmp = (u16*)NTC_Table; //ָ��Ҫ�¶ȱ�ĵ�ַ

//*************************************  
// �������ƣ�FineTab  ���ֲ����㷨 ->���¶ȱ�  
// �������ܣ����������ڱ��ж�Ӧ��λ�� �������ݴӴ�С  
// ��ڲ��������ַ�����ȡ�Ҫ���ҵ�����  
// ���ڲ�������  
// �� �� ֵ�������ڱ��е�λ��  
//*************************************  
u8 FineTab(u16 *a,u8 TabLong,u16 data)//�������ݴӴ�С  
{  
    u8 st,ed,m ;  
    u8 i ;  
  
    st = 0 ;  
    ed = TabLong-1 ;  
    i = 0  ;  
  
    if(data >= a[st]) return st ;  
    else if(data <= a[ed]) return ed ;  
  
    while(st < ed)  
    {  
        m = (st+ed)/2 ;  
  
        if(data == a[m] ) break ;  
        if(data < a[m] && data > a[m+1]) break ;  
          
          
        if(data > a[m])  ed = m ;                      
        else st = m ;     
          
        if(i++ > TabLong) break ;  
    }  
  
    if(st > ed ) return 0 ;   
  
    return m ;  
}

int GetTemp(u8 CD4051_ch,u8 order)     //   CD4051_ch ����ѡ��ͨ�� order ƽ������
{
	u16 RT, R_NTCV, a, temp;
	int adc;
	// 0x01, 0x02, 0x04 3����  �ж��Ƿ����3�����ǵ�3λ 0111 ��
	GPIO_WriteBit(GPIOA, GPIO_Pin_8,  CD4051_ch&0x01?Bit_SET:Bit_RESET);  //bit0 
	GPIO_WriteBit(GPIOA, GPIO_Pin_11,  CD4051_ch&0x02?Bit_SET:Bit_RESET);  //bit1
	GPIO_WriteBit(GPIOA, GPIO_Pin_12,   CD4051_ch&0x04?Bit_SET:Bit_RESET);  //bit2
	
	a = order;
	while(a--)
		adc += Get_Adc(0);                       //ADC ͨ��ѡ��
	adc = adc/order;
	
	R_NTCV=(adc*3300)/4095;
//	printf("adc:%u, %u\r\n", adc, R_NTCV);    //���Բ鿴
	RT = 33000000/R_NTCV - R-Rd;
//	printf("RT:%u\r\n", RT);               //���Բ鿴
	
	temp = FineTab(pTmp,100,RT);    //�� С��λ
	if(temp != 99)
		temp = temp*10 + (pTmp[temp] - RT)*10/(pTmp[temp]-pTmp[temp+1]);
	return temp;
}

u32 Get_zhuodu()
{
	int Voltage =0, a;
	u8 CD4051_ch = 2;
	
	GPIO_WriteBit(GPIOA, GPIO_Pin_8,  CD4051_ch&0x01?Bit_SET:Bit_RESET);  //bit0 
	GPIO_WriteBit(GPIOA, GPIO_Pin_11,  CD4051_ch&0x02?Bit_SET:Bit_RESET);  //bit1
	GPIO_WriteBit(GPIOA, GPIO_Pin_12,   CD4051_ch&0x04?Bit_SET:Bit_RESET);  //bit2
	
    a = 5;
	while(a--)
		Voltage += Get_Adc(0);                       //ADC ͨ��ѡ��
	Voltage = Voltage/5;
	
	Voltage=(Voltage*3300)/4095;
	printf("ZhuoDu %u \r\n",Voltage);
	Voltage = Voltage*5000/3300;
	return Voltage;
}
