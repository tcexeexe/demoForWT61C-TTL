#ifndef _ANALYSE_H_
#define _ANALYSE_H_

#include <stdint.h>

void CopeSerial2Data(uint8_t ucData[], uint8_t len);
struct SAcc read_acc();
void acc2speed(void);
#endif