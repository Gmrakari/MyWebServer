#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <assert.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

ssize_t recv(int sockfd,void *buf,size_t len,int flags);
ssize_t send(int sockfd,const void *buf,size_t len,int flags);

//recv读取sockfd上的数据，buf和len参数分别指定读缓冲区的位置和大小，flags通常设置为0
//recv成功时返回实际读取到的数据的长度，它可能小于我们期望的长度len，因此我们需要多次调用recv，才能读取到完整的数据
//recv可能返回0 这意味着通信对方已经关闭连接了，recv出错时返回-1 并设置errno


//send往sockfd上写入数据，buf和len参数分别指定写缓冲区的位置和大小。send成功时返回实际写入的数据的长度，失败则返回-1并设置errno


