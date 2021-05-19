

/*
 * Date:2021-05-19 20:57
 * filename:01_pthread_create.cpp
 *
 */

#include <pthread.h>
int pthread_create(pthread_t* thread,const pthread_attr_t* attr,void* (*start_routine)(void *),void* arg);

/*
 * thread 参数是新线程的标识符,后续pthread_*函数通过它来引用新线程。
 * 其类型如下:
 */
#include <bits/pthreadtypes.h>
typedef unsigned long int pthread_t;

/*
 * pthread_t 是一个整型类型
 * Linux上几乎所有的资源标识符都是一个整型数，比如socket,各种System V IPC标识符等
 *
 * arrt参数用于设置新线程的属性。给它传递NULL表示使用默认线程属性。线程拥有众多属性
 *
 * start_routine 和 arg 参数分别指定新线程将运行的函数及其参数
 *
 * pthread_create成功时返回0，失败时返回错误码
 * 一个用户可以打开的线程数量不能超过RLIMIT_NPROC软资源限制
 * 此外,系统上所有用户能创建的线程总数也不能超过/proc/sys/kernel/threads-max内核参数所定义的值
 */


