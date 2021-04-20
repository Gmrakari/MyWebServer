

#include <unistd.h>
pid_t getpgid( pid_t pid );

//获取进程的PGID


//每个进程组都有一个首领进程，其PGID和PID相同，进程组将一直存在，知道其中所有进程都退出，或者加入到其他进程组


//设置进程组

#include <unistd.h>
int setpgid( pid_t pid, pid_t pgid );

//该函数将PID为pid的进程PGID设置为pgid。如果pid和pgid相同，则由pid指定的进程将被设置为进程组首领
//如果pid为0，则表示设置当前进程的PGID为gpid
//如果pgi为0，则使用pid作为目标PGID
//函数执行成功时返回0 错误失败返回 -1 


