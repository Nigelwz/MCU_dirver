#include "lpc1830_lcd.h"
#include "board.h"
#include <stdio.h>
#include "lpc_types.h"
#include "chip.h"
#include "app_button.h"
#include "main.h"
#include "lpc1830_gpio_i2c.h"



#define WAIT_BF 	while(read_BF()){;}
					
void lpc_1830_lcd_init(void){
	
	
	gpio_set_dir(LED_RS,0);
	gpio_set_dir(LED_R_W,0);
	gpio_set_dir(LED_E,0);
		gwrite_cmd_nowait_BP(0x38);
		Delay(5000);
		gwrite_cmd_nowait_BP(0x38);
		Delay(5000);

		gwrite_cmd_nowait_BP(0x38);
		Delay(5000);
	gwrite_cmd_nowait_BP(0x38);
		Delay(5000);
		gwrite_cmd_nowait_BP(0x38);
		Delay(5000);
			
		gwrite_cmd_nowait_BP(0x38);
			Delay(5000);
		gwrite_cmd_nowait_BP(0x0C);
		Delay(5000);
		gwrite_cmd_nowait_BP(0x06);
		Delay(5000);
			gwrite_cmd_nowait_BP(0x01);
		Delay(5000);
		gwrite_cmd_nowait_BP(0x80);
		Delay(5000);
}
void gwrite_cmd_nowait_BP(uint8_t cmd){
	
	int tmp_dir = 0;
	int i = 0;
	//	while(read_BF())
	//{
	//	;
	//}
	//Delay(30);
		for(i = LED_DB0;i < (LED_DB7+1);i++){
		if(cmd & (1 << (i - LED_DB0)))
				tmp_dir = 1;
		else
				tmp_dir = 0;
		
		gpio_set_dir(i,tmp_dir);
	}
gpio_set_dir(LED_E,0);
	Delay(10);
	
	gpio_set_dir(LED_RS,0);
	Delay(1);
	gpio_set_dir(LED_R_W,0);
	Delay(100);
	gpio_set_dir(LED_E,1);
	
	Delay(3000);
	gpio_set_dir(LED_E,0);
	Delay(30);
}


void gwrite_lcd_cmd(uint8_t cmd){
	int tmp_dir = 0;
	int i = 0;
		while(read_BF())
	{
		;
	}
		for(i = LED_DB0;i < (LED_DB7+1);i++){
		if(cmd & (1 << (i - LED_DB0)))
				tmp_dir = 1;
		else
				tmp_dir = 0;
		
		gpio_set_dir(i,tmp_dir);
	}
gpio_set_dir(LED_E,0);
	Delay(10);
	
	gpio_set_dir(LED_RS,0);
	Delay(1);
	gpio_set_dir(LED_R_W,0);
	Delay(100);
	gpio_set_dir(LED_E,1);
	
	Delay(3000);
	gpio_set_dir(LED_E,0);
	Delay(30);
}


void gwrite_lcd_data(uint8_t cmd){
	int tmp_dir = 0;
	int i = 0;
	while(read_BF())
	{
		;
	}
	Delay(10);
	
	for(i = LED_DB0;i < (LED_DB7+1);i++){
		if(cmd & (1 << (i - LED_DB0)))
			tmp_dir = 1;
		else
			tmp_dir = 0;
		
		gpio_set_dir(i,tmp_dir);
	}
	Delay(10);
	gpio_set_dir(LED_RS,1);
	Delay(1);
	gpio_set_dir(LED_R_W,0);
	Delay(100);
	gpio_set_dir(LED_E,1);

	Delay(5000);
	gpio_set_dir(LED_E,0);
	Delay(30);
	//gpio_set_dir(LED_E,1);
	
}


void gwrite_lcd_data_char(char cmd){
	int tmp_dir = 0;
	int i = 0;
	while(read_BF())
	{
		;
	}
	Delay(10);
	
	for(i = LED_DB0;i < (LED_DB7+1);i++){
		if(cmd & (1 << (i - LED_DB0)))
			tmp_dir = 1;
		else
			tmp_dir = 0;
		
		gpio_set_dir(i,tmp_dir);
	}
	Delay(10);
	gpio_set_dir(LED_RS,1);
	Delay(1);
	gpio_set_dir(LED_R_W,0);
	Delay(100);
	gpio_set_dir(LED_E,1);

	Delay(5000);
	gpio_set_dir(LED_E,0);
	Delay(30);
	//gpio_set_dir(LED_E,1);
	
}
int read_BF(void){

	
	int BF_flag = 0;
	#if 1
	uint32_t tmp_pin = 0;
	Delay(1000);
	gpio_set_dir(LED_E,0);
	Delay(10);
	gpio_set_dir(LED_RS,0);
	Delay(1);
	gpio_set_dir(LED_R_W,1);
	Delay(1000);
	gpio_set_dir(LED_E,1);
	Delay(3000);
	gpio_func_input(LED_DB0);
	gpio_func_input(LED_DB1);
	
	gpio_func_input(LED_DB2);
	gpio_func_input(LED_DB3);
	
	gpio_func_input(LED_DB4);
	gpio_func_input(LED_DB5);
	
	gpio_func_input(LED_DB6);
	gpio_func_input(LED_DB7);
	
	tmp_pin = Chip_GPIO_ReadValue(LPC_GPIO_PORT,2);
	if(tmp_pin & 0x0100)
		BF_flag = 1;
	else
		BF_flag = 0;
	//while(gpio_input_get_dir(LED_DB7));
	//BF_flag = gpio_input_get_dir(LED_DB7);
	Delay(30);
	gpio_set_dir(LED_E,0);
	Delay(30);
	gpio_set_dir(LED_R_W,0);
	//while(gpio_input_get_dir(LED_DB7) == 0)
	Delay(10);
	gpio_func_output(LED_DB0,0);
	gpio_func_output(LED_DB1,0);
	gpio_func_output(LED_DB2,0);
	gpio_func_output(LED_DB3,0);
	gpio_func_output(LED_DB4,0);
	gpio_func_output(LED_DB5,0);
	gpio_func_output(LED_DB6,0);
	gpio_func_output(LED_DB7,0);
	#endif
	return BF_flag;
}

/*lcd appilication*/
void lcd_goto(uint8_t column,uint8_t row)
{
	if(row == 0)
		gwrite_lcd_cmd(0x80 + column);
	else if(row == 1)
		gwrite_lcd_cmd(0xC0 + column);
}

void lcd_clear(void)
{
	gwrite_lcd_cmd(0x01);
	gwrite_lcd_cmd(0x02);
}
uint8_t read_ddram(void)
{
uint32_t tmp_pin = 0;
	uint8_t tmp_val = 0;
	//gwrite_lcd_cmd(0x80);
	
	
	Delay(1000);
	gpio_set_dir(LED_E,0);
	Delay(10);
	gpio_set_dir(LED_RS,1);
	Delay(1);
	gpio_set_dir(LED_R_W,1);
	Delay(1000);
	gpio_set_dir(LED_E,1);
	Delay(3000);
	gpio_func_input(LED_DB0);
	gpio_func_input(LED_DB1);
	
	gpio_func_input(LED_DB2);
	gpio_func_input(LED_DB3);
	
	gpio_func_input(LED_DB4);
	gpio_func_input(LED_DB5);
	
	gpio_func_input(LED_DB6);
	gpio_func_input(LED_DB7);
	
	tmp_pin = Chip_GPIO_ReadValue(LPC_GPIO_PORT,2);
	tmp_val = tmp_pin;
  if((tmp_pin & 0x0100) == 1)
		tmp_val |= 0x80;
	
	Delay(30);
	gpio_set_dir(LED_E,0);
	Delay(30);
	gpio_set_dir(LED_R_W,0);
	//while(gpio_input_get_dir(LED_DB7) == 0)
	Delay(10);
	gpio_func_output(LED_DB0,0);
	gpio_func_output(LED_DB1,0);
	gpio_func_output(LED_DB2,0);
	gpio_func_output(LED_DB3,0);
	gpio_func_output(LED_DB4,0);
	gpio_func_output(LED_DB5,0);
	gpio_func_output(LED_DB6,0);
	gpio_func_output(LED_DB7,0);
	return tmp_val;
}
uint8_t read_cusor_pos(void)
{
	uint8_t is_val;
	gwrite_lcd_cmd(0x80);
	is_val = read_ddram();
	if(is_val == 0x3E)
		return 1;
	gwrite_lcd_cmd(0xC0);
	is_val = read_ddram();
	if(is_val == 0x3E)
		return 2;
	
	return 0;
}

uint8_t read_char_pos(uint8_t pos)
{
	uint8_t tmp_val;
	gwrite_lcd_cmd(pos);
	tmp_val = read_ddram();
	return tmp_val;
}

struct _LCD_MENU_{
	char* menu_1;
	char* menu_2;
}LCD_MENU;


struct _LCD_MENU_ main_menu[] = {
	{"1.LED","2.EEPROM"},
	{"3.GPIO","4.UART"},
};

struct _MENU_CMD_{
	char* option_name;
	uint8_t option;
	//char* menu_2;
}MENU_CMD;


struct _MENU_CMD_ GPIO_MENU[] = {
	{"GPIO_5_8",0},
	{"GPIO_5_9",0},
};

struct _MENU_CMD_ LED_MENU[] = {
	{"LED_1",0},
	{"LED_2",0},
};

struct _MENU_CMD_ EEPROM_MENU[] = {
	{"read_0x001",0},
	{"write_0x001",0},
};


void print_cursor(uint8_t pos)
{
	if(pos == 0)
	{
		lcd_goto(0,1);
		//gwrite_lcd_cmd(0xC0);
		gwrite_lcd_data_char(0x20);
			
		lcd_goto(0,0);
		gwrite_lcd_data_char('>');
		}
		else if(pos == 1)
		{
			lcd_goto(0,0);
		gwrite_lcd_data_char(0x20);
			lcd_goto(0,1);
		gwrite_lcd_data_char('>');
		}
}

void print_menu(uint8_t type)
{
		if(type == 0)
		{
			lcd_clear();
			lcd_goto(1,0);
				LCD_printf(main_menu[0].menu_1);
			lcd_goto(1,1);
					LCD_printf(main_menu[0].menu_2);
			lcd_goto(23,1);
				gwrite_lcd_data(0x7E);
		}
		else if(type == 1)
		{
			lcd_clear();
			//	lcd_goto(1,0);
			//LCD_printf("                  ");
			//lcd_goto(1,1);
			//		LCD_printf("                  ");
			lcd_goto(1,0);
				LCD_printf(main_menu[1].menu_1);
			lcd_goto(1,1);
					LCD_printf(main_menu[1].menu_2);
		}
}

void print_gpio_menu(void)
{
	  lcd_clear();
		lcd_goto(1,0);
		LCD_printf("1.GPIO_5_8   %d",GPIO_MENU[0].option);
		lcd_goto(1,1);
		LCD_printf("2.GPIO_5_9   %d",GPIO_MENU[1].option);
}

void gpio_menu_option(uint8_t pin,uint8_t action)
{
	if(pin == 0)
	{
		lcd_goto(1,0);
		LCD_printf("1.GPIO_5_8   %d",action);
	}
	else if(pin == 1)
	{
		lcd_goto(1,1);
		LCD_printf("2.GPIO_5_9   %d",action);
	}

}


void print_LED_menu(void)
{
	  lcd_clear();
		lcd_goto(1,0);
		LCD_printf("1.LED_1   %d",LED_MENU[0].option);
		lcd_goto(1,1);
		LCD_printf("2.LED_2   %d",LED_MENU[1].option);
}


void led_menu_option(uint8_t pin,uint8_t action)
{
	if(pin == 0)
	{
		lcd_goto(1,0);
		LCD_printf("1.LED_1   %d",action);
	}
	else if(pin == 1)
	{
		lcd_goto(1,1);
		LCD_printf("2.LED_2   %d",action);
	}
}


void print_EEPROM_menu(void)
{
	  lcd_clear();
		lcd_goto(1,0);
		LCD_printf("1.addr 0x0001 =  %d",EEPROM_MENU[0].option);
		//lcd_goto(1,1);
		//LCD_printf("2.write addr 0x0001 = %d",EEPROM_MENU[1].option);
}

void eeprom_menu_option(uint8_t addr,uint8_t val,uint8_t action)
{
	uint8_t tmp_val = 0;
	if(action == 0)
	{
		lcd_clear();
		lcd_goto(1,0);
		tmp_val = read_adr_data(0x0002);
		LCD_printf("1.rom 0x0001 = %d",tmp_val);
	}
	//else if(action == 1)
	//{
	//	lcd_goto(1,1);
	//	LCD_printf("2.LED_2   %d",action);
	//}
}
#if 0
struct MENU_FUNC{
		uint8_t menu_index;
		uint8_t key_down_state;
		uint8_t key_up_state;
		uint8_t key_enter_state;
		char *menu_name;
		void (*menu_action);
};
void index_0_action(void)
{

}
struct MENU_FUNC gmenu_func[]={
		{0,1,0,9,"hello1",index_0_action},
		{1,2,0,9,"hello2",index_0_action},
		{2,3,1,9,"hello3",index_0_action},
		{3,4,2,9,"hello4",index_0_action},
};
#endif

