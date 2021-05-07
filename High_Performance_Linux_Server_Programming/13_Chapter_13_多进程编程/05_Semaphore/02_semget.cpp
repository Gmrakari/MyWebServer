

/*
 * Date:2021-05-07 21:38
 * filename:02_semget.cpp
 *
 */

//semget系统调用创建一个新的信号量集，或者获取一个已经存在的信号量集


#include <sys/sem.h>
int semget(key_t key,int num_sems,int sem_flags);

//key是一个键值，用来标识一个全局唯一的信号量集，就像文件名全局唯一地标识一个文件一样。
//要通过信号量通信地进程需要使用相同地键值来创建/获取该信号量

//num_sems指定要创建/获取地信号量集中信号量地数目
//如果是创建信号量，则该值必须被指定；如果是获取已经存在的信号量，则可以把它设置为0

//sem_flags指定一组标志。它低端的9个比特是该信号量的权限，其格式和含义都与系统调用open的mode参数相同
//它还可以和IPC——CREAT标志做按位"或"运算以创建新的信号量集。
//此时即使信号量已经存在，semget也不会产生错误。

//我们还可以联合使用IPC_CREAT和IPC_EXCL标志来确保创建一组新的、唯一的信号量集。
//在这种情况下,如果信号量已经存在，则semget返回错误并设置errno为EEXIST。

//semget成功时返回一个正整数值,它是信号量集的标识符;
//semget失败时返回-1，并设置errno


//如果semget用于创建信号量集,则与之关联的内核数据结构体semid_ds被创建并初始化
#include <sys/sem.h>
/* 该结构体用于描述IPC对象(信号量、共享内存和消息队列)的权限 */

struct ipc_perm
{
	key_t key;
	uid_t uid;
	gid_t gid;
	uid_t cuid;
	gid_t cgid;
	mode_t mode;
}

struct semid_ds
{
	struct ipc_perm sem_perm;
	unsigned long int sem_nsems;
	time_t sem_otime;
	time_t sem_ctime;
};
