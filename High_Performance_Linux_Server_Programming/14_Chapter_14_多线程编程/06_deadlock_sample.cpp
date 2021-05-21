

/*
 * Date:2021-05-21 21:16
 * filename:06_deadlock_sample.cpp
 *
 */

/*
 * 死锁使得一个或多个线程被挂起而无法继续执行，而且这种情况还不容易被发现
 * 在一个线程种对一个已经加锁的普通所再次加锁，将导致死锁
 * 这种情况可能出现在设计得不够仔细得递归函数种
 * 另外，如果两个线程按照不同得顺序来申请两个互斥锁，也容易产生死锁
 */

#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
int pthread_create(pthread_t* thread,const pthread_attr_t* attr,void* ( *start_routine ) (void*),void* arg);
int pthread_join(pthread_t thread,void** retval);

int a = 0;
int b = 0;

pthread_mutex_t mutex_a;
pthread_mutex_t mutex_b;

void* another( void* arg ) {
	pthread_mutex_lock( &mutex_b );
	printf("in child thread,got mutex b,waiting for mutex a\n");
	sleep(5);
	++b;
	pthread_mutex_lock( &mutex_a );
	b += a++;
	pthread_mutex_unlock( &mutex_a );
	pthread_mutex_unlock( &mutex_b );
	pthread_exit( NULL );

}

int main() {
	pthread_t id;

	pthread_mutex_init( &mutex_a, NULL);
	pthread_mutex_init( &mutex_b, NULL);

	pthread_create( &id, NULL, another, NULL );

	pthread_mutex_lock( &mutex_a );
	printf("in parent thread,got mutex a,waiting for mutex b\n");
	sleep(5);
	++a;
	pthread_mutex_lock( &mutex_b );
	a += b++;
	pthread_mutex_unlock( &mutex_b );
	pthread_mutex_unlock( &mutex_a );

	pthread_join(id,NULL);
	pthread_mutex_destroy( &mutex_a );
	pthread_mutex_destroy( &mutex_b );
	return 0;
}

/*
 * 主线程试图先占有互斥锁mutex_a，然后操作被该加锁保护得变量a,
 * 但操作完毕之后，主线程并没有立即释放互斥锁mutex_a，而是又申请互斥锁mutex_b，
 * 并在两个互斥锁得保护下,操作变量a和b，最后才一起释放这两个互斥锁;
 * 与此同时，子线程按照相反的顺序来申请互斥锁mutex_a和mutex_b，并在两个锁的保护下操作变量a和变量b
 * 用们用sleep函数来模拟连续两次调用pthread_mutex_lock之间的时间差，以确保代码种的两个线程各自先占有一个互斥锁
 * (主线程占有mutex_b,子线程等待mutex_a)。这样，两个线程就僵持住了，谁都不能继续往下执行
 * 从而形成死锁。如果代码种不加入sleep函数，则这段代码或许能成功地运行，从而为程序留下了一个潜在地BUG
 */

