


//获取进程当前工作目录和改变进程工作目录的函数分别是:

#include <unistd.h>
char* getcwd( char* buf,size_t size );
int chdir( const char* path );

//buf参数指向的内存用于存储进程当前工作目录的绝对路径名，其大小由size参数指定

//如果当前工作目录的绝对路径的长度(再加上一个空结束符"\0")超过了size，则getcwd将返回NULL，并设置errno为ERANGE
//
//chdir函数的path参数指定要切换到的目标目录。


#include <unistd.h>
int chroot(const char* path);

//path参数制定要切换到的目标跟目录
//chroot并不改变进程的当前工作目录，所以调用chroot之后，我们仍然需要使用chdir("/")来将工作目录切换至新的根目录。
//改变进程的根目录之后，程序可能无法访问类似/dev的文件(和目录),因为这些文件(和目录)并非处于新的根目录之下。
//不过好在调用chroot之后，进程原先打开的文件描述符依然生效，所以我们可以利用这些早先打开的文件描述符来访问调用chroot之后不能直接访问的文件(和目录)
