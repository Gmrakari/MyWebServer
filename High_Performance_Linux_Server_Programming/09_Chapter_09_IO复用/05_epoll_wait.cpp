
//epoll系列系统调用的主要接口是epoll_wait函数
//它在一段超时时间内等待一组文件描述符上的事件

#include <sys/epoll.h>
int epoll_wait(int epfd,struct epoll_event* events,int maxevents,int timeout);

//maxevents参数指定最多监听多少个事件，它必须大于0

//epoll_wait函数如果检测到事件，就将所有就绪的事件从内核事件表(由epfd参数指定)中复制到它的第二个参数events指向的数组中
//这个数组只用于输出epoll_wait检测到的就绪时间，
//而不像seletct和poll的数组参数那样即用于传入用户注册的时间，又用于输出内核检测到的就绪事件
