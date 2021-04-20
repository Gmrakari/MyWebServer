
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int connect(int sockfd,const struct sockaddr *serv_addr,socklen_t addrlen);

//sockfd由soket系统调用返回一个socket。serv_addr参数是服务器监听的socket地址
//addrlen参数则指定这个地址的长度

//connect成功时返回0，一旦成功建立连接，sockfd就唯一地标识了这个连接，客户端就可以通过读写sockfd来与服务器通信。而失败返回-1 并设置errno
//ECONNREFUSED 目标端口不存在
//ETIMEDOUT 连接超时
//
