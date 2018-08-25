#include "EasyGUI.h"
#include "string.h"
#include "touch.h"
#include "lcd.h"
#include "text.h"



unsigned int EASYGUI_TIME_MS = 0;

extern u16 POINT_COLOR;

u32 EasyGUI_Time()
{
	return EASYGUI_TIME_MS;
}

void EasyGUI_ShowxNum(u16 x, u16 y, u32 num, u8 len)
{  
	//LCD_Fill(x, y, x + GUI_FONTSIZE*len/2, y + GUI_FONTSIZE, COLOR_WINDOW_BACKDROP);
	LCD_ShowxNum(x, y, num, len, GUI_FONTSIZE, 0x01);
} 

void EasyGUI_GetTouch(Touch_Info_Type *dat)
{
	static u8 last = 0, now;
	static Touch_Info_Type last_info;
	tp_dev.scan(0);
	now = (tp_dev.sta&TP_PRES_DOWN)?1:0;
	if(now)
	{
		if(last == 0)
			last_info.click = 1;
		else
			last_info.click = 0;
		
		last = 1;
		last_info.x = tp_dev.x[0];
		last_info.y = tp_dev.y[0];
	}
	else
	{
		if(last == 1)
			last_info.click = -1;
		else
			last_info.click = 0;
		last = 0;
	}
	dat->click = last_info.click;
	dat->x = last_info.x;
	dat->y = last_info.y;
}

void EasyGUI_ShowStr(u16 x, u16 y, u16 width, u16 height, u16 color, char *str)
{
	POINT_COLOR = color;
	Show_Str(x, y, width, height, (u8 *)str, 24, 1);
}

void EasyGUI_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color)
{
	
	LCD_Fill(sx, sy, sx+ex, sy+ey, color);
}

void EasyGUI_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1, y1, x2, y2);
}

void EasyGUI_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawRectangle(x1, y1, x2, y2);
}
