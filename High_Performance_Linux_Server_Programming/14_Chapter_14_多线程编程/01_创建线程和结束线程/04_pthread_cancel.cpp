

/*
 * Date:2021-05-19 21:16
 * filename:04_pthread_cancel.cpp
 *
 */

/*
 * 有时候我们希望异常终止一个线程,即取消线程,它是通过如下函数实现的:
 */
#include <pthread.h>
int pthread_cancel(pthread_t thread);

/*
 * thread参数是目标线程的标识符
 * 该函数成功时返回0，失败时返回错误码
 * 不过接收到取消请求的目标线程可以决定是否允许被取消以及如何取消，这分别由如下两个函数完成
 */
#include <pthread.h>
int pthread_setcancelstate(int state,int *oldstate);
int pthread_setcanceltype(int type,int *oldtype);

/*
 * 第一个参数分别用于设置线程的取消状态(是否允许取消)和取消类型(如何取消)
 * 第二个参数分别记录线程原来的取消状态和取消类型
 * state参数由两个可选值:
 * PTHREAD_CANCEL_ENABLE,允许线程被取消
 * PTHREAD_CANCEL_DISABLE,禁止线程被取消
 *
 * type也有两个可选值:
 * PTHREAD_CANCEL_ASYNCHRONOUS,线程随时都可以被取消
 * PTHREAD_CANCEL_DEFERRED,允许目标线程推迟行动，直到它调用了如下几个所谓的取消点函数中的一个:
 * pthread_join,pthread_testcancel,pthread_cond_wait,pthread_cond_timedwait,sem_wait和sigwait
 *
 * 为了安全起见,最好在可能会被取消的代码中调用pthread_testcancel函数以设置取消点
 * pthread_setcancelstate和pthread_setcanceltype成功时返回0，失败时则返回错误码
 */

