

/*
 * Date:2021-05-12 21:24
 * filename:02_shmat&shmdt.cpp
 *
 */

/*
 * 共享内存被创建/获取之后，我们不能立即访问它，而是需要先将它关联到进程的地址空间中
 * 使用完共享内存之后，我们也需要将它从进程地址空间中分离。这两项任务分别由shmat和shmdt实现
 *
 */

#include <sys/shm.h>
void* shmat(int shm_id,const void *  shm_addr,int shmflg);
int shmdt(const void* shm_addr);

/*
 * shm_id参数是由shmget调用返回的共享内存标识符
 * shm_addr参数指定将共享内存关联到进程的哪块地址空间，最终的效果还受到shmflg参数的可选标志SHM_RND的影响
 * 		如果shm_addr为NULL，则被关联的地址由操作系统选择
 * 		如果shm_addr非空，并且设置了SHM_RND标志，则被关联的地址是[shm_addr(shm_addr % SHMLBA)]
 * SHMLBA的含义是"段低端边界地址倍数"(Segment Low Boundary Address Multiple),它必须是内存页面大小(PAGE_SIZE)的整数倍
 * 现在的Linux内核中,它等于一个内存页大小。SHM_RND的含义是圆整(round)，即将共享内存被关联的地址向下圆整到离shm_addr
 * 最低的SHMLBA的整数倍地址处。
 */
