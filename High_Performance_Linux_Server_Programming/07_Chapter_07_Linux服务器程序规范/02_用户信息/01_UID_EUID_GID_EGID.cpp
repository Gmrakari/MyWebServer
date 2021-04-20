
#include <sys/types.h>
#include <unistd.h>

uid_t getuid(); 			/* 获取真实用户ID */
uid_t geteuid();			/* 获取有效用户ID */

gid_t getgid();				/* 获取真实组ID */
gid_t getegid();			/* 获取有效组ID */

int setuid( uid_t uid );	/* 设置真实用户ID */
int seteuid( uid_t uid );	/* 设置有效用户ID */

int setgid( gid_t gid );	/* 设置真实组ID */
int setegid( gid_t gid );   /* 设置有效组ID */

//一个进程拥有有个用户ID：UID和EUID
//EUID存在的目的是方便资源访问：它使得运行程序的用户拥有该程序的有效用户的权限
//有效用户为root的进程称为特权进程(privileged processes)
//EGID的含义与EUID类似：给运行目标程序的组用户提供有效组的权限
