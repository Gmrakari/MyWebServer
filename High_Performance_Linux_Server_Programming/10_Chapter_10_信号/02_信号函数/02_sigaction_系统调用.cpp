
#include <signal.h>
int sigaction(int sig,const struct sigaction* act,struct sigaction* oact);

//sig 捕获的信号类型
//act 指定新的信号处理方式
//oact 则输出信号先前的处理方式(如果不为NULL的话)

//act & oact 都是sigaction结构体类型的指针

struct sigaction
{
#ifdef __USE_POSIX199309
	union
	{
		_sighandler_t sa_handler;
		void (*sa_sigaction) (int,siginfo_t*,void *);
	}
	_sigaction_handler;
#define sa_handler __sigaction_handler.sa_handler
#define sa_sigaction __sigaction_handler.sa_sigaction
	_sighandler_t sa_handler;
#endif
	_sigset_t sa_mask;
	int sas_flags;
	void (*sa_restorer) (void);
};

// sa_hander 成员指定喜好处理函数
// sa_mask  成员设置进程的信号掩码,以指定哪些信号不能发送给本进程
// sa_make 是信号集sigset_t类型，该类型指定一组信
