#ifndef __595__
#define __595__

#include "8051.h"

#define SDATA_595 P3_0        //������������
#define SCLK_595 P3_1         //��λʱ������
#define RCK_595 P3_2           //�����������������


void Write595(unsigned char dat);
void Lock595(void);

#endif