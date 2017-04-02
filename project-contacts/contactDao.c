/*
 * contactDAO.c
 *
 *  Created on: 2010-7-29
 *      Author: Aaron Chou
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "include/contactType.h"

char *fileName = "/data1.dat";		/*保存目录*/
char *exportPath = "./contact.txt";	/*导出目录*/

/**
 * 函数名：saveContact
 * 功能：把系统数据保存到文件
 * 参数：
 *    -链表头指针
 * 返回值：
 *    -无
 */
void saveContact(Contact *head)
{
	FILE *fp = NULL;
	Contact *p = NULL;

	fp = fopen(fileName, "wb");
	p=head->next;

	/*系统无数据时*/
	if (head->next == NULL)
		return;

	/*文件打开失败*/
	if (fp == NULL){
		printf("unknown error in you system");
		return;
	}

	while (p != NULL) {
		fwrite(p, sizeof(Contact), 1, fp);
		p = p->next;
	}

	fclose(fp);

}

/**
 * 函数名：readContact
 * 功能：从文件中读取数据
 * 参数：
 *    -链表头指针
 * 返回值：
 *    -新链表头指针
 */
Contact *readContact(Contact *head)
{
	Contact *head1 = head;
	Contact *previous = head;
	Contact *node = NULL;
	int length = 0;
	FILE *fp = NULL;

	fp = fopen(fileName, "rb");
	if (fp == NULL)
		return NULL;

	node = (Contact *)malloc(sizeof(Contact));
	length = fread(node, sizeof(Contact), 1, fp);

	/*文件指针还没有到文件最后时，循环读取*/
	while (!feof(fp)) {
		if (head == NULL) {
			head1 = node;
		} else {
			previous->next = node;
		}
		node->next = NULL;
		previous = node;
		node = (Contact *)malloc(sizeof(Contact));
		length = fread(node, sizeof(Contact), 1, fp);
	}

	fclose(fp);
	return head1;
}

/**
 * 函数名：helpWithNone
 * 功能：从文件中读取帮助文档
 * 参数：
 *    -无
 * 返回值：
 *    -无
 */
void helpWithNone(void)
{
	char str[2000] = {'\0'};
	FILE *fp = NULL;

	fp = fopen("/root/help/help1.txt", "r+");
	if (fp == NULL)
		return NULL;
	fread(str, 2000, 1, fp);
	printf("%s", str);

	fclose(fp);
}

/**
 * 函数名：helpWithCommand
 * 功能：从文件中读取帮助文档
 * 参数：
 *    -命令
 * 返回值：
 *    -无
 */
void helpWithCommand(char *command)
{
	char str[2000] = {'\0'};
	FILE *fp = NULL;

	if (strcmp(command, "add") == 0) {
		fp = fopen("./help/add.txt", "r+");
		fread(str, 2000, 1, fp);
		printf("%s", str);
		fclose(fp);
	} else if (strcmp(command, "find") == 0) {
		fp = fopen("./help/find.txt", "r+");
		fread(str, 2000, 1, fp);
		printf("%s", str);
		fclose(fp);
	} else if (strcmp(command, "modify") == 0) {
		fp = fopen("./help/modify.txt", "r+");
		fread(str, 2000, 1, fp);
		printf("%s", str);
		fclose(fp);
	} else if (strcmp(command, "delete") == 0) {
		fp=fopen("./help/delete.txt", "r+");
		fread(str, 2000, 1, fp);
		printf("%s", str);
		fclose(fp);
	} else if (strcmp(command, "list") == 0) {
		fp = fopen("./help/list.txt", "r+");
		fread(str, 2000, 1, fp);
		printf("%s", str);
		fclose(fp);
	} else if (strcmp(command, "export") == 0) {
		fp = fopen("./help/export.txt", "r+");
		fread(str, 2000, 1, fp);
		printf("%s", str);
		fclose(fp);
	} else if (strcmp(command, "help") == 0) {
		fp = fopen("./help/help.txt", "r+");
		fread(str, 2000, 1, fp);
		printf("%s", str);
		fclose(fp);
	} else if (strcmp(command, "exit") == 0) {
		fp=fopen("./help/exit.txt", "r+");
		fread(str, 2000, 1, fp);
		printf("%s",str);
		fclose(fp);
	}
}
