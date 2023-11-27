/*
 * uart_tools.h
 *
 *  Created on: Apr 7, 2022
 *      Author: Stéphane Guillemette
 */


#ifndef BLUENAV_COMMON_DEBUG_TOOLBOX_INC_UART_TOOLS_H_
#define BLUENAV_COMMON_DEBUG_TOOLBOX_INC_UART_TOOLS_H_

#include "stdio.h"
#include "usart.h"
#include "string.h"
	#ifndef _TRUE
		#define _FALSE		0
		#define _TRUE		1
		#define _DONE		2
	#endif
//
// BYTE TO BINARY MACROS
#define PRINTF_BINARY_PATTERN_INT8 "%c%c%c%c%c%c%c%c"
#define PRINTF_BYTE_TO_BINARY_INT8(i)    \
    (((i) & 0x80ll) ? '1' : '0'), \
    (((i) & 0x40ll) ? '1' : '0'), \
    (((i) & 0x20ll) ? '1' : '0'), \
    (((i) & 0x10ll) ? '1' : '0'), \
    (((i) & 0x08ll) ? '1' : '0'), \
    (((i) & 0x04ll) ? '1' : '0'), \
    (((i) & 0x02ll) ? '1' : '0'), \
    (((i) & 0x01ll) ? '1' : '0')
//
// COLORS
#define _UDBG_COLOR_DEFAULT		0
#define _UDBG_COLOR_ORANGE		1
// FIXME : legacy color codes cnst
static const char* const udbg_colors[] = {
		"\e[38;5;10m",	/* default, fallback color */
		"\e[38;5;202m", /* orange */
};
// new ! MACRO for color outputs.
// input = char array,
// output = char array with pre / post color ANSI code inserted
// SEE https://xdevs.com/guide/color_serial/ for more colors
#define FG_RED(text) 	("\033[1;31m" text "\033[0;39m")	/* bright red */
#define FG_GREEN(text) 	("\033[1;32m" text "\033[0;39m")	/* bright green */
#define FG_YELLOW(text) 	("\033[1;33m" text "\033[0;39m")	/* bright yellow */



extern uint8_t	udebug_CommandReady;		// TRUE / FALSE
extern uint8_t 	udebug_Command;				// input 'command' char, for tests
extern UART_HandleTypeDef *udebug_uart_handler;
extern uint8_t				udebug_RxBuffer[32];		// multibyte(?) rx buffer. sized with udebug_enable_rx_polling()

// init
void	udebug_init(UART_HandleTypeDef *huart);
// input scan
HAL_StatusTypeDef 	udebug_enable_rx_polling(uint32_t char_count);
// debug text , various functions
void 	udebug(char *text);
void	udebug_string(char* text_container,const char* text);
void	udebug_char(char* text_container,char asc_value);
void 	udebug_colored(char *text,uint8_t udbg_colorcode);
void 	udebug_raw(char* what);
void 	udebug_formatted(char* text,int integer_val);
void 	udebug_formatted_str(char* text,const char* text2);
void 	udebug_formatted_twice(char* text,int integer_val,int integer_wal);
void 	udebug_formatted_twice_int16_binary(char* text,int integer_val,int binary_wal);
void 	udebug_formatted_four(char* text,int integer_val,int integer_wal,int integer_xal,int integer_yal);
void	udebug_binary_variable(char* var_name,uint8_t var_val);
void 	udebug_function_name(const char* text2);	/* for __FUNCTION__ like calls debug */
uint8_t* udebug_get_RxBuffer();
// HAL based

//__attribute((weak)) void 	HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart); // needs to be enabled (NVIC) !
void udebug_RxCpltCallback(UART_HandleTypeDef *huart);

#endif /* BLUENAV_COMMON_DEBUG_TOOLBOX_INC_UART_TOOLS_H_ */
