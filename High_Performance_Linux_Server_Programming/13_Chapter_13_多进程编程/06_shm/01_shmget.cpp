

/*
 * Date:2021-05-12 21:07
 * filename:01_shmget.cpp
 *
 */

/*
 * 创建一段新的共享内存,或者获取一段已经存在的共享内存。
 */

#include <sys/shm.h>
int shmget(key_t key,size_t size,int shmflg);

/*
 * 和semget系统调用一样,key参数是一个键值,用来标识一段全局唯一的共享内存。
 * size参数指定共享内存的大小，单位是字节。如果是创建新的共享内存，则size值必须被指定。
 * 如果是获取已经存在的共享内存，则可以把size设置为0
 * 
 * shmflg参数的使用和含义与semget系统调用的sem_flags参数相同
 * 不过shmflg支持两个额外的标志-SHM_HUGETLB和SHM_NORESERVE
 *
 * SHM_HUGETLB,类似mmap的MAP_HUGETLB标志，系统将使用"大页面"来为共享内存分配空间
 * SHM_NORESERVE,类似mmap的MAP_NORESERVE标志,不为共享内存保留交换分区(swap空间)。
 * 这样当物理内存不足的时候，对该共享内存执行写操作将触发SIGSEGV信号
 *
 * shmget成功时返回一个正整数值，它是共享内存的标识符。shmget失败时返回-1,并设置errno
 *
 * 如果shmget用于创建共享内存,则这段共享内存的所有字节都被初始化为0,与之关联的内核数据结构shmid_ds
 * 将被创建并初始化。shmid_ds结构体的定义如下
 */

struct shmid_ds
{
	struct ipc_perm shm_perm;		//共享内存的操作权限
	size_t shm_segsz;				//共享内存的大小,单位是字节
	__time_t shm_atime;				//对这段内存最后一次调用shmat的时间
	__time_t shm_dtime;
	__time_t shm_ctime;
	__pid_t shm_cpid;				//创建者的PID
	__pid_t shm_lpid;				//最后一次执行shmat或shmdt操作的进程的PID
	shmatt_t shm_nattach;			//目前关联到此共享内存的进程数量
};


/*
 * shmget对shmid_ds结构体的初始化包括:
 * 将shm_perm.cuid和shm_perm.uid设置为调用进程的有效用户ID
 * 将shm_perm.cgid和shm_perm.gid设置为调用进程的有效组ID
 * 将shm_perm.mode的最低9位设置位shmflg参数的最低9位
 * 将shm_segsz设置为size
 * 将shm_lpid,shm_nattach,shm_atime,shm_dtime设置为0
 * 将shm_ctime设置为当前时间
 */


