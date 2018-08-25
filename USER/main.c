#include "include.h"


void EXOUT_PutDat(void);
extern void uart5_init(u32 bound);
extern const unsigned char gImage_bmp[];
extern unsigned int TaskMan_TIME_MS;
extern unsigned int EXOUT_DATBUFF;

void GPIO_Auto_Init(GPIO_TypeDef * GPIOx,uint32_t PINx, GPIOMode_TypeDef GPIOMode)
{
	uint32_t ABP2NUM;
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	if(GPIOx == GPIOA)
		 ABP2NUM = RCC_APB2Periph_GPIOA;
	if(GPIOx == GPIOB)
		 ABP2NUM = RCC_APB2Periph_GPIOB;
	if(GPIOx == GPIOC)
		 ABP2NUM = RCC_APB2Periph_GPIOC;
	if(GPIOx == GPIOD)
		 ABP2NUM = RCC_APB2Periph_GPIOD;
	if(GPIOx == GPIOE)
		 ABP2NUM = RCC_APB2Periph_GPIOE;
	if(GPIOx == GPIOF)
		 ABP2NUM = RCC_APB2Periph_GPIOF;
	if(GPIOx == GPIOG)
		 ABP2NUM = RCC_APB2Periph_GPIOG;
	RCC_APB2PeriphClockCmd(ABP2NUM, ENABLE);	 //ʹ��PA,PD�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = 0x01 << PINx;				 // �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIOMode; 		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
	GPIO_Init(GPIOx, &GPIO_InitStructure);	
	GPIO_SetBits(GPIOx,0x01 << PINx);
}


void Init()
{
    EXOUT_Init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2 
	delay_init();	    	 //��ʱ������ʼ��	  
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600			 
	LCD_Init();			//��ʼ��Һ�� 
	tp_dev.init();			//��������ʼ��
	KEY_Init();    //gate ���ų�ʼ��
	Adc_Init();
	
	
	TIM3_Int_Init(9,7199);//1MSϵͳ��ʱ
    uart5_init(9600);//WIFI��ʼ��
	memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));//�豸״̬�ṹ���ʼ��
	gizwitsInit();
	
	usmart_dev.init(72);	//usmart��ʼ��	
 	mem_init();				//��ʼ���ڴ��	    
 	exfuns_init();			//Ϊfatfs��ر��������ڴ�  
  //f_mount(fs[0],"0:",1); 	//����SD�� 
 	f_mount(fs[1],"1:",1); 	//����FLASH.
	font_init();            //��ʼ��������Ϣ
	
	EasyGUI_WindowShow(&Activity_main_window);
	
	GPIO_Auto_Init(GPIOA, 8, GPIO_Mode_Out_PP);      // A �˿ڳ�ʼ�� CD4051 
	GPIO_Auto_Init(GPIOA, 11, GPIO_Mode_Out_PP);     // B �˿ڳ�ʼ��
	GPIO_Auto_Init(GPIOA, 12, GPIO_Mode_Out_PP);     // C �˿ڳ�ʼ��
	
	currentDataPoint.valueSwitch_Total = 1;
}

void Auto_Start()
{
	static unsigned int timess = 0;
	if(TaskMan_TIME_MS-timess < 1000)
		return;
	printf("output: %04X\r\n", EXOUT_DATBUFF);
	timess = TaskMan_TIME_MS;
	if(TaskMan_State.auto_start != 0)
	{
		if(TaskMan_State.auto_start-- == 1)
		{
			TaskMan_State.auto_start = 0;
			TaskMan_TaskStart(Task_Auto);
		}
		printf("start: %u\r\n", TaskMan_State.auto_start);
		TaskMan_State.auto_shutdown = 0;
	}
	
	if(TaskMan_State.auto_shutdown != 0)
	{
		if(TaskMan_State.auto_shutdown-- == 1)
		{
			TaskMan_State.auto_shutdown = 0;
			TaskMan_State.power_sw = 0;
			TaskMan_TaskStop();
			EasyGUI_Message(&Activity_main_window, "�ػ��ˣ�");
		}
		TaskMan_State.auto_start = 0;
		printf("stop: %u\r\n", TaskMan_State.auto_shutdown);
	}
}

int main(void)
{ 	  	 
	unsigned int time123 = 0;
	Init();
	Temp_Set(34);
	EXOUT_Out_16Bit(0);
	while(1)
	{
		currentDataPoint.valueSwitch_Total = TaskMan_State.power_sw;
		currentDataPoint.valueSwitch_Node = TaskMan_State.mode1;
		currentDataPoint.valueSwitch_Custody = TaskMan_State.mode2;
		currentDataPoint.valueTiming_Off = TaskMan_State.auto_shutdown/60;
		currentDataPoint.valueTiming_Order_On = TaskMan_State.auto_start/60;

		gizwitsHandle((dataPoint_t *)&currentDataPoint);
        EasyGUI_Loop();
		TaskMan_Handler();
		Temp_Control_Handler();
		Auto_Start();
		if(TaskMan_TIME_MS-time123 >= 100)
		{
			time123 = TaskMan_TIME_MS;
			EXOUT_PutDat();
		}
		printf("zhuodu: %u\r\n",Get_zhuodu());
	} 
}

