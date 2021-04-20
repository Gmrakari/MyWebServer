#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>

int accept(int sockfd,struct sockaddr *addr,socklen_t *addrlen);

//sockfd参数是执行过listen系统调用的监听socket
//addr参数用来获取被接受连接的远端socket地址，该socket地址的长度由addrlen参数指出
//accept成功时返回一个新的连接socket，该socket唯一地标识了被接受的这个连接，服务器可通过读写该socket来与被接受连接对应的客户端通信



