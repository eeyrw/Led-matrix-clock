#ifndef __LED_DISPLAY_H__
#define __LED_DISPLAY_H__

#define LED_MATRIX_ROW 6

extern __bit NegativeNum1;
extern __bit NegativeNum2;
extern void LEDScanHandler(void);
extern void LEDScan1msProc(void);
extern char* LEDDisplayGetBuffer(void);
extern void LEDDisplaySetNegative(unsigned char index,__bit isNegative);
extern void LEDDisplayInit(void);

#endif