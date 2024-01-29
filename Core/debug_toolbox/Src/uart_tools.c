/*
 * uart_tools.c
 *
 *  Created on: Apr 7, 2022
 *      Author: Stéphane Guillemette
 */
#include "../Inc/uart_tools.h"
//
UART_HandleTypeDef *udebug_uart_handler;
uint8_t				udebug_RxBuffer[32];		// multibyte(?) rx buffer. sized with udebug_enable_rx_polling()
uint8_t				udebug_CommandReady;		// TRUE / FALSE
uint8_t 			udebug_Command;				// input 'command' char, for tests
//



void udebug_init(UART_HandleTypeDef *what)
{
	udebug_uart_handler=what;		// for next prints
	udebug_CommandReady=_FALSE;
	udebug_Command=0;
	uint32_t c;
	for(c=0;c<32;c++) udebug_RxBuffer[c]=0;
}
HAL_StatusTypeDef udebug_enable_rx_polling(uint32_t char_count)
{
	udebug_CommandReady=_FALSE;
	return HAL_UART_Receive_IT(udebug_uart_handler, udebug_RxBuffer, char_count); //<- rearm  for RX : again 'til next rx complete
}
// output functions
void udebug(char *text)
{
	uint8_t	obuf[1024];
	int len=sprintf((char*)obuf,text);
	HAL_UART_Transmit(udebug_uart_handler,obuf,len,1000);
}
void udebug_string(char* text_container,const char* text)
{
	uint8_t	obuf[1024];
	int len=sprintf((char*)obuf,text_container,text);
	HAL_UART_Transmit(udebug_uart_handler,obuf,len,1000);
}
void	udebug_char(char* text_container,char asc_value)
{
	uint8_t	obuf[1024];
	int len=sprintf((char*)obuf,text_container,asc_value);
	HAL_UART_Transmit(udebug_uart_handler,obuf,len,1000);
}
void 	udebug_colored(char *text,uint8_t udbg_colorcode)
{
	uint8_t	obuf[1024];
	int len=sprintf((char*)obuf,"%s%s%s",udbg_colors[udbg_colorcode],text,udbg_colors[_UDBG_COLOR_DEFAULT]);
	HAL_UART_Transmit(udebug_uart_handler,obuf,len,1000);
}
void udebug_raw(char* what)
{
	int len=strlen(what);
	HAL_UART_Transmit(udebug_uart_handler, (uint8_t *)what,len,1000); // [-Wpointer-sign]

}
void udebug_formatted(char* text,int integer_val)
{
	uint8_t	obuf[1024];
	int len=sprintf((char*)obuf,text,integer_val);
	HAL_UART_Transmit(udebug_uart_handler,obuf,len,1000);
}

void udebug_formatted_float(char* text,float integer_val)
{
	uint8_t	obuf[1024];
	int len=sprintf((char*)obuf,text,integer_val);
	HAL_UART_Transmit(udebug_uart_handler,obuf,len,1000);
}

void udebug_formatted_str(char* text,const char* text2)
{
	uint8_t	obuf[1024];
	int len=sprintf((char*)obuf,text,text2);
	HAL_UART_Transmit(udebug_uart_handler,obuf,len,1000);
}
//
void udebug_formatted_twice(char* text,int integer_val,int integer_wal)
{
	uint8_t	obuf[1024];
	int len=sprintf((char*)obuf,text,integer_val,integer_wal);
	HAL_UART_Transmit(udebug_uart_handler,obuf,len,1000);
}
void udebug_formatted_four(char* text,int integer_val,int integer_wal,int integer_xal,int integer_yal)
{
	uint8_t	obuf[1024];
	int len=sprintf((char*)obuf,text,integer_val,integer_wal,integer_xal,integer_yal);
	HAL_UART_Transmit(udebug_uart_handler,obuf,len,1000);
}
void udebug_formatted_eight(char* text,int integer_val,int integer_wal,int integer_xal,int integer_yal,int integer_zal,int integer_qal,int integer_nal,int integer_mal)
{
	uint8_t	obuf[1024];
	int len=sprintf((char*)obuf,text,integer_val,integer_wal,integer_xal,integer_yal,integer_zal,integer_qal,integer_nal,integer_mal);
	HAL_UART_Transmit(udebug_uart_handler,obuf,len,1000);
}

void udebug_formatted_six(char* text,int integer_val,int integer_wal,int integer_xal,int integer_yal,int integer_zal,int integer_qal)
{
	uint8_t	obuf[1024];
	int len=sprintf((char*)obuf,text,integer_val,integer_wal,integer_xal,integer_yal,integer_zal,integer_qal);
	HAL_UART_Transmit(udebug_uart_handler,obuf,len,1000);
}

//
void	udebug_binary_variable(char* var_name,uint8_t var_val)
{
	uint8_t	obuf[1024];
	int len=sprintf((char*)obuf,"%8s[%c%c%c%c%c%c%c%c]",var_name,PRINTF_BYTE_TO_BINARY_INT8(var_val));
	HAL_UART_Transmit(udebug_uart_handler,obuf,len,1000);
}
void udebug_formatted_twice_int16_binary(char* text,int integer_val,int binary_wal)
{
	uint8_t	obuf[1024];
	int len=sprintf((char*)obuf,text,integer_val,PRINTF_BYTE_TO_BINARY_INT8(binary_wal));
	HAL_UART_Transmit(udebug_uart_handler,obuf,len,1000);
}
uint8_t* udebug_get_RxBuffer()
{
	return &udebug_RxBuffer[0];
}
//
void udebug_function_name(const char* text2)
{
	uint8_t	obuf[1024];
	int len=sprintf((char*)obuf,"call:%s\r\n",text2);
	HAL_UART_Transmit(udebug_uart_handler,obuf,len,1000);
}

// input RX char CALLBACK

__attribute__((weak)) void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart==udebug_uart_handler)
	{
		if(udebug_CommandReady==_FALSE)
		{
			udebug_Command=udebug_RxBuffer[0];
			udebug_CommandReady=_TRUE;
		}
	}
}



