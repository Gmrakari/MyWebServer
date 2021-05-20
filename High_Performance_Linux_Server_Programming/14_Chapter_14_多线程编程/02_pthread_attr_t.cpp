

/*
 * Date:2021-05-20 21:04
 * filename:02_pthread_attr_t.cpp
 *
 */

/*
 * 线程属性
 * pthread_attr_t结构体定义了一套完整的线程属性
 */
#include <bits/pthreadtypes.h>
#define __SIZEOF_PTHREAD_ATTR_T 36
typedef union
{
		char __size[__SIZEOF_PTHREAD_ATTR_T];
		long int __align;
}pthread_attr_t;

/*
 * 线程属性全部包含在一个字符数组中
 * 线程库定义了一系列函数来操作pthread_attr_t类型的变量,以方便我们获取和设置线程属性
 */
#include <pthread.h>

/*init*/
int pthread_attr_init (pthread_attr_t* attr);

/* 销毁线程属性对象.被销毁的线程属性对象只有再次初始化之后才能继续使用 */
int pthread_attr_destroy (pthread_attr_t* attr);

//get && set attr

//detachstate 线程的脱离状态
//它有PTHREAD_CREATE_JOINABLE和PTHREAD_CREATE_DETACH两个可选值
//前者指定线程是可以被回收的,后者使调用线程脱离与进程中其它线程的同步
//脱离了与其它线程同步的线程称为"脱离线程"。脱离线程在退出时将自行释放其占用的系统资源
int pthread_attr_getdetachstate (const pthread_attr_t* attr, int* detachstate);
int pthread_attr_setdetachstate (pthread_attr_t* attr, int detachstate);

// stackaddr 和 stacksize 线程堆栈的起始地址和大小
int pthread_attr_getstackaddr (const pthread_attr_t* attr, void ** stackaddr);
int pthread_attr_setstackaddr (pthread_attr_t* attr, void* stackaddr);

int pthread_attr_getstacksize (const pthread_attr_t* attr, size_t* stacksize);
int pthread_attr_setstacksize (pthread_attr_t* attr, size_t stacksize);

int pthread_attr_getstack (const pthread_attr_t* attr, void** stackaddr, size_t* stacksize);
int pthread_addr_setstack (pthread_attr_t* attr, void* stackaddr, size_t stacksize);

//guardsize 保护区域大小
//如果guardsize > 0 则系统创建线程的时候会在其堆栈的尾部额外发呢配guardsize字节的空间
//作为保护堆栈不被错误地覆盖地区域。
//如果guardsize = 0 则系统不为新创建地线程设置堆栈保护区
//如果使用者通过pthread_attr_setstackaddr 或 pthread_attr_setstack函数手动设置线程的堆栈,
//guardsize属性将忽略
int pthread_attr_getguardsize (const pthread_attr_t *__attr, size_t* guardsize);
int pthread_attr_setguardsize (pthread attr_t* attr,size_t guardsize);

//schedparam,线程调度参数
//其类型是sched_param结构体
//该结构体目前还只有一个整型类型的成员--shed_priority,该成员表示线程的运行优先级
int pthread_attr_getschedparam (const pthread_attr_t* attr, struct sched_param* param);
int pthread_attr_setschedparam (pthread_attr_t* attr, const struct sched_param* param);

//schedpolicy 线程调度策略
//该属性有SHED_FIFO,SCHED_RR,SCHED_OTHER三个可选值
//其中SCHED_OTHER是默认值。
//SCHED_RR表示采用轮转算法(round-robin)调度
//SCHED_FIFO表示使用先进先出的方法调度
//这两种调度方法都具备实时调度功能,但只能用于以超级用户身份运行的进程
int pthread_attr_getschedpolicy (const  pthread_attr_t* attr, int* policy);
int pthread_attr_setschedpolicy (pthread_attr_t* attr, int policy);

//inheritshed 是否继承调用线程的调度属性
//该属性有PTHREAD_INHERIT_SCHED和PTHREAD_EXPLICIT_SCHED两个可选值
//前者表示新线程沿用其创建者的线程调度参数，这种情况下再设置新线程的调度参数属性将没有任何效果
//后者表示调用者要明确地指定新线程地调度参数
int pthread_attr_getinheritsched (const pthread_attr_t* attr, int* inherit);
int pthread_attr_setinheritsched (pthread_attr_t* attr, int inherit);

//scope 线程间竞争CPU的范围,即线程优先级的有效范围
//POSIX定义了该属性的PTHREAD_SCOPE_SYSTEM和PTHREAD_SCOPE_PROCESS两个可选值
//前者表示目标线程与系统中所有线程一起竞争CPU时间
//后者表示目标吸纳成仅与其他隶属同一进程的线程竞争CPU的使用
int pthread_attr_getscope (const pthread_attr_t* attr, int* scope);
int pthread_attr_setscope (pthread_attr_t* attr, int scope);


