/*
 * contactView.c
 *
 *  Created on: 2010-8-6
 *      Author: Aaron Chou
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/contactType.h"
#include "include/contactDao.h"
#include "include/contactMenu.h"
#include "include/contactView.h"
#include "include/util.h"
#include "include/contactDatabaseDao.h"
#include "include/config.h"

/*==============================addContact=====================*/
/**
 * 函数名：addContact
 * 功能：返回添加的节点
 * 参数：
 *    -头指针
 *    -二维数组
 *    -二维数组行数，即命令的个数
 * 返回值：
 *    -头指针
 */
Contact *addContact(Contact *head, char **commands, int length)
{
	Contact *node = NULL;
	char *p;

	if (length == 1) {			/*只有Add命令时*/
		node = getContactWithNone();
	} else if (length == 2) {	/*有add和姓名或电话号码时*/
		p = commands[1];
		if ((*p > 'a' && *p < 'z') || (*p > 'A' && *p < 'Z')) {		/*如果输入的是字母*/
			node = getContactWithName(commands[1]);
		} else if (*p>'0' && *p<'9') {
			node = getContactWithPhone(commands[1]);
		}

	} else if (length == 3) {	/*add，姓名，电话号码都有时*/
			node = getContactWithNameAndPhone(commands[1], commands[2]);
	}
#if 1
	/*执行数据库存储环境时*/
	if (databaseConfig.is_enable) {
		/*添加数据库*/
		addDatabase(node);
		free(node);
	}
#endif

	/*执行文件系统存储环境时*/
	if(fileSystemConfig.is_enable)
		head = add(head, node);

	return head;
	free(node);
}

/*
 *函数名：getContactWithNone
 *功能：通过提示得到要添加的用户数据
 *参数：
 *   -无
 *返回值：
 *   -要添加的node
 */
Contact *getContactWithNone(void)
{
	Contact *node = NULL;

	node = (Contact *)malloc(sizeof(Contact));

	printf("\n please input the name:");
	setbuf(stdin, NULL);
	scanf("%s", node->name);
	strcpy(node->name, judgeName(node->name));
	printf("\n please input the telephone:");
	setbuf(stdin, NULL);
	scanf("%s", node->phone);
	strcpy(node->phone, judgePhone(node->phone));
	node->id = idgenerator();
	node->next = NULL;

	return node;
}

/*
 *函数名：getContactWithName
 *功能：通过用户名得到你要添加的用户信息
 *参数：
 *   -输入的用户名
 *返回值：
 *   -要添加的node
 */
Contact *getContactWithName(char *name)
{
	Contact *node = NULL;

	node = (Contact *)malloc(sizeof(Contact));

	strcpy(node->name, judgeName(name));
	printf("\n please input the telephone:");
	setbuf(stdin, NULL);
	scanf("%s", node->phone);
	strcpy(node->phone, judgePhone(node->phone));
	node->id = idgenerator();
	node->next = NULL;

	return node;
}

/*
 *函数名：getContactWithPhone
 *功能：通过电话号码得到你要添加的用户信息
 *参数：
 *   -输入的电话号码
 *返回值：
 *   -要添加的node
 */
Contact *getContactWithPhone(char *phone)
{
	Contact *node = NULL;

	node = (Contact *)malloc(sizeof(Contact));

	strcpy(node->phone, judgePhone(phone));
	printf("\n please input the name:");
	setbuf(stdin, NULL);
	scanf("%s", node->name);
	strcpy(node->name, judgeName(node->name));
	node->id = idgenerator();
	node->next = NULL;

	return node;
}

/*
 *函数名：getContactWithNameAndPhone
 *功能：通过电话号码和用户名得到你要添加的用户信息
 *参数：
 *   -输入的电话号码和用户名
 *返回值：
 *   -要添加的node
 */
Contact *getContactWithNameAndPhone(char *name, char *phone)
{
	Contact *node = NULL;

	node = (Contact *)malloc(sizeof(Contact));

	strcpy(name, judgeName(name));
	strcpy(node->name, name);
	strcpy(phone, judgePhone(phone));
	strcpy(node->phone, phone);
	node->id = idgenerator();
	node->next = NULL;

	return node;
	free(node);
}

/*============================find================================*/
/**
 *函数名：findContact
 *功能：返回查找的节点
 *参数：
 *   -链表头指针
 *   -二维数组
 *   -二维数组行数，即命令的个数
 *返回值：
 *   -查找到的node
 */
Contact *findContact(Contact *head, char **commands, int length)
{
	Contact *node = NULL;
	char *p;
#if 1
	/*执行数据库存储环境时*/
	if (databaseConfig.is_enable)
		node = findDatabase(head, commands[1]);
#endif

	/*执行文件系统存储环境时*/
	if (fileSystemConfig.is_enable) {
		if (length == 1) {
			node = findWithNone(head);
		} else if (length == 2) {
			p = commands[1];
			if (( *p > 'a' && *p < 'z') || (*p > 'A' && *p < 'Z')) {	
				strcpy(commands[1], judgeName(commands[1]));
				node = findByName(head, commands[1]);
			} else if (*p>'0' && *p<'9') {							
				strcpy(commands[1], judgeName(commands[1]));
				node = findByPhone(head, commands[1]);
			}
		}
	}

	return node;
	free(node);
}

/*
 * 函数名：findWithNone
 * 功能：通过提示用户输入找到数据信息
 * 参数：
 *    -头指针
 * 返回值：
 *    -找到的节点
 */
Contact *findWithNone(Contact *head)
{
	char name[20];
	char phone[20];
	char in;
	Contact *p = NULL;

	printf("\n1.according name\n2.according phone\n");
	setbuf(stdin, NULL);
	scanf("%c", &in);

	if (in == '1') {	
		printf("\nplease input the name:");
		setbuf(stdin, NULL);
		scanf("%s", name);
		strcpy(name, judgeName(name));
		p = findByName(head, name);
	} else {
		printf("\nplease input the phone:");
		setbuf(stdin, NULL);
		scanf("%s", phone);
		strcpy(phone, judgePhone(phone));
		p = findByPhone(head, phone);
	}

    return p;
    free(p);
}

//============================modify================================
/**
 * 函数名：modifyContact
 * 功能：返回修改的节点
 * 参数：
 *    -头指针
 *    -二维数组
 *    -二维数组行数，即命令的个数
 * 返回值：
 *    -修改的指针node
 */
Contact *modifyContact(Contact *head, char **commands, int length)
{
	Contact *node = NULL;
	char *p;
#if 1
	/*执行数据库存储环境时*/
	if (databaseConfig.is_enable)
		updateDatabaseWithName(commands[1],commands[2],commands[3]);
#endif

	/*执行文件系统存储环境时*/
	if (fileSystemConfig.is_enable) {
		if (length == 1){
			node = modifyWithNone(head);
		} else if (length == 2) {
			p = commands[1];
			if ((*p > 'a' && *p < 'z') || (*p > 'A' && *p < 'Z')) {
				strcpy(commands[1], judgeName(commands[1]));
				node = modifyByName(head, commands[1]);
			} else if (*p > '0' && *p < '9') {					
				strcpy(commands[1], judgeName(commands[1]));
				node = modifyByPhone(head, commands[1]);
			}
		} else if (length == 3) {

		}
	}

	return node;
}

/*
 * 函数名：ModifyWithNone
 * 功能：通过提示用户输入找到要修改的用户数据信息
 * 参数：
 *    -头指针
 * 返回值：
 *    -修改的节点
 */
Contact *modifyWithNone(Contact *head)
{
	Contact *p = NULL;
	char in;
	char name[20];
	char phone[20];

	printf("\n1.modify name\n2.modify phone\n");
	setbuf(stdin, NULL);
	scanf("%s", &in);

	if (in == '1') {
		printf("\ninput the name you want to modify:");
		setbuf(stdin, NULL);
		scanf("%s", name);
		strcpy(name, judgeName(name));
		p = modifyByName(head, name);
	} else {		/*修改电话号码*/
		printf("\ninput the phone you want to modify:");
		setbuf(stdin, NULL);
		scanf("%s", phone);
		strcpy(phone, judgePhone(phone));
		p = modifyByPhone(head, phone);
	}

	return p;
	free(p);
}

/*============================delete================================*/
/**
 * 函数名：deleteContact
 * 功能：返回删除的节点
 * 参数：
 *    -头指针
 *    -二维数组
 *    -二维数组行数，即命令的个数
 * 返回值：
 *    -删除的指针node
 */
Contact *deleteContact(Contact *head, char **commands, int length)
{
	Contact *node = NULL;
	char *p;

#if 1
	/*执行数据库存储环境时*/
	if (databaseConfig.is_enable)
		deleteDatabase(commands[1]);
#endif

	/*执行文件系统存储环境时*/
	if (fileSystemConfig.is_enable) {
		if (length == 1) {
			node=deleteWithNone(head);
		} else if (length == 2) {	
			p = commands[1];
			if (*p > 'a' && *p < 'z') {
				strcpy(commands[1], judgeName(commands[1]));
				node = deleteByName(head, commands[1]);
			} else if(*p>'0' && *p<'9') {
				strcpy(commands[1], judgePhone(commands[1]));
				node = deleteByPhone(head, commands[1]);			}
		} else if (length == 3) {

		}
	}

	return node;
}

/*
 * 函数名：ModifyWithNone
 * 功能：通过提示用户输入找到要删除的用户数据信息
 * 参数：
 *    -头指针
 * 返回值：
 *    -删除的节点
 */
Contact *deleteWithNone(Contact *head)
{
	Contact *temp = NULL;
	char name[20];
	char in;
	char phone[20];

	/*判断按照那一种方法删除*/
	printf("1.according name\n2.according phone\n");
	setbuf(stdin, NULL);
	scanf("%s", &in);

	if (in == '1') {
		printf("\ninput the name you want to delete:");
		setbuf(stdin, NULL);
		scanf("%s", name);
		strcpy(name, judgeName(name));
		temp = deleteByName(head, name);
	} else { 
		printf("\ninput the phone you want to delete:");
		setbuf(stdin, NULL);
		scanf("%s", phone);
		strcpy(phone, judgePhone(phone));
		temp = deleteByPhone(head,phone);
	}

	return temp;
	free(temp);
}

//============================list================================
/**
 *函数名：listContact
 *功能：列表系统中所有的信息数据
 *参数：
 *   -链表头指针
 *返回值：
 *   -无
 */
void listContact(Contact *head)
{
#if 1
	/*执行数据库存储环境时*/
	if (databaseConfig.is_enable) {
		head = getAllContactFromDatabase();
		list(head);
	}
#endif
	/*执行文件系统存储环境时*/
    if(fileSystemConfig.is_enable) 
		list(head);
}

/*============================export================================*/
/**
 * 函数名：exportContact
 * 功能：导出通讯录中的所有数据信息到指定文件
 * 参数：
 *    -头指针
 *    -二维数组
 *    -二维数组行数，即命令的个数
 * 返回值：
 *    -无
 */
void exportContact(Contact *head, char **commands, int length)
{
	if (length == 1)
		exportTxt(head);
}

/*
 * 函数名：exportWithNone
 * 功能：将文件系统中的信息导出到指定的文件中区
 * 参数：
 *   -链表头指针
 * 返回值:
 *   -无
 */
void exportTxt(Contact *head)
{
	char *exportPath="./contact.txt";
	FILE *fp = NULL;
	char str[50];
	Contact *p = NULL;

	fp = fopen(exportPath, "w");

	if (head->next == NULL)
		return;

	p = head;
	while (p != NULL) {
		strcpy(str, p->name);
		strcat(str, ",");
		strcat(str, p->phone);
		fprintf(fp, "%s\n", str);
		p = p->next;
	}

	fclose(fp);
}

/*============================help================================*/
/**
 * 函数名：helpContact
 * 功能：提供帮助
 * 参数：
 *    -头指针
 *    -二维数组
 *    -二维数组行数，即命令的个数
 * 返回值：
 *    -无
 */
void helpContact(Contact *head, char **commands, int length)
{
	if (length == 1) {
		helpWithNone();
	} else if (length == 2) {
		 helpWithCommand(commands[1]);
	}
}

//*============================exitContact================================*/
/*
 * 名称:exitContact
 * 功能:退出通讯录
 * 参数：
 *    -无
 * 返回值:
 *    -无
*/
void exitContact(void)
{
	char cn;

	printf("\nAre you sure to exit?(y/n)");
	setbuf(stdin, NULL);
	scanf("%c", &cn);
	/*当用户输入'Y'或'y'时,退出通讯录,否则继续*/
	if((cn == 'y') || (cn == 'Y'))
	    exit(0);
}
