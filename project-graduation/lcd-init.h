#ifndef __LCDInit_H 
#define __LCDInit_H

#include <tool.h>

/***********************************************************************
* 函数名：WriteCom
* 入参：cmdcode -- 要写入的命令
* 返回值：无
* 函数功能：液晶写命令
***********************************************************************/
void WriteCom(uchar cmdcode)
{
	LCDRSLow;		    
	LCDRWLow;
	LCDEHigh;
	Lcd_Bus = cmdcode;
	DelayLCD(5);	/*在数据写入的时候加入适当的延时*/
	LCDELow;
	DelayLCD(5);
}

/***********************************************************************
* 函数名：WriteData
* 入参：Dispdata -- 要写入的数据
* 返回值：无
* 函数功能：液晶写数据
***********************************************************************/
void WriteData(uchar Dispdata)
{
	LCDRSHigh;
	LCDRWLow;
	LCDEHigh;
	Lcd_Bus = Dispdata;
	DelayLCD(5);	/*在数据写入的时候加入适当的延时*/
	LCDELow;
	DelayLCD(5); 
}

/***********************************************************************
* 函数名：LCDInit
* 入参：无
* 返回值：无
* 函数功能：液晶复位初始
***********************************************************************/
void LCDInit(void)
{
	DelayLCD(5);
	WriteCom(0x30);	/*选择基本指令集*/
	DelayLCD(5);
	WriteCom(0x30);	/*选择8bit数据流*/
	DelayLCD(5);
	WriteCom(0x0c);	/*开显示(无游标,不反白)*/
	DelayLCD(5);
	WriteCom(0x01);	/*清除显示,并且设定地址指针为00H*/
	DelayLCD(5);
	WriteCom(0x06);	/*指定在资料的读取及写入时,设定游标的移动方向及指定显示的移位*/
}

/***********************************************************************
* 函数名：DisplayBuffer
* 入参：addr -- 要写入的位置
*       str	-- 要写入的字符串
* 返回值：无
* 函数功能：液晶显示字符串
***********************************************************************/
void DisplayBuffer(uchar addr,uchar *str)
{
	uchar i;

	WriteCom(addr);
	for (i=0; i<strlen(str); i++)
		WriteData(str[i]);
}

/***********************************************************************
* 函数名：Location_xy_12864
* 入参：x -- 横坐标
*       y -- 纵坐标
* 返回值：无
* 函数功能：设定光标，定位 ，用于清屏
***********************************************************************/
void LocationScreen(uchar x,uchar y)
{
	switch (x) {
	case 0:
		x = 0x80;
		break;
	case 1:
		x = 0x90;
		break;
	case 2:
		x = 0x88;
		break;
	case 3:
		x = 0x98;
		break;
	default:
		x = 0x80;
	}
	WriteCom(y+x);
}

#endif
