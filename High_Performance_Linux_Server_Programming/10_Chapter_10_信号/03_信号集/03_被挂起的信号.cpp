
//设置进程信号掩码后，被屏蔽的信号将不能被进程接收
//如果给进程发送一个被屏蔽的信号，则操作系统将该信号设置为进程的一个被挂起的信号
//如果我们取消对被挂起信号的屏蔽，则它能立即被进程接收到

#include <signal.h>
int sigpending(sigset_t* set);

//set参数用于保存被挂起的信号集



//注意
//要始终清楚地知道进程在每个运行时刻的信号掩码，以及如何适当地处理捕获到的信号。
//在多进程、多线程环境中，我们要以进程、线程为单位来处理信号和信号掩码


