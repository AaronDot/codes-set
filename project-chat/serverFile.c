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

int sockSrv;
int sockConn1;
int sockConn2;
struct message_file info;

void init_network(void)
{
	socklen_t len;
	char sendBuf[100];
	struct sockaddr_in addrClient1;
	struct sockaddr_in addrClient2;
	struct sockaddr_in addrSrv;
	
/*服务器设置*/
	sockSrv = socket(AF_INET, SOCK_STREAM, 0);
	
	addrSrv.sin_addr.s_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons((uint16_t)123456);
	
	bind(sockSrv, (struct sockaddr *)&addrSrv, sizeof(struct sockaddr));
	listen(sockSrv, 5);
	
/*等待服务器连接*/
	len = sizeof(struct sockaddr);
	printf("等待链接。。。\r\n");
	sockConn1 = accept(sockSrv, (struct sockaddr *)&addrClient1, &len);
	sprintf(sendBuf,"Welcome %s to www.yewusishi.com\r\n", inet_ntoa(addrClient1.sin_addr));
	send(sockConn1, sendBuf, strlen(sendBuf)+1, MSG_DONTWAIT);
	
	sockConn2 = accept(sockSrv, (struct sockaddr *)&addrClient2, &len);
	sprintf(sendBuf,"Welcome %s to www.yewusishi.com\r\n", inet_ntoa(addrClient2.sin_addr));
	send(sockConn2, sendBuf, strlen(sendBuf)+1, MSG_DONTWAIT);
}

void form_send_client(void)
{
	int ret;

	memset(&info, 0, sizeof(info));
	while (1) {
		ret = recv(sockConn1, &info, sizeof(info), MSG_DONTWAIT);
		if (ret > 0) {
			printf("form_send_client success\r\n");
			send(sockConn2, &info, sizeof(info), MSG_DONTWAIT);
			return;
		}
	}
}

void to_receive_client(void)
{
	int ret;

	memset(&info, 0, sizeof(info));
	while (1) {
		ret = recv(sockConn2, &info, sizeof(info), MSG_DONTWAIT);
		if (ret > 0) {
			printf("to_receive_client success\r\n");
			send(sockConn1, &info, sizeof(info), MSG_DONTWAIT);
			return;
		}
	}
}

int main(void)
{	
	int pid;

	init_network();
	
	pid = fork();

	while (1) {
		if (pid > 0) {
			form_send_client();		/*从终端2接收数据*/
		} else if (pid == 0) {
			to_receive_client();	/*从终端1接收数据*/
		}
	}

	return 0;
}
