#ifndef _LPC_1830_LCD_H_
#define _LPC_1830_LCD_H_
//#include <stdio.h>
#include "board.h"
#include <stdio.h>
#include "lpc_types.h"
#include "chip.h"
#include "app_button.h"
#include "main.h"
void gwrite_lcd_cmd(uint8_t cmd);
void gwrite_lcd_data(uint8_t cmd);
void gwrite_cmd_nowait_BP(uint8_t cmd);
int read_BF(void);
int read_BF_and_ddram_addr(void);
void gwrite_lcd_data_char(char cmd);
void lpc_1830_lcd_init(void);

void print_gpio_menu(void);
void lcd_goto(uint8_t column,uint8_t row);
uint8_t read_cusor_pos(void);
void lcd_clear(void);
void print_menu(uint8_t type);
void print_cursor(uint8_t pos);
uint8_t read_char_pos(uint8_t pos);
void gpio_menu_option(uint8_t pin,uint8_t action);
void print_EEPROM_menu(void);
void eeprom_menu_option(uint8_t addr,uint8_t val,uint8_t action);
//void read_cusor(void);
#endif

