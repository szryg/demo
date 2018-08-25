#ifndef __EASYGUI_H__
#define __EASYGUI_H__
#include "stm32f10x.h"

/*
#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned int
*/
/************ Config - 配置选项 **************/
#define GUI_FONTSIZE 24            //字体大小，需要正确设置

#define BUTTON_NACTIV_COLOR 0x043F
#define BUTTON_ACTIV_COLOR  0x02f7
#define BUTTON_TEXT_COLOR 0xffff
#define COLOR_WINDOW_BACKDROP 0xfbe4                 //窗口底色
#define COLOR_TAG_BACKDROP COLOR_WINDOW_BACKDROP    //标签背景颜色
#define COLOR_TAG_TEXT 0x0000                       //标签字体颜色



/***************** 数据定义 ******************/
#define GUIE_BUTTON 0x01    //窗口元素，按钮
#define GUIE_TAG    0x02    //窗口元素，标签，可显示文本或数字
#define GUIE_TIMES  0x03    //串口元素，时钟，可以定时执行事件，value中定义时钟周期，单位为ms
/******************* END *********************/

typedef struct{
	signed char click;
	u16 x;
	u16 y;
}Touch_Info_Type;

typedef struct{
	u16 lift;     //定义组件位置和大小
	u16 top;
	u16 width;
	u16 height;
	
	u8  type;     //定义组件类型
	u32  value;    //组件输入或输出的值
	u32  reflash;  //组件将此变量置1，程序将会刷新此元素
	char *text;   //个别组件需要展示文本
	
}Window_element_Type;

typedef struct _Window_Type{
	u8 element_num;                  //用户输入，窗口中元素的数量
	Window_element_Type *element;    //指向窗口的元素列表
	void (*event_handler)(struct _Window_Type *, signed short element);
}Window_Type;

typedef struct{
	Window_Type *current_window;
	signed short current_element;  //记录当前窗口激活的元素
	unsigned char init;
}Window_State_Type;

typedef enum{
	BUTTON_STATE_NACTIV = 0,  //平常状态
	BUTTON_STATE_ACTIV = 1    //激活状态
}BUTTON_STATE;

void EasyGUI_Loop(void);
void EasyGUI_WindowShow(Window_Type *window);
void EasyGUI_Exit(void);
void EasyGUI_TAG_SetValue(Window_element_Type *element, u32 value);
void EasyGUI_TAG_ShowText(Window_element_Type *element, char *text);
void EasyGUI_Message(Window_Type* re, char * info);

#endif

