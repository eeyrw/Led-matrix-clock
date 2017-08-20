#ifndef __KEY_H__
#define __KEY_H__


extern __bit KeySetValue;
extern __bit KeyPlusValue;
extern __bit KeyMinuValue;

extern void KeyScanHanlder(void);
extern void KeyScan1msProc(void);
extern void KeyInit(void);

#endif