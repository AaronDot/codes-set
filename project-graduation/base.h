#ifndef _Base_H
#define _Base_H

#include <stdio.h>
#include <string.h>
#include <INTRINS.H>

/********************************************C8051f020********************************************************/
#define BAUDRATE     115200           
#define SYSCLK       22118400 
#define INT_DEC      256 
#define SAR_CLK      2500000 
#define SAMPLE_DELAY 50 
#define SAMPLE_RATE  50000

#define uchar unsigned char
#define uint unsigned int

#define POINTNUM 2			/*监测点的个数*/

/********************************************全局变量********************************************************/

uchar code Num[10] = {0x30, 0x31, 0x32, 0x33, 0x34,
		      0x35, 0x36, 0x37, 0x38, 0x39}; /*数字0——9*/

/*键盘*/
static uint count_hor_point = 0;	/*监测点的水平选择*/
static uint count_ver_point = 0;	/*监测点的垂直选择*/
static uint count_hor_set = 0;		/*设置选项的水平选择*/
static uint count_ver_set = 0;		/*设置选项的垂直选择*/
bit key_down = 0;	 		/*0-->没有按下按键，1-->按下了某个按键*/
uint select_point;			/*选择了哪一个监测点*/
uint select_set;			/*选择了什么设置选项*/

uint point_alarm;			/*循环显示时的point*/
uchar num_all;				/*输入的数据*/
static uint num_count = 0;		/*输入数据的数目*/

/*LCD*/
uchar set_choice[6][13] = {"短信报警温度",
			   "电话报警温度",
			   "烟雾报警浓度",
			   "短信报警号码",
			   "电话报警号码",
			   "            "};
uchar flag_screen = 0; 		/*当前在哪一屏*/
uchar before_screen = 0;	/*上一屏*/

/*DS18B20*/
uchar tempL,tempH; 					/*温度数据的高低位*/
uchar integer,decimals; 				/*温度整数位和小数位*/
uchar temp_message[POINTNUM][3] = {'\0'};		/*输入的短信报警温度*/
uchar temp_call[POINTNUM][3] = {'\0'}; 	  		/*输入的短信温度*/
uchar temp_buffer[POINTNUM][8] = {'\0'};		/*传感器读取的数据数组*/	
uchar code DS18B20Code[POINTNUM][8] = {{0x28,0x9D,0x56,0x21,0x03,0x00,0x00,0xF7},
					{0x28,0x17,0x50,0x21,0x03,0x00,0x00,0x4E}};

uint temp_comp_message[POINTNUM] = {50,50};		/*比较的温度，转换的*/
uint temp_comp_call[POINTNUM] = {80,80};

uint temp_comp;						/*温度比较值*/
	
/*TC35*/
uchar flag_send[POINTNUM] = 0; 		/*0表示还没有发短信，1表示已经发过短信*/
uchar flag_call[POINTNUM] = 0;		/*0表示还没有发短信，1表示已经发过短信*/
uchar phone_message[POINTNUM][12] = {{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x46},
				     {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x46}};  /*预报警电话号码转换*/
uchar phone_call[11] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};	 		 /*集中报警电话号码转换*/
uchar phone_change[12] = {0x00};  	/*存放电话号码*/
uchar phone_display[11] = {0x00};	/*显示的电话号码数组*/

/*NQ_2*/
long Result;
long measurement;
uchar smoke_call[POINTNUM][4] = {'\0'};
uchar smokp_buffer[POINTNUM][4] = {'\0'}; 
long smoke_comp[POINTNUM];	 	/*烟雾的比较值*/

/********************************************接口定义********************************************************/
/*LCD控制接口*/
#define LCDRSLow  P6&=~0x80;  		/*P6^7*/
#define LCDRSHigh P6|=0x80;
#define LCDRWLow  P6&=~0x40;  		/*P6^6*/
#define LCDRWHigh P6|=0x40;
#define LCDELow  P6&=~0x20;	  	/*P6^5*/
#define LCDEHigh P6|=0x20;
#define LCDPSBLow  P6&=~0x10;		/*P6^4*/
#define LCDPSBHigh P6|=0x10;
#define LCDRSTLow  P6&=~0x04;  		/*P6^3*/
#define LCDRSTHigh P6|=0x04;
/*LCD数据接口*/
#define Lcd_Bus    P5

/*键盘接口*/
#define KEY  P2

/*温度传感器接口*/
sbit DQ = P3^7; 

/*蜂鸣器接口*/
sbit bing=P3^5;

/*语音接口*/
sbit play_voice = P3^6;

#endif
