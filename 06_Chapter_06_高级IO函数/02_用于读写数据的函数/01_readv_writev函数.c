

//readv函数将数据从文件描述符读到分散的内存块中，即分散读
//writev函数将多块分散的内存数据一并写入文件描述符中，即集中写

#include <sys/uio.h>
ssize_t readv(int fd,const struct iovec* vector,int count);
ssize_t writev(int fd,const struct iovec* vector,int count);

//fd参数是被操作的目标文件描述符
//vector参数的类型是iovec结构体数组 见Chapter_05,该结构体描述一块内存区
//count参数是vector数组的长度，即有多少块内存数据需要从fd读出或写到fd。
//readv和writev在成功时返回读出/写入fd的字节数，失败时则返回-1并设置errno
