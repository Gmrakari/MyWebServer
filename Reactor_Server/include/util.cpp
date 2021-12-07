

/*
 * Date:2021-12-06 16:58
 * filename:util.cpp
 *
 */

#include "util.h"

#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>
#include <errno.h>

ssize_t readn(int fd, void* buff, size_t n) {
	//剩余未读
	size_t nleft = n;
	//已经读了
	size_t nread = 0;
	//要读的字节数
	size_t readSum = 0;

	char* ptr = (char*)buff;
	while (nleft > 0) {
		if ((nread = read(fd, ptr, nleft)) < 0) {
			if (errno == EINTR)
				nread = 0;
			else if (errno == EAGAIN) 
				return readSum;
			else 
				return -1;
		}
		else if (nread == 0)
			break;
		readSum = readSum + nread;
		nleft = nleft - nread;
		ptr = ptr + nread;
	}
	return readSum;
}

ssize_t writen(int fd, void* buff, size_t n) {
	size_t nleft = n;
	size_t nwritten = 0;
	size_t writeSum = 0;

	char* ptr = (char*)buff;
	while (nleft > 0) {
		if ((nwritten = write(fd, ptr, nleft)) <= 0) {
			if (nwritten < 0) {
				if (errno == EINTR || errno == EAGAIN) {
					nwritten = 0;
					continue;
				}
				else
					return -1;
			}
		}
		writeSum += nwritten;
		nleft -= nwritten;
		ptr += nwritten;
	}
	return writeSum;
}

//处理sigpipei信号
void handle_for_sigpipe() {
	struct sigaction sa;//信号处理结构体
	memset(&sa, '\0', sizeof(sa));
	sa.sa_handler = SIG_IGN;//设置信号的处理回调函数，这个SIG_IGN宏代表的操作就是忽略该信号
	sa.sa_flags = 0;
	if (sigaction(SIGPIPE, &sa, NULL)) 
		return ;
}

int setSocketNonBlocking(int fd) {
	int flag = fcntl(fd, F_GETFL, 0);
	if (flag == -1)
		return -1;

	flag |= O_NONBLOCK;
	if (fcntl(fd, F_SETFL, flag) == -1)
		return -1;
	return 0;
}

