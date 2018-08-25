#include "EasyGUI.h"
#include "GUI_User.h"
#include "stdio.h"
#include "string.h"

void EasyGUI_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 color);
void EasyGUI_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);
void EasyGUI_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);
void EasyGUI_GetTouch(Touch_Info_Type *dat);
void EasyGUI_ShowStr(u16 x, u16 y, u16 width, u16 height, u16 color, char *str);
void EasyGUI_ShowxNum(u16 x, u16 y, u32 num, u8 len);
u32 EasyGUI_Time(void);
extern Window_Type message_window;


Window_State_Type GUI_STATE = {NULL, -1, 1};

void EasyGUI_Message(Window_Type* re, char * info)   //弹出一个提示框，参数1：点击返回后跳到的窗口，参数2：提示信息内容
{
	message_window.element[0].value = (unsigned int)re;
	message_window.element[1].text = info;
	EasyGUI_WindowShow(&message_window);
}

void EasyGUI_ShowStr_Mid(u16 x, u16 y, u16 width, u16 height, u16 color, char *str)
{
	u16 strsize = strlen(str);
	strsize *= GUI_FONTSIZE/2;
	if(strsize>width)
		EasyGUI_ShowStr(x, y+(height/2-GUI_FONTSIZE/2), width, GUI_FONTSIZE, color, str);
	else
	{
		strsize = (width-strsize)/2;
		EasyGUI_ShowStr(strsize+x, y+(height/2-GUI_FONTSIZE/2), width, GUI_FONTSIZE, color, str);
	}
}



void EasyGUI_BUTTON(Window_element_Type *element, BUTTON_STATE button_state)
{
	EasyGUI_Fill(element->lift, element->top, element->width, element->height, button_state==BUTTON_STATE_ACTIV?BUTTON_ACTIV_COLOR:BUTTON_NACTIV_COLOR);
	EasyGUI_ShowStr_Mid(element->lift, element->top, element->width, element->height, BUTTON_TEXT_COLOR, element->text);
}

void EasyGUI_TAG_SetValue(Window_element_Type *element, u32 value)
{
	if(element->value != value)
	{
		element->value = value;
		element->text = NULL;
		element->reflash = 1;
	}
}

void EasyGUI_TAG_ShowText(Window_element_Type *element, char *text)
{
	if(element->text != text)
	{
		element->text = text;
		element->reflash = 1;
	}
}

void EasyGUI_TAG(Window_element_Type *element)
{
	element->reflash = 0;
	EasyGUI_Fill(element->lift, element->top, element->width, element->height, COLOR_TAG_BACKDROP);
	if(element->text != NULL)
		EasyGUI_ShowStr_Mid(element->lift, element->top, element->width, element->height, COLOR_TAG_TEXT, element->text);
	else
		EasyGUI_ShowxNum(element->lift, element->top, element->value, 4);
}

void EasyGUI_Drawelement(Window_element_Type *element, BUTTON_STATE button_state)
{
	if(element->type == GUIE_BUTTON)
		EasyGUI_BUTTON(element, button_state);
	else if(element->type == GUIE_TAG)
		EasyGUI_TAG(element);
}

void EasyGUI_WindowShow(Window_Type *window)
{
	u8 cnt;
	GUI_STATE.current_window = window;
	EasyGUI_Fill(0, 0, 240, 320, COLOR_WINDOW_BACKDROP);
	for(cnt=0; cnt < window->element_num; cnt++)
		EasyGUI_Drawelement(&window->element[cnt], BUTTON_STATE_NACTIV);
	GUI_STATE.init = 1;
}

void EasyGUI_Exit(void)
{
	GUI_STATE.current_window = NULL;
	GUI_STATE.current_element = -1;
}

char EasyGUI_Region(Window_element_Type *element, u16 x, u16 y)  //判断点击位置是否在某元素中
{
	if((element->lift<=x) && (element->top<=y) && ((element->width+element->lift)>=x) && (element->height+element->top>=y))
		return 1;
	else
		return 0;
}

void EasyGUI_Loop(void)
{
	static Touch_Info_Type touch_info;
	u8 cnt;
	u8 run_headler = 0;
	
	EasyGUI_GetTouch(&touch_info);
	if(GUI_STATE.current_window == NULL)
	{
		GUI_STATE.current_element = -1;
		return;
	}
	if(GUI_STATE.init == 1)
	{
		GUI_STATE.init = 0;
		if(GUI_STATE.current_window->event_handler != NULL)  //如果窗口有回调函数
			GUI_STATE.current_window->event_handler(GUI_STATE.current_window, -1);  //元素数为-1意味着是窗口初始化事件
	}
	
	for(cnt=0; cnt<GUI_STATE.current_window->element_num; cnt++)
	{
		run_headler = 0;
		
		if(GUI_STATE.current_window->element[cnt].type == GUIE_TAG)    //标签操作判断
		{
			if(GUI_STATE.current_window->element[cnt].reflash)
			{
				EasyGUI_Drawelement(&GUI_STATE.current_window->element[cnt], BUTTON_STATE_ACTIV);
				//printf("刷洗 显示\r\n");
			}
		}
		
		else if(GUI_STATE.current_window->element[cnt].type == GUIE_TIMES)   //时钟操作判断
		{   //定时器使用reflash值来记录上次执行的时间
			if((EasyGUI_Time() - GUI_STATE.current_window->element[cnt].reflash) >= GUI_STATE.current_window->element[cnt].value)
			{
				GUI_STATE.current_window->element[cnt].reflash = EasyGUI_Time();
				run_headler = 1; //条件满足，执行回调函数
			}
		}
		
		else if(GUI_STATE.current_window->element[cnt].type == GUIE_BUTTON)  //按钮操作判断
		{
			if(touch_info.click==1 && EasyGUI_Region(&GUI_STATE.current_window->element[cnt], touch_info.x, touch_info.y))
			{
				EasyGUI_Drawelement(&GUI_STATE.current_window->element[cnt], BUTTON_STATE_ACTIV);
				GUI_STATE.current_element = cnt;
			}
			else if(touch_info.click==-1 && GUI_STATE.current_element!=-1 && GUI_STATE.current_element==cnt)
			{
				EasyGUI_Drawelement(&GUI_STATE.current_window->element[cnt], BUTTON_STATE_NACTIV);
				GUI_STATE.current_element = -1;
				if(EasyGUI_Region(&GUI_STATE.current_window->element[cnt], touch_info.x, touch_info.y))
				{
					run_headler = 1; //条件满足，执行回调函数
				}
			}
		}
		
		if(GUI_STATE.current_window->event_handler != NULL && run_headler>=1 && cnt<GUI_STATE.current_window->element_num)  //
			GUI_STATE.current_window->event_handler(GUI_STATE.current_window, cnt);
		if(GUI_STATE.init)
		{
			return;
		}
	}
}

