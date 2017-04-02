/*
 * contactDatabasDao.h
 *
 *  Created on: 2010-8-7
 *      Author: Aaron Chou
 */

#ifndef CONTACTDATABASDAO_H_
#define CONTACTDATABASDAO_H_

void addDatabase(Contact *node);
Contact *getAllContactFromDatabase(void);
void deleteDatabase(char *flag);
Contact *findDatabase(Contact *head, char *flag);
void updateDatabaseWithName(char *updatename, char *name, char *phone);

#endif /* CONTACTDATABASDAO_H_ */
