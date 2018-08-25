#ifndef __WINDOW_H__
#define __WINDOW_H__
#include "EasyGUI.h"
#include "stdio.h"
#include "gizwits_product.h"
#include "touch.h" 
#include "lcd.h"
extern void rtp_test(void);

extern Window_Type Activity_main_window;
extern Window_Type Activity1_window;
extern Window_Type Activity2_window;
extern Window_Type Activity3_window;
extern Window_Type Activity4_window;
extern Window_Type general_window;
extern Window_Type Poweron_window;

void general_window_ShowInfo(char *text);
void general_window_ShowNumber(u32 num);
void general_window_ShowTitie(char *text);
void general_window_CloseTimeInfo(void);

#endif
