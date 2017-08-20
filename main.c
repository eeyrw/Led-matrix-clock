#include <8052.h>
#include "Key.h"
#include "LedDisplay.h"
#include "LedUi.h"
#include <stdint.h>
#include "DS1302.h"




void Timer0() __interrupt(1)
{
    TH0 = 0xFF;
    TL0 = 0x30;

    LEDScan1msProc();
    KeyScan1msProc();
    LedUi1msProc();
}

void Timer0Init(void)
{
    TMOD = 0x01;
    TH0 = 0xFF; 
    TL0 = 0x30;

    EA = 1;
    ET0 = 1;
    TR0 = 1;
}

int main(void)
{
    DS1302_Initial();
    LEDDisplayInit();
    LedUiInit();
    KeyInit();
    Timer0Init();

    while (1)
    {
        KeyScanHanlder();
        LedUiHandler();
    }
}