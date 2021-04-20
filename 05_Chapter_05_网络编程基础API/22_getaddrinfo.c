

#include <netdb.h>
int gwtaddrinfo( const char* hostname,const char* service,const struct addrinfo* hints,struct addrifo** result);

//hostname接受主机名，也可以接收字符串表示的IP地址（IPV4采用点分十进制字符串）

//service接收服务名，也可以接收字符串表示的十进制端口号

//hints是应用程序给getaddrinfo的一个提示，以对getaddrinfo的输出进行更精确的控制
//hints可以被设置为NULL，表示允许getaddrinfo反馈任何可用的结果

//result参数指向一个链表，该链表用于存储getaddrinfo反馈的结果


//getaddrinfo反馈的每一条结果都是addrinfo结构体类型的对象，结构体addrinfo的定义如下
struct addrinfo
{
	int ai_flags;
	int ai_family;
	int ai_socktype;
	int ai_protocol;
	socklen_t ai_addrlen;
	char* ai_canonname;
	struct sockaddr* ai_addr;
	struct addrinfo* ai_next;
};


//使用getaddrinfo函数
struct addrinfo hints
struct addrinfo* res;

bzero(&hints,sizeof(hints));
hints.ai_socktype = SOCK_STREAM;
getaddrinfo("ernest-laptop","daytime",&hints,&res);


//getaddrinfo将隐式地分配堆内存，因为res指针原本没有指向一块合法内存的，所以，getaddrinfo调用结束后，
//我们必须使用如下配对函数来释放这块内存
#include <netdb.h>
void freeaddrinfo(struct addrinfo* res);


