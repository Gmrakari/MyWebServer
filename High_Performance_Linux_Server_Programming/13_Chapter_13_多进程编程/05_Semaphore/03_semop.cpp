

/*
 * Date:2021-05-08 16:32
 * filename:03_semop.cpp
 *
 */

/* semop系统调用改变信号量的值,即执行P、V操作 */

//内核相关变量
unsigned short semval;	//信号量的值
unsigned short semzcnt;	//等待信号量值变为0的进程数量
unsigned short semncnt;	//等待信号量增加的进程数量
pid_t sempid;			//最后一次执行semop操作的进程ID

#include <sys/sem.h>
int semop(int sem_id,struct sembuf* sem_ops,size_t num_sem_ops);

/*
 *
sem_id参数是由semget调用返回的信号量集标识符,用以指定被操作的目标信号量集
sem_ops参数指向一个sembuf结构体类型的数组,sembuf结构体的定义如下:

*/

struct sembuf
{
	unsigned short int sem_num;
	short int sem_op;
	short int sem_flg;
};

/*
 *
sem_num成员是信号量集中信号量的编号，0表示信号量集中的第一个信号量。
sem_op成员指定操作类型,其可选值为正整数、0和负整数。每种类型的操作的行为又受到sem_flg成员的影响。
sem_flg的可选值是IPC_NOWAIT和SEM_UNDO.IPC_NOWAIT的含义是，无论信号量操作是否成功,semop调用都将立即返回
SEM_UNDO的含义是，当进程退出的时取消正在进行的semop操作,详细看sem_flg影响(P246)
semop系统调用的第三个参数num_sem_ops指定要执行的操作个数，即sem_ops数组中元素的个数.
semop对数组sem_ops中的每个成员按照数组顺序依次执行操作，并且该过程是原子操作，
以避免别的进程在同一时刻按照不同的顺序对该信号集中的信号量执行semop操作导致的竟态条件

semop成功时返回0，失败则返回-1并设置errno，失败的时候，sem_ops数组中指定的所有操作都不被执行

*
*/

