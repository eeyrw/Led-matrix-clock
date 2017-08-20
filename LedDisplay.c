#include "constantTable.h"
#include "74hc595.h"
#include "LedDisplay.h"
#include "state.h"


union LineData
{
    unsigned long Dat;
    unsigned char Array[4];
};

unsigned char LEDDisplayStr[5]="    ";
unsigned char CurrentLine;

unsigned char LEDStateTick;
unsigned char LEDState;

__bit NegativeNum1 = 0;
__bit NegativeNum2 = 0;


void LEDScan1msProc(void)
{
    if ((LEDStateTick != 0) && (LEDState == StateLEDWait))
    {
        LEDStateTick--;
    }

    if (LEDStateTick == 0)
    {
        LEDState = StateLEDScan;
        LEDStateTick = 5;
    }
}
void LEDDisplayInit(void)
{
    char i;
    for (i = 0; i < 4; i++)
    {
        Write595(0x00);
    }
    Lock595();
    LEDState = StateLEDScan;
    LEDStateTick = 0;
}

void LEDDisplaySetNegative(unsigned char index,__bit isNegative)
{
    if(index==0)
        NegativeNum1=isNegative;
    else
        NegativeNum2=isNegative;
}

char* LEDDisplayGetBuffer(void)
{
    return LEDDisplayStr;
}

void LEDScanHandler(void)
{
    union LineData Line;
    unsigned char *str;
    char i=0;
    unsigned char BasicAddr=0;

    if (LEDState==StateLEDScan)
    {
        Line.Dat=0;
        str=LEDDisplayStr;

        for (i=0;i<5;i++)
        {
            BasicAddr=(*str)-0x20;
            if ((NegativeNum1!=0) &&(i==0||i==1))
            {
                Line.Dat|=(unsigned long)((~Font[BasicAddr*7+CurrentLine])&0xFC)<<(i*6);
            } else
            {
                if ((NegativeNum2!=0)&&(i==3||i==4))
                {
                    Line.Dat|=((unsigned long)((~Font[BasicAddr*7+CurrentLine])&0xFC)<<(i*6));
                } else
                {
                    Line.Dat|=((unsigned long)Font[BasicAddr*7+CurrentLine]<<(i*6));
                }
            }
            str++;
        }
        Line.Dat=~Line.Dat;

        for (i=0;i<4;i++)
        {
            Write595(Line.Array[i]);
        }
        P2=0xFF;
        Lock595();

        P2=SelectTable[CurrentLine];

        if (CurrentLine<LED_MATRIX_ROW)
        {
            CurrentLine++;
        } else
        {
            CurrentLine=0;
        }
        LEDState=StateLEDWait;
    }
}