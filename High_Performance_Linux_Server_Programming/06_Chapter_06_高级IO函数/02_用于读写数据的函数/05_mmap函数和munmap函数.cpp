

//mmap函数用于申请一段内存空间。
//我们可以将这段内存作为进程间通信的共享内存，也可以将文件直接映射到其中。
//munmap函数则释放由mmap创建的这段内存空间
//

#include <sys/mman.h>
void* mmap(void *start,size_t length,int prot,int flags,int fd, off_t offset);

int munmap(void *start,size_t length);

//start允许用户使用某个特定的地址作为这段内存的起始地址 如果它被设置成NULL，则系统自动分配一个地址

//length参数则指定内存段的长度

//prot参数用来设置内存段的访问权限
//--PROT_READ,内存段可读
//--PROT_WRITE，内存段可写
//--PROT_exec,内存段可执行
//--PROT_NONE,内存段不能被访问

//flags控制内存段内容被修改后程序的行为
//--MAP_SHARED
//--MAP_PRIVATE
//--MAP_ANONYMOUS
//--MAP_FIXED
//--MAP_HUGETLB

//fd参数是被映射对应的文件描述符。它一般通过open系统调用获得。

//offset参数设置从文件的何处开始映射（对于不需要读入整个文件的情况)

//mmap函数成功时返回指向目标内存区域的指针，失败则返回MAP_FAILED((void*) - 1)并设置errno
