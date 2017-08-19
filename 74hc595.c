#include "74hc595.h"

void Write595(unsigned char dat)
{
   SBUF = dat;
   while (!TI);
   TI = 0;
}

void Lock595(void)
{
   RCK_595 = 0; 
   RCK_595 = 1;                       //�����ؽ������͵����������
   RCK_595 = 0;
}
