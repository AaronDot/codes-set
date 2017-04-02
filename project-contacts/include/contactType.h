/*
 * contactData.h
 *
 *  Created on: 2010-8-2
 *      Author: Aaron Chou
 */

#ifndef CONTACTDATA_H_
#define CONTACTDATA_H_

/*定义数据结构*/
typedef struct Student{
	long id;
	/*用户名*/
	char name[20];
	/*电话号码*/
	char phone[20];
	struct Student *next;
} Contact;

/*定义文件系统*/
struct FileConfig{
	/*是否有效，1代表有效，0代表无效*/
	int is_enable;
	/*文件数据的路径*/
	char filePath[100];
	/*文件数据的导出路径*/
	char exportPath[100];
} fileSystemConfig;

void init_system(void);

Contact *init_LinkList(void);

/*===============================addContact=====================*/
Contact *add(Contact *head, Contact *node);
Contact *addWhitNameAndphone(Contact *head, char *name, char *phone);

/*==========================modify==============================*/
Contact *modifyByName(Contact *head, char *name);
Contact *modifyByPhone(Contact *head, char *phone);

/*============================delete============================*/
Contact *deleteById(Contact *head, long id);
Contact *deleteByName(Contact *head, char *name);
Contact *deleteByPhone(Contact *head, char *phone);

/*==========================find================================*/
Contact *findById(Contact *head, long id);
Contact *findByName(Contact *head, const char *name);
Contact *findByPhone(Contact *head, const char *telephone);
Contact *findLastNode(Contact *head);
void freeContact(Contact *node);
void freeLinkList(Contact *head);
void list(Contact *head);

#endif /* CONTACTDATA_H_ */
