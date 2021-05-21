

/*
 * Date:2021-05-21 20:30
 * filename:03_POSIX_sem.cpp
 *
 */

/*
 * 和多进程程序一样，多线程程序也必须考虑同步问题
 * pthred_koin可以看作一种简单的线程同步方式，不过它无法高效地实现复杂地同步需求，
 * 比如控制对共享资源地独占式访问，又抑或是在某个条件满足之后唤醒一个线程
 * 3种专门用于线程同步地机制:POSIX信号量,互斥量和条件变量
 */

/*
 * POSIX信号量
 */

#include <semaphore.h>

/*
 * 用于初始化一个为命名地信号量(POSIX信号量API支持命令信号量)
 * pshared 参数指定信号量地类型.如果其值为0，就表示这个信号量是当前进程地局部信号量
 * 否则该信号量就可以在多个进程之间共享
 * value参数指定信号量地初始值。此外，初始化一个已经被初始化地信号量将导之不可预期地结果
 */
int sem_init(sem_t* sem, int pshared, unsigned int value);

/*
 * sem_destroy 用于销毁信号量，以解释其占用地内核资源
 * 如果销毁一个正被其它线程等待额信号量，则将导致不可预期地结果
 */
int sem_destroy( sem_t* sem );

/*
 * sem_wait 以原子操作地方式将信号量的值减1
 * 如果信号量的值为0，则sem_wait将被阻塞，直到这个信号量具有非0值
 */
int sem_wait( sem_t* sem );

/*
 * sem_trywait与sem_wait函数相似，不过它始终立即返回，而不论被操作的信号量是否具有非0值，
 * 相当于sem_wait的非阻塞版本。当信号量的值非0时，sem_trywait对信号量执行-1操作。
 * 当信号量的值为0时，它将返回-1并设置errno为EAGAIN
 */
int sem_trywait( sem_t* sem );

/*
 * 以原子操作的方式将信号量的值增加1.当信号量的值大于0时，其它正在调用sem_wait等待信号量的线程被唤醒
 */
int sem_post(sem_t* sem);


