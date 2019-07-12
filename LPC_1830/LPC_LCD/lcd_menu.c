#include "lcd_menu.h"
#include "lpc1830_lcd.h"

uint8_t current_menu_index = 0;
struct MENU_FUNC{
		uint8_t menu_index;
		uint8_t key_down_state;
		uint8_t key_up_state;
		uint8_t key_enter_state;
		uint8_t key_back_state;
		char *menu_name;
		void (*menu_action)(uint8_t index);
};
void index_0_action(uint8_t tmp_idx)
{
	//struct MENU_FUNC* tmp_menu_func = &gmenu_func[tmp_idx];
	//show(tmp_menu_func -> key_enter_state);
}
struct MENU_FUNC gmenu_func[]={	
		/*index|key_down|key_up|key_enter|key_back*/
		{0,1,6,0,0,"menu0",index_0_action},
		{1,2,0,0,0,"menu1",index_0_action},
		{2,3,1,0,0,"menu2",index_0_action},
		{3,4,2,0,0,"menu3",index_0_action},
		{4,5,3,7,0,"menu4",index_0_action},
		{5,6,4,0,0,"menu5",index_0_action},
		{6,0,5,11,0,"menu6",index_0_action},
		/**/
		{7,8,10,0,0,"menu7",index_0_action},
		{8,9,7,0,0,"menu8",index_0_action},
		{9,10,8,0,0,"menu9",index_0_action},
		{10,7,9,0,0,"menu10",index_0_action},
		/**/
		{11,12,14,0,7,"menu11",index_0_action},
		{12,13,11,0,7,"menu12",index_0_action},
		{13,14,12,0,7,"menu13",index_0_action},
		{14,11,13,0,7,"menu14",index_0_action},
};

#define GMENU_FUNC_SIZE (sizeof(gmenu_func)/sizeof(gmenu_func[0]))



void key_menu_show_two_column(uint8_t one_column,uint8_t two_column,uint8_t cursor_pos)
{
	lcd_clear();
	lcd_goto(1,0);
	LCD_printf(gmenu_func[one_column].menu_name);
	if(gmenu_func[one_column].key_enter_state)
	{
			lcd_goto(23,0);
			gwrite_lcd_data(0x7E);
	}
	else
	{
			lcd_goto(23,0);
			gwrite_lcd_data(0x10);
	}
	lcd_goto(1,1);
	LCD_printf(gmenu_func[two_column].menu_name);
	if(gmenu_func[two_column].key_enter_state)
	{
			lcd_goto(23,1);
			gwrite_lcd_data(0x7E);
	}
	else
	{
			lcd_goto(23,1);
			gwrite_lcd_data(0x10);
	}
	print_cursor(cursor_pos);
}
void key_back_action(void)
{
	uint8_t current_back_index = 0;
	//if(gmenu_func[current_menu_index].key_back_state)
	{
		current_back_index = gmenu_func[current_menu_index].key_back_state;
		current_menu_index = current_back_index;
		key_menu_show_two_column(current_back_index,current_back_index+1,0);
		//current_menu_index = 0;
	}
}
void key_home_action(void)
{
		key_menu_show_two_column(0,1,0);
		current_menu_index = 0;
}


void key_down_action(uint8_t menu_index)
{
	uint8_t tmp_down_index = 0;
	uint8_t one_colume = 0;
	uint8_t two_colume = 0;
	uint8_t two_colume_next = 0;
	if(menu_index%2 == 1)
	{
		one_colume = gmenu_func[current_menu_index].key_down_state;
		two_colume = gmenu_func[one_colume].key_down_state;
		current_menu_index = one_colume;
		key_menu_show_two_column(one_colume,two_colume,0);
	
	}
	else
	{
		one_colume = gmenu_func[current_menu_index].key_down_state;
		current_menu_index = one_colume;
		print_cursor(1);
	}
	
}

void key_up_action(uint8_t menu_index)
{
	uint8_t one_colume = 0;
	uint8_t two_colume = 0;
	if(menu_index%2 == 0)
	{
		one_colume = gmenu_func[current_menu_index].key_up_state;
		two_colume = gmenu_func[one_colume].key_up_state;
		current_menu_index = one_colume;
		key_menu_show_two_column(two_colume,one_colume,1);
	}
	else
	{
		one_colume = gmenu_func[current_menu_index].key_up_state;
		current_menu_index = one_colume;
		print_cursor(0);
	}
}
void key_enter_action(void)
{
	uint8_t one_colume_enter = 0;
	uint8_t two_colume_enter = 0;
	
	if(gmenu_func[current_menu_index].key_enter_state)
	{
		one_colume_enter = gmenu_func[current_menu_index].key_enter_state;
		two_colume_enter = gmenu_func[one_colume_enter].key_down_state;
		current_menu_index = one_colume_enter;
		key_menu_show_two_column(one_colume_enter,two_colume_enter,0);
	}
}