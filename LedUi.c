#include "DS1302.h"
#include "LedUi.h"
#include "constantTable.h"
#include "Key.h"
#include "state.h"
#include "LedDisplay.h"
#include "version.h"
#include <string.h>


DateTime DT;

unsigned short StarupScreenCountDownTick;
unsigned char UiDisplayState;


void ShowTwoNumbers(unsigned char Num1, unsigned char Num2);
void ShowYearNumbers(unsigned char Num1);
void ShowWeekStr(unsigned char Num1);
void ShowStarupScreenHandler(void);
void ShowPointHandler(void);
void ShowTimeHandler(void);
void ShowDateHandler(void);
void ShowYearHandler(void);
void ShowWeekHandler(void);
void SetHourHandler(void);
void SetMinuteHandler(void);
void SetYearHandler(void);
void SetMonthHandler(void);
void SetDayHandler(void);
void BlackScreenHandler(void);


void LedUi1msProc(void)
{
    if ((StarupScreenCountDownTick != 0) && (UiDisplayState == StateShowStarupScreen))
    {
        StarupScreenCountDownTick--;
    }
}

void LedUiInit(void)
{
    UiDisplayState = StateShowStarupScreen;
    StarupScreenCountDownTick = 20000;
}

void LedUiHandler(void)
{
    if(!(UiDisplayState==StateSetHour || 
            UiDisplayState==StateSetMinute ||
            UiDisplayState==StateSetYear ||
            UiDisplayState==StateSetMonth ||
            UiDisplayState==StateSetDay))
    {
                DS1302_GetTime(&DT);
    }
        
    switch (UiDisplayState)
    {
    case StateShowStarupScreen:
        ShowStarupScreenHandler();
        if (StarupScreenCountDownTick == 0)
            UiDisplayState = StateShowTime;
        break;

    case StateShowTime:
        if (KeySetValue)
        {
            UiDisplayState = StateSetYear;
        }
        if (KeyMinuValue)
        {
            UiDisplayState = StateBlackScreen;
        }
        ShowTimeHandler();
        ShowPointHandler();
        break;
    case StateShowYear:
        if (KeySetValue)
        {
            UiDisplayState = StateSetYear;
        }
        if (KeyMinuValue)
        {
            UiDisplayState = StateBlackScreen;
        }
        ShowYearHandler();
        break;
    case StateShowDate:
        if (KeySetValue)
        {
            UiDisplayState = StateSetYear;
        }
        if (KeyMinuValue)
        {
            UiDisplayState = StateBlackScreen;
        }
        ShowDateHandler();
        break;
    case StateShowWeek:
        if (KeySetValue)
        {
            UiDisplayState = StateSetYear;
        }
        if (KeyMinuValue)
        {
            UiDisplayState = StateBlackScreen;
        }
        ShowWeekHandler();
        break;
    case StateBlackScreen:
        if (KeyPlusValue)
        {
            UiDisplayState = StateShowTime;
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

void ShowTwoNumbers(unsigned char Num1, unsigned char Num2)
{

    unsigned char *source;
    unsigned char *target;
    unsigned char i;

    source = (unsigned char *)(NumberStr2 + Num2);
    target = DisplayStr + 3;
    for (i = 0; i < 2; i++)
    {
        (*target) = (*source);
        source++;
        target++;
    }

    source = (unsigned char *)(NumberStr + Num1);
    target = DisplayStr;
    for (i = 0; i < 2; i++)
    {
        (*target) = (*source);
        source++;
        target++;
    }
}

void ShowYearNumbers(unsigned char Num1)
{

    unsigned char *source;
    unsigned char *target;
    unsigned char i;

    DisplayStr[0] = ' ';
    DisplayStr[1] = '2';
    DisplayStr[2] = '0';
    source = (unsigned char *)(NumberStr2 + Num1);
    target = DisplayStr + 3;
    for (i = 0; i < 2; i++)
    {
        (*target) = (*source);
        source++;
        target++;
    }
}

void ShowWeekStr(unsigned char Num1)
{

    unsigned char *source;
    unsigned char *target;
    unsigned char i;

    source = (unsigned char *)(WeekStr + Num1);
    target = DisplayStr;
    for (i = 0; i < 5; i++)
    {
        (*target) = (*source);
        source++;
        target++;
    }
}

void ShowStarupScreenHandler(void)
{
    char len = strlen(VER_STRING);

    if (len > 5)
        len = 5;
    memcpy(DisplayStr, &VER_STRING, len);
}

void ShowPointHandler(void)
{
    if ((DT.Second % 2) == 0 && UiDisplayState == StateShowTime)
    {
        DisplayStr[2] = ':';
    }
    else
    {
        DisplayStr[2] = ' ';
    }
}

void ShowTimeHandler(void)
{

    if (DT.Second == 5)
    {
        UiDisplayState = StateShowYear;
    };

    ShowTwoNumbers(DT.Hour, DT.Minute);
}

void ShowDateHandler(void)
{
    if (DT.Second == 15)
    {
        UiDisplayState = StateShowWeek;
    };

    DisplayStr[2] = '-';
    ShowTwoNumbers(DT.Month, DT.Day);
}

void ShowYearHandler(void)
{

    if (DT.Second == 10)
    {
        UiDisplayState = StateShowDate;
    };

    ShowYearNumbers(DT.Year);
}

void ShowWeekHandler(void)
{

    if (DT.Second == 20)
    {
        UiDisplayState = StateShowTime;
    };
    ShowWeekStr(DT.Week);
}

void SetHourHandler(void)
{
    
    DisplayStr[2] = ':';
    NegativeNum1 = 1;
    ShowTwoNumbers(DT.Hour, DT.Minute);
    if (KeySetValue)
    {
        NegativeNum1 = 0;
        UiDisplayState = StateSetMinute;
    }

    if (KeyPlusValue && DT.Hour < 23)
    {
        DT.Hour++;
    }

    if (KeyMinuValue && DT.Hour >= 1)
    {
        DT.Hour--;
    }
}

void SetMinuteHandler(void)
{
    DisplayStr[2] = ':';
    NegativeNum2 = 1;
    ShowTwoNumbers(DT.Hour, DT.Minute);
    if (KeySetValue)
    {
        NegativeNum2 = 0;
        DT.Second = 0;
        DS1302_SetTime(&DT);
        UiDisplayState = StateShowTime;
    }

    if (KeyPlusValue && DT.Minute < 59)
    {
        DT.Minute++;
    }

    if (KeyMinuValue && DT.Minute >= 1)
    {
        DT.Minute--;
    }
}

void SetYearHandler(void)
{
    ShowYearNumbers(DT.Year);
    NegativeNum2 = 1;
    if (KeySetValue)
    {
        NegativeNum2 = 0;
        UiDisplayState = StateSetMonth;
    }

    if (KeyPlusValue && DT.Year < 99)
    {
        DT.Year++;
    }

    if (KeyMinuValue && DT.Year >= 1)
    {
        DT.Year--;
    }
}

void SetMonthHandler(void)
{
    DisplayStr[2] = '-';
    NegativeNum1 = 1;
    ShowTwoNumbers(DT.Month, DT.Day);
    if (KeySetValue)
    {
        NegativeNum1 = 0;
        UiDisplayState = StateSetDay;
    }

    if (KeyPlusValue && DT.Month < 12)
    {
        DT.Month++;
    }

    if (KeyMinuValue && DT.Month > 1)
    {
        DT.Month--;
    }
}

void SetDayHandler(void)
{
    DisplayStr[2] = '-';
    NegativeNum2 = 1;
    ShowTwoNumbers(DT.Month, DT.Day);
    if (KeySetValue)
    {
        NegativeNum2 = 0;
        UiDisplayState = StateSetHour;
    }

    if (KeyPlusValue && DT.Day < 31)
    {
        DT.Day++;
    }

    if (KeyMinuValue && DT.Day > 1)
    {
        DT.Day--;
    }
}

void BlackScreenHandler(void)
{
    DisplayStr[0] = ' ';
    DisplayStr[1] = ' ';
    DisplayStr[2] = ' ';
    DisplayStr[3] = ' ';
    DisplayStr[4] = ' ';
}

