/*
 * contactDatabasDao.c
 *
 *  Created on: 2010-8-7
 *      Author: Aaron Chou
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
#include "include/contactType.h"
#include "include/config.h"
#include "include/util.h"

/*
 * 函数名：getAllContactFromDatabase
 * 功能：读取数据库中的所有数据
 * 参数：
 *    -无
 * 返回值：
 *    -链表头指针
 */
Contact *getAllContactFromDatabase(void)
{
	MYSQL mysql;					/*建立数据库链接句柄*/
	MYSQL *conn;
	MYSQL_RES *res;					/*result set*/
	MYSQL_ROW row;					/*row data*/
	char *sql = NULL;

	Contact *head=init_LinkList();
	mysql_init(&mysql);
	/*define the database*/
	conn = mysql_real_connect(&mysql,
				databaseConfig.host,
				databaseConfig.usrname,
				databaseConfig.password,
				databaseConfig.databaseName,
				databaseConfig.port,
				NULL,
				0);

	if (conn != NULL) {		/*connect successfully*/
		sql = "select * from contact";	/*do the sql*/

		if (!mysql_real_query(&mysql, sql, strlen(sql))) {	/*success*/
			res = mysql_store_result(&mysql);	/*get the result set*/
			while ((row = mysql_fetch_row(res)) != NULL)	/*get one of the result set's row */
				head = addWhitNameAndphone(head, row[1], row[2]);	/*the data of the row*/
			mysql_free_result(res);	/*free the result set*/
		}
	}
	/*close the database*/
	mysql_close(&mysql);

	return head;
}

/*
 * 函数名：addDatabase
  * 功能：向数据库中添加信息
 * 参数：
 *   -链表指针
 *返回值：
 *    -无
 */
void addDatabase(Contact *node)
{
	MYSQL mysql;
	MYSQL *conn;
	char sql[512];

	mysql_init(&mysql);
	conn = mysql_real_connect(&mysql,
				databaseConfig.host,
				databaseConfig.usrname,
				databaseConfig.password,
				databaseConfig.databaseName,
				databaseConfig.port,
				NULL,
				0);

	if (conn != NULL) {
		strcpy(sql, "insert into contact values (default,'");
		strcat(sql, node->name);
		strcat(sql, "','");
		strcat(sql, node->phone);
		strcat(sql, "')");

		if (!mysql_real_query(&mysql, sql, strlen(sql))) {
			printf("insert table success!\n");
		} else {
			printf("insert table fail!\n");
		}
	}

	mysql_close(&mysql);
}

/*
 * 函数名：findDatabaseWithName
  * 功能：根据姓名查找数据库中的信息
 * 参数：
 *   -要查找的姓名
 *   -链表头指针
 *返回值：
 *    -链表指针node
 */
Contact *findDatabase(Contact *head,char *flag)
{
	MYSQL mysql;
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;
	char sql[512];

	Contact *node = (Contact *)malloc(sizeof(Contact));
	mysql_init(&mysql);
	conn = mysql_real_connect(&mysql,
				databaseConfig.host,
				databaseConfig.usrname,
				databaseConfig.password,
				databaseConfig.databaseName,
				databaseConfig.port,
				NULL,
				0);

	if (conn != NULL) {
		strcpy(sql, "select * from contact where name like '");
		strcat(sql, flag);
		strcat(sql, "%' ");
		strcat(sql, " or phone like '");
		strcat(sql, flag);
		strcat(sql, "%'");

		if (!mysql_real_query(&mysql, sql, strlen(sql))) {
			res = mysql_store_result(&mysql);
			while((row = mysql_fetch_row(res)) != NULL) {
				strcpy(node->name, row[1]);
				strcpy(node->phone, row[2]);
				node->id = idgenerator();
				node->next = NULL;
				head = add(head, node);
			}

			mysql_free_result(res);
			mysql_close(&mysql);
		}
	}

	return node;
	free(node);
}

/*
 * 函数名：deleteDatabase
  * 功能：根据姓名删除数据库中的信息
 * 参数：
 *   -要删除的姓名
 *返回值：
 *    -无
 */
void deleteDatabase(char *flag)
{
	MYSQL mysql;
	MYSQL *conn;
	char sql[512];

	mysql_init(&mysql);
	conn = mysql_real_connect(&mysql,
				databaseConfig.host,
				databaseConfig.usrname,
				databaseConfig.password,
				databaseConfig.databaseName,
				databaseConfig.port,
				NULL,
				0);

	if (conn != NULL) {
		strcpy(sql, "delete from contact where name=");
		strcat(sql, "'");
		strcat(sql, flag);
		strcat(sql, "'");
		strcat(sql, " or phone='");
		strcat(sql, flag);
		strcat(sql, "'");

		if (!mysql_real_query(&mysql, sql, strlen(sql))) {
			printf("delete table success!\n");
		} else {
			printf("delete table fail!\n");
		}
	}

	mysql_close(&mysql);
}

/*
 * 函数名：updateDatabaseWithName
 * 功能：修改数据库中的信息
 * 参数：
 *   -要更新的姓名
 *   -更新的姓名
 *   -更新的电话号码
 *返回值：
 *    -无
 */
void updateDatabaseWithName(char *updatename, char *name, char *phone)
{
	MYSQL mysql;
	MYSQL *conn;
	char sql[512];

	mysql_init(&mysql);
	conn = mysql_real_connect(&mysql,
				databaseConfig.host,
				databaseConfig.usrname,
				databaseConfig.password,
				databaseConfig.databaseName,
				databaseConfig.port,
				NULL,
				0);

	if (conn != NULL) {
		strcpy(sql, "update contact set name='");
		strcat(sql, name);
		strcat(sql, "'");
		strcat(sql, ",phone='");
		strcat(sql, phone);
		strcat(sql, "' where name='");
		strcat(sql, updatename);
		strcat(sql, "'");

		if (!mysql_real_query(&mysql, sql, strlen(sql))) {
			printf("update table success!\n");
		} else {
			printf("update table fail!\n");
		}
	}

	mysql_close(&mysql);
}
