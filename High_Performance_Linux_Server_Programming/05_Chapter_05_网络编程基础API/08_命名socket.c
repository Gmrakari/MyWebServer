#include <sys/types.h>
#include <sys/socket.h>
int bind(int sockfd,const struct sockaddr* my_addr,socklen_t addrlen);

bind将my_addr所指的socket地址分配给未命名的sockfd文件描述符，addrlen参数指出该socket地址的长度

bind成功时返回0 失败则返回-1 并设置errno。-- 其中常见的errno有两种 EACCES和EADDRINUSE

EACCES，被绑定的地址受保护的地址，仅超级用户能够访问

EADDRINUSE，被绑定的地址正在使用中。



