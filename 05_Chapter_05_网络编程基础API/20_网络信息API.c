#include <netdb.h>

struct hostent* gethostbyname(const char* name);

struct hostent* gethostbyaddr(const void* addr,size_t len,int type);

//name 参数指定目标主机的主机名,addr参数指定目标主机的IP地址，len参数指定addr所指IP地址的长度，type参数指定addr所指IP地址的类型


#include <netdb.h>
struct hostent{
	char* h_name;			//主机名
	char** h_aliases;		//主机别名列表，可能有多个
	int h_addrtype;			//地址族
	int h_length;			//地址长度
	char** h_addr_list		//按网络字节序列出的主机IP地址列表
};

/* --------------------------------------------------------------- */

#include <netdb.h>
//gethostbyname 和 getserverbyport

struct servent* getservbyname(const char* name,const char* proto);
struct servent* getserverbyport(int port,const char* proto);

//name 指定目标服务的名字，proto--> tcp 表示获取流服务 | udp 表示获取数据报服务 
// 返回类型由下面的数据结构类型表示


#include <netdb.h>
struct servent{
	char* s_name;			//服务名称
	char** s_aliases;		//服务的别名列表，可能有多个
	int s_port;				//端口号
	char* s_proto;			//服务类型 tcp | udp
};



