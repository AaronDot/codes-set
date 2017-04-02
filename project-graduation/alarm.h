 #ifndef __Alarm_H 
 #define __Alarm_H

/***********************************************************************
* 函数名：AlarmAll
* 入参：无
* 返回值：无
* 函数功能：报警功能
***********************************************************************/
void AlarmAll(void)
{
	uchar i;
	/*循环显示各个监测点的数据*/
	if (flag_screen == 2 && before_screen == 5) {
		TempToStr(point_alarm);
		SmokToStr();
		PointDisplayScreen(point_alarm);
		/*短信报警*/
		if(temp_comp >= temp_comp_message[point_alarm] &&
				temp_comp < temp_comp_call[point_alarm] &&
				flag_send[point_alarm] == 0) {
			P4 = 0xf0;
			DisplayBuffer(0x86, "报警");
			bing = 1;
			SendMessage(); /*发短信*/
			delay1ms(500);
			flag_send[point_alarm] = 1;
		} else if ((temp_comp >= temp_comp_call[point_alarm] ||
				smoke_comp[point_alarm] >= 255) &&
				flag_call[point_alarm] == 0) { /*电话报警*/
			P4 = 0xf0;
			DisplayBuffer(0x86, "报警");
			bing = 1;
			Call();	/*打电话*/
			for (i=0; i<3; i++) {	
				delay1ms(5000); delay1ms(5000); delay1ms(5000);
				delay1ms(5000); delay1ms(5000); delay1ms(5000);
				delay1ms(5000); delay1ms(5000); delay1ms(5000);
				delay1ms(5000); delay1ms(5000); delay1ms(5000);
				delay1ms(5000); delay1ms(5000); delay1ms(5000);
				delay1ms(5000); delay1ms(5000); delay1ms(5000);
				play_voice = 1;		/*播放语音*/
				delay1ms(5000); delay1ms(5000); delay1ms(5000);
				delay1ms(5000); delay1ms(5000); delay1ms(5000);
				delay1ms(5000); delay1ms(5000); delay1ms(5000);
				delay1ms(5000); delay1ms(5000); delay1ms(5000);
				delay1ms(5000); delay1ms(5000); delay1ms(5000);
				delay1ms(5000); delay1ms(5000); delay1ms(5000);
				play_voice = 0;
			}
			flag_call[point_alarm] = 1;
		} else {	/*不报警，循环显示监测点数据*/
			bing = 0;
			point_alarm ++;
			if (point_alarm > POINTNUM-1)
				point_alarm = 0;
			delay1ms(5000); delay1ms(5000); delay1ms(5000);
		}
	} else if (flag_screen == 2 && before_screen != 5) {	/*只显示选中的监测点的数据*/
		P4 = 0xff;
		TempToStr(select_point);
		SmokToStr();
		PointDisplayScreen(select_point);
	}
}

#endif
