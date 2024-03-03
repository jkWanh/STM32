#ifndef _STDUSART_RETARGET_H__
#define _STDUSART_RETARGET_H__

#include <stdio.h>
#include "stm32f4xx_usart.h"

#ifdef __GNUC__
/* With GCC, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

#ifdef __GNUC__
#define GETCHAR_PROTOTYPE int __io_getchar (void)
#else
#define GETCHAR_PROTOTYPE int fgetc(FILE * f)
#endif /* __GNUC__ */

/**
 * @brief ע���ض��򴮿�
 * @param usartx ��Ҫ�ض�����������Ĵ���
 */
void RetargetInit(USART_TypeDef *huart);

#endif //_STDUSART_RETARGET_H__