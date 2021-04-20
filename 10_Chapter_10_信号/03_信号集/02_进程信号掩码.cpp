
#include <signal.h>
int sigprocmask(int _how,_const sigset_t* _set,sigset_t* _oset);

//_set参数指定新的信号掩码,_oset参数则输出原来的信号掩码
//如果_set参数不为NULL，则_how参数指定设置进程信号掩码的方式

//_how
// SIG_BLOCK	新的进程信号掩码是其当前值和_set指定信号集的并集
// SIG_UNBLOCL  新的进程信号掩码是其当前值和~_set信号集的交集，因此_set指定的信号集将不被屏蔽
// SIG_SETMASK	直接将进程信号掩码设置为_set

//成功时返回0,失败则返回-1并设置errno


