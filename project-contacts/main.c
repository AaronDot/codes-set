/*
 * Main.c
 *
 *  Created on: 2010-7-29
 *      Author: Aaron Chou
 */

#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include "include/contactType.h"
#include "include/contactDao.h"
#include "include/contactMenu.h"
#include "include/contactView.h"
#include "include/config.h"
#include "include/util.h"

/**
 * 函数名：init_system
 * 功能：系统初始化，读取配置文件，初始化系统环境
 * fileSystemConfig：文件数据存储环境
 * databaseConfig：数据库存储环境
 * 参数：
 *   -无
 * 返回值：
 *   -无
 */
void init_system(void)
{
	FILE *fp;
	char line[512];		/*存储配置文件各行数据*/
	char **options;
	int port;
	struct ConfigStruct *configNode = NULL;
	struct ConfigStruct *configHead = NULL;
	char *configPath = "./config";
	extern struct FileConfig fileSystemConfig;
	extern struct DatabaseConfig databaseConfig;

	fp = fopen(configPath, "rb");

	if (fp == NULL) {
		/*输出错误*/
		perror("config file error\n");
		fileSystemConfig.is_enable = 0;
		databaseConfig.is_enable = 0;
		return;
	}

	/*初始化配置文件链表头指针*/
	configHead = init_configStruct();
	/*循环读取配置文件*/
	do {
		fgets(line, 512, fp);
		/*去掉结尾的\r\n*/
		trim_r_n(line);
		/*去掉注释*/
		trim_comment(line);
		/*继续解析*/
		if(strlen(line) == 0)
			continue;

		/*初始化配置项链表*/
		options = mallocArrayString(2, 20);
		/*按照=分隔字符串*/
		splitStringToken(line, '=', options);
		/*去掉options[0]右边的空格*/
		rtrim(options[0]);
		/*去掉options[0]左边的空格*/
		ltrim(options[0]);
		/*去掉options[1]右边的空格*/
		rtrim(options[1]);
		/*去掉options[1]左边的空格*/
		ltrim(options[1]);

		printf("%s=%s\n", options[0], options[1]);
		addConfig(configHead, options[0], options[1]);

		freeArrayString(options, 2);
	} while(!feof(fp));

	configNode = getConfigBykey(configHead, "host");
	strcpy(databaseConfig.host, configNode->value);

	configNode = getConfigBykey(configHead, "username");
	strcpy(databaseConfig.usrname, configNode->value);

	configNode = getConfigBykey(configHead, "password");
	strcpy(databaseConfig.password, configNode->value);

	configNode = getConfigBykey(configHead, "databaseName");
	strcpy(databaseConfig.databaseName, configNode->value);

	configNode = getConfigBykey(configHead, "port");

	port = atoi(configNode->value);
	databaseConfig.port = (unsigned short)port;
	configNode = getConfigBykey(configHead, "databaseEnable");
	if (strcmp(configNode->value, "yes") == 0)
		databaseConfig.is_enable = 1;
	else
		databaseConfig.is_enable = 0;

	configNode = getConfigBykey(configHead, "filePath");
	strcpy(fileSystemConfig.filePath, configNode->value);

	configNode = getConfigBykey(configHead, "exportPath");
	strcpy(fileSystemConfig.exportPath, configNode->value);

	configNode = getConfigBykey(configHead,"fileSystemEnable");
	if (strcmp(configNode->value, "yes") == 0)
		fileSystemConfig.is_enable = 1;
	else
		fileSystemConfig.is_enable = 0;

	freeConfig(configHead);
}

int main(void) 
{
	init_system();
	Contact *head = init_LinkList();
	/*当执行文件系统时*/
	if (fileSystemConfig.is_enable)
		/*初始化,读取数据文件，建立初始链表。*/
		readContact(head);
	/*显示菜单*/
	displayMenu(head);
	if (head != NULL)
		free(head);

	return EXIT_SUCCESS;
}
