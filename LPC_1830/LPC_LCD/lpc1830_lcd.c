#include "lpc1830_lcd.h"
#include "board.h"
#include <stdio.h>
#include "lpc_types.h"
#include "chip.h"
#include "app_button.h"
#include "main.h"
#include "lpc1830_gpio_i2c.h"



#define WAIT_BF 	while(read_BF()){;}
					
void lpc_1830_lcd_init(void)
{	
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
	for(i = LED_DB0;i < (LED_DB7+1);i++)
	{
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
	for(i = LED_DB0;i < (LED_DB7+1);i++)
	{
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
	
	for(i = LED_DB0;i < (LED_DB7+1);i++)
	{
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
}


void gwrite_lcd_data_char(char cmd){
	int tmp_dir = 0;
	int i = 0;
	while(read_BF())
	{
		;
	}
	Delay(10);
	
	for(i = LED_DB0;i < (LED_DB7+1);i++)
	{
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

void print_cursor(uint8_t pos)
{
	if(pos == 0)
	{
		lcd_goto(0,1);
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




