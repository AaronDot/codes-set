/*
 * configuration.c
 *
 *  Created on: 2010-8-7
 *      Author: Aaron Chou
 */
#include <stdlib.h>
#include <string.h>
#include "include/config.h"

/*
 * 函数名： init_configStruct
 * 功能：初始化ConfigStruct链表
 * 参数：
 *    -无
 * 返回值：
 *    -ConfigStruct链表的头指针
 */
struct ConfigStruct *init_configStruct(void)
{
	/*给头指针开辟空间，定义空头指针*/
	struct ConfigStruct *configHead;

	configHead = (struct ConfigStruct *)calloc(sizeof(struct ConfigStruct), 1);
	configHead->next = NULL;

	return configHead;
}

/*
 * 函数名：addConfig
 * 功能：添加ConfigStruct链表指针
 * 参数：
 *   -ConfigStruct链表头指针
 *   -config中的关键字
 *   -关键字的值
 * 返回值：
 *   -无
 */
void addConfig(struct ConfigStruct *head, char *key, char *value)
{
	struct ConfigStruct *node = NULL;
	struct ConfigStruct *temp = NULL;

	node = (struct ConfigStruct *)calloc(sizeof(struct ConfigStruct), 1);
	strcpy(node->key, key);
	strcpy(node->value, value);

	temp = head->next;
	head->next = node;
	node->next = temp;
}

/*
 * 函数名：getConfigBykey
 * 功能：通过key找到链表指针
 * 参数：
 *    -链表头指针
 *    -key
 * 返回值：
 *    -找到的指针
 */
struct ConfigStruct *getConfigBykey(struct ConfigStruct *head, char *key)
{
	struct ConfigStruct *node = NULL;

	node= head->next;
	/*循环链表，通过key查找*/
	while(node != NULL) {
		if (strcmp(node->key, key) == 0) {
			return node;
		}
		node = node->next;
	}

	return NULL;
}

/*
 *函数名：freeConfig
 *功能：释放ConfigStruct空间
 *参数：
 *   -链表头指针
 *返回值
 *   -无
 */
void freeConfig(struct ConfigStruct *head)
{
	struct ConfigStruct *node = NULL;

	node = head;
	//循环链表，逐个释放
	while (head != NULL) {
		head = head->next;
		free(node);
		node = head;
	}
}
