#ifndef BASE_H_
#define BASE_H_

#define TRUE (1)

/*最大存储数据记录*/
#define RECORD_MAX  (100)

/*定义三个信号量*/
#define SEM1PRODT        (100)			/*保护客户端到服务器数据*/
#define SEM2TOSYS        (300)	        /*通知服务器读取数据*/
#define SEM3TOCLI        (500)	        /*通知客户端读取返回结果*/

/*定义共享内存大小*/
#define SHAREMEMORY (800)

/*定义客户端的数据结构*/
struct Student
{
	int id;				/*学员编号*/
	char score[4];      /*学员成绩*/
	char name[20];		/*学员姓名*/
	char type;			/*客户段的请求类型  0:添加操作  1：查找操作*/
	int res;			/*服务端的响应类型  0:添加成功  1: 空间不足  2:查找成功  3：查找失败*/
};

static struct sembuf sem2, sem3;

#endif
