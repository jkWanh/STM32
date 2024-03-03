#include "../Include/retarget.h"
#include "stdio.h"
/* ����USART�˿ڣ�����ע���ض���Ĵ���(Ҳ������UART������ʵ���������д) */
static USART_TypeDef *sg_retargetUsart;

/**
 * @brief ע���ض��򴮿�
 * @param usartx ��Ҫ�ض�����������Ĵ���
 */
void RetargetInit(USART_TypeDef *usartx) {
    /* ע�ᴮ�� */
    sg_retargetUsart = usartx;

    /* Disable I/O buffering for STDOUT stream, so that
     * chars are sent out as soon as they are printed. */
    setvbuf(stdout, NULL, _IONBF, 0);
    /* Disable I/O buffering for STDIN stream, so that
     * chars are received in as soon as they are scanned. */
    setvbuf(stdin, NULL, _IONBF, 0);

}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE {
/* ����һ���ֽ����ݵ����� */
/* �ܼ򵥣�ֱ�ӵ��ÿ⺯���е� ���ڷ������ݺ��� */
USART_SendData(sg_retargetUsart, (uint8_t) ch);

/*�ȴ��������*/
while (USART_GetFlagStatus(sg_retargetUsart, USART_FLAG_TXE) == RESET);
/* ���ط��͵��ַ� */
return ch;

}

/**
  * @brief  Retargets the C library scanf, getchar function to the USART.
  * @param  None
  * @retval None
  */
GETCHAR_PROTOTYPE {

/* �ܼ򵥣�ֱ�ӵ��ÿ⺯���еĽ��� */
/* �ȴ������������� */
while (USART_GetFlagStatus(sg_retargetUsart, USART_FLAG_RXNE) == RESET);
/* ֱ�ӷ��ؽ��յ����ַ� */
return (int) USART_ReceiveData(sg_retargetUsart);

}
