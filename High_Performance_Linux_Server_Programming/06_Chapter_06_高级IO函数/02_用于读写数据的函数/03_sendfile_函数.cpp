

//sendfile函数
//sendfile函数在两个文件描述符之间直接传递数据（完全在内核中操作），从而避免了内核缓冲区和用户缓冲区之间的数据拷贝，效率很高，这种称为零拷贝。
//
//sendfile的定义

#include <sys/sendfile.h>
ssize_t sendfile(int out_fd,int in_fd,off_t* offset,size_t count);

//in_fd 是待读出内容的文件描述符
//out_fd是待写入内容的文件描述符
//offset指定从读入文件流的哪个位置开始读 如果为空，则使用读入文件流默认的起始位置
//count指定在文件描述符in_fd和out_fd之间传输的字节数
//sendfile成功时返回传输的字节数，失败则返回-1并设置errno
