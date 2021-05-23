

/*
 * Date:2021-05-23 18:06
 * filename:11_a_pthread_handdle_all_singal.cpp
 *
 */

/*
 * 线程和信号
 * 每个线程都可以独立地设置信号掩码。
 * 
 * 进程中信号掩码地函数sigprocmask,但是在多线程环境下我们应该使用pthread版本的sigprocmask函数来设置线程信号掩码:
 */
#include <pthread.h>
#include <signal.h>
int pthread_sigmask(int how, const sigset_t* newmask, sigset_t* oldmask);

/*
 * 由于进程中的所有线程共享该进程的信号，所以线程库将根据线程掩码决定把信号发送给哪个具体的线程。
 * 因此，如果我们在每个子线程中都单独设置信号掩码，就很容易导致逻辑错误。
 * 此外，所有线程共享信号处理函数。
 * 也就是说,当我们在一个线程中设置了某个信号的信号处理函数后，它将覆盖其他线程为同一个信号设置的信号处理函数。
 * 这两点说明，我们应该定义一个专门的线程来处理所有的信号。
 *
 * 通过两个步骤实现:
 * 1、在主线程创建出其他子线程之前就调用pthread_sigmask来设置好信号掩码,所有新创建的在进程都将自动继承这个信号掩码
 * 这样做之后，实际上所有线程都不会影响被屏蔽的信号了
 * 2、在某个线程中调用如下函数来等待信号并处理：
 *
 */
#include <signal.h>
int sigwait( const sigset_t* set,int* sig );
/*
 * set参数指定需要等待的信号的集合。
 * 我们可以简单地将其指定为第一步中创建的信号掩码，表示在该线程中等待所有被屏蔽的信号
 * 参数sig指向的整数用于存储函数返回接收到的信号做处理了
 *
 * 很显然，如果我们使用了sigwait，就不应该再为信号设置信号处理函数了。
 * 这是因为当程序接收到信号时，二者中只能有一个起作用
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>

#define handle_error_en(en,msg) \
	do { errno = en;perror(msg);exit(EXIT_FAILURE); } while (0)

static void *sig_thread( void *arg ) {
	sigset_t *set = (sigset_t *) arg;
	int s,sig;
	for( ;; ) {
		/* 第二个步骤，调用sigwait等待信号 */
		s = sigwait(set, &sig);
		if (s != 0)
			handle_error_en(s, "sigwait");
		printf("Signal handling thread got signal %d\n",sig);
	}
}

int main(int argc, char* argv[]) {
	pthread_t thread;
	sigset_t set;
	int s;

	/* 第一个步骤，在主线程中设置信号掩码 */
	sigemptyset( &set );
	sigaddset(&set, SIGQUIT);
	sigaddset(&set, SIGUSR1);
	s = pthread_sigmask(SIG_BLOCK, &set, NULL);
	if (s != 0) 
		handle_error_en(s,"pthread_sigmask");

	s = pthread_create(&thread, NULL, &sig_thread, (void *)&set);
	if( s != 0 )
		handle_error_en(s, "pthread_create");

	pause();
}

/*
 * 最后pthread还提供了下面的方法，使得我们可以明确地将一个信号发送给指定的线程:
 */
//#include <signal.h>
int pthread_kill( pthread_t thread, int sig );
/*
 * thread指定目标线程
 * sig参数指定等待发送的信号
 * 如果sig = 0,则pthread_kill不发送信号，但它仍然会执行检查错误
 * 我们可以利用这种方式检测目标线程是否存在
 */
