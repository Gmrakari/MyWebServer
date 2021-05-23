

/*
 * Date:2021-05-23 17:30
 * filename:10_multi-pthread_fork.cpp
 *
 */

/*
 * 线程和进程
 */

/*
 * 如果一个多线程程序的某个线程调用了fork函数,那么新创建的子进程是否将自动创建和父进程相同数量的线程呢?
 * Anster:No
 * 子进程只拥有一个执行线程，它是调用fork的那个线程的完整赋值。并且子进程将自动继承父进程中互斥锁(条件变量与之类似)的状态。
 * 也就是说，父进程中已经被加锁的互斥锁在子进程也是被锁住的。这就引起一个问题:
 * 子进程可能不清楚从父进程继承而来的互斥锁的具体状态(是加锁状态还是解锁状态).
 * 这个互斥锁可能被加锁了,但并不是由调用fork函数的那个线程锁住的,而是由其他线程锁住的。
 * 如果是这种情况，则子进程若再次对该互斥锁执行加锁操作就会导致死锁。
 *
 */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <wait.h>

pthread_mutex_t mutex;
/* 子线程运行的函数。它首先获得互斥锁mutex,然后暂停5s，再释放该互斥锁 */
void* another( void* arg ) {
	printf("in child thread,lock the mutex\n");
	pthread_mutex_lock(&mutex);
	sleep(5);
	pthread_mutex_unlock(&mutex);
	//return 0;	
}

int main() {
	pthread_mutex_init(&mutex, NULL);
	pthread_t id;
	pthread_create( &id, NULL, another, NULL );
	/* 父进程中的主线程暂停1s,以确保在执行fork操作之前,子线程已经开始运行并获得了互斥锁变量mutex */
	sleep(1);
	int pid = fork();
	if ( pid < 0 ) {
		pthread_join(id, NULL);
		pthread_mutex_destroy(&mutex);
		return 1;
	}else if (pid == 0) {
		printf("I am in the child,want to get the lock\n");
		/* 子进程从父进程继承了互斥锁mutex的状态,该互斥锁处于锁住的状态
		 * 这事由父进程中的子线程执行pthread_mutex_lock引起的
		 * 因此，下面这句加锁操作会一直阻塞,尽管从逻辑上来说它是不应该阻塞的
		 */
		pthread_mutex_lock(&mutex);
		printf("I can not run to here,oop!\n");
		pthread_mutex_unlock(&mutex);
		exit(0);
	} else {
		wait(NULL);
	}
	pthread_join(id, NULL);
	pthread_mutex_destroy(&mutex);
	return 0;
}

/*
 * pthread提供了一个专门的函数pthread_atfork,以确保fork调用后父进程和子进程都拥有一个清楚的锁状态
 */

int pthread_atfork(void (*prepare)(void), void (*parent)(void), void (*child)(void));

/*
 * 该函数将建立3个fork句柄来帮助哦我们清理互斥锁的状态
 * prepare句柄将在fork调用创建出子进程之前被执行。它可以用来锁住所有父进程中的互斥锁
 * parent句柄则是fork调用创建出子进程之后，而fork返回之前，在父进程中被执行。它的作用是释放所有在prepare句柄中被锁住的互斥锁
 * child句柄是fork返回之前，在子进程中被执行。和parent句柄一样,child句柄也是用于释放所有在prepare句柄中被锁住的互斥锁
 * 该函数成功时返回0，失败时返回错误码
 */

void prepare() {
	pthread_mutex_lock(&mutex);
}

void infork() {
	pthread_mutex_unlock(&mutex);
}

pthread_atfork(prepare,infork,infork);
