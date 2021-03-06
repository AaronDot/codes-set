#ifndef __Tc35_H 
#define __Tc35_H

#include <tool.h>

/***********************************************************************
* 函数名：AT
* 入参：无
* 返回值：无
* 函数功能：发送“AT”命令
***********************************************************************/
void AT(void)				
{
	uchar code mode[4] = {0x41, 0x54, 0X0D, 0x0A};	/*AT回车*/
	uint i;

	for (i=0; i<4; i++) {
		SBUF0 = mode[i];
		while(!TI0);
		TI0 = 0;
	}
}

/***********************************************************************
* 函数名：CMGF
* 入参：无
* 返回值：无
* 函数功能：发送“AT+CMGF=0”指令  设置短信格式
***********************************************************************/
void CMGF(void)			
{
	uchar code mode[11] = {0x41, 0x54, 0x2B, 0x43, 0x4D,
			       0x47, 0x46, 0x3D, 0x30, 0x0D, 0x0A};	/*AT+CMGF=0回车*/
	uint i;

	for (i=0; i<11; i++) {
		SBUF0 = mode[i];
		while (!TI0) ;
		TI0 = 0;
	}
}

/***********************************************************************
* 函数名：CMGS
* 入参：无
* 返回值：无
* 函数功能：发送“AT+CMGS=41”指令	 发送短信
***********************************************************************/
void CMGS(void)		
{
	uchar code mode[12] = {0x41, 0x54, 0x2B, 0x43, 0x4D, 0x47,
			       0x53, 0x3D, 0x34, 0x31, 0x0D, 0x0A};	/*AT+CMGS=41回车*/
	uint i;

	for (i=0; i<12; i++) {
		SBUF0 = mode[i];
		while (!TI0) ;
		TI0 = 0;
     }
}

/***********************************************************************
* 函数名：SendGSMHead
* 入参：无
* 返回值：无
* 函数功能：发送GSM头序列
***********************************************************************/
void SendGSMHead(void)
{
	uchar code mode[12] = {0x30, 0x30, 0x31, 0x31, 0x30, 0x30,
			       0x30, 0x44, 0x39, 0x31, 0x36, 0x38};
	uint i;

	for (i=0; i<12; i++) {
		SBUF0 = mode[i];
		while (!TI0) ;
		TI0 = 0;
	}
}

/***********************************************************************
* 函数名：SendPhoneNum
* 入参：无
* 返回值：无
* 函数功能：电话号码发送
***********************************************************************/
void SendPhoneNum(void)		  
{
	uint i;
	for (i=0; i<12; i++) {
		SBUF0 = phone_change[i];
		while (!TI0) ;
		TI0 = 0;
	}
}

/***********************************************************************
* 函数名：Pdu2
* 入参： 无
* 返回值： 无
* 函数功能： 短信内容
***********************************************************************/
void SendText(void)
{
	uchar code mode[63] = {0x30, 0x30, 0x30, 0x38, 0x30, 0x31, 0x31, 0x38,		/*00080118*/
			       0x35, 0x43, 0x34, 0x42,					/*屋*/
			       0x35, 0x31, 0x38, 0x35,					/*内*/
			       0x36, 0x37, 0x30, 0x39,					/*有*/
			       0x37, 0x30, 0x36, 0x42,					/*火*/
			       0x36, 0x30, 0x43, 0x35,					/*情*/
			       0x46, 0x46, 0x30, 0x43,					/*，*/
			       0x38, 0x42, 0x46, 0x37,					/*请*/
			       0x39, 0x30, 0x31, 0x46,					/*速*/
			       0x35, 0x36, 0x44, 0x45,					/*回*/
			       0x35, 0x42, 0x44, 0x46,					/*察*/
			       0x37, 0x37, 0x30, 0x42,					/*看*/
			       0x46, 0x46, 0x30, 0x31,					/*！*/
			       0x30, 0x30, 0x32, 0x31,					/*0021*/
			       0x1A, 0x0D, 0x0A						/*Ctrl+Z,回车,换行*/
			       };
	uint i;

	for (i=0; i<63; i++) {
		SBUF0 = mode[i];
		while (!TI0) ;
		TI0 = 0;
	}
}

/***********************************************************************
* 函数名：Change
* 入参：无
* 返回值：无
* 函数功能：转换电话号码
***********************************************************************/
void Change(uchar phone_all[])
{	
	phone_change[0] = phone_all[1];
	phone_change[1] = phone_all[0];
	phone_change[2] = phone_all[3];
	phone_change[3] = phone_all[2];
	phone_change[4] = phone_all[5];
	phone_change[5] = phone_all[4];
	phone_change[6] = phone_all[7];
	phone_change[7] = phone_all[6];
	phone_change[8] = phone_all[9];
	phone_change[9] = phone_all[8];
	phone_change[10] = phone_all[11];
	phone_change[11] = phone_all[10];
}

/***********************************************************************
* 函数名：SendMessage
* 入参：无
* 返回值：无
* 函数功能：发短信
***********************************************************************/
void SendMessage(void)
{
	Change(phone_message[select_point]);
	AT();
	delay1ms(5000); delay1ms(5000);
	CMGF();
	delay1ms(5000); delay1ms(5000);
	CMGS();
	delay1ms(1000);
	SendGSMHead();
	SendPhoneNum();
	SendText();
}

/***********************************************************************
* 函数名：Call
* 入参：无
* 返回值：无
* 函数功能：ATD"15193115590+";回车	（打电话）
***********************************************************************/
void Call(void)        
{
	uchar j;
	uint i;
	uchar cell[20] = {0x41, 0x54, 0x44, 0x22,						/*ATD"*/
			  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,	/*电话号码*/
			  0x2B, 0x22, 0x3B,  							/*+";*/
			  0x0D, 0x0A};					   			/*回车*/

	for (j=0; j<=10; j++)	/*在指令中填充电话号码*/
		cell[j+4] = phone_call[j];
	for (i=0; i<20; i++) {
		SBUF0 = cell[i];
		while (!TI0) ;
		TI0 = 0;
	}				
}

#endif
