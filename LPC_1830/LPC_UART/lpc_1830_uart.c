#include "lpc1830_gpio_i2c.h"
#include "board.h"
#include <stdio.h>
#include "lpc_types.h"
#include "chip.h"
#include "app_button.h"
#include "main.h"
#include "lpc_1830_uart.h"


/* Transmit and receive ring buffers */
STATIC RINGBUFF_T txring, rxring;

/* Ring buffer size */
#define UART_RB_SIZE 256

/* Transmit and receive buffers */
static uint8_t rxbuff[UART_RB_SIZE], txbuff[UART_RB_SIZE];
void uart_rx_data_handler(void);

void uart_init(LPC_USART_T *pUART)
{
		Chip_SCU_PinMuxSet(0x2, 0, (SCU_MODE_PULLDOWN | SCU_MODE_FUNC1));
	Chip_SCU_PinMuxSet(0x2, 1, (SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC1));
	Chip_UART_Init(LPC_USART0);
	Chip_UART_SetBaudFDR(LPC_USART0, 115200);
	Chip_UART_ConfigData(LPC_USART0,  UART_LCR_WLEN8 | UART_LCR_SBS_1BIT);
	Chip_UART_TXEnable(LPC_USART0);
Chip_UART_IntEnable(LPC_USART0, (UART_IER_RBRINT | UART_IER_RLSINT));	
	
		RingBuffer_Init(&rxring, rxbuff, 1, UART_RB_SIZE);
	RingBuffer_Init(&txring, txbuff, 1, UART_RB_SIZE);
}

void LPC_1830_UARTPutChar(char ch)
{
//#if defined(DEBUG_UART)
	/* Wait for space in FIFO */
	while ((Chip_UART_ReadLineStatus(LPC_USART0) & UART_LSR_THRE) == 0) {}
	Chip_UART_SendByte(LPC_USART0, (uint8_t) ch);
//#endif
}
void for_uart_int(void)
{
	Chip_UART_IRQRBHandler(LPC_USART0, &rxring, &txring);
}
uint8_t uart_buf[10];
uint8_t rx_index = 0;
uint8_t rx_state = 0;
uint8_t tmplen = 0;
uint8_t tmp_rx_data = 0;
uint8_t remain = 0;
void uart_handler(void)
{
	int len = 0;
	
	len =Chip_UART_ReadRB(LPC_USART0, &rxring, &uart_buf[rx_index], 1);
	if(len>0)
	{
		len = 0;
		tmp_rx_data = uart_buf[rx_index];
		if(rx_state == 0)
		{
				if(tmp_rx_data == 0xA5)
				{
					rx_index++;
					rx_state = 1;
				}
		}
		else if(rx_state == 1)
		{
				tmplen = tmp_rx_data;
				rx_index++;
				rx_state = 2;
			  remain = tmplen - 1;
		}
		else if(rx_state == 2)
		{
			uint8_t i = 0;
			uint8_t check_sum = 0x33;
				rx_index++;
				remain--;
				if(remain == 0)
				{
					for(i = 0;i<tmplen;i++)
					{
						check_sum += uart_buf[i];
					}
					if(check_sum == uart_buf[i])
					{
						//uart_rx_data_handler();
						//LPC_1830_UARTPutChar('A');
					}
					uart_rx_data_handler();
					rx_state = 0;
					rx_index = 0;
					
				}
		}
		
	}
}

char tmp_i2c_uart[256];
void uart_rx_data_handler(void)
{
	uint16_t eeprom_addr;
	uint8_t eeprom_data;
	uint8_t eeprom_size;
	uint8_t i = 0;
	if(uart_buf[0] == 0xA5)
	{
		if(uart_buf[2] == 0xA2)
		{
			eeprom_addr = uart_buf[3];
			eeprom_addr = (eeprom_addr << 8)|uart_buf[4];
			eeprom_data = uart_buf[5];
			eeprom_size = uart_buf[6];
			write_adr_multi_data(eeprom_addr,&eeprom_data,eeprom_size,1);
		}
		else if(uart_buf[2] == 0xA3)
		{
			read_rand_data(0x0000,tmp_i2c_uart,256);

					for(i = 0;i<255;i++)
					{
						if(i%16 == 0)
							uart0_printf("\n");
						uart0_printf(" 0x%x ",tmp_i2c_uart[i]);
					}
		}
	}

}

