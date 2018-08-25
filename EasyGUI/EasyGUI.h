#ifndef __EASYGUI_H__
#define __EASYGUI_H__
#include "stm32f10x.h"

/*
#define u8 unsigned char
#define u16 unsigned short
#define u32 unsigned int
*/
/************ Config - ����ѡ�� **************/
#define GUI_FONTSIZE 24            //�����С����Ҫ��ȷ����

#define BUTTON_NACTIV_COLOR 0x043F
#define BUTTON_ACTIV_COLOR  0x02f7
#define BUTTON_TEXT_COLOR 0xffff
#define COLOR_WINDOW_BACKDROP 0xfbe4                 //���ڵ�ɫ
#define COLOR_TAG_BACKDROP COLOR_WINDOW_BACKDROP    //��ǩ������ɫ
#define COLOR_TAG_TEXT 0x0000                       //��ǩ������ɫ



/***************** ���ݶ��� ******************/
#define GUIE_BUTTON 0x01    //����Ԫ�أ���ť
#define GUIE_TAG    0x02    //����Ԫ�أ���ǩ������ʾ�ı�������
#define GUIE_TIMES  0x03    //����Ԫ�أ�ʱ�ӣ����Զ�ʱִ���¼���value�ж���ʱ�����ڣ���λΪms
/******************* END *********************/

typedef struct{
	signed char click;
	u16 x;
	u16 y;
}Touch_Info_Type;

typedef struct{
	u16 lift;     //�������λ�úʹ�С
	u16 top;
	u16 width;
	u16 height;
	
	u8  type;     //�����������
	u32  value;    //�������������ֵ
	u32  reflash;  //������˱�����1�����򽫻�ˢ�´�Ԫ��
	char *text;   //���������Ҫչʾ�ı�
	
}Window_element_Type;

typedef struct _Window_Type{
	u8 element_num;                  //�û����룬������Ԫ�ص�����
	Window_element_Type *element;    //ָ�򴰿ڵ�Ԫ���б�
	void (*event_handler)(struct _Window_Type *, signed short element);
}Window_Type;

typedef struct{
	Window_Type *current_window;
	signed short current_element;  //��¼��ǰ���ڼ����Ԫ��
	unsigned char init;
}Window_State_Type;

typedef enum{
	BUTTON_STATE_NACTIV = 0,  //ƽ��״̬
	BUTTON_STATE_ACTIV = 1    //����״̬
}BUTTON_STATE;

void EasyGUI_Loop(void);
void EasyGUI_WindowShow(Window_Type *window);
void EasyGUI_Exit(void);
void EasyGUI_TAG_SetValue(Window_element_Type *element, u32 value);
void EasyGUI_TAG_ShowText(Window_element_Type *element, char *text);
void EasyGUI_Message(Window_Type* re, char * info);

#endif

