

/*
 * Date:2021-05-12 21:39
 * filename:04_POSIX.cpp
 *
 */

/*
 * 06_Chapter_06_高级IO函数/02_用于读写数据的函数/05_mmap函数和munmap函数.cpp
 *
 * 利用它的MAP_ANONYMOUS标志我们可以实现父、子进程之间的匿名内存共享
 * 通过打开同一个文件,mmap也可以实现无关进程之间的内存共享
 * Linux提供了另外一种利用mmap在无关进程之间共享内存的方式。
 * 这种方式无须任何文件的支持,但它需要先使用如下函数来创建或打开一个POSIX共享内存对象:
 * 
 */

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int shm_open(const char * name,int oflag,mode_t mode);

/*
 * shm_open和open系统调用完全相同
 * name要指定要创建/打开的共享内存对象
 * oflag:
 * 		O_RDONLY
 * 		O_RDWR
 * 		O_CREAT
 * 		O_EXCL
 * 		O_TRUNC
 *
 * shm_open调用成功时返回一个文件描述符。该文件描述符可以用于后续的mmap调用，从而将共享内存关联到调用进程
 * 和打开的文件最后需要关闭一样，由shm_open创建的共享内存对象使用完之后也需要被删除
 */

#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

int shm_unlink(const char *name);

/*
 * 该函数将name参数指定的共享内存对象标记为等待删除对象.当所有使用该共享内存对象的都使用ummap将它从进程中分离之后,
 * 系统将销毁这个共享内存对象所占据的资源
 */
