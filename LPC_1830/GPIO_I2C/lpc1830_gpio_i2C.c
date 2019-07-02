#include "lpc1830_gpio_i2c.h"
#include "board.h"
#include <stdio.h>
#include "lpc_types.h"
#include "chip.h"
#include "app_button.h"
#include "main.h"
#include "lpc1830_gpio_i2c.h"


#define SDA_HI gpio_set_dir(GPIO_I2C_SDA,1)
#define SCL_HI gpio_set_dir(GPIO_I2C_SCL,1)

#define SDA_LO gpio_set_dir(GPIO_I2C_SDA,0)
#define SCL_LO gpio_set_dir(GPIO_I2C_SCL,0)

#define SDA_IN gpio_func_input(GPIO_I2C_SDA)
#define SDA_OUT gpio_func_output(GPIO_I2C_SDA,1)

#define CHECK_SDA_IN gpio_input_get_dir(GPIO_I2C_SDA)


/*direct acess IO register,it can speed up acess speed*/
#define SDA_BUF	LPC_GPIO_PORT->B[5][26]
#define SCL_BUF LPC_GPIO_PORT->B[5][25]
#define SDA_INPUT_BUF LPC_GPIO_PORT->B[5][26]
/*I2c soft delay 10us,it mean which is I2c Speed is 100K*/
#define I2C_Delay Delay(10)
#define I2C_WAIT Delay(5)

int I2C_check_ack(void);

void I2C_gpio_init(void)
{
	SDA_HI;
	SCL_HI;
}

void I2C_gpio_start()
{
	SDA_HI;
	SCL_HI;
	I2C_WAIT;
	SDA_LO;
	I2C_WAIT;
	SCL_LO;
}


void I2C_gpio_stop()
{
	SDA_LO;
	SCL_HI;
	I2C_WAIT;
	SDA_HI;
	I2C_WAIT;
}


int I2C_addrWR(int addr,int wr)
{ 
		uint8_t i,da,tmpdir;
	
		da = addr |wr;
	
		SDA_OUT;
		for(i = 0;i<8;i++){
				if(da & 0x80)
					tmpdir =1;
				else
					tmpdir =0;
				
				SDA_BUF = tmpdir;
				da = da << 1;
				I2C_Delay;
				SCL_BUF = 1;
				I2C_Delay;
				SCL_BUF = 0;
				
		}
		//send 8-bit data,and set sda = 0,otherwise wave can be half(1.25V)
		SDA_BUF = 0;
		I2C_Delay;
		if(I2C_check_ack() == 0)
		{
			I2C_gpio_stop();
			return 1;
		}
		else
		{
			return 0;
		}
}

int I2C_writedata(int data)
{ 
	int i,da,tmpdir;
	da = data;
	SDA_OUT;
	for(i = 0;i<8;i++){
		
		if(data & 0x80)
			tmpdir =1;
		else
			tmpdir =0;
		
		SDA_BUF = tmpdir;
		data = data << 1;
		I2C_Delay;
		SCL_BUF = 1;
		I2C_Delay;
		//if(i == 7)
		//	LPC_GPIO_PORT->DIR[5] &= ~(1UL << 26);
		SCL_BUF = 0;
	}
	//send 8-bit data,and set sda = 0,otherwise wave can be half(1.25V)
	SDA_BUF = 0;
	I2C_Delay;
		if(I2C_check_ack() == 0)
		{
			I2C_gpio_stop();
			return 1;
		}
		else
		{
			SDA_OUT;
			return 0;
		}
}
int I2C_check_ack(void)
{
		int sda_status = 0;
		SDA_IN;
		SDA_BUF = 1;
	
		I2C_Delay;

		SCL_BUF = 1;
		if(SDA_INPUT_BUF == 0)
			sda_status = 1;
		else
			sda_status = 0;
		
		I2C_Delay;
		SCL_BUF = 0;
		
		return sda_status;
}

void gpio_i2c_ack()
{
	SDA_BUF = 0;
	I2C_Delay;
	SCL_BUF = 1;
	I2C_Delay;
	SCL_BUF = 0;
	I2C_Delay;
	SDA_BUF = 1;
}

int gpio_i2c_read_byte(int ack)
{
	int idx,da;
	da = 0x0;
	SDA_IN;
	for(idx = 0;idx<8;idx++)
	{
	
		I2C_Delay;
		SCL_BUF = 1;
			da <<= 1;
		if(SDA_INPUT_BUF)
			da |= 1;
		I2C_Delay;
		SCL_BUF = 0;
	}
	SDA_OUT;
	if(ack)
		SDA_BUF = 1;
	else
		SDA_BUF = 0;
	SCL_BUF = 1;
	I2C_Delay;
	SCL_BUF = 0;
	I2C_gpio_stop();
	return da;
}

void gpio_i2C_read()
{
	//I2C_gpio_start();
	//if(I2C_addrWR(0xA0,1) == 0)
	//		gpio_i2c_read_byte(0);

}

void write_adr_data(uint16_t addr,uint8_t data)
{
	uint8_t addr_L = addr;
		uint8_t addr_H = addr>>8;
	I2C_gpio_start();
			I2C_addrWR(0xA0,0);
			I2C_writedata(addr_H);
			I2C_writedata(addr_L);
	I2C_writedata(data);
	
I2C_gpio_stop();

}

uint8_t read_adr_data(uint16_t addr)
{
	uint8_t addr_L = addr;
		uint8_t addr_H = addr>>8;
	uint8_t data;
	I2C_gpio_start();
			I2C_addrWR(0xA0,0);
			I2C_writedata(addr_H);
			I2C_writedata(addr_L);
	I2C_Delay;
	I2C_gpio_start();
	I2C_addrWR(0xA0,1);
	I2C_Delay;
	data = gpio_i2c_read_byte(1);
	
	return data;
}



