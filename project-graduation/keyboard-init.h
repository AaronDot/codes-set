#ifndef __KeyBoard_H 
#define __KeyBoard_H

#include <tool.h>

/***********************************************************************
* 函数名：ScanKey
* 入参：无
* 返回值：无
* 函数功能：扫描键盘，看是否有键按下
***********************************************************************/
uint ScanKey(void)
{
	uint temp;
	uint value;

	/*扫描键盘第一行*/
	KEY = 0xfe;
	temp = KEY;
	temp = temp&0xf0;
	if (temp != 0xf0) {
		delay_DS(500);
		temp = KEY;
		temp = temp&0xf0;
		if (temp != 0xf0) {/*取消键盘抖动*/
			delay_DS(500);
			temp = KEY;
			switch(temp) {
			case 0xee:	/*第一行第一列被按下 显示1*/
				key_down = 1;
				value = 1;
				break;
			case 0xde:	/*第一行第二列被按下 显示2*/
				key_down = 1;
				value = 2;
				break;
			case 0xbe:	/*第一行第三列被按下 显示3*/
				key_down = 1;
				value = 3;
				break;
			case 0x7e:	/*第一行第四列被按下  →  */
				key_down = 1;
				value = 14;
				break;
			default:
				value = 100;
				break;
			}
			while (temp != 0xf0) {	/*取消键盘抖动*/
				temp = KEY;
				temp = temp & 0xf0;
			}
		}
	}
	/*扫描键盘第二行*/
	KEY = 0xfd;
	temp = KEY;
	temp = temp&0xf0;
	if (temp != 0xf0) {	/*取消键盘抖动*/
		delay_DS(500);
		temp = KEY;
		temp = temp&0xf0;
		if (temp != 0xf0) {
			delay_DS(500);
			temp = KEY;
			switch (temp) {
			case 0xed:	/*第二行第一列被按下 显示4*/
				key_down = 1;
				value = 4;
				break;
			case 0xdd:	/*第二行第二列被按下 显示5*/
				key_down = 1;
				value = 5;
				break;
			case 0xbd:	/*第二行第三列被按下 显示6*/
				key_down = 1;
				value = 6;
				break;
			case 0x7d:	/*第二行第四列被按下   ←  */
				key_down = 1;
				value = 24;
				break;
			default:
				value = 100;
				break;
			}
			while (temp != 0xf0) {	/*取消键盘抖动*/
				temp = KEY;
				temp = temp & 0xf0;
			}
		}
	}
	/*扫描键盘第三行*/
	KEY = 0xfb;
	temp = KEY;
	temp = temp&0xf0;
	if (temp != 0xf0) {	/*取消键盘抖动*/
		delay_DS(500);
		temp = KEY;
		temp = temp&0xf0;
		if (temp != 0xf0) {
			delay_DS(500);
			temp = KEY;
			switch (temp) {
			case 0xeb:	/*第三行第一列被按下 显示7*/
				key_down = 1;
				value = 7;
				break;
			case 0xdb:	/*第三行第二列被按下 显示8*/
				key_down = 1;
				value = 8;
				break;
			case 0xbb:	/*第三行第三列被按下 显示9*/
				key_down = 1;
				value = 9;
				break;
			case 0x7b:	/*第三行第四列被按下  ↑  */
				key_down = 1;
				value = 34;
				break;
			default:
			  	value = 100;
				break;
			}
			while (temp != 0xf0) {	/*取消键盘抖动*/
				temp = KEY;
				temp = temp & 0xf0;
			}
		}
	}
	/*扫描键盘第四行*/
	KEY = 0xf7;
	temp = KEY;
	temp = temp&0xf0;
	if (temp != 0xf0) {	/*取消键盘抖动*/
		delay_DS(500);
		temp = KEY;
		temp = temp&0xf0;
		if (temp != 0xf0) {
			delay_DS(500);
			temp = KEY;
			switch (temp) {
			
			case 0xe7:	/*第四行第一列被按下 设定/返回键*/
				key_down = 1;
				value = 41;
				break;
			case 0xd7:	/*第四行第二列被按下 显示0*/
				key_down = 1;
				value = 0;
				break;
			case 0xb7:	/*第四行第三列被按下 确定键*/
				/*在确定界面再次按下key_down = 0*/			
				key_down = 1;
				value = 43;
				break;
			case 0x77:	/* 第四行第四列被按下  ↓  */
				key_down = 1;
				value = 44;
				break;
			default:
		        	value = 100;
				break;
			}
			while (temp != 0xf0) {	/*取消键盘抖动*/
				temp = KEY;
				temp = temp & 0xf0;
			}
		}
	}

	return value;
}

#endif
