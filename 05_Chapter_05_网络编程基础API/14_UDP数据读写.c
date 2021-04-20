#include <sys/types.h>
#include <sys/socket.h>

ssize_t recvfrom(int sockfd,void* buf,size_t len,int flag,struct sockaddr* src_addr,socklen_t* addrlen);

ssize_t sendto(int socket,const void* buf,size_t len,int flags,const struct sockaddr* dest_addr,socklen_t addrlen);

//buf和len分别指定读缓冲区的位置和大小 
//因为UDP通信没有链接的概念，所以我们每次读取数据都需要获取发送端的socket的地址，即参数src_addr所指的内容，addrlen是指定该地址的长度


//dest_addr是指定接受端的socket地址，addrlen参数则指定该地址的长度


//flags 见TCP
