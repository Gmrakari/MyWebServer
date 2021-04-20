
#include <signal.h>
typedef void (*__sighandler_t) (int);

//用户自定义信号

#include <bits/signum.h>
#define SIG_DFL ((__sighandler_t) 0)
#define SIG_IGN ((__sighandler_t) 1)

//SIG_IGN表示忽略目的信号，SIG_DFL表示使用信号的默认处理方式
//信号的默认处理方式有以下几种：
//结束进程(Term)、忽略信号(Ign)、结束进程并生成核心转储文件(Core)、暂停进程(Stop),以及继续进程(Cont)


