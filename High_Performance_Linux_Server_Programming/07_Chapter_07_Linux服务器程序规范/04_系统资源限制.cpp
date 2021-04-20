
#include <sys/resource.h>
int getrlimit( int resource,struct rlimit * rlim );
int setrlimit( int resource,const struct rlimit * rlim );

//rlim参数是rlimit结构体类型的指针,rlimit结构体的定义如下:

struct rlimit
{
	rlim_t rlim_cur;
	rlim_t rlim_max;
};

