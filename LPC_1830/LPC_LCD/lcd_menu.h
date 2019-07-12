#ifndef _LCD_MENU_
#define _LCD_MENU_


#include <stdio.h>
#include "board.h"
#include <stdio.h>
#include "lpc_types.h"
#include "chip.h"
#include "app_button.h"
#include "main.h"



void key_home_action(void);


void key_down_action(uint8_t menu_index);
void key_enter_action(void);
void key_up_action(uint8_t menu_index);
void key_back_action(void);


#endif



