/*
 * contactMenu.c
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

/**
 * 函数名:displayMenu
 * 功能:菜单功能
 * 参数:
 *	head:链表头指针
 * 返回值：
 *	无
 **/
void displayMenu(Contact *head)
{
	char command[512];/*用户输入的字符*/
	int spaceLength;
	char **commands = NULL;

	/*开始界面，显示所有命令菜单*/
	printf("\nContact\n");
	printf("Welcome to this contact!\n");
	printf("**************************************************\n");
	printf("add:		add contact person\n");
	printf("find:		find contact person\n");
	printf("modify:		modify information\n");
	printf("delete:		delete information\n");
	printf("list:		list information\n");
	printf("export:		export information\n");
	printf("help:		help you to use this contact\n");
	printf("exit:		exit contact\n");
	printf("**************************************************");

	while (1)
	{
		printf("\ncontact>");
		setbuf(stdin, NULL);

		getString(command, 512);	/*receive string*/
		spaceLength = getTokenCount(command, ' ');	/*get the number of blank space in command*/
		commands = mallocArrayString(spaceLength+1, 20);	/*malloc depend on the number of blank space in command*/
		splitStringToken(command, ' ', commands);	/*divid the command depend on the blank space in command*/
		
		/*judge what commands input*/
		if (strcmp(commands[0], "add") == 0) {			/*add operations*/
			head=addContact(head, commands, spaceLength+1);
			printf("\nadd success!");
		} else if (strcmp(commands[0], "find") == 0) {	/*find operations*/
			Contact *node = NULL;
			node = findContact(head, commands, spaceLength+1);
			if(node == NULL) {
				printf("There are not the record!");
			} else {
				printf("\nid\t\tname\ttelephone");
				printf("\n%ld\t%s\t%s", node->id, node->name, node->phone);
			}
			free(node);
		} else if (strcmp(commands[0], "modify") == 0) {	/*modify operations*/
			Contact *node = NULL;
			node = modifyContact(head, commands, spaceLength+1);
			if (node == NULL) {
				printf("There are not the record!");
			} else {
				printf("\nid\t\tname\ttelephone");
				printf("\n%ld\t%s\t%s", node->id, node->name, node->phone);
				printf("\n modify success!");
			}
			free(node);
		} else if (strcmp(commands[0], "delete") == 0) {	/*delete operations*/
			Contact *node = NULL;
			node = deleteContact(head, commands, spaceLength+1);
			if (node == NULL) {
				printf("There are not the record!");
			} else {
				printf("delete success");
			}
			free(node);
		} else if (strcmp(commands[0], "list") == 0) {		/*list operations*/
			listContact(head);
		} else if (strcmp(commands[0], "export") == 0) {	/*export operations*/
			exportContact(head, commands, spaceLength+1);
		} else if (strcmp(commands[0], "help") == 0) {		/*help operations*/
			helpContact(head, commands, spaceLength+1);
		} else if (strcmp(commands[0], "exit") == 0) {		/*exit operations*/
			if (fileSystemConfig.is_enable) {
				saveContact(head);
				freeLinkList(head);
			}
			freeArrayString(commands, spaceLength+1);
			exitContact();
		} else {						/*invalid commands*/
			printf("the command is invalid,please input another!");
		}
		freeArrayString(commands, spaceLength+1);
	}
}
