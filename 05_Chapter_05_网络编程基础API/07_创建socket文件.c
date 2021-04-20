#include <sys/types.h>
#include <sys/socket.h>

int socket(int domain,int type,int protocol);

//domain -- PF_INET(Protocol Family of Internet,用于IPv4)
//type --SOCK-STREAM服务(流服务)和SOCK_UGRAM(数据报)服务 前者是TCP 后者是UDP
//protocol 参数是在前两个参数构成的协议集合下，再选择一个具体的协议。不过这个值通常都是唯一的（前两个参数已经决定）
//几乎所有情况下，我们都应该把它设置为0，表示使用默认协议


