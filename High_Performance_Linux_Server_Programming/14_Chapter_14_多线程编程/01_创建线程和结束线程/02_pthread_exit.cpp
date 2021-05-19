

/*
 * Date:2021-05-19 21:09
 * filename:02_pthread_exit.cpp
 *
 */

/*
 * 线程一旦被创建好，内核就可以调度内核线程来执行start_routine函数指针指向的函数了
 * 线程函数在结束时最好调用如下函数,以确保安全、干净地退出
 */

#include <pthread.h>
void pthread_exit(void* retval);

/*
 * 通过retval参数向线程地回收者传递其退出信息
 * 它执行完之后不会返回到调用者,而且永远不会失败
 */

