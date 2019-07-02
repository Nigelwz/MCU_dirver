#ifndef _LPC_1830_GPIO_I2C_H_
#define _LPC_1830_GPIO_I2C_H_
#include <stdio.h>
#include "board.h"
#include <stdio.h>
#include "lpc_types.h"
#include "chip.h"
#include "app_button.h"
#include "main.h"

void I2C_gpio_init(void);
void I2C_gpio_start(void);

int I2C_addrWR(int addr,int wr);
int I2C_writedata(int data);
void gpio_i2C_read(void);
void I2C_gpio_stop(void);
void write_adr_data(uint16_t addr,uint8_t data);
uint8_t read_adr_data(uint16_t addr);
#endif

