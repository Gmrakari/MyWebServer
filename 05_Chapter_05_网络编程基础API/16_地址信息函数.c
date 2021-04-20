#include <sys/socket.h>

int getsockname(int sockfd,struct sockaddr* address,socklen_t* address_len);
int getpeername(int sockfd,struct sockaddr* address,socklen_t* address_len);

//获取sockfd对应的本端socket地址，并将其存储于address参数指定的内存中，该socket地址的长度则存储于address_len参数指向的变量中。
//如果实际socket地址的长度大于address所指内存区的大小，那么该socket地址将被截断


//getpeername获取sockfd对应的远端socket地址，其参数及返回值的含义与getsockname的参数及返回值相同
