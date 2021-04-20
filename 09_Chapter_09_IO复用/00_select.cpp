

#include <sys/select.h>

int select(int nfds,fd_set* readfds,fd_set* writefds,fd_set* exceptfds,struct timeval* timeout);

//nfds参数指定被监听的文件描述符的总数。它通常被设置为select监听的所有文件描述符中的最大值加1，因为文件描述符是从0开始计数的

//readfds、wirtefds和exceptfds参数分别指向可读、可写和异常等事件对应的文件描述符集合。
//应用程序调用select函数时，通过这3个参数传入自己感兴趣的文件描述符
//select调用返回时，内核将修改它们来通知应用程序哪些文件描述符已经就绪。

//这3个参数是fd_set结构指针类型

#include <typesizes.h>
#define __FD_SETSIZE 1024
#include <sys/select.h>

#define FD_SETSIZE __FD_SETSIZE
typedef long int __fd_mask;

#undef __NFDBITS
#define __NFDBITS (8 * (int) sizeof(__fd_mask))
typedef struct
{
#ifdef __USE_XOPEN
	__fd_mask fds_bits[ __FD_SETSIZE / __NFDBITS ];
#define __FDS_BITS(set) ((set)->fds_bits)
#else
	__fd_mask __fds_bits[ __FD_SETSIZE / __NFDBITS ];
#define __FDS_BITS(set) ((set)->__fds_bits)
#endif
}fd_set;

#include <sys/select.h>
FD_ZERO( fd_set *fdset );				//清楚fdset的所有位
FD_SET( int fd,fd_set *fdset );			//设置fdset的位fd
FD_CLR( int fd,fd_set *fdset );			//清楚fdset的位fd
int FD_ISSET(int fd,fd_set *fdset);		//测试fdset的位fd是否被设置


//timeout参数用来设置select函数的超时时间，他是一个timeval结构类型的指针，采用指针参数是因为内核将修改它以告诉应用程序select等待多久
//不过不能完全新人select调用返回后的timeout值，比如调用失败时timeout值是不确定的

struct timeval
{
	long tv_sec;
	long tv_usec;
};

//如果给timeout变量的tv_sec成员和tv_usec成员都传递0，则select将立即返回
//如果给timeout传递NULL,则select将一直阻塞,知道某个文件描述符就绪


