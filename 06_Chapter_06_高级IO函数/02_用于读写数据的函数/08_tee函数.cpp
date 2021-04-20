
//tee函数在两个管道文件描述符之间复制数据，也是零拷贝操作
//它不消耗数据，因此源文件描述符上的数据仍然可以用于后续的读操作


#include <fcntl.h>
ssize_t tee(int fd_in,int fd_out,size_t len,unsigned int flags);

//该函数的参数的含义与splice相同(但fd_in和fd_out必须都是管道文件描述符)

