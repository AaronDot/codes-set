#ifndef __DSFunction_H 
#define __DSFunction_H

#include <DS18B20-init.h>

/***********************************************************************
* 函数名：B20MatchRom
* 入参：uint point---监测点
* 返回值：无
* 函数功能：Ds18b20匹配ROM
***********************************************************************/
void B20MatchRom(uint point)	 
{
	uchar j;
	DS16B20Start();
	WriteOneByte(0x55);	/*发送匹配ROM命令*/
	/*监测点*/
	for (j=0; j<8; j++)
		WriteOneByte(DS18B20Code[point][j]);	/*发送18B20的序列号*/
}

/***********************************************************************
* 函数名：ReadTemperature
* 入参：无
* 返回值：无
* 函数功能：Ds18b20读温度函数
***********************************************************************/
uchar ReadTemperature(uint point)
{
	uchar t;

	DS16B20Start();
	B20MatchRom(point);	/*匹配ROM*/
	WriteOneByte(0x44);	/*启动温度转换*/
	DS16B20Start();
	delay_DS(500);
	B20MatchRom(point);	/*匹配ROM*/	
	WriteOneByte(0xBE);	/*读温度寄存器（头两个值分别为温度的低位和高位）*/
	tempL = ReadOneByte();	/*低位温度*/
	tempH = ReadOneByte();	/*高位温度*/
	t = (tempH & 0xf8);

	return t;                                    
}

/***********************************************************************
* 函数名：TempToStr
* 入参：无
* 返回值：无
* 函数功能：Ds18b20温度数据整合
***********************************************************************/
void TempToStr(uint point)
{	
	uchar temp;

	temp = ReadTemperature(point);
	if (temp) {/*温度为负*/ 
		temp_buffer[point][0] = '-';
		integer = tempH << 4;
		integer += (tempL & 0xf0) >> 4;  
		integer = ~integer + 1;
		decimals = ~tempL & 0x0f;
	} else {
		integer = tempH << 4;
		integer += (tempL & 0xf0) >> 4; 
		decimals = tempL & 0x0f;
		temp_buffer[point][0] = integer / 100 + '0';	/*百位*/
		if (temp_buffer[point][0] == '1') {
			temp_buffer[point][0] = '1';
		} else {
			temp_buffer[point][0] = ' ';
		} 
	}
	temp_comp = integer;
	temp_buffer[point][1] = integer % 100 / 10 + '0';	/*十位*/
	temp_buffer[point][2] = integer % 10 + '0';  		/*个位*/
	temp_buffer[point][3] = '.';
	temp_buffer[point][4] = decimals * 625 / 1000 % 10 + '0';
	temp_buffer[point][5] = decimals * 625 / 100 % 10 + '0';
	temp_buffer[point][6] = decimals * 625 / 10 % 10 + '0';
	temp_buffer[point][7] = '\0';	
}

#endif
