#include "main.h"

int fputc(int ch, FILE *p)
{
	USART_SendData(USART1,(uint8_t)ch);	
	//while(USART_GetFlagStatus(USART1,USART_FLAG_TXE)==RESET);
	while (!(USART1->SR & USART_FLAG_TXE));
	return ch;
}
#if 0
#pragma import(__use_no_semihosting)
struct __FILE
{
	int handle;
		/* Whatever you require here. If the only file you are using is */
	/* standard output using printf() for debugging, no file handling */
	/* is required. */
};
/* FILE is typedef’ d in stdio.h. */
FILE __stdout;
/* ??_sys_exit()?????????? */
void _sys_exit(int x)
{
	x = x;
}
#endif
