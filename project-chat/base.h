#ifndef BASE_H_
#define BASE_H_

#define MAX 1000

struct message_chat
{
	int type;
	char data[MAX];
};

struct message_file
{
	int type;
	int tatol;
	int num;
	int datalen;
	char data[MAX];
};

struct message_file info;
struct message_file biginfo[100];
int sockClient;
int store;

#endif
