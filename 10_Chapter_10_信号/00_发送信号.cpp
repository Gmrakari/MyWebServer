
#include <sys/types.h>
#include <signal.h>
int kill(pid_t pid,int sig);

//该函数把信号sig发送给目标进程，目标进程由pid参数指定，其可能的取值及含义如下
//pid > 0	信号发生给PID为pid的进程
//pid = 0	信号发送给本进程组内的其他进程
//pid = -1	信号发送给除去init进程外的所有进程，但发送者需要拥有对目标进程发送信号的权限
//pid < -1	信号发送给组ID为-pid的进程组中的所有成员

//几种可能的errno
//EINVAL 	无效的信号
//EPERM		该进程没有权限发送信号给任何一个目的进程
//ESRCH		目标进程或进程组不存在


