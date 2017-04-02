#ifndef __LCDScreen_H 
#define __LCDScreen_H

#include <lcd-init.h>

/***********************************************************************
* 函数名：WriteComPosLcd
* 入参：uchar x -- LCD的x坐标
	uchar y -- LCD的y坐标
	uchar Com -- 要写入的命令 
* 返回值：无
* 函数功能：在指定的坐标写入命令
***********************************************************************/
void WriteComPosLcd(uchar x, uchar y, uchar Com)
{
	LocationScreen(x, y);
	WriteCom(Com);
} 

/***********************************************************************
* 函数名：LcmClearTXT
* 入参：无
* 返回值：无
* 函数功能：清屏
***********************************************************************/
void ClearScreen(void)
{
	uchar i;

	WriteCom(0x30);
	WriteCom(0x80);
	for(i=0; i<64; i++)
		WriteData(0x20);
	LocationScreen(0, 0);  
}

/***********************************************************************
* 函数名：WelcomeScreen		  ---屏一
* 入参：无
* 返回值：无
* 函数功能：首页界面显示
***********************************************************************/
void WelcomeScreen(void)
{
	DisplayBuffer(0x90, "智能楼宇单元火灾");
	DisplayBuffer(0x8A, "报警系统");
}

/***********************************************************************
* 函数名：SelectorOfPoScreen	---屏二
* 入参：无
* 返回值：无
* 函数功能：监测点选择界面
***********************************************************************/
void SelectorOfPoScreen(void)
{
	uint Dis1, Dis2, Dis3;

	DisplayBuffer(0x80, "监测点");
	DisplayBuffer(0x90, "监测点");
	DisplayBuffer(0x88, "监测点");
	
	Dis1 = count_hor_point * 3;
	Dis2 = count_hor_point * 3 + 1;
	Dis3 = count_hor_point * 3 + 2;

	WriteCom(0x83);
	WriteData(Dis1 + '0');
	WriteCom(0x93);
	WriteData(Dis2 + '0');
	WriteCom(0x8B);
	WriteData(Dis3 + '0');

   	DisplayBuffer(0x99, "←");
	DisplayBuffer(0x9D, "→");
	WriteComPosLcd(count_ver_point, 0x05, 0x0f);
	flag_screen = 1;
}

/***********************************************************************
* 函数名：PointDisplayScreen	---屏三
* 入参： uint point_p -- 选择的监测点编号
* 返回值：无
* 函数功能：监测点数据显示界面
***********************************************************************/
void PointDisplayScreen(uint point_p)
{
	uchar danwei[4] = "ppm";

	DisplayBuffer(0x82, "监测点");
	WriteCom(0x85);
	WriteData(point_p + '0');
	DisplayBuffer(0x88, "Temp:");
	DisplayBuffer(0x98, "Smog:");
	DisplayBuffer(0x8F, "℃");	
	DisplayBuffer(0x9E, danwei);
	DisplayBuffer(0x86, "    ");
	/*读取显示的数据*/
	DisplayBuffer(0x8B, temp_buffer[point_p]);
    	DisplayBuffer(0x9C, smokp_buffer[point_p]);
	flag_screen = 2;
}

/***********************************************************************
* 函数名：PointSetScreen	---屏四
* 入参：无
* 返回值：无
* 函数功能：监测点设置选择界面
***********************************************************************/
void PointSetScreen(void)
{
	uint Dis1,Dis2,Dis3;
	
	Dis1 = count_hor_set * 3;
	Dis2 = count_hor_set * 3 + 1;
	Dis3 = count_hor_set * 3 + 2;
	DisplayBuffer(0x80, set_choice[Dis1]);
	DisplayBuffer(0x90, set_choice[Dis2]);
	DisplayBuffer(0x88, set_choice[Dis3]);
	 	
	DisplayBuffer(0x99, "←");
	DisplayBuffer(0x9D, "→");
	WriteComPosLcd(count_ver_set, 0x06, 0x0f);
	flag_screen = 3;	
}

/***********************************************************************
* 函数名：PointInputScreen	---屏五
* 入参：无
* 返回值：无
* 函数功能：数据输入界面
***********************************************************************/
void PointInputScreen(void)
{
	DisplayBuffer(0x80, set_choice[select_set]);
	WriteCom(0x90);
	flag_screen = 4;
}

/***********************************************************************
* 函数名：InputVerifyScreen	---屏六
* 入参：无
* 返回值：无
* 函数功能：数据输入的确认界面
***********************************************************************/
void InputVerifyScreen(void)
{
	DisplayBuffer(0x80, "输入：");
	switch (select_set) {
	case 0:	/*短信温度*/
		temp_comp_message[select_point] = Conver(temp_message[select_point]);
		DisplayBuffer(0x91, temp_message[select_point]);
		break;
	case 1:	/*电话温度*/
		temp_comp_call[select_point] = Conver(temp_call[select_point]);
		DisplayBuffer(0x91, temp_call[select_point]);
		break;
	case 2:	/*烟雾浓度*/
		DisplayBuffer(0x91, smoke_call[select_point]);
		break;
	case 3:	/*短信电话号码*/
		CopyPhone(phone_display, phone_message[select_point], 11);
		DisplayBuffer(0x8A, phone_display);
		break;
	case 4:	/*打电话的号码*/
		CopyPhone(phone_display, phone_call, 11);
		DisplayBuffer(0x8A, phone_display);
		break;
	}
	DisplayBuffer(0x9B, "设置成功！");
	num_count = 0;
	flag_screen = 5;
}

#endif
