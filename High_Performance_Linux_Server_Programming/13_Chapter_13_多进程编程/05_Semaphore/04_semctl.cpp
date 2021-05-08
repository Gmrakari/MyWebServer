

/*
 * Date:2021-05-08 16:55
 * filename:04_semctl.cpp
 *
 */

/* semctl系统调用允许调用者对信号量进行直接控制 */
#include <sys/sem.h>
int semctl(int sem_id,int sem_num,int command);

/*
 *
 sem_id 由semget调用返回的信号量集标识符,用以指定被操作的信号量集
 sem_num 参数指定被操作的信号量在信号量集中的编号
 command 指定要执行的命令
 额外的参数由用户自己定义
 *
 */

union semun
{
	int val;				//用于SETVAL命令
	struct semid_ds* buf;	//用于IPC_STAT和IPC_SET命令
	unsigned short* array;	//用于GETALL和SETALL命令
	struct seminfo* __buf;	//用于IPC_INFO命令
};

struct seminfo
{
	int semmap;				//Linux内核中没有使用
	int semmni;				//系统最多可以拥有的信号量集数目
	int semmns;				//系统最多可以拥有的信号量数目
	int semmnu;				//Linux内核中没有使用
	int semmsl;				//一个信号量集最多允许包含的信号量数目
	int semopm;				//semop一次最多能执行的sem_op操作数目
	int semume;				//Linux内核中没有使用
	int semusz;				//sem_undo结构体大小
	int semvmx;				//最大允许的信号量值
	/* 最多允许的UNDO次数(带SEM_UNDO标志的semop操作的次数) */
	int semaem;
};

//semctl成功时的返回值取决于command参数，semctl失败时返回-1,并设置errno.
