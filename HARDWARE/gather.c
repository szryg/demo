/******************/
//高320，宽240
#include "gather.h"

void Screen_init(void)                                              //屏幕初始化总的
{
	LCD_Init();			   	//初始化LCD 	
	tp_dev.init();			//触摸屏初始化
}

//画矩形 触摸屏按键 区域
//(x1,y1),(x2,y2):矩形的对角坐标
u8 Key_Screen(u16 x1, u16 y1, u16 x2, u16 y2)                                  
{
	if(tp_dev.sta&TP_PRES_DOWN)			//触摸屏被按下
	{	
		if(tp_dev.x[0]<lcddev.width&&tp_dev.y[0]<lcddev.height)
		{
			if(((tp_dev.x[0]>x1)&&(tp_dev.x[0]<x2))&&((tp_dev.y[0]>y1)&&(tp_dev.y[0]<y2))) {
				return 1;
			}				
		}
	} 
	return 0;
}



void Activity_main()
{
	POINT_COLOR=BLUE;                                 //字体颜色
	Show_Str(24,24,192,24, "超声波智能洗碗机",24,0);
	
	Show_Str(60,96,140,24, "清 洗 程 序",24,0);
	Show_Str(60,144,140,24,"保 管 模 式",24,0);
	Show_Str(60,192,140,24,"预 约 模 式",24,0);
}

void Activity1()
{
	POINT_COLOR=BLUE;                                 //字体颜色
	Show_Str(60, 12,140,24,"清 洗 程 序",24,0);
	
	Show_Str(48, 84,60,24,"智 能",24,0);
	Show_Str(144,84,60,24,"标 准",24,0);	
	Show_Str(48, 132,60,24,"节 能",24,0);
	Show_Str(144,132,60,24,"果 蔬",24,0);
	Show_Str(60, 180,140,24,"腔 体 清 洁",24,0);
	Show_Str(48, 280,60,24,"返 回",24,0);
	Show_Str(144,280,60,24,"确 认",24,0);
}

void Activity2()
{
	POINT_COLOR=BLUE;                                 //字体颜色
	Show_Str(36,24,168,24, "保  管  模  式",24,0);
	
	Show_Str(60,96,140,24, "热 风 烘 干",24,0);
	Show_Str(60,144,140,24,"紫 外 杀 菌",24,0);
	Show_Str(60,192,140,24,"混 合 模 式",24,0);
	Show_Str(48, 280,60,24,"返 回",24,0);
	Show_Str(144,280,60,24,"确 认",24,0);
}

void Activity3()
{
	POINT_COLOR=BLUE;                                 //字体颜色
	Show_Str(36,24,168,24, "预  约  模  式",24,0);
	
	Show_Str(60,84,140,24, "定 时 开 机",24,0);
	Show_Str(36,132,24,24, "减",24,0);
	Show_Str(120,132,24,24, "加",24,0);
	Show_Str(156,132,140,24, "分钟",24,0);
	
	Show_Str(60,180,140,24,"定 时 关 机",24,0);
	Show_Str(36,228,24,24,"减",24,0);
	Show_Str(120,228,24,24,"加",24,0);
	Show_Str(156,228,140,24,"分钟",24,0);
	
	Show_Str(48, 280,60,24,"返 回",24,0);
	Show_Str(144,280,60,24,"确 认",24,0);
}










