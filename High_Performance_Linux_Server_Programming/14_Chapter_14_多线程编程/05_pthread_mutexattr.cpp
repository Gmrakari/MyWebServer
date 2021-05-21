

/*
 * Date:2021-05-21 21:06
 * filename:05_pthread_mutexattr.cpp
 *
 */

/*
 * pthread_mutexattr_t 结构体定义了一套完整的互斥锁属性
 * 线程库提供了一系列函数来操作pthread_mutexattr_t类型的变量，以方便我们获取和设置互斥锁属性
 */

#include <pthread.h>

/* 初始化互斥锁属性对象 */
int pthread_mutexattr_init( pthread_mutexattr_t* attr );

/* 销毁互斥锁属性对象 */
int pthread_mutexattr_destroy( pthread_mutexattr_t* attr );

/* 获取和设置互斥锁的pshared属性 */
int pthread_mutexattr_getpshared( const pthread_mutexattr_t* attr, int* pshared );
int pthread_mutexattr_setpshared( pthread_mutexattr_t* attr,int pshared );

/* 获取和设置互斥锁的type属性 */
int pthread_mutexattr_gettype( const pthread_mutexattr_t* attr, int* type );
int pthread_mutexattr_settype( pthread_mutexattr_t* attr,int type );

/*
 * 互斥锁属性pshared指定是否允许跨进程共享互斥锁，其可选值有两个:
 * PTHREAD_PROCESS_SHARED 互斥锁可以被跨进程共享
 * PTHREAD_PROCESS_PRIVATE 互斥锁只能被和锁的初始化线程隶属于同一个进程的线程共享
 */

/*
 * type指定互斥锁的类型
 * Linux 提供4种类型的互斥锁
 * PTHREAD_MUTEX_NORMAL,普通锁
 * PTHREAD_MUTEX_ERRORCHECK,检错锁
 * PTHREAD_MUTEX_RECURSIVE,嵌套锁
 * PTHREAD_MUTEX_DEFAULT,默认锁
 */
