#ifndef _DEV_USART_H_
#define _DEV_USART_H_

#include <stdint.h>

#define NO_TIMEOUT			0

void set_speed(uint32_t fd, uint32_t speed);
int set_Parity(uint32_t fd, uint32_t bits, uint32_t stop, uint32_t parity, uint32_t timeout_sec);
void bwton_clear_com_buff(uint32_t fd);


#endif //_DEV_USART_H_
