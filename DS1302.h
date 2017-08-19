#ifndef _DS1302_H_
#define _DS1302_H_
#include <8052.h>


#define  DS1302_CLK   P3_5	//ʵʱʱ��ʱ��������
#define  DS1302_IO    P3_6	//ʵʱʱ������������
#define  DS1302_RST  P3_7	//ʵʱʱ�Ӹ�λ������

#define Time_24_Hour	0x00
#define Time_Start		0x00
#define Time_Stop		0x80

#define DS1302_SECOND	0x80
#define DS1302_MINUTE	0x82
#define DS1302_HOUR		0x84
#define DS1302_WEEK		0x8A
#define DS1302_DAY		0x86
#define DS1302_MONTH	0x88
#define DS1302_YEAR		0x8C
#define DS1302_WRITE	0x8E
#define DS1302_POWER	0x90

#define BCD2DEC(X)	(((X&0x70)>>4)*10 + (X&0x0F))
#define DEC2BCD(X)	((X/10)<<4 | (X%10))

typedef struct __DateTime__
{
	unsigned char Second;
	unsigned char Minute;
	unsigned char Hour;
	unsigned char Week;
	unsigned char Day;
	unsigned char Month;
	unsigned char Year;
}DateTime;


void DS1302InputByte(unsigned char d);
unsigned char DS1302OutputByte(void);
void Write1302(unsigned char ucAddr, unsigned char ucDa);
unsigned char Read1302(unsigned char ucAddr);
void DS1302_GetTime(DateTime *Time);
void DS1302_SetTime(DateTime *Time);
void DS1302_Initial(void);
unsigned char GetWeekDay(unsigned int year,unsigned char month,unsigned char day);
#endif
