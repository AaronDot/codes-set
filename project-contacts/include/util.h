/*
 * util.h
 *
 *  Created on: 2010-7-29
 *      Author: Aaron Chou
 */

#ifndef UTIL_H_
#define UTIL_H_

extern void ltrim(char str[]);
extern void rtrim(char str[]);
extern void trim_comment(char str[]);
extern void trim_r_n(char str[]);
extern int IsvalidPhone(char *phone);
extern int getch(void);
void getString(char *const buff,...);
void splitStringToken(char *buff, char token, char *result[]);
int getTokenCount(char *buff, char token);
char **mallocArrayString(int rows, int cols);
void freeArrayString(char **arrs, int rows);
long idgenerator(void);
char *judgeName(char *name);
char *judgePhone(char *phone);

#endif /* UTIL_H_ */
