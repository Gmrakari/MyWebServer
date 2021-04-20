

//getnameinfo函数能通过socket地址同时获得以字符串表示的主机名(内部使用的是gethostbyaddr函数)和服务名(内部使用的是getservbyport函数）

#include <netdb.h>
int getnameinfo(const struct sockaddr* sockaddr,socklen_t addrlen,char* host,socklen_t hostlen,char* serv,socklen_t servlen,int flags);


//Linux下strerror函数能将数值错误码errno转换成易读的字符串形式
//下面的函数可将P99错误码转换成其它字符串形式

#include <netdb.h>
const char* gai_strerror(int error);
