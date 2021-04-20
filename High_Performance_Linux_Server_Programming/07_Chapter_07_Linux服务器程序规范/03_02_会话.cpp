
#include <unistd.h>
pid_t setsid( void );

//该函数不能由进程组的首领进程调用，否则将产生一个错误。
//对于非组首领的进程，调用该函数不仅创建新会话，而且有如下额外效果：
//	调用进程称为会话的首领，此时该进程是会话的唯一成员
//	新建一个进程组，其PGID就是调用进程的PID，调用进程称为改组的首领
//	调用进程将甩开终端（如果存在）


//Linux进程并未提供所谓会话ID(SID)的概念，但Linux系统认为它等于会话首领所在的进程组的PGID，并提供了如下函数来读取SID
#include <unistd.h>
pid_t getsid( pid_t pid );
