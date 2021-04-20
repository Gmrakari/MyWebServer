
#include <signal.h>
_sighandler_t signal (int sig,_sighandler_t _handler)

//sig_参数指出要捕获的信号类型
//_handler参数是_sighandler_t类型的函数指针，用于指定信号sig的处理函数

//signal函数成功时返回一个函数指针，该函数指针的类型也是_sighandler_t

//signal系统调用出错时返回SIG_ERR,并设置errno


