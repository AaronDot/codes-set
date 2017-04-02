#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "base.h"

/*存储文件*/
void save_file(char *buf)
{
	int fd;
	int n = 0;
	int ret;

	fd = open(buf, O_RDWR | O_CREAT | O_APPEND, 00600);
	
	while (n <= store) {
		ret = write(fd, biginfo[n].data, biginfo[n].datalen);
		if (ret < 0)
			break;
		n++;
	}

    close(fd);
}

/*接收文件*/
void receive_file(void)
{
	int rec = 1;
	int ret;

	memset(info.data, 0, MAX);

	while (1) {
		ret = recv(sockClient, &info,sizeof(info),MSG_DONTWAIT);
		if (ret > 0) {
			printf("receive success\r\n");

	    	/*复制文件信息*/	
			strncpy(biginfo[info.num-1].data, info.data, strlen(info.data));
			biginfo[info.num-1].tatol = info.tatol;
			biginfo[info.num-1].num = info.num;
			biginfo[info.num-1].datalen = info.datalen;

			/*正发过来的个数与前面已传过来的包编号一致时存储*/
			if (info.tatol == info.num) {
				store = rec;
				return;
			}
	    	rec ++;
		}
	}
}

void init_network(void)
{
	char recvBuf[100];
	/*设置服务器信息*/
	struct sockaddr_in addrSrv;

/*网络设置*/   	
	/*创建*/	
   	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	
	addrSrv.sin_addr.s_addr = inet_addr("127.0.0.1");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons((uint16_t)123456);	

	/*链接*/
	connect(sockClient, (struct sockaddr *)&addrSrv, sizeof(struct sockaddr));
	
	/*等待接受*/
	memset(recvBuf, '\0', 100);
	recv(sockClient, recvBuf, 100, MSG_DONTWAIT);

	printf("%s\n", recvBuf);
}

void read_file(char *buf)
{
	int fd;
	
	fd = open(buf, O_RDWR);

	read(fd, buf, MAX);
	strncpy(info.data, buf, strlen(buf)+1);

	close(fd);
}

void deliever_file(char *buf)
{
	int n;
	int i = 1;
	int fd;
	int count;
	int num;
	
	/*发送*/  	
	printf("file send now?(0 or 1)\r\n");
	printf("0 stand for no\r\n");
	printf("1 stand for begin\r\n");

	scanf("%d", &n);

	if (n == 1) {
		fd = open(buf, O_RDWR);
		
		if (fd < 0) {
			printf("file  is not  exist\r\n");
			return;
		} else {
			num = lseek(fd, 0, SEEK_END);
			lseek(fd, 0, SEEK_SET);
			if ((num % MAX) == 0)
				info.tatol = num / MAX;
			else
				info.tatol = num / MAX + 1;

			info.type = 2;

			while (1) {	
				count = read(fd, info.data, MAX);
				if (count > 0) {
					info.num = i;
					info.datalen = strlen(info.data);
					count = send(sockClient, &info, sizeof(info), MSG_DONTWAIT);
					i++;
				} else {
				 	return;
				}
			}
			close(fd);
		}
	}
}

void trans(void)
{	
   	int command;
	char buf[100];
	
		printf("please input the command:\r\n");
		printf("1 stand for send file\r\n");
		printf("2 stand for receive file\r\n");
		printf("3 stand for quit\r\n");

/*文件操作界面*/	
	while (1) {
		printf("file#");
		scanf("%d", &command);

		/*发送文件选项*/
		if (command == 1) {
			printf("please input the path of sending file:\r\n");
			memset(buf, '\0', 100);
			scanf("%s", buf);
			//read_file(buf);
			if (strcmp(buf, "quit") == 0)
				return;
			/*链接服务器，并发送*/	
			deliever_file(buf);
		} else if (command == 2) { 	/*接受文件选项*/
			printf("please input the path of receive file:\r\n");
			memset(buf, '\0', 100);
			scanf("%s", buf);
			if (strcmp(buf, "quit") == 0)
				return;
			/*链接服务器，并接收数据*/
			receive_file();
			/*将数据写入文件*/
			save_file(buf);
		} else if (command == 3) {  /*退回到菜单*/	
			return;
		}
	}
}

void init_choice(void)
{
	printf("--------------------Command List----------------------\r\n");
	printf("-----------------------1:chat-------------------------\r\n");
	printf("-----------------------2:Transmit Flie----------------\r\n");
}

/*聊天*/
void chat(void)
{
	int pid;
	int ret;
	char sendBuf[100];

	pid = fork();

	if (pid < 0) {
		perror("fork");
		exit(1);
	} else if (pid > 0) {
		while (1) {
			printf("chating#");
			scanf("%s", sendBuf);

			if (strcmp(sendBuf, "quit") == 0) {	/*退出聊天*/
				return;
			}
			strcpy(info.data, sendBuf);
			info.type = 0;
			send(sockClient, &info, sizeof(info), MSG_DONTWAIT);
		}
	} else {
		while (1) {
			ret = recv(sockClient, &info, sizeof(info), MSG_DONTWAIT);
			if (ret > 0) {
				printf("chating#");
				printf("%s\r\n", info.data);
			}
		}
	}
}

int main(void)
{
	int choice;

	init_choice();
	init_network();

	while (1) {
		printf("Please input your choice ...\n");
		scanf("%d", &choice);

		while ((choice != 1) && (choice != 2) && (choice != 3)) {
			printf("Choice error,please choose again:\r\n");
			init_choice();
			scanf("%d", &choice);
		}
		
		if (choice == 1)
			chat();
		else if (choice == 2)
			trans();
		else if (choice == 3)
			return 0;
	}
	return 0;
}
