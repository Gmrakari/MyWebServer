
//epoll是Linux特有的I/O复用函数
//首先,epoll使用一组函数来完成任务，而不是单个函数
//其次，epoll把用户关心的文件描述符上的事件放在内核里的一个时间表中，
//从而无需像seletct和poll那样每次调用都要重复传入文件描述符集或事件集

//但epoll需要使用一个额外的文件描述符，来唯一标识内核中的这个事件表

#include <sys/epoll.h>
int epoll_create(int size);

//下面的函数用来操作epoll的内核事件表
#include <sys/epoll.h>

int epoll_ctl( int epfd,int op,int fd,struct epoll_event *event )

//op指定操作类型
//EPOLL_CTL_ADD 往事件表中注册fd上的事件
//EPOLL_CTL_MOD 修改fd上的注册事件
//EPOLL_CTL_DEL 删除fd上的注册事件

//event 参数指定事件，它是epoll_event结构指针类型

struct epoll_event
{
	__uint32_t events;//epoll事件
	epoll_data_t data;//用户数据
};

typedef union epoll_data
{
	void* ptr;
	int fd;
	uint32_t u32;
	uint64_t u64;
}epoll_data_t;


