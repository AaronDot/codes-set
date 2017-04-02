#ifndef __MQ_2_H 
#define __MQ_2_H

#include <tool.h>

/***********************************************************************
* 函数名：ADC0_Init
* 入参：uint point -- 选择的监测点
* 返回值：无
* 函数功能：ADC0初始化
***********************************************************************/
void ADC0_Init ()
{
	ADC0CN = 0x84;
	REF0CN = 0x03;
	AMX0CF = 0x00;
	AMX0SL = 0x02;
	ADC0CF = (SYSCLK / SAR_CLK) << 3;
	ADC0CF |= 0x00;
	EIE2 |= 0x02;
}

/***********************************************************************
* 函数名：Timer3_Init
* 入参：count—— 定时器设置的初值
* 返回值：无
* 函数功能：定时器3初始化
***********************************************************************/
void Timer3_Init(int counts)
{
	TMR3CN = 0x02;
	TMR3RLL = -counts;
	TMR3L = TMR3RLL;
	EIE2 &= ~0x01;
	TMR3CN |= 0x04;
}

/***********************************************************************
* 函数名：ADC0_ISR
* 入参：无
* 返回值：无
* 函数功能：ADC0中断
***********************************************************************/
void ADC0_ISR (void) interrupt 15
{
	static uint int_dec=INT_DEC;
	static long accumulator = 0L; 

	AD0INT = 0;
	accumulator += ADC0L;
	int_dec--;
	if (int_dec == 0) {
		int_dec = INT_DEC;
		Result = accumulator >> 8;
		accumulator = 0L;
	}
}

/***********************************************************************
* 函数名：SmokToStr
* 入参：无
* 返回值：无
* 函数功能：烟雾数据整合
***********************************************************************/
void SmokToStr(void)
{
	 long measurement;

	 measurement = Result;
	 smoke_comp[select_point] = Result;
	 smokp_buffer[select_point][0] = measurement / 100 + '0';
	 smokp_buffer[select_point][1] = measurement / 10 % 10 + '0';
	 smokp_buffer[select_point][2] = measurement % 10 + '0';
	 smokp_buffer[select_point][3] = '\0';
}

#endif
