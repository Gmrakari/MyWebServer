

/*
 * Date:2021-12-06 10:07
 * filename:main.cpp
 *
 */

#include <sys/epoll.h>
#include <queue>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <unistd.h>

using namespace std;

const int THREADPOOL_THREAD_NUM = 4;
const int QUEUE_SIZE = 65535;

const int PORT = 8888;
const int ASK_STATIC_FILE = 1;
const int ASK_IMAGE_STITCH = 2;

const string PATH = "/";

const int TIMER_TIME_OUT = 500;

extern pthread_mutex_t qlock;
extern struct epoll_event* events;
void acceptConnection(int listen_fd, int epoll_fd, const string &path);

extern priority_queue<mytimer*, deque<mytimer*>, timerCmp> myTimerQueue;

int socket_bind_listen(int port) {
	if (port < 1024 || port > 65535)
		return -1;

	int listen_fd = 0;
	if (-1 == (listen_fd = socket(AF_INET, SOCK_STREAM, 0))) 
		return -1;

	//消除bind时出现"Address alread in use"错误
	int optval = 1;
	if (-1 == (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval))))
		return -1;

	//设置服务器IP和PORT 和监听描述符绑定
	struct sockaddr_in server_addr;
	bzero((char*)&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons((unsigned short)port);
	if (-1 == (bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr))))
		return -1;

	//开始监听，最大等待队列长为LISTENQ
	if (listen(listen_fd, LISTENQ) == -1)
		return -1;

	//无效监听描述符
	if (listen_fd == -1) {
		close(listen_fd);
		return -1;
	}

	return listen_fd;
}

void myHandler(void* args) {
	requestData* req_data = (requestData*)args;//因为在main函数一开始epoll事件结构体的event.data.ptr
	//项就是用requestData转换过去的，所以这里可以转换回来
	req_data->handleRequest();
}
