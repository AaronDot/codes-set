/*
 * databaseConfig.h
 *
 *  Created on: 2010-8-7
 *      Author: Aaron Chou
 */

#ifndef DATABASECONFIG_H_
#define DATABASECONFIG_H_

/*数据库结构定义*/
struct DatabaseConfig
{
	/*0代表无效，1代表有效*/
	int is_enable;
	/*数据库用户名*/
	char usrname[20];
	/*数据库密码*/
	char password[20];
	/*数据库服务器主机*/
	char host[20];
	char databaseName[20];
	/*数据库服务器端口*/
	unsigned short port;
} databaseConfig;

/*定义配置文件数据模型*/
struct ConfigStruct
{
	/*config中的关键字*/
	char key[50];
	/*关键字的值*/
	char value[50];
	/*链表指针*/
	struct ConfigStruct *next;
};

struct ConfigStruct *init_configStruct(void);
void freeConfig(struct ConfigStruct *head);
void addConfig(struct ConfigStruct *head, char *key, char *value);
struct ConfigStruct *getConfigBykey(struct ConfigStruct *head, char *key);

#endif /* DATABASECONFIG_H_ */
