#include <8052.h>
#include "74hc595.h"
#include "state.h"
#include "DS1302.h"
#include "key.h"
#include "constantTable.h"
#include <stdint.h>
#include <string.h>
//#define DEBUG


#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

#define MAJOR_VER 1
#define MINOR_VER 0
#define VER_STRING "V" STR(MAJOR_VER) "." STR(MINOR_VER)

union LineData
{
    unsigned long Dat;
    unsigned char Array[4];
};

DateTime DT;

unsigned char DisplayStr[5]="    ";
unsigned char CurrentLine;

unsigned char LEDStateTick;
unsigned char LEDState;

unsigned char KeyStateTick;
unsigned char KeyState;

unsigned short StarupScreenCountDownTick;

unsigned char DisplayState;

unsigned char KeySetState;
unsigned char KeyPlusState;
unsigned char KeyMinuState;


__bit NegativeNum1=0;         
__bit NegativeNum2=0;

__bit KeySetValue=0;         
__bit KeyPlusValue=0;
__bit KeyMinuValue=0;



void ShowTwoNumbers(unsigned char Num1,unsigned char Num2)
{

    unsigned char *source;
    unsigned char *target;
    unsigned char i;
    source=(unsigned char *)(NumberStr2+Num2);
    target=DisplayStr+3;
    for (i=0;i<2;i++)
    {
        (*target)=(*source);
        source++;
        target++;

    } 


    source=(unsigned char *)(NumberStr+Num1);
    target=DisplayStr;
    for (i=0;i<2;i++)
    {
        (*target)=(*source);
        source++;
        target++;

    } 
}

void ShowYearNumbers(unsigned char Num1)
{

    unsigned char *source;
    unsigned char *target;
    unsigned char i;
    DisplayStr[0]=' ';
    DisplayStr[1]='2';
    DisplayStr[2]='0';
    source=(unsigned char *)(NumberStr2+Num1);
    target=DisplayStr+3;
    for (i=0;i<2;i++)
    {
        (*target)=(*source);
        source++;
        target++;

    } 

}

void ShowWeekStr(unsigned char Num1)
{

    unsigned char *source;
    unsigned char *target;
    unsigned char i;

    source=(unsigned char *)(WeekStr+Num1);
    target=DisplayStr;
    for (i=0;i<5;i++)
    {
        (*target)=(*source);
        source++;
        target++;

    } 

}


void Timer0() __interrupt(1)
{
    TH0=0xFF;
    TL0=0x30;
	//WDTRST=0x1E;
	//WDTRST=0xE1;
    if ((StarupScreenCountDownTick!=0) && (DisplayState==StateShowStarupScreen))
    {
        StarupScreenCountDownTick--;
    }
    if ((LEDStateTick!=0) && (LEDState==StateLEDWait))
    {
        LEDStateTick--;
    }

    if (LEDStateTick==0)
    {
        LEDState=StateLEDScan;
        LEDStateTick=5;
    }

    if ((KeyStateTick!=0) && (KeyState==StateKeyWait))
    {
        KeyStateTick--;
    }
    if (KeyStateTick==0)
    {
        KeyState=StateKeyScan;
        KeyStateTick=1;
    }


}
void KeyScanHanlder(void)
{
    __bit TempKeyValue;

    if (KeyState==StateKeyScan)
    {
        TempKeyValue=KeySetPin;
        KeySetValue=0;
        switch (KeySetState)
        {
        case StateKeyFree:
            if (!KeySetPin)
            {
                KeySetState=StateKeyPress;
            }
            break;
        case StateKeyPress:
            if (!TempKeyValue)
            {
                KeySetState=StateKeyRelease;
                KeySetValue=1;
            } else
            {
                KeySetState=StateKeyFree;
            }
            break;
        case StateKeyRelease:

            if (TempKeyValue)
            {
                KeySetState=StateKeyFree;
            }
            break;
        }




        TempKeyValue=KeyPlusPin;
        KeyPlusValue=0;
        switch (KeyPlusState)
        {
        case StateKeyFree:
            if (!KeyPlusPin)
            {
                KeyPlusState=StateKeyPress;
            }
            break;
        case StateKeyPress:
            if (!TempKeyValue)
            {
                KeyPlusState=StateKeyRelease;
                KeyPlusValue=1;
            } else
            {
                KeyPlusState=StateKeyFree;
            }
            break;
        case StateKeyRelease:

            if (TempKeyValue)
            {
                KeyPlusState=StateKeyFree;
            }
            break;
        }


        TempKeyValue=KeyMinuPin;
        KeyMinuValue=0;
        switch (KeyMinuState)
        {
        case StateKeyFree:
            if (!KeyMinuPin)
            {
                KeyMinuState=StateKeyPress;
            }
            break;
        case StateKeyPress:
            if (!TempKeyValue)
            {
                KeyMinuState=StateKeyRelease;
                KeyMinuValue=1;
            } else
            {
                KeyMinuState=StateKeyFree;
            }
            break;
        case StateKeyRelease:

            if (TempKeyValue)
            {
                KeyMinuState=StateKeyFree;
            }
            break;
        }

        KeyState=StateKeyWait;
    }






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
        str=DisplayStr;

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


        // for (i=3;i>=0;i--)
        // {
        //     Write595(Line.Array[i]);
        // }

        for (i=0;i<4;i++)
        {
            Write595(Line.Array[i]);
        }


#ifdef DEBUG
        P2=0x00;
#else
        P2=0xFF;
#endif

        Lock595();



#ifdef DEBUG
        P2=~SelectTable[CurrentLine];
#else
        P2=SelectTable[CurrentLine];
#endif

        if (CurrentLine<6)
        {
            CurrentLine++;
        } else
        {
            CurrentLine=0;
        }





        LEDState=StateLEDWait;
    }

}

void ShowStarupScreenHandler(void)
{
    char len=strlen(VER_STRING);
    if(len>5)
        len=5;
    memcpy(DisplayStr,&VER_STRING,len);
}



void ShowPointHandler(void)
{
    //static unsigned char secflag;
    //static __bit point;
    //if (secflag<DT.Second && DisplayState==StateShowTime)
    if ((DT.Second%2)==0 && DisplayState==StateShowTime)
    {
        DisplayStr[2]=':';
    } else
    {
        DisplayStr[2]=' ';
    }

}

void ShowTimeHandler(void)
{

    if (DT.Second==5)
    {
        DisplayState=StateShowYear;
    };

    ShowTwoNumbers(DT.Hour,DT.Minute); 

}

void ShowDateHandler(void)
{

    if (DT.Second==15)
    {
        DisplayState=StateShowWeek;
    };

    DisplayStr[2]='-';
    ShowTwoNumbers(DT.Month,DT.Day);

}

void ShowYearHandler(void)
{

    if (DT.Second==10)
    {
        DisplayState=StateShowDate;
    };

    ShowYearNumbers(DT.Year);

}

void ShowWeekHandler(void)
{

    if (DT.Second==20)
    {
        DisplayState=StateShowTime;
    };
    ShowWeekStr(DT.Week);
}



void SetHourHandler(void)
{
    DisplayStr[2]=':';
    NegativeNum1=1;
    ShowTwoNumbers(DT.Hour,DT.Minute);
    if (KeySetValue)
    {
        NegativeNum1=0;
        DisplayState=StateSetMinute;
    }


    if (KeyPlusValue && DT.Hour<23)
    {
        DT.Hour++;
    }

    if (KeyMinuValue && DT.Hour>=1)
    {
        DT.Hour--;
    }



}

void SetMinuteHandler(void)
{
    DisplayStr[2]=':';
    NegativeNum2=1;
    ShowTwoNumbers(DT.Hour,DT.Minute);
    if (KeySetValue)
    {
        NegativeNum2=0;
		DT.Second=0;
		DS1302_SetTime(&DT);
        DisplayState=StateShowTime;
    }


    if (KeyPlusValue && DT.Minute<59)
    {
        DT.Minute++;
    }

    if (KeyMinuValue && DT.Minute>=1)
    {
        DT.Minute--;
    }


}

void SetYearHandler(void)
{
    ShowYearNumbers(DT.Year);
    NegativeNum2=1;
    if (KeySetValue)
    {
        NegativeNum2=0;
        DisplayState=StateSetMonth;
    }


    if (KeyPlusValue && DT.Year<99)
    {
        DT.Year++;
    }

    if (KeyMinuValue && DT.Year>=1)
    {
        DT.Year--;
    }

}

void SetMonthHandler(void)
{
    DisplayStr[2]='-';
    NegativeNum1=1;
    ShowTwoNumbers(DT.Month,DT.Day);
    if (KeySetValue)
    {
        NegativeNum1=0;
        DisplayState=StateSetDay;
    }


    if (KeyPlusValue && DT.Month<12)
    {
        DT.Month++;
    }

    if (KeyMinuValue && DT.Month>1)
    {
        DT.Month--;
    }

}

void SetDayHandler(void)
{
    DisplayStr[2]='-';
    NegativeNum2=1;
    ShowTwoNumbers(DT.Month,DT.Day);
    if (KeySetValue)
    {
        NegativeNum2=0;
		DisplayState=StateSetHour;
    }


    if (KeyPlusValue && DT.Day<31)
    {
        DT.Day++;
    }

    if (KeyMinuValue && DT.Day>1)
    {
        DT.Day--;
    }

}



void BlackScreenHandler(void)
{
    DisplayStr[0]=' ';
    DisplayStr[1]=' ';
    DisplayStr[2]=' ';
	DisplayStr[3]=' ';
    DisplayStr[4]=' ';
}




int main(void)
{

    unsigned char i=0;

    DS1302_Initial();
    LEDState=StateLEDScan;
    KeySetState=StateKeyFree;
    KeyPlusState=StateKeyFree;
    KeyMinuState=StateKeyFree;
    KeyState=StateKeyScan;
    DisplayState=StateShowStarupScreen;
    StarupScreenCountDownTick=20000;
    LEDStateTick=0;
    KeyStateTick=0;
    CurrentLine=0;
    TMOD=0x01; //��ʽ1
    TH0=0xFF;  //1ms
    TL0=0x30;


    EA=1; //���ж�
    ET0=1;
    TR0=1;

    for (i=0;i<4;i++)
    {
        Write595(0x00);
    }
    Lock595();

    while (1)
    {

        LEDScanHandler();
        KeyScanHanlder();
        ShowPointHandler();


        switch (DisplayState)
        {
        case StateShowStarupScreen:
        ShowStarupScreenHandler();
            if(StarupScreenCountDownTick==0)
                DisplayState=StateShowTime;
            break;

        case StateShowTime:
            if (KeySetValue)
            {
                DisplayState=StateSetYear;
            }
			if(KeyMinuValue)
            {
                DisplayState=StateBlackScreen;
            }
            DS1302_GetTime(&DT);
            ShowTimeHandler();
            break;
        case StateShowYear:
            if (KeySetValue)
            {
                DisplayState=StateSetYear;
            }
			if(KeyMinuValue)
            {
                DisplayState=StateBlackScreen;
            }
            DS1302_GetTime(&DT);
            ShowYearHandler();
            break;
        case StateShowDate:
            if (KeySetValue)
            {
                DisplayState=StateSetYear;
            }
			if(KeyMinuValue)
            {
                DisplayState=StateBlackScreen;
            }
            DS1302_GetTime(&DT);
            ShowDateHandler();
            break;
        case StateShowWeek:
            if (KeySetValue)
            {
                DisplayState=StateSetYear;
            }
			if(KeyMinuValue)
            {
                DisplayState=StateBlackScreen;
            }
            DS1302_GetTime(&DT);
            ShowWeekHandler();
            break;
		case StateBlackScreen:
		    if (KeyPlusValue)
            {
                DisplayState=StateShowTime;
            }
			BlackScreenHandler();
			break;
        case StateSetHour:
            SetHourHandler();
            break;
        case StateSetMinute:
            SetMinuteHandler();
            break;
        case StateSetYear:
            SetYearHandler();
            break;
        case StateSetMonth:
            SetMonthHandler();
            break;
        case StateSetDay:
            SetDayHandler();
            break;
        }






    }
}