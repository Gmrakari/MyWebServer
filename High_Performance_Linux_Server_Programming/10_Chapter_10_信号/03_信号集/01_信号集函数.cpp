
#include <bits/sigset.h>

#define _SIGSET_NWORDS (1024 / (8 * sizeof(unsigned long int)))

typedef struct
{
	unsigned long int __val[_SIGSET_NWORDS];
}__sigset_t;

#include <signal.h>
int sigemptyset(sigset_t* _set);				   /* 清空信号集 */
int sigfillset(sigset_t* _set);					   /* 在信号集中设置所有信号 */
int sigaddset(sigset_t* _set,int _signo);		   /* 将信号_signo添加至信号集中 */
int sigdelset(sigset_t* _set,int _signo);		   /* 将信号_signo从信号集中删除 */
int sigismember(_const sigset_t* _set,int _signo); /* 测试_signo是否在信号集中 */





