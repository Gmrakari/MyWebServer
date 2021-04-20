

#include <sys/socket.h>

ssize_t recvmsg(int sockfd,struct msghdr* msg,int flags);
ssize_t sendmsg(int sockfd,struct msghdr* msg,int flags);

struct msghdr{
	void* msg_name;				//socket地址
	socklen_t msg_namelen;		//socket地址的长度
	struct iovec* msg_iov;		//分散的内存块
	int msg_iovlen;				//分散内存块的数量
	void* msg_control;			//指向辅助数据的起始位置
	socklen_t msg_controllen;	//辅助数据的大小
	int msg_flags;				//复制函数中的flags参数，并在调用过程中更新
};

struct iovec{
	void *iov_base;				//内存起始地址
	size_t iov_len;				//这块内存的长度
};

//msg_iovlen指定这样的iovec结构对象有多少个。对于recvmsg而言，数据将被读取并存放在msg_iovlen块分散的内存中，这些内存的位置和长度则由msg_iov指向的数组指定，这称为分散读
//对于sendmsg而言，msg_iovlen块分散内存中的数据将被一并发送，这称为集中写(gather write)


//msg_control 和 msg_controllen成员用于辅助数据的传送。13章介绍如何使用它们来实现在进程间传递文件描述符

//msg_flags 和 flags 一样

