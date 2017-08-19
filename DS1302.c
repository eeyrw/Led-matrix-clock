#include "DS1302.h"

//实时时钟写入一字节(内部函数)
void DS1302InputByte(unsigned char d)
{
	unsigned char i;
	for(i=8; i>0; i--)
	{
		DS1302_IO = d&0x01;				//相当于汇编中的 RRC
		DS1302_CLK = 1;
		DS1302_CLK = 0;
		d = d >> 1;
	}
}

//实时时钟读取一字节(内部函数)
unsigned char DS1302OutputByte(void)
{
	unsigned char i;
	unsigned char ret=0;
	for(i=8; i>0; i--)
	{
		ret = ret >>1;					//相当于汇编中的 RRC
		ret |= (DS1302_IO<<7);
		DS1302_CLK = 1;
		DS1302_CLK = 0;
	}
	return(ret);
}

//写DS1302,ucAddr: DS1302地址, ucData: 要写的数据
void Write1302(unsigned char ucAddr, unsigned char ucDa)
{
	DS1302_RST = 0;
	DS1302_CLK = 0;
	DS1302_RST = 1;
	DS1302InputByte(ucAddr);	   	// 地址，命令
	DS1302InputByte(ucDa);		 	// 写1Byte数据
	DS1302_CLK = 1;
	DS1302_RST = 0;
}

//读取DS1302某地址的数据
unsigned char Read1302(unsigned char ucAddr)
{
	unsigned char ucData;
	DS1302_RST = 0;
	DS1302_CLK = 0;
	DS1302_RST = 1;
	DS1302InputByte(ucAddr|0x01);		 // 地址，命令
	ucData = DS1302OutputByte();		 // 读1Byte数据
	DS1302_CLK = 1;
	DS1302_RST = 0;
	return(ucData);
}

//读取时间函数
void DS1302_GetTime(DateTime *Time)
{
	unsigned char ReadValue;

	ReadValue = Read1302(DS1302_SECOND);
	Time->Second = BCD2DEC(ReadValue&0x7F);

	ReadValue = Read1302(DS1302_MINUTE);
	Time->Minute = BCD2DEC(ReadValue);

	ReadValue = Read1302(DS1302_HOUR);
	Time->Hour = BCD2DEC(ReadValue&0x7F);

	ReadValue = Read1302(DS1302_DAY);
	Time->Day = BCD2DEC(ReadValue);	

	ReadValue = Read1302(DS1302_WEEK);
	Time->Week = BCD2DEC(ReadValue);

	ReadValue = Read1302(DS1302_MONTH);
	Time->Month = BCD2DEC(ReadValue);

	ReadValue = Read1302(DS1302_YEAR);
	Time->Year = BCD2DEC(ReadValue);	
}

//设置时间函数
void DS1302_SetTime(DateTime *Time)
{
	Write1302(DS1302_WRITE,0x00);		//关闭写保护
	
	Write1302(DS1302_YEAR,DEC2BCD(Time->Year));
	Write1302(DS1302_MONTH,DEC2BCD(Time->Month));
	Write1302(DS1302_WEEK,DEC2BCD(GetWeekDay(Time->Year+2000,Time->Month,Time->Day)));
	Write1302(DS1302_DAY,DEC2BCD(Time->Day));
	Write1302(DS1302_HOUR,DEC2BCD(Time->Hour)|Time_24_Hour);
	Write1302(DS1302_MINUTE,DEC2BCD(Time->Minute));
	Write1302(DS1302_SECOND,DEC2BCD(Time->Second)|Time_Start);
	
	Write1302(DS1302_WRITE,0x80);		//打开写保护	
}

unsigned char GetWeekDay(unsigned int year,unsigned char month,unsigned char day)
{
	  unsigned int j,count=0;
	  __code unsigned int MonthAdd[12] = {0,31,59,90,120,151,181,212,243,273,304,334};
	  count = MonthAdd[month-1];
	  count = count + day;
	  if((year%4 == 0&&year %100 != 0||year % 400 == 0)&& month >= 3)
		 count += 1;

	  count = count + (year - 1901) * 365;

	  for(j = 1901;j < year;j++)

	  {

		 if(j % 4 == 0 && j % 100 != 0 || j % 400 == 0)

			 count++;

	  }

	  return ((count+1) % 7);

}








//初始化DS1302
void DS1302_Initial(void)
{

if(Read1302(DS1302_SECOND)>=0x80)
{
	Write1302(DS1302_WRITE,0x00);		//关闭写保护
	Write1302(DS1302_SECOND,Time_Stop);//停止计时
	Write1302(DS1302_HOUR,Time_24_Hour);//24时制
	Write1302(DS1302_POWER,0xA5);		//单二极管,2K电阻充电

	Write1302(DS1302_YEAR,DEC2BCD(2013));
	Write1302(DS1302_MONTH,DEC2BCD(12));
	Write1302(DS1302_WEEK,DEC2BCD(GetWeekDay(2013,12,12)));
	Write1302(DS1302_DAY,DEC2BCD(12));
	Write1302(DS1302_HOUR,DEC2BCD(13)|Time_24_Hour);
	Write1302(DS1302_MINUTE,DEC2BCD(13));
	Write1302(DS1302_SECOND,DEC2BCD(13)|Time_Start);


	Write1302(DS1302_WRITE,0x80);		//打开写保护 

	}
}

