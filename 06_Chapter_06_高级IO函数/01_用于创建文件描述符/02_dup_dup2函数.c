

#include <unistd.h>
int dup(int file_descriptor);
int dup2(int file_descriptor_one,int file_descriptor_two);

//dup函数创建一个新的文件描述符，该新文件描述符和原有文件描述符file_descriptor指向相同的文件、管道或者网络连接。
//并且dup返回的文件描述符总是取系统当前可用的最小整数值

//dup2和dup类似，不过它将返回第一个不小于file_descriptor_two的整数值
//失败时返回-1并设置errno


