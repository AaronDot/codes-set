#include <c8051f020.h>
#include <keyboard-function.h>
#include <DS18B20-function.h>
#include <tc35-init.h>
#include <mq2-init.h>
#include <alarm.h>

/***********************************************************************
* 函数名：main
* 入参：无
* 返回值：0
* 函数功能：主函数
***********************************************************************/
int main(void)
{
	uint key = 100;
	WDTCN = 0xde;				/*关闭看门狗*/
	WDTCN = 0xad;
	SysclkInit();                   	/*晶振配置*/
	PortInit();				/*端口初始化*/
	Timer3_Init(SYSCLK / SAMPLE_RATE);	/*定时器3初始化*/
	ADC0_Init(); 				/*ADC0初始化*/
	LCDInit();				/*LCD初始化*/
	delay_DS(50);                       
	AD0EN = 1;                   		       
	EA = 1;
	bing = 0;
	play_voice = 0;
	WelcomeScreen();
	delay1ms(5000); delay1ms(5000);delay1ms(5000);
	ClearScreen();
	SelectorOfPoScreen();
	while (1) {
		key = ScanKey();
		/*有键按下*/
		if (key_down == 1) {
			/*判断是什么键*/
			if (key < 10 && key >= 0)	/*数字键*/
				KeyOfNum(key);
			else if (key % 10 == 4)		/*方向键*/
				KeyOfDirection(key);
			else
				if (key == 43)		/*确认键*/
					KeyOfEnsure();
				else if (key == 41)	/*设定/返回键*/
					KeyOfSet();
		} else if (key_down == 0) {		/*报警*/
			AlarmAll();
		}
	}
	delay1ms(1000);

	return 0;
}
