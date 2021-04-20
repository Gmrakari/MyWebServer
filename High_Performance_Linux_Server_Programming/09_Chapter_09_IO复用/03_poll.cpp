
//poll系统调用和seletct类似,也是在指定时间内轮询一定数量的文件描述符，以测试其中是否有就绪者

#include <poll.h>

int poll(struct pollfd* fds,nfds_t nfds,int timeout);

//fds参数试一个pollfd结构类型的数组，它指定所有我们感兴趣的文件描述符上发生的可读、可写和异常等事件

//pollfd结构体的定义如下
struct pollfd
{
	int fd;			//文件描述符
	short events;	//注册的事件
	short revents;	//实际发生的事件，由内核填充
};

//nfds参数指定被监听事件集合fds的大小,其类型nfds_t的定义如下
typedef unsigned long int nfds_t;

//timeout参数指定poll的超时值，单位是毫秒。当timeout为-1时，poll调用将永远阻塞，直到某个事件发生;当timeout为0时，poll调用将立即返回

//poll系统调用的返回值的含义与select相同


