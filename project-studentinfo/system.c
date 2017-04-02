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

static int shm_id;
static int sem1prodt;
static int sem2tosys;
static int sem3tocli;

int initSystem(void)
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
int main(void)
{
	struct Student *add;
	struct Student data[100];
	int i = 0;	/*当前系统中学生的数量*/
	int j = 0;	/*用户查找学生信息*/

	initSystem();
	add = (struct Student *)shmat(shm_id, 0, 0);

	while (TRUE) {
		/*连续等待客户端的通知*/
		sem2.sem_num = 0;   
		sem2.sem_op = -1;
		sem2.sem_flg = 0;
		semop(sem2tosys,&sem2,1);

		if (add->type == 0){	
			if (i < 100) {
				memcpy(&data[i], add, 30);
				memset(add, 0, 30);
				add->res=0;		/*返回操作信息*/

				/*通知客户端获取返回数据*/
				sem3.sem_num = 0;   
				sem3.sem_op  = 1;
				sem3.sem_flg = 0;
				semop(sem3tocli, &sem3, 1);

				/*测试添加的记录*/
				printf("\t\tthe student information is:\r\n");
				printf("\t\tnumber\tname\tscore\r\n");
				printf("\t\t%d\t%s\t%s\n\r", data[i].id, data[i].name, data[i].score);

				i++;
			} else {
				memset(add, 0, 30);
				add->res = 1;  /*返回操作信息*/
			}
		}
		/*执行查找操作*/
		if (add->type == 1) {	
			for (j=0; j<i; j++) {
				if (add->id == data[j].id) {	
					memset(add, 0, 30);
					memcpy(add, &data[j], 30);
					add->res = 2;	/*返回操作信息*/
					break;
				} else {
					memset(add, 0, 30);
					add->res = 3;	/*返回操作信息*/
				}						
			}

			/*通知客户端获取返回数据*/
			sem3.sem_num = 0;   
			sem3.sem_op  = 1;
			sem3.sem_flg = 0;
			semop(sem3tocli, &sem3, 1);
		}
	}

	return 0;
}
