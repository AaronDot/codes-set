/*
 * util.c
 *
 *  Created on: 2010-7-29
 *      Author: Aaron Chou
 */
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>
#include <stdarg.h>
#include <time.h>
#include <string.h>

/**
 * 函数名：ltrim
 * 功能：去掉字符串中的左边空格
 * 参数 ：
 *    -字符串
 * 返回值：
 *    -无
 */
void ltrim(char str[])
{
	char *p = str;
	int count = 0, i = 0;

	while (*p == ' ') {
		count++;
		p++;
	}

	if (count == 0)
		return;

	while (*p != '\0') {
		str[i] = *p;
		p++;
		i++;
	}

	str[i] = '\0';
}

/**
 * 函数名：rtrim
 * 功能：去掉字符串中的右边空格
 * 参数 ：
 *    -字符串
 * 返回值：
 *    -无
 */
void rtrim(char str[])
{
	char *p = str;
	char *q = NULL;

	while (*p == ' ')
		p++;

	while (*p != '\0') {
		if (*p == ' ') {
			q = p;
			while (*q == ' ')
				q++;
			if (*q != '\0') {
				p = q;
				continue;
			}
			*p = '\0';
			break;
		}
		p++;
	}
}

/**
 * 函数名：trim_comment
 * 功能：去掉字符串中的#字符
 * 参数 ：
 *    -字符串
 * 返回值：
 *    -无
 */
void trim_comment(char str[])
{
	char *p = str;
	while (*p != '\0') {
		if (*p == '#') {
			*p = '\0';
			break;
		}
		p++;
	}
}

/**
 * 函数名：trim_r_n
 * 功能： 去掉字符串中的\r\n
 * 参数：
 *   -字符串
 * 返回值；
 *   -无
 */
void trim_r_n(char str[])
{
	char *p = str;
	while (*p != '\0') {
		if ((*p == '\r') || (*p == '\n'))
			*p='\0';
		p++;
	}
}

/*
 * 函数名：idgenerator
 * 功能：根据时间生成一个随机数
 * 参数：
 *   -无
 * 返回值：
 *   -长整形随机数
 */
long idgenerator(void)
{
	time_t t;
	time(&t);
	return t;
}

/**
 * 函数名：freeArrayString
 * 功能：释放二维数组空间
 * 参数：
 *    -二维数组
 *    -行
 * 返回值：
 *     -无
 */
void freeArrayString(char **arrs, int rows)
{
	int32_t i;

	for (i=0; i<rows; i++)
		free(arrs[i]);

	free(arrs);
}

/**
 * 函数名：mallocArrayString
 * 功能：申请空间，二维字符数组
 * 参数：
 *   -行
 *   -列
 * 返回值：
 *   -二维字符数组
 */
char **mallocArrayString(int rows, int cols)
{
	char **commands = (char **)calloc(sizeof(char *), rows);
	int i;

	for (i=0; i<rows; i++)
		commands[i] = (char *)malloc(sizeof(char) * cols);

	return commands;
}

/**
 * 函数名：splitStringToken
 * 功能：按照token分割字符串buff，分割后的结果赋值给result中
 * 参数：
 *    -字符串
 *    -token
 *    -字符串数组
 *返回值：
 *    -无
 */
void splitStringToken(char *buff, char token, char *result[])
{
	int i = 0;
	char *p = buff;
	int j = 0;

	while ( *p != '\0') {
		if (*p != token) {
			result[i][j] = *p;
			j++;
		} else {
			result[i][j] = '\0';
			i++;
			j = 0;
			while (*(p + 1) == token)
				p++;
		}
		p++;
	}
	result[i][j] = '\0';
}

/**
 * 函数名：getTokenCount
 * 功能：获取字符串中token的个数
 * 参数：
 *   -字符串
 *   -token
 * 返回值：
 *   - token的个数
 */
int getTokenCount(char *buff, char token)
{
	char *p = buff;
	int count = 0;

	while (*p != '\0') {
		if (*p == token)
			count++;
		p++;
	}

	return count;
}

/**
 * 函数名：getString
 * 功能：实现类似gets功能，获取从键盘输入一个是字符串，
 * 参数:
 *   -可变参数
 * 返回值：
 *   -无
 */
void getString(char *const buff, ...)
{
	va_list ap;
	va_start(ap,buff);
	int length = 1024;
	char *p = buff;
	int i = 0;

	length = va_arg(ap, int);
	if (length > 1024)
		length = 1024;
	va_end(ap);
	fgets(buff, length, stdin);

	while (*p != '\0' && i < length) {
		if (*p == '\n') {
			*p = '\0';
			break;
		}
		i++;
		p++;
	}
	if (i == length)
		buff[i-1] = '\0';
}

/**
 * 函数名：getch
 * 功能：输入一个字符，无需回车键即可继续执行，返回输入字符的ascii码
 * 参数：
 *   -无
 * 返回值：
 *   -标志
 */
int getch(void)
{
	struct termios tm, tm_old;
	int fd, c;

	fd = STDIN_FILENO;
	if (tcgetattr(fd, &tm) < 0)
		return -1;

	tm_old = tm;
	cfmakeraw(&tm);
	if (tcsetattr(fd, TCSANOW, &tm) < 0)
		return -1;

	c = fgetc(stdin);
	if (tcsetattr(fd, TCSANOW, &tm_old) < 0)
		return -1;

	return c;
}

/*
 * 函数名:isValidName
 * 功能:判断用户名是否合法
 * 参数:用户名
 * 返回值:0:不合法,1:合法
 **/
int IsvalidName(char *name)
{
	char *p = name;

	if (strlen(name) < 20) {
		while (*p != '\0') {
			if ((*p > 'a' && *p < 'z') || (*p > 'A' && *p < 'Z'))
				return 1;
			p++;
		}
	}

	return 0;
}

/*
 * 函数名:isValidphone
 * 功能:判断电话号码是否合法
 * 参数:电话号码
 * 返回值:0:不合法,1:合法
 */
int IsvalidPhone(char *phone)
{
	char *p = phone;

	if (strlen(phone) == 11) {
		while (*p != '\0') {
			if (*p>'0' && *p<'9')
				return 1;
			p++;
		}
	}

	return 0;
}

/*
 * 函数名：judgeName
 * 功能：如果输入的用户名不正确，重新输入
 * 参数：
 *    -输入的用户名
 *返回值：合法用户名
 */
char *judgeName(char *name)
{
	while (!IsvalidName(name)) {
		printf("\nyour name is invalid,input again:");
		setbuf(stdin, NULL);
		scanf("%s", name);
	}

	return name;
}

/*
 * 函数名：judgePhone
 * 功能：如果输入的电话号码不正确，重新输入
 * 参数：
 *    -输入的电话号码
 *返回值：合法电话号码
 */
char *judgePhone(char *phone)
{
	while (!IsvalidPhone(phone)) {
		printf("\nyour phone is invalid,input again:");
		setbuf(stdin, NULL);
		scanf("%s", phone);
	}

	return phone;
}
