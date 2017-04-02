/*
 * contact-dao.h
 *
 *  Created on: 2010-7-29
 *      Author: Aaron Chou
 */

#ifndef CONTACTDAO_H_
#define CONTACTDAO_H_

extern void saveContact(Contact *head);
Contact *readContact(Contact *head);
void helpWithNone(void);
void helpWithCommand(char *command);

#endif /* CONTACTDAO_H_ */
