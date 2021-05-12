

/*
 * Date:2021-05-12 21:33
 * filename:03_shmctl.cpp
 *
 */

/*
 * shmctl系统调用控制共享内存的某些属性
 */

#include <sys/shm.h>
int shmctl(int shm_id,int command,struct shmid_ds* buf);

/*
 * 其中,shm_id是由shmget调用返回的共享内存标识符
 * command要执行的命令
 * 	支持:IPC_STAT,IPC_SET,IPC_RMID,IPC_INFO,SHM_INFO,SHM_STAT,SHM_LOCK,SHM_UNLOCK
 */


