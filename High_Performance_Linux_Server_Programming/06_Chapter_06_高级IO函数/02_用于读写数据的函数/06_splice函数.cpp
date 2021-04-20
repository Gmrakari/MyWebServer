
//splice函数用于两个文件描述符之间移动数据，也是零拷贝操作。

#include <fcntl.h>
ssize_t splice(int fd_in,loff_t* off_in,int fd_out,loff_t* off_out,size_t len,unsigned int flags);

//fd_in参数是待输入数据的文件描述符。如果fd_in是一个管道文件描述符，那么off_in参数必须被设置为NULL。如果fd_in不是一个管道文件描述符(比如socket)，那么off_in表示从输入数据流的何处开始读取数据。此时，若off_in被设置成NULL,则表示从输入数据流的当前偏移位置读入;若off_in不为NULL，则它将指出具体的偏移位置

//fd_out/off_out参数的含义与fd_in/off_in相同，不过用于输出数据流

//len参数指定移动数据的长度flags参数则控制数据如何移动，它可以被设置为P109中的某些值的按位或


//使用splice函数时，fd_in和fd_out必须至少有一个是管道文件描述符，splice函数调用成功时返回移动字节的数量。它可能返回0,表示没有数据需要移动，这发生在从管道中读取数据(fd_in是管道文件描述符)而该管道没有被写入任何数据时。splice函数失败时返回-1并设置errno
