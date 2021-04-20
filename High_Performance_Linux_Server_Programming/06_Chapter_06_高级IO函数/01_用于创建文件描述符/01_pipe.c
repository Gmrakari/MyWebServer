
#include <unistd.h>
int pipe(int fd[2]);

//pipe函数的参数是一个包含两个int型整数的数组指针。
//该函数成功时返回0，并将一对打开的文件描述符值填入其参数指向的数组
//如果失败，则返回-1并设置errno

//此外，socket的基础API中有一个socketpair函数，它能够方便地创建双向管道。
#include <sys/types.h>
#include <sys/socket.h>

int socketpair(int domain,int type,int protocol,int fd[2]);


