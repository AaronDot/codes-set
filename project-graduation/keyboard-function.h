#ifndef __KBFunction_H 
#define __KBFunction_H 

#include <keyboard-init.h>
#include <lcd-screen.h>

/***********************************************************************
* 函数名：KeyOfEnsure
* 入参：无
* 返回值：无
* 函数功能：确认键的功能
***********************************************************************/
void KeyOfEnsure(void)
{	
	if (flag_screen == 1) {/*监测点的选择界面--->监测点显示界面*/
		ClearScreen();
		WriteCom(0x0c); 
		select_point = 3 * count_hor_point + count_ver_point;
		PointDisplayScreen(select_point);
		count_hor_point = 0;
		count_ver_point = 0;
		key_down = 0;
	} else if (flag_screen == 3) {/*设置选项的选择界面--->数据输入界面*/
		ClearScreen();
		WriteCom(0x0c);
		select_set = 3 * count_hor_set + count_ver_set;
		PointInputScreen();
		count_ver_set = 0;
		count_hor_set = 0;
		key_down = 0;
	} else if (flag_screen == 4) {/*数据输入界面--->显示确认界面*/
		ClearScreen();
		WriteCom(0x0c);
		InputVerifyScreen();
		key_down = 0;
	} else if (flag_screen == 5) {/*确认界面--->监测点显示界面*/
		 ClearScreen();
		 before_screen = 5;
		 PointDisplayScreen(select_point);
		 point_alarm = select_point;
		 key_down = 0;
	} else if (flag_screen == 2) {/*从监测点显示--->监测点选择界面*/
		  ClearScreen();
		  SelectorOfPoScreen();
		  key_down = 0;
	}
}

/***********************************************************************
* 函数名：KeyOfDirection
* 入参：uint key -- 按下的键
* 返回值：无
* 函数功能：方向键的功能
***********************************************************************/
void KeyOfDirection(uint key)
{
	switch(key) {
	case 14:  /*右键*/
		if (count_hor_point >= 3 || count_hor_set >= 2) {
		} else {
			if (flag_screen == 1) {
				count_hor_point ++;
				SelectorOfPoScreen();
			}
			else if (flag_screen == 3) {
				count_hor_set ++;
				ClearScreen();
				PointSetScreen();
			}	
		}
		break;
	case 24:/*左键*/
		if (count_hor_point <= 0 && count_hor_set <= 0) {		
		} else {
			if (flag_screen == 1) {
				count_hor_point --;
				SelectorOfPoScreen();
			}
			else if (flag_screen == 3) {
				count_hor_set --;
				ClearScreen();
				PointSetScreen();
			}
		}
		break;
	case 34: /*上键*/
		if (count_ver_point <= 0 && count_ver_set <= 0) {	
		} else {
			if (flag_screen == 1) {
				count_ver_point --; 
				SelectorOfPoScreen();
			} else if (flag_screen == 3) {
				count_ver_set --;
				PointSetScreen();
			}
		}
		break;
	case 44: /*下键*/
		if (count_ver_point >= 2 && count_ver_set >= 2) {	
		} else {
			if (flag_screen == 1) {
				count_ver_point ++;	 
				SelectorOfPoScreen();
			} else if (flag_screen == 3) {
				 count_ver_set ++;
				 PointSetScreen();
			}
		}
		break;
	}
}

/***********************************************************************
* 函数名：KeyOfNum
* 入参：uint key -- 按下的键
* 返回值：无
* 函数功能：数字键的功能
***********************************************************************/
void KeyOfNum(uint key)
{
	num_all = Num[key];
	if (flag_screen == 4) {
		switch (select_set) {
		case 0:	/*短信温度*/
			if (num_count <= 2) {
				num_count ++;
				temp_message[select_point][num_count-1] = num_all;
				WriteData(num_all);
			} else if (num_count > 2) {
				WriteData(' ');
			}
			key_down =0;
			break;
		case 1:	/*电话温度*/
			if (num_count <= 2) {
				num_count ++;
				temp_call[select_point][num_count-1] = num_all;
				WriteData(num_all);
			} else if (num_count > 2) {
				WriteData(' ');
			}
			key_down = 0;
			break;
		case 2:	/*烟雾浓度*/
			if (num_count <= 3) {
				num_count ++;
				smoke_call[select_point][num_count-1] = num_all;
				WriteData(num_all);
			} else if (num_count > 3)
			{
				WriteData(' ');;
			}
			key_down = 0;
			break;
		case 3:	/*短信号码*/
			if (num_count <= 10) {
				num_count ++;
				phone_message[select_point][num_count-1] = num_all;
				WriteData(num_all);
			} else if (num_count > 10) {
				WriteData(' ');
			}
			key_down = 0;
			break;
		case 4:	/*打电话的号码*/
			if (num_count <= 10) {
				num_count ++;
				phone_call[num_count-1] = num_all;
				WriteData(num_all);
			} else if (num_count > 10) {
				WriteData(' ');
			}
			key_down = 0;
			break;
		}
	}
}

/***********************************************************************
* 函数名：KeyOfSet
* 入参：无
* 返回值：无
* 函数功能：设置键的功能
***********************************************************************/
void KeyOfSet(void)
{
	if (flag_screen == 2) { /*设定--设置监测点的参数*/
		ClearScreen();
		PointSetScreen();
	} else if (flag_screen == 5) { /*返回--返回到参数的选择*/
		ClearScreen();
		PointSetScreen();
	}
}
#endif
