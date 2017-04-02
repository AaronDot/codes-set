#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include "base.h"

static int shm_id = 1;
static int sem1prodt = 2;
static int sem2tosys = 3;
static int sem3tocli = 4;
static struct sembuf sem1;

int initClient(void)
{
	/*创建一个30字节的共享内存区域*/
	shm_id = shmget(SHAREMEMORY, 30, 0);
	if (shm_id < 0) {
		perror("shmget fail\r\n");
		exit(1);
	}

	/*分别创建三个信号量*/
	sem1prodt = semget(SEM1PRODT, 1, 0);
	if (sem1prodt < 0) {
		perror("semget sem1prodt error\r\n");
		exit(1);
	}

	sem2tosys = semget(SEM2TOSYS, 1, 0);
	if (sem2tosys < 0) {
		perror("semget sem2tosys error\r\n");
		exit(1);
	}
	
	sem3tocli = semget(SEM3TOCLI, 1, 0);
	if (sem3tocli < 0) {
		perror("semget");
		exit(1);
	}

	return 0;
}

struct Student *msgWrite(struct Student *info)
{
	printf("please input the student's id:");
	scanf("%d", &info->id);

	printf("please input the student's name:");
	scanf("%s", info->name);

	printf("please input the student's score:");
	scanf("%s", info->score);

	return info;
}

struct Student *msgFind(struct Student *info)
{
	printf("please input the student's id:");
	scanf("%d", &info->id);

	return info;
}
int main(void)
{
	struct Student info;
	struct Student *p = &info; 
	struct Student *add;
	int command;

	initClient();

	add = (struct Student *)shmat(shm_id, 0, 0);

	printf("================help==============\r\n");
	printf("0--add a student's information into database\r\n");
	printf("1--find a student's information by id\r\n");
	printf("2--exit the client\r\n");
	printf("================end===============\r\n");

	while (TRUE) {
		printf("command#");
		scanf("%d", &command);

		/*请求添加操作*/
		if (command == 0) {
			/*保护数据资源*/
			sem1.sem_num = 0;
			sem1.sem_op = -1;
			sem1.sem_flg = 0;
			semop(sem1prodt, &sem1, 1);

			/*执行添加操作*/
			p->type = 0;
			msgWrite(p);		/*向info写入数据*/
			memset(add, 0, 30);
			memcpy(add, p, 30);

			/*通知服务器读取数据*/
			sem2.sem_num = 0;
			sem2.sem_op  = 1;
			sem2.sem_flg = 0;
			semop(sem2tosys, &sem2, 1);

			/*获取服务器返回数据*/
			sem3.sem_num = 0;
			sem3.sem_op  = -1;
			sem3.sem_flg = 0;
			semop(sem3tocli, &sem3, 1);

			/*判断返回数据*/
			if (add->res == 0)
				printf("add the student information success...\r\n");
			if (add->res == 1)
				printf("there is not enough room...\r\n");

			/*释放数据资源*/
			sem1.sem_num = 0;
			sem1.sem_op = 1;
			sem1.sem_flg = 0;
			semop(sem1prodt,&sem1,1);
		} else if (command == 1) { 	/*请求查找操作*/
			/*保护数据资源*/
			sem1.sem_num = 0;
			sem1.sem_op = -1;
			sem1.sem_flg = 0;
			semop(sem1prodt, &sem1, 1);

			/*执行查找操作*/
			p->type = 1;
			msgFind(p);
			memset(add, 0, 30);
			memcpy(add, p, 30);

			/*通知服务器读取数据*/
			sem2.sem_num = 0;
			sem2.sem_op  = 1;
			sem2.sem_flg = 0;
			semop(sem2tosys, &sem2, 1);

			/*获取服务器返回数据*/
			sem3.sem_num = 0;
			sem3.sem_op  = -1;
			sem3.sem_flg = 0;
			semop(sem3tocli, &sem3, 1);

			/*判断返回数据*/
			if (add->res == 2) {
				printf("\t\tthe student information is:\r\n");
				printf("\t\tnumber\tname\tscore\r\n");
				printf("\t\t%d\t%s\t%s\n\r",add->id,add->name,add->score);
			} else if(add->res == 3) {
				printf("sorry,no such an student...\r\n");
			}

			/*保护数据资源*/
			sem1.sem_num = 0;
			sem1.sem_op = 1;
			sem1.sem_flg = 0;
			semop(sem1prodt, &sem1, 1);
		} else if (command == 2){/*退出操作*/	
			exit(0);
		} else {
			printf("no such a command...try again\r\n");
		}
	}

	return 0;
}
