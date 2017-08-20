#include "Key.h"
#include "state.h"
#include <8052.h>

#define KeySetPin P1_0
#define KeyPlusPin P1_1
#define KeyMinuPin P1_2

unsigned char KeyStateTick;
unsigned char KeyState;

unsigned char KeySetState;
unsigned char KeyPlusState;
unsigned char KeyMinuState;

__bit KeySetValue = 0;
__bit KeyPlusValue = 0;
__bit KeyMinuValue = 0;

void KeyScanHanlder(void)
{
    __bit TempKeyValue;

    if (KeyState == StateKeyScan)
    {
        TempKeyValue = KeySetPin;
        KeySetValue = 0;
        switch (KeySetState)
        {
        case StateKeyFree:
            if (!KeySetPin)
            {
                KeySetState = StateKeyPress;
            }
            break;
        case StateKeyPress:
            if (!TempKeyValue)
            {
                KeySetState = StateKeyRelease;
                KeySetValue = 1;
            }
            else
            {
                KeySetState = StateKeyFree;
            }
            break;
        case StateKeyRelease:

            if (TempKeyValue)
            {
                KeySetState = StateKeyFree;
            }
            break;
        }

        TempKeyValue = KeyPlusPin;
        KeyPlusValue = 0;
        switch (KeyPlusState)
        {
        case StateKeyFree:
            if (!KeyPlusPin)
            {
                KeyPlusState = StateKeyPress;
            }
            break;
        case StateKeyPress:
            if (!TempKeyValue)
            {
                KeyPlusState = StateKeyRelease;
                KeyPlusValue = 1;
            }
            else
            {
                KeyPlusState = StateKeyFree;
            }
            break;
        case StateKeyRelease:

            if (TempKeyValue)
            {
                KeyPlusState = StateKeyFree;
            }
            break;
        }

        TempKeyValue = KeyMinuPin;
        KeyMinuValue = 0;
        switch (KeyMinuState)
        {
        case StateKeyFree:
            if (!KeyMinuPin)
            {
                KeyMinuState = StateKeyPress;
            }
            break;
        case StateKeyPress:
            if (!TempKeyValue)
            {
                KeyMinuState = StateKeyRelease;
                KeyMinuValue = 1;
            }
            else
            {
                KeyMinuState = StateKeyFree;
            }
            break;
        case StateKeyRelease:

            if (TempKeyValue)
            {
                KeyMinuState = StateKeyFree;
            }
            break;
        }

        KeyState = StateKeyWait;
    }
}


void KeyScan1msProc(void)
{
    if ((KeyStateTick != 0) && (KeyState == StateKeyWait))
    {
        KeyStateTick--;
    }
    if (KeyStateTick == 0)
    {
        KeyState = StateKeyScan;
        KeyStateTick = 1;
    }
}

void KeyInit(void)
{
    KeySetState = StateKeyFree;
    KeyPlusState = StateKeyFree;
    KeyMinuState = StateKeyFree;
    KeyState = StateKeyScan;
}