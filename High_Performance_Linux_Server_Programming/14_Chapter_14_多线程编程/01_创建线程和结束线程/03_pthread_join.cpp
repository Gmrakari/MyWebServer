

/*
 * Date:2021-05-19 21:12
 * filename:03_pthread_join.cpp
 *
 */

/*
 * 一个进程中的所有线程都可以调用pthread_join函数来回收其它线程(前提是目标线程是可回收的)，
 * 等待其它线程结束,这类似于回收进程的wait和waitpid系统调用
 */

#include <pthread.h>
int pthread_join(pthread_t thread,void** retval);

/*
 * thread参数是目标线程的标识符,retval参数则是目标线程返回的退出信息
 * 该函数会一直阻塞,直到被回收的线程结束为止
 * 该函数成功时返回0，失败时返回错误码
 */

/*
 * EDEADLK:可能引起死锁
 * EINVAL:目标线程不可回收的，或者已经又其它线程在回收该目标线程
 * ESRCH:目标线程不存在
 */

