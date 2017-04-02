/*
 * contactView.h
 *
 *  Created on: 2010-8-6
 *      Author: Aaron Chou
 */

#ifndef CONTACTVIEW_H_
#define CONTACTVIEW_H_

/*==============================addContact=====================*/
Contact *addContact(Contact *head, char **commands, int spaceLength);
Contact *getContactWithNone(void);
Contact *getContactWithName(char *name);
Contact *getContactWithPhone(char *phone);
Contact *getContactWithNameAndPhone(char *name, char *phone);

/*=========================find================================*/
Contact *findContact(Contact *head, char **commands, int length);
Contact *findWithNone(Contact *head);

/*============================modify===========================*/
Contact *modifyContact(Contact *head, char **commands, int length);
Contact *modifyWithNone(Contact *head);

/*================deleteContact================================*/
Contact *deleteContact(Contact *head, char **commands, int length);
Contact *deleteWithNone(Contact *head);

/*============================listContact======================*/
void listContact(Contact *head);

/*==========================exportContact======================*/
void exportContact(Contact *head, char **commands, int length);
void exportTxt(Contact *head);

/*============================helpContact======================*/
void helpContact(Contact *head, char **commands, int length);

/*=======================exitContact===========================*/
void exitContact(void);

#endif /* CONTACTVIEW_H_ */
