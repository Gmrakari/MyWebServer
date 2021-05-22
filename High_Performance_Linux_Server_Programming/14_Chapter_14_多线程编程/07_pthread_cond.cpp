

/*
 * Date:2021-05-22 19:48
 * filename:07_pthread_cond.cpp
 *
 */

/*
 * 如果说互斥锁是用于同步线程对共享数据的访问的话，那么条件变量则是用于在线程之间同步共享数据的值
 * 条件变量提供了一种线程间的通知机制:当某个共享数据达到某个值的时候,唤醒等待这个共享数据的线程。
 */

#include <pthread.h>

int pthread_cond_init( pthread_cond_t* cond, pthread_condattr_t* cond_attr );
int pthread_cond_destroy( pthread_cond_t* cond);
int pthread_cond_broadcast( pthread_cond_t* cond );
int pthread_cond_signal( pthread_cond_t* cond );
int pthread_cond_wait( pthread_cond_t* cond, pthread_mutex_t* mutex);

/*
 * 第一个参数cond 指向要操作的目标条件变量，条件变量的类型是pthread_cond_t结构体
 * 
 * pthread_cond_init函数用于初始化条件变量。cond_attr参数指定条件变量的属性。
 * 如果将它设置为NULL,则表示使用默认属性。条件变量的属性不多，而且和互斥锁的属性类型相似
 * 除了pthread_cond_init函数外，我们还可以使用:
 * pthread_cond_t cond = PTHREAD_COND_INITALIZER;
 * 宏PTHREAD_COND_INITALIZER实际上只是把条件变量的各个字段都初始化为0
 *
 * pthread_cond_destroy函数用于销毁条件变量，以释放其占用的内核资源。
 * 销毁一个正在被等待的条件变量将失败并返回EBUSY
 *
 * pthread_cond_broadcast函数以广播的方式唤醒所有等待目标条件变量的线程
 * 
 * pthread_cond_signal函数用于唤醒一个等待目标条件变量的线程。至于哪个
 * 线程被唤醒，则取决于线程的优先级和调度策略。有时候我们可能想唤醒一个指定的
 * 线程,但pthread没有对该需求提供解决方法。不过我们可以间接地实现该需求:
 * 定义一个能够唯一表示目标线程的全局变量,在唤醒等待条件变量的线程前先设置该变量为目标线程，
 * 然后采用广播方式唤醒所有等待条件变量，这些线程被唤醒后都检查该变量以判断被唤醒的是否是自己，
 * 如果是就开始执行后续代码，如果不是则返回继续等待。
 *
 * pthread_cond_wait函数用于等待目标条件变量
 * mutex参数是用于保护条件爱你变量的互斥锁,以确保pthread_cond_wait操作的原子性
 * 在调用pthread_cond_wait前，必须确保互斥锁mutex已经加锁,否则将导致不可预期的结果。
 * pthread_cond_wait函数执行时，首先把调用线程放入条件变量的等待队列中，然后将互斥锁mutex解锁
 *
 * 可见，从pthread_cond_wait开始执行到其调用线程被放入条件变量的等待队列之间的这段时间内
 * pthread_cond_signal和pthread_cond_broadcast等函数不会修改条件变量
 *
 * pthread_cond_wait函数不会错过目标条件变量的任何变化，
 * 当pthread_cond_wait函数成功返回时，互斥锁mutex将再次被锁上
 */


