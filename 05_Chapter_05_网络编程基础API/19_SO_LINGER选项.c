
SO_LINGER选项用于控制close系统调用在关闭TCP连接时的行为。

当我们使用close系统调用来关闭一个socket时，close将立即返回，TCP模块负责把该socket对应的TCP发送缓冲区中残留的数据发送给对方。

#include <sys/socket.h>
struct linger{
	int l_onoff;
	int l_linger;//滞留时间
};


// l_onoff = 0 不起作用，close默认行为来关闭socket

// l_onoff != 0,l_linger = 0。此时close系统调用立即返回，TCP模块将丢弃被关闭的socket对应的TCP发送缓冲区中残留的数据，同时给对方发送一个复位报文段
// 这种情况给服务器提供了异常终止一个连接的方法。

// l_onoff != 0,l_linger > 0。此时close的行为取决于两个条件：
// 一是被关闭的socket对应的TCP发送缓冲区中是否还有残留的数据
// 二是该socket是阻塞的还是非阻塞的。对于阻塞的socket,close将等待一段长为l_linger的时间，直到TCP模块发送完所有残留数据并得到对方的确认。
// 如果这段时间内TCP模块没有发送完残留数据并得到对方的确认，那么close系统调用将返回-1并设置errno为EWOULDBLOCK
// 如果socket是非阻塞，close将立即返回，此时我们需要根据其返回值和errno来判断残留数据是否已经发送完毕
