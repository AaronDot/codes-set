/*
 * contactData.c
 *
 *  Created on: 2010-8-2
 *      Author: Aaron Chou
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "include/contactType.h"
#include "include/util.h"

/**
 * 函数名：init_LinkList
 * 功能：链表初始化
 * 参数：
 *   -无
 * 返回值：
 * 	-链表头指针
 */
Contact *init_LinkList(void)
{
	Contact *head = NULL;

	head = (Contact *)malloc(sizeof(Contact));
	head->next = NULL;

	return head;
}

/*==============================addContact=====================*/
/**
 * 函数名：add
 * 功能：添加数据到指定链表，返回链表头指针
 * 参数:
 * 	  -链表头指针
 *    -新的链表数据
 * 返回值:
 * 	  -链表头指针
 */
Contact *add(Contact *head, Contact *node)
{
	Contact *lastNode = findLastNode(head);
	/*将node连接到最后*/
	node->next = NULL;
	lastNode->next = node;

	return head;
}

/**
 * 函数名：addWhitNameAndphone
 * 功能：添加数据到指定链表，返回链表头指针
 * 参数:
 * 	  -链表头指针
 *    -用户名
 *    -电话号码
 * 返回值:
 * 	  -链表头指针
 */
Contact *addWhitNameAndphone(Contact *head, char *name, char *phone)
{
	Contact *lastNode = NULL;
	Contact *node = NULL;

	lastNode = findLastNode(head);
	node = (Contact *)calloc(sizeof(Contact), 1);
	strcpy(node->name, name);
	strcpy(node->phone, phone);
	node->id = idgenerator();

	node->next = NULL;
	lastNode->next = node;

	return head;
}

/*============================modify================================*/
/*
 * 函数名：modifyWithName
 * 功能：通过输入用户名找到要修改的用户数据信息
 * 参数：
 *    -头指针
 *    -用户名
 * 返回值：
 *    -修改的节点
 */
Contact *modifyByName(Contact *head, char *name)
{
	Contact *p = NULL;

	p = findByName(head, name);

	if (p == NULL) {
		return NULL;
	} else {
		printf("\ninput the name you modified:");
		setbuf(stdin, NULL);
		scanf("%s", p->name);
		/*判断输入的用户名是不是合法，并赋值*/
		strcpy(p->name, judgeName(p->name));
	}

	return p;
}
 
/*
 * 函数名：modifyByPhone
 * 功能：通过输入电话号码找到要修改的用户数据信息
 * 参数：
 *    -头指针
 *    -电话号码
 * 返回值：
 *    -修改的节点
 */
Contact *modifyByPhone(Contact *head, char *phone)
{
	Contact *p = NULL;

	p = findByPhone(head, phone);

	if (p == NULL) {
		return NULL;
	} else {
		printf("\ninput the phone you modified:");
		setbuf(stdin, NULL);
		scanf("%s", p->phone);
		strcpy(p->phone, judgePhone(p->phone));
	}

	return p;
}

/*============================delete================================*/
/*
 * 函数名：deleteByName
 * 功能：根据用户名删除你想要删除的用户信息
 * 参数：
 *   -链表头指针
 *   -用户名
 * 返回值：
 *   -要删除的信息的指针
 */
Contact *deleteByName(Contact *head, char *name)
{
	Contact *p = NULL;
	/*要删除指针的前一个*/
	Contact *q = NULL;
	
	p = head->next;
	q = head;

	/*文件系统中无数据*/
	if (head->next == NULL)
		return NULL;
	while (p != NULL) {
		if (strcmp(p->name, name) == 0)
			break;
		q = p;
		p = p->next;
	}
	if (p != NULL)
		q->next= p->next;

	return p;
}

/*
 * 函数名：deleteByPhone
 * 功能：根据电话号码删除你想要删除的用户信息
 * 参数：
 *   -链表头指针
 *   -用户名
 * 返回值：
 *   -要删除的信息的指针
 */
Contact *deleteByPhone(Contact *head,char *phone)
{
	Contact *p = NULL;
	Contact *q = NULL;
	
	p = head->next;
	q = head;

	if (head->next == NULL)
		return NULL;
	while (p != NULL) {
		if (strcmp(p->phone, phone) == 0)
			break;
		q = p;
		p = p->next;
	}
	if (p != NULL)
		q->next=p->next;

	return p;

}

/**
 * 从链表中删除指定的信息,返回删除的数据
 */
Contact *deleteById(Contact *head,long id)
{
	Contact *p = NULL;
	Contact *q = NULL;

	p = head->next;
	q = head;

	while (p != NULL) {
		if (p->id == id) {
			break;
		} else {
			q = p;
			p = p->next;
		}
	}
	if (p != NULL) {
		q->next = p->next;
	}

	return p;

}

/*============================find================================*/
/**
 *函数名:findById
 *功能:根据id查询所需要的数据
 *参数：
 *   -链表头指针
 *   -id
 *返回值：
 * 	 -查询到得数据的指针
 */
Contact *findById(Contact *head, long id)
{
	Contact* p = NULL;

	p = head->next;

	while (p != NULL) {
		if (p->id == id)
			break;
		p = p->next;
	}

	return p;
}

/**
 *函数名:findByName
 *功能:根据用户名查询所需要的数据
 *参数：
 *   -链表头指针
 *   -用户名
 *返回值：
 * 	 -查询到得数据的指针
 */
Contact *findByName(Contact *head, const char *name)
{
	Contact *p = NULL;

	p = head->next;
	while (p != NULL) {
		if (strcmp(p->name, name) == 0)
			break;
		p = p->next;
	}

	return p;
}

/**
 *函数名:findByPhone
 *功能:根据电话号码查询所需要的数据
 *参数：
 *   -链表头指针
 *   -电话号码
 *返回值：
 * 	 -查询到得数据的指针
 */
Contact *findByPhone(Contact *head, const char *telephone)
{
	Contact *p = NULL;

	p = head->next;

	while (p != NULL) {
		if (strcmp(p->phone, telephone) == 0)
			break;
		p=p->next;
	}

	return p;
}

/**
 * 函数名：freeContact
 * 功能：释放节点空间
 * 参数：
 *    -要释放的节点
 * 返回值：
 *    -无
 */
void freeContact(Contact *node)
{
	free(node);
}

/**
 * 函数名：freeLinkList
 * 功能：释放链表空间
 * 参数：
 *    -链表头指针
 * 返回值：
 *   -无
 */
void freeLinkList(Contact *head)
{
	Contact *previous = NULL;
	Contact  *p = NULL;

	previous = p = head;

	do {
		previous = p;
		p = p->next;
		freeContact(previous);
	} while(p != NULL);
}

/**
 *函数名：findLastNode
 * 功能：查询最后一个节点数据
 * 参数：
 *   -链表头指针
 * 返回值:
 * 	-查询到得数据的指针
 */
Contact *findLastNode(Contact *head)
{
	Contact *p = NULL;

	p = head->next;

	if(head->next == NULL)
		return head;

	while(p->next != NULL)
		p=p->next;

	return p;
}

/*
 * 函数名：list
 * 功能：列表所有数据
 * 参数：
 *   -链表头指针
 * 返回值：
 *   -无
 */
void list(Contact *head)
{
	Contact *p = NULL;

	p = head->next;

	if (head->next == NULL)
		printf("there is on record");
	printf("\nid\t\tname\ttelephone");

	while (p != NULL) {
		printf("\n%ld\t%s\t%s", p->id, p->name, p->phone);
		p = p->next;
	}
}
