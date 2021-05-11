

/*
 * Date:2021-05-11 20:33
 * filename:05_IPC_PRIVATE.cpp
 *
 */

/*
 * semget的调用者可以给其key参数传递一个特殊的键值IPC_PRIVATE(其值为0),这杨无论该信号量是否已经存在,semget都将创建一个新的信号量
 * 使用该键值创建的信号量并非像它的名字声称的那样是进程私有的，应该是IPC_NEW.名字有点误导
 */

#include <sys/sem.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

union semun
{
	int val;
	struct semid_ds* buf;
	unsigned short int* array;
	struct seminfo* __buf;
};

/* op 为 -1时执行P操作,op为1时执行V操作 */
void pv(int sem_id,int op)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = op;
	sem_b.sem_flg = SEM_UNDO;
	semop(sem_id,&sem_b,1);
}

int main(int argc,char* argv[])
{
	int sem_id = semget(IPC_PRIVATE,1,0666);

	union semun sem_un;

	sem_un.val = 1;
	semctl(sem_id,0,SETVAL,sem_un);
	pid_t id = fork();
	if( id < 0 ) return 1;
	else if(id == 0){
		printf("child try to get binary sem\n");
		/* 在父、子进程间共享IPC_PRIVATE信号量的关键就在于两者都可以操作该信号量的标识符sem_id */
		pv(sem_id,-1);
		printf("child get the sem and would release it after 5 seconds\n");
		sleep(5);
		pv(sem_id,1);
		exit(0);
	}else
	{
		printf("parent try to get binary sem\n");
		pv(sem_id,-1);
		printf("parent get the sem and would release it after 5 seconds\n");
		sleep(5);
		pv(sem_id,1);
	}

	waitpid(id,NULL,0);
	semctl(sem_id,0,IPC_RMID,sem_un);//delete sem;
	return 0;
}
