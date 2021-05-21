

/*
 * Date:2021-05-21 20:44
 * filename:04_mutex.cpp
 *
 */

/*
 * 互斥锁(也称互斥量) 可以用于保护关键代码段，以确保其独占式的访问
 * 当进入关键代码段时，我们需要获得互斥锁并将其加锁；
 * 当离开关键代码段时，我们需要对互斥锁解锁，以唤醒其他等待该互斥锁的线程
 */

/*
 * 互斥锁基础API
 */

#include <pthread.h>
int pthread_mutex_init( pthread_mutex_t* mutex, const pthread_mutexattr_t* mutexattr );

int pthread_mutex_destroy( pthread_mutex_t* mutex );
int pthread_mutex_lock( pthread_mutex_t* mutex );
int pthread_mutex_trylock( pthread_mutex_t* mutex );
int pthread_mutex_unlock( pthread_mutex_t* mutex );

/*
 * 一个参数mutex指向要操作的目标互斥锁，互斥锁的类型是pthread_mutex_t结构体
 *
 * pthread_mutex_init 函数用于初始化互斥锁。mutexattr参数指定互斥锁的属性
 * 如果将它设置为NULL，则表示使用默认属性
 * 还可以用 pthread_mutex_t mutex = PTHREAD_MUTEX_INITALIZER;初始化一个互斥锁
 * 宏PTHREAD_MUTEX_INITALIZER 实际上只是把互斥锁的各个字段都初始化为0
 *
 * pthread_mutex_destroy 用于销毁互斥锁，以释放其占用的内核资源
 * 销毁一个已经加锁的互斥锁导致不可预期的后果
 *
 * pthread_mutex_lock 函数以原子操作的方式给一个互斥锁加锁
 * 如果目标互斥锁已经被锁上，则pthread_mutex_lock 调整将阻塞,直到互斥锁的占有者将其解锁
 *
 * pthread_mutex_trylock 与 pthread_mutex_lock 函数相似不过它始终立即返回，
 * 而不论被操作的互斥锁是否已经被加锁，相当于pthread_mutex_lock的非阻塞版本。
 * 当目标互斥锁未被加锁时，pthread_mutex_trylock对互斥锁执行加锁操作。
 * 当互斥锁已经被加锁时,pthread_mutex_trylock将返回错误码EBUSY
 *
 * pthread_mutex_unlock 函数以原子的操作的方式给互斥锁解锁。
 * 如果此时有其他线程正在等待这个互斥锁，则这些线程中的某一个将获得它。
 */
